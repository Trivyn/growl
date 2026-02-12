"""Reference reasoner tests: compare Growl output against Python owlrl.

Runs both reasoners on real ontologies and asserts Growl produces all
named triples that owlrl produces (zero missing). Extra triples in Growl
are logged but not treated as failures.

Filtered out (not comparable across systems):
- Blank node triples (different skolemization)
- Literal-subject triples (eq-ref/dt-type2 produce these in owlrl, but
  they cannot be serialized in Turtle)
- Plain vs xsd:string literal differences (equivalent in RDF 1.1)
- Reflexive owl:sameAs (trivially true, eq-ref tested in conformance suite)
- Datatype owl:disjointWith (owlrl extension, not in OWL 2 RL spec tables)
"""

import os
import subprocess
import tempfile
from collections import defaultdict

import pytest
import rdflib
from rdflib import OWL, XSD
from owlrl import DeductiveClosure, OWLRL_Semantics

GROWL = os.path.join(os.path.dirname(__file__), "../../build/growl")
FIXTURES = os.path.join(os.path.dirname(__file__), "fixtures")


def shorten_uri(uri):
    """Shorten common URIs for display."""
    prefixes = [
        ("http://www.w3.org/1999/02/22-rdf-syntax-ns#", "rdf:"),
        ("http://www.w3.org/2000/01/rdf-schema#", "rdfs:"),
        ("http://www.w3.org/2002/07/owl#", "owl:"),
        ("http://www.w3.org/2001/XMLSchema#", "xsd:"),
    ]
    s = str(uri)
    for full, short in prefixes:
        if s.startswith(full):
            return short + s[len(full):]
    if "#" in s:
        return "..." + s[s.rfind("#"):]
    if "/" in s:
        return "..." + s[s.rfind("/"):]
    return s


def is_comparable(triple):
    """Return True if triple can be meaningfully compared across systems.

    Excludes:
    - Blank node subjects/objects (different skolemization across systems)
    - Literal subjects (owlrl generates these via eq-ref/dt-type2, but they
      cannot be serialized in Turtle)
    - Reflexive owl:sameAs (?x owl:sameAs ?x) — trivially true tautologies,
      eq-ref correctness is tested in the per-rule conformance suite
    - Datatype owl:disjointWith — owlrl adds these as an extension, not
      required by the OWL 2 RL spec tables
    """
    s, p, o = triple
    if isinstance(s, rdflib.BNode) or isinstance(o, rdflib.BNode):
        return False
    if isinstance(s, rdflib.Literal):
        return False
    if p == OWL.sameAs and s == o:
        return False
    if p == OWL.disjointWith and _is_xsd_datatype(s) and _is_xsd_datatype(o):
        return False
    return True


def _is_xsd_datatype(term):
    """Check if term is an XSD datatype URI."""
    return isinstance(term, rdflib.URIRef) and str(term).startswith(str(XSD))


def normalize_literal(term):
    """Normalize a literal for RDF 1.1 comparison.

    In RDF 1.1, plain literals are equivalent to xsd:string typed literals.
    owlrl may add explicit xsd:string types that Growl omits (or vice versa).
    """
    if isinstance(term, rdflib.Literal):
        if term.datatype == XSD.string or term.datatype is None:
            return rdflib.Literal(str(term))
    return term


def normalize_triple(triple):
    """Normalize a triple for cross-system comparison."""
    s, p, o = triple
    return (s, p, normalize_literal(o))


def run_owlrl(path):
    """Run owlrl on a TTL file, return rdflib Graph."""
    g = rdflib.Graph()
    g.parse(path, format="turtle")
    DeductiveClosure(OWLRL_Semantics).expand(g)
    return g


def run_growl(path):
    """Run growl --quiet --complete --emit on a TTL file, return rdflib Graph."""
    with tempfile.NamedTemporaryFile(suffix=".ttl", delete=False) as f:
        emit_path = f.name
    try:
        cmd = [GROWL, "--quiet", "--complete", "--emit", emit_path, path]
        result = subprocess.run(cmd, capture_output=True, text=True, timeout=60)
        assert result.returncode == 0, (
            f"Growl failed (rc={result.returncode})\nstderr: {result.stderr}"
        )
        g = rdflib.Graph()
        g.parse(emit_path, format="turtle")
        return g
    finally:
        if os.path.exists(emit_path):
            os.unlink(emit_path)


def format_missing(missing):
    """Format missing triples grouped by predicate for diagnostic output."""
    by_pred = defaultdict(list)
    for s, p, o in missing:
        by_pred[str(p)].append((s, p, o))

    lines = []
    for pred in sorted(by_pred, key=lambda p: -len(by_pred[p])):
        triples = by_pred[pred]
        lines.append(f"  {shorten_uri(pred):40s} {len(triples):>4d}")
        for s, p, o in triples[:3]:
            lines.append(
                f"    e.g. ({shorten_uri(s)}, {shorten_uri(p)}, {shorten_uri(o)})"
            )
    return "\n".join(lines)


ONTOLOGIES = [
    "bfo-core.ttl",
    "benchmarks/pizza.ttl",
    "equivalent-class.ttl",
    "sameas-chain.ttl",
    "subclass-chain.ttl",
]


@pytest.mark.parametrize("ontology", ONTOLOGIES, ids=[o.split("/")[-1] for o in ONTOLOGIES])
def test_reference_no_missing(ontology):
    """Assert Growl produces all named triples that owlrl produces."""
    path = os.path.join(FIXTURES, ontology)
    assert os.path.exists(path), f"Fixture not found: {path}"

    owlrl_graph = run_owlrl(path)
    growl_graph = run_growl(path)

    owlrl_set = {normalize_triple(t) for t in owlrl_graph if is_comparable(t)}
    growl_set = {normalize_triple(t) for t in growl_graph if is_comparable(t)}

    missing = owlrl_set - growl_set
    extra = growl_set - owlrl_set

    if extra:
        print(f"\n  Extra triples (Growl only): {len(extra)}")

    assert len(missing) == 0, (
        f"{len(missing)} named triples in owlrl but not in Growl:\n"
        f"{format_missing(missing)}"
    )
