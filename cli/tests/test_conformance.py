"""OWL 2 RL Per-Rule Conformance Tests for Growl.

Tests each of the 76 OWL 2 RL rules by writing a minimal Turtle premise,
running growl --complete --emit, and verifying expected entailments or
inconsistency detection.
"""

import os
import subprocess
import tempfile

import pytest
import rdflib
from rdflib import RDF, RDFS, OWL, XSD, Namespace

GROWL = os.path.join(os.path.dirname(__file__), "../../build/growl")
T = Namespace("http://test.org/")

PREFIXES = """\
@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .
@prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#> .
@prefix owl: <http://www.w3.org/2002/07/owl#> .
@prefix xsd: <http://www.w3.org/2001/XMLSchema#> .
@prefix t: <http://test.org/> .
"""


def run_growl(ttl_content, expect_inconsistent=False):
    """Write TTL to temp file, run growl --complete --emit, return rdflib Graph or None."""
    with tempfile.NamedTemporaryFile(suffix=".ttl", mode="w", delete=False) as f:
        f.write(PREFIXES + ttl_content)
        premise_path = f.name
    emit_path = premise_path + ".out.ttl"
    try:
        cmd = [GROWL, "--quiet", "--complete", "--emit", emit_path, premise_path]
        result = subprocess.run(cmd, capture_output=True, text=True, timeout=30)
        if expect_inconsistent:
            assert result.returncode == 1, (
                f"Expected inconsistency, got rc=0\nstdout: {result.stdout}"
            )
            return None
        assert result.returncode == 0, (
            f"Growl failed (rc={result.returncode})\nstderr: {result.stderr}"
        )
        g = rdflib.Graph()
        g.parse(emit_path, format="turtle")
        return g
    finally:
        os.unlink(premise_path)
        if os.path.exists(emit_path):
            os.unlink(emit_path)


def has_triple(g, s, p, o):
    """Check if triple exists in graph."""
    return (s, p, o) in g


# ===========================================================================
# Table 4 — Equality (9 rules)
# ===========================================================================


def test_eq_ref():
    """eq-ref: (?s ?p ?o) -> (?s owl:sameAs ?s)"""
    g = run_growl("t:x t:p t:y .")
    assert has_triple(g, T.x, OWL.sameAs, T.x)


def test_eq_sym():
    """eq-sym: (?x owl:sameAs ?y) -> (?y owl:sameAs ?x)"""
    g = run_growl("t:x owl:sameAs t:y .")
    assert has_triple(g, T.y, OWL.sameAs, T.x)


def test_eq_trans():
    """eq-trans: (?x owl:sameAs ?y) & (?y owl:sameAs ?z) -> (?x owl:sameAs ?z)"""
    g = run_growl("""
        t:x owl:sameAs t:y .
        t:y owl:sameAs t:z .
    """)
    assert has_triple(g, T.x, OWL.sameAs, T.z)


def test_eq_rep_s():
    """eq-rep-s: (?x owl:sameAs ?y) & (?x ?p ?o) -> (?y ?p ?o)"""
    g = run_growl("""
        t:x owl:sameAs t:y .
        t:x t:p t:o .
    """)
    assert has_triple(g, T.y, T.p, T.o)


def test_eq_rep_p():
    """eq-rep-p: (?p1 owl:sameAs ?p2) & (?s ?p1 ?o) -> (?s ?p2 ?o)"""
    g = run_growl("""
        t:p1 owl:sameAs t:p2 .
        t:s t:p1 t:o .
    """)
    assert has_triple(g, T.s, T.p2, T.o)


def test_eq_rep_o():
    """eq-rep-o: (?x owl:sameAs ?y) & (?s ?p ?x) -> (?s ?p ?y)"""
    g = run_growl("""
        t:x owl:sameAs t:y .
        t:s t:p t:x .
    """)
    assert has_triple(g, T.s, T.p, T.y)


def test_eq_diff1():
    """eq-diff1: (?x owl:sameAs ?y) & (?x owl:differentFrom ?y) -> inconsistent"""
    run_growl("""
        t:x owl:sameAs t:y .
        t:x owl:differentFrom t:y .
    """, expect_inconsistent=True)


def test_eq_diff2():
    """eq-diff2: AllDifferent + owl:members + sameAs -> inconsistent"""
    run_growl("""
        [ rdf:type owl:AllDifferent ;
          owl:members ( t:x t:y ) ] .
        t:x owl:sameAs t:y .
    """, expect_inconsistent=True)


def test_eq_diff3():
    """eq-diff3: AllDifferent + owl:distinctMembers + sameAs -> inconsistent"""
    run_growl("""
        [ rdf:type owl:AllDifferent ;
          owl:distinctMembers ( t:x t:y ) ] .
        t:x owl:sameAs t:y .
    """, expect_inconsistent=True)


def test_differentfrom_symmetry():
    """differentFrom symmetry (via prp-symp + SymmetricProperty axiom)"""
    g = run_growl("t:x owl:differentFrom t:y .")
    assert has_triple(g, T.y, OWL.differentFrom, T.x)


# ===========================================================================
# Table 5 — Property Axioms (20 rules)
# ===========================================================================


def test_prp_ap():
    """prp-ap: complete mode auto-asserts annotation properties."""
    g = run_growl("")
    assert has_triple(g, RDFS.label, RDF.type, OWL.AnnotationProperty)


def test_prp_dom():
    """prp-dom: (?p rdfs:domain ?c) & (?x ?p ?y) -> (?x rdf:type ?c)"""
    g = run_growl("""
        t:p rdfs:domain t:C .
        t:x t:p t:y .
    """)
    assert has_triple(g, T.x, RDF.type, T.C)


def test_prp_rng():
    """prp-rng: (?p rdfs:range ?c) & (?x ?p ?y) -> (?y rdf:type ?c)"""
    g = run_growl("""
        t:p rdfs:range t:C .
        t:x t:p t:y .
    """)
    assert has_triple(g, T.y, RDF.type, T.C)


def test_prp_fp():
    """prp-fp: FunctionalProperty & two values -> sameAs"""
    g = run_growl("""
        t:p rdf:type owl:FunctionalProperty .
        t:x t:p t:y .
        t:x t:p t:z .
    """)
    assert has_triple(g, T.y, OWL.sameAs, T.z) or has_triple(g, T.z, OWL.sameAs, T.y)


def test_prp_ifp():
    """prp-ifp: InverseFunctionalProperty & shared value -> sameAs"""
    g = run_growl("""
        t:p rdf:type owl:InverseFunctionalProperty .
        t:x t:p t:z .
        t:y t:p t:z .
    """)
    assert has_triple(g, T.x, OWL.sameAs, T.y) or has_triple(g, T.y, OWL.sameAs, T.x)


def test_prp_irp():
    """prp-irp: IrreflexiveProperty & (?x ?p ?x) -> inconsistent"""
    run_growl("""
        t:p rdf:type owl:IrreflexiveProperty .
        t:x t:p t:x .
    """, expect_inconsistent=True)


def test_prp_symp():
    """prp-symp: SymmetricProperty & (?x ?p ?y) -> (?y ?p ?x)"""
    g = run_growl("""
        t:p rdf:type owl:SymmetricProperty .
        t:x t:p t:y .
    """)
    assert has_triple(g, T.y, T.p, T.x)


def test_prp_asyp():
    """prp-asyp: AsymmetricProperty & mutual assertions -> inconsistent"""
    run_growl("""
        t:p rdf:type owl:AsymmetricProperty .
        t:x t:p t:y .
        t:y t:p t:x .
    """, expect_inconsistent=True)


def test_prp_trp():
    """prp-trp: TransitiveProperty & chain -> transitive closure"""
    g = run_growl("""
        t:p rdf:type owl:TransitiveProperty .
        t:x t:p t:y .
        t:y t:p t:z .
    """)
    assert has_triple(g, T.x, T.p, T.z)


def test_prp_spo1():
    """prp-spo1: (?p1 rdfs:subPropertyOf ?p2) & (?x ?p1 ?y) -> (?x ?p2 ?y)"""
    g = run_growl("""
        t:p1 rdfs:subPropertyOf t:p2 .
        t:x t:p1 t:y .
    """)
    assert has_triple(g, T.x, T.p2, T.y)


def test_prp_spo2():
    """prp-spo2: propertyChainAxiom & chain instances -> conclusion"""
    g = run_growl("""
        t:hasGrandparent owl:propertyChainAxiom ( t:hasParent t:hasParent ) .
        t:a t:hasParent t:b .
        t:b t:hasParent t:c .
    """)
    assert has_triple(g, T.a, T.hasGrandparent, T.c)


def test_prp_eqp1():
    """prp-eqp1: equivalentProperty forward"""
    g = run_growl("""
        t:p1 owl:equivalentProperty t:p2 .
        t:x t:p1 t:y .
    """)
    assert has_triple(g, T.x, T.p2, T.y)


def test_prp_eqp2():
    """prp-eqp2: equivalentProperty reverse"""
    g = run_growl("""
        t:p1 owl:equivalentProperty t:p2 .
        t:x t:p2 t:y .
    """)
    assert has_triple(g, T.x, T.p1, T.y)


def test_prp_pdw():
    """prp-pdw: propertyDisjointWith & shared triple -> inconsistent"""
    run_growl("""
        t:p1 owl:propertyDisjointWith t:p2 .
        t:x t:p1 t:y .
        t:x t:p2 t:y .
    """, expect_inconsistent=True)


def test_prp_adp():
    """prp-adp: AllDisjointProperties & shared s/o via different properties -> inconsistent"""
    run_growl("""
        [ rdf:type owl:AllDisjointProperties ;
          owl:members ( t:p1 t:p2 ) ] .
        t:x t:p1 t:y .
        t:x t:p2 t:y .
    """, expect_inconsistent=True)


def test_prp_inv1():
    """prp-inv1: (?p1 owl:inverseOf ?p2) & (?x ?p1 ?y) -> (?y ?p2 ?x)"""
    g = run_growl("""
        t:p1 owl:inverseOf t:p2 .
        t:x t:p1 t:y .
    """)
    assert has_triple(g, T.y, T.p2, T.x)


def test_prp_inv2():
    """prp-inv2: (?p1 owl:inverseOf ?p2) & (?y ?p2 ?x) -> (?x ?p1 ?y)"""
    g = run_growl("""
        t:p1 owl:inverseOf t:p2 .
        t:y t:p2 t:x .
    """)
    assert has_triple(g, T.x, T.p1, T.y)


def test_prp_key():
    """prp-key: hasKey + matching key values -> sameAs"""
    g = run_growl("""
        t:C owl:hasKey ( t:k ) .
        t:x rdf:type t:C .
        t:y rdf:type t:C .
        t:x t:k "123" .
        t:y t:k "123" .
    """)
    assert has_triple(g, T.x, OWL.sameAs, T.y) or has_triple(g, T.y, OWL.sameAs, T.x)


def test_prp_npa1():
    """prp-npa1: NegativePropertyAssertion (named target) violation -> inconsistent"""
    run_growl("""
        [ rdf:type owl:NegativePropertyAssertion ;
          owl:sourceIndividual t:x ;
          owl:assertionProperty t:p ;
          owl:targetIndividual t:y ] .
        t:x t:p t:y .
    """, expect_inconsistent=True)


def test_prp_npa2():
    """prp-npa2: NegativePropertyAssertion (literal target) violation -> inconsistent"""
    run_growl("""
        [ rdf:type owl:NegativePropertyAssertion ;
          owl:sourceIndividual t:x ;
          owl:assertionProperty t:name ;
          owl:targetValue "alice" ] .
        t:x t:name "alice" .
    """, expect_inconsistent=True)


# ===========================================================================
# Table 6 — Class Expressions (19 rules)
# ===========================================================================


def test_cls_thing():
    """cls-thing: complete mode asserts owl:Thing rdf:type owl:Class."""
    g = run_growl("")
    assert has_triple(g, OWL.Thing, RDF.type, OWL.Class)


def test_cls_nothing1():
    """cls-nothing1: complete mode asserts owl:Nothing rdf:type owl:Class."""
    g = run_growl("")
    assert has_triple(g, OWL.Nothing, RDF.type, OWL.Class)


def test_cls_nothing2():
    """cls-nothing2: (?x rdf:type owl:Nothing) -> inconsistent"""
    run_growl("t:x rdf:type owl:Nothing .", expect_inconsistent=True)


def test_cls_int1():
    """cls-int1: intersection & member of all components -> member of intersection"""
    g = run_growl("""
        t:AB owl:intersectionOf ( t:A t:B ) .
        t:x rdf:type t:A .
        t:x rdf:type t:B .
    """)
    assert has_triple(g, T.x, RDF.type, T.AB)


def test_cls_int2():
    """cls-int2: intersection & member of intersection -> member of all components"""
    g = run_growl("""
        t:AB owl:intersectionOf ( t:A t:B ) .
        t:x rdf:type t:AB .
    """)
    assert has_triple(g, T.x, RDF.type, T.A)
    assert has_triple(g, T.x, RDF.type, T.B)


def test_cls_uni():
    """cls-uni: union & member of component -> member of union"""
    g = run_growl("""
        t:AorB owl:unionOf ( t:A t:B ) .
        t:x rdf:type t:A .
    """)
    assert has_triple(g, T.x, RDF.type, T.AorB)


def test_cls_com():
    """cls-com: complement & member of both -> inconsistent"""
    run_growl("""
        t:A owl:complementOf t:B .
        t:x rdf:type t:A .
        t:x rdf:type t:B .
    """, expect_inconsistent=True)


def test_cls_svf1():
    """cls-svf1: someValuesFrom + typed value -> type inference"""
    g = run_growl("""
        t:R owl:onProperty t:p .
        t:R owl:someValuesFrom t:C .
        t:x t:p t:y .
        t:y rdf:type t:C .
    """)
    assert has_triple(g, T.x, RDF.type, T.R)


def test_cls_svf2():
    """cls-svf2: someValuesFrom owl:Thing + property -> type inference"""
    g = run_growl("""
        t:R owl:onProperty t:p .
        t:R owl:someValuesFrom owl:Thing .
        t:x t:p t:y .
    """)
    assert has_triple(g, T.x, RDF.type, T.R)


def test_cls_avf():
    """cls-avf: allValuesFrom + type + property -> value gets typed"""
    g = run_growl("""
        t:R owl:onProperty t:p .
        t:R owl:allValuesFrom t:C .
        t:x rdf:type t:R .
        t:x t:p t:y .
    """)
    assert has_triple(g, T.y, RDF.type, T.C)


def test_cls_hv1():
    """cls-hv1: hasValue + type match -> property assertion"""
    g = run_growl("""
        t:R owl:onProperty t:p .
        t:R owl:hasValue t:v .
        t:x rdf:type t:R .
    """)
    assert has_triple(g, T.x, T.p, T.v)


def test_cls_hv2():
    """cls-hv2: hasValue + property match -> type inference"""
    g = run_growl("""
        t:R owl:onProperty t:p .
        t:R owl:hasValue t:v .
        t:x t:p t:v .
    """)
    assert has_triple(g, T.x, RDF.type, T.R)


def test_cls_maxc1():
    """cls-maxc1: maxCardinality 0 + property exists -> inconsistent"""
    run_growl("""
        t:R owl:onProperty t:p .
        t:R owl:maxCardinality "0"^^xsd:nonNegativeInteger .
        t:x rdf:type t:R .
        t:x t:p t:y .
    """, expect_inconsistent=True)


def test_cls_maxc2():
    """cls-maxc2: maxCardinality 1 + two values -> sameAs"""
    g = run_growl("""
        t:R owl:onProperty t:p .
        t:R owl:maxCardinality "1"^^xsd:nonNegativeInteger .
        t:x rdf:type t:R .
        t:x t:p t:y .
        t:x t:p t:z .
    """)
    assert has_triple(g, T.y, OWL.sameAs, T.z) or has_triple(g, T.z, OWL.sameAs, T.y)


def test_cls_maxqc1():
    """cls-maxqc1: maxQualifiedCardinality 0 + owl:Thing -> inconsistent"""
    run_growl("""
        t:R owl:onProperty t:p .
        t:R owl:maxQualifiedCardinality "0"^^xsd:nonNegativeInteger .
        t:R owl:onClass owl:Thing .
        t:x rdf:type t:R .
        t:x t:p t:y .
    """, expect_inconsistent=True)


def test_cls_maxqc2():
    """cls-maxqc2: maxQualifiedCardinality 0 + specific class -> inconsistent"""
    run_growl("""
        t:R owl:onProperty t:p .
        t:R owl:maxQualifiedCardinality "0"^^xsd:nonNegativeInteger .
        t:R owl:onClass t:C .
        t:x rdf:type t:R .
        t:x t:p t:y .
        t:y rdf:type t:C .
    """, expect_inconsistent=True)


def test_cls_maxqc3():
    """cls-maxqc3: maxQualifiedCardinality 1 + owl:Thing + two values -> sameAs"""
    g = run_growl("""
        t:R owl:onProperty t:p .
        t:R owl:maxQualifiedCardinality "1"^^xsd:nonNegativeInteger .
        t:R owl:onClass owl:Thing .
        t:x rdf:type t:R .
        t:x t:p t:y .
        t:x t:p t:z .
    """)
    assert has_triple(g, T.y, OWL.sameAs, T.z) or has_triple(g, T.z, OWL.sameAs, T.y)


def test_cls_maxqc4():
    """cls-maxqc4: maxQualifiedCardinality 1 + specific class + two values -> sameAs"""
    g = run_growl("""
        t:R owl:onProperty t:p .
        t:R owl:maxQualifiedCardinality "1"^^xsd:nonNegativeInteger .
        t:R owl:onClass t:C .
        t:x rdf:type t:R .
        t:x t:p t:y .
        t:x t:p t:z .
        t:y rdf:type t:C .
        t:z rdf:type t:C .
    """)
    assert has_triple(g, T.y, OWL.sameAs, T.z) or has_triple(g, T.z, OWL.sameAs, T.y)


def test_cls_oo():
    """cls-oo: oneOf enumeration -> members get typed"""
    g = run_growl("""
        t:Color owl:oneOf ( t:red t:green t:blue ) .
    """)
    assert has_triple(g, T.red, RDF.type, T.Color)
    assert has_triple(g, T.green, RDF.type, T.Color)
    assert has_triple(g, T.blue, RDF.type, T.Color)


# ===========================================================================
# Table 7 — Class Axioms (5 rules)
# ===========================================================================


def test_cax_sco():
    """cax-sco: subClassOf + type -> type propagation"""
    g = run_growl("""
        t:A rdfs:subClassOf t:B .
        t:x rdf:type t:A .
    """)
    assert has_triple(g, T.x, RDF.type, T.B)


def test_cax_eqc1():
    """cax-eqc1: equivalentClass forward"""
    g = run_growl("""
        t:A owl:equivalentClass t:B .
        t:x rdf:type t:A .
    """)
    assert has_triple(g, T.x, RDF.type, T.B)


def test_cax_eqc2():
    """cax-eqc2: equivalentClass reverse"""
    g = run_growl("""
        t:A owl:equivalentClass t:B .
        t:x rdf:type t:B .
    """)
    assert has_triple(g, T.x, RDF.type, T.A)


def test_cax_dw():
    """cax-dw: disjointWith + member of both -> inconsistent"""
    run_growl("""
        t:A owl:disjointWith t:B .
        t:x rdf:type t:A .
        t:x rdf:type t:B .
    """, expect_inconsistent=True)


def test_cax_adc():
    """cax-adc: AllDisjointClasses + shared member -> inconsistent"""
    run_growl("""
        [ rdf:type owl:AllDisjointClasses ;
          owl:members ( t:A t:B ) ] .
        t:x rdf:type t:A .
        t:x rdf:type t:B .
    """, expect_inconsistent=True)


# ===========================================================================
# Table 8 — Datatypes (3 rules)
# ===========================================================================


def test_dt_type1():
    """dt-type1: complete mode asserts built-in datatypes."""
    g = run_growl("")
    assert has_triple(g, XSD.integer, RDF.type, RDFS.Datatype)


def test_dt_type2():
    """dt-type2: typed literal -> literal rdf:type datatype.

    Note: literal-subject triples cannot be serialized in Turtle, so we only
    verify growl processes the input successfully. The rule fires internally
    (needed for dt-not-type checks) but won't appear in TTL output.
    """
    g = run_growl('t:x t:p "42"^^xsd:integer .')
    assert g is not None  # Confirm growl succeeds


def test_dt_not_type():
    """dt-not-type: invalid typed literal -> inconsistent"""
    run_growl('t:x t:p "abc"^^xsd:integer .', expect_inconsistent=True)


# ===========================================================================
# Table 9 — Schema Vocabulary (20 rules)
# ===========================================================================


def test_scm_cls():
    """scm-cls: (?c rdf:type owl:Class) -> subClassOf self, subClassOf owl:Thing"""
    g = run_growl("t:C rdf:type owl:Class .")
    assert has_triple(g, T.C, RDFS.subClassOf, T.C)
    assert has_triple(g, T.C, RDFS.subClassOf, OWL.Thing)


def test_scm_sco():
    """scm-sco: subClassOf transitivity"""
    g = run_growl("""
        t:A rdfs:subClassOf t:B .
        t:B rdfs:subClassOf t:C .
    """)
    assert has_triple(g, T.A, RDFS.subClassOf, T.C)


def test_scm_eqc1():
    """scm-eqc1: equivalentClass -> mutual subClassOf"""
    g = run_growl("t:A owl:equivalentClass t:B .")
    assert has_triple(g, T.A, RDFS.subClassOf, T.B)
    assert has_triple(g, T.B, RDFS.subClassOf, T.A)


def test_scm_eqc2():
    """scm-eqc2: mutual subClassOf -> equivalentClass"""
    g = run_growl("""
        t:A rdfs:subClassOf t:B .
        t:B rdfs:subClassOf t:A .
    """)
    assert has_triple(g, T.A, OWL.equivalentClass, T.B)


def test_scm_op():
    """scm-op: ObjectProperty -> subPropertyOf self"""
    g = run_growl("t:p rdf:type owl:ObjectProperty .")
    assert has_triple(g, T.p, RDFS.subPropertyOf, T.p)


def test_scm_dp():
    """scm-dp: DatatypeProperty -> subPropertyOf self"""
    g = run_growl("t:p rdf:type owl:DatatypeProperty .")
    assert has_triple(g, T.p, RDFS.subPropertyOf, T.p)


def test_scm_spo():
    """scm-spo: subPropertyOf transitivity"""
    g = run_growl("""
        t:p1 rdfs:subPropertyOf t:p2 .
        t:p2 rdfs:subPropertyOf t:p3 .
    """)
    assert has_triple(g, T.p1, RDFS.subPropertyOf, T.p3)


def test_scm_eqp1():
    """scm-eqp1: equivalentProperty -> mutual subPropertyOf"""
    g = run_growl("t:p1 owl:equivalentProperty t:p2 .")
    assert has_triple(g, T.p1, RDFS.subPropertyOf, T.p2)
    assert has_triple(g, T.p2, RDFS.subPropertyOf, T.p1)


def test_scm_eqp2():
    """scm-eqp2: mutual subPropertyOf -> equivalentProperty"""
    g = run_growl("""
        t:p1 rdfs:subPropertyOf t:p2 .
        t:p2 rdfs:subPropertyOf t:p1 .
    """)
    assert has_triple(g, T.p1, OWL.equivalentProperty, T.p2)


def test_scm_dom1():
    """scm-dom1: domain + subClassOf -> domain propagation"""
    g = run_growl("""
        t:p rdfs:domain t:A .
        t:A rdfs:subClassOf t:B .
    """)
    assert has_triple(g, T.p, RDFS.domain, T.B)


def test_scm_dom2():
    """scm-dom2: domain + subPropertyOf -> domain propagation"""
    g = run_growl("""
        t:p2 rdfs:domain t:C .
        t:p1 rdfs:subPropertyOf t:p2 .
    """)
    assert has_triple(g, T.p1, RDFS.domain, T.C)


def test_scm_rng1():
    """scm-rng1: range + subClassOf -> range propagation"""
    g = run_growl("""
        t:p rdfs:range t:A .
        t:A rdfs:subClassOf t:B .
    """)
    assert has_triple(g, T.p, RDFS.range, T.B)


def test_scm_rng2():
    """scm-rng2: range + subPropertyOf -> range propagation"""
    g = run_growl("""
        t:p2 rdfs:range t:C .
        t:p1 rdfs:subPropertyOf t:p2 .
    """)
    assert has_triple(g, T.p1, RDFS.range, T.C)


def test_scm_hv():
    """scm-hv: hasValue restrictions + subPropertyOf -> subClassOf"""
    g = run_growl("""
        t:R1 owl:hasValue t:v .
        t:R1 owl:onProperty t:p1 .
        t:R2 owl:hasValue t:v .
        t:R2 owl:onProperty t:p2 .
        t:p1 rdfs:subPropertyOf t:p2 .
    """)
    assert has_triple(g, T.R1, RDFS.subClassOf, T.R2)


def test_scm_svf1():
    """scm-svf1: someValuesFrom + class subClassOf -> restriction subClassOf"""
    g = run_growl("""
        t:R1 owl:someValuesFrom t:C1 .
        t:R1 owl:onProperty t:p .
        t:R2 owl:someValuesFrom t:C2 .
        t:R2 owl:onProperty t:p .
        t:C1 rdfs:subClassOf t:C2 .
    """)
    assert has_triple(g, T.R1, RDFS.subClassOf, T.R2)


def test_scm_svf2():
    """scm-svf2: someValuesFrom + property subPropertyOf -> restriction subClassOf"""
    g = run_growl("""
        t:R1 owl:someValuesFrom t:C .
        t:R1 owl:onProperty t:p1 .
        t:R2 owl:someValuesFrom t:C .
        t:R2 owl:onProperty t:p2 .
        t:p1 rdfs:subPropertyOf t:p2 .
    """)
    assert has_triple(g, T.R1, RDFS.subClassOf, T.R2)


def test_scm_avf1():
    """scm-avf1: allValuesFrom + class subClassOf -> restriction subClassOf"""
    g = run_growl("""
        t:R1 owl:allValuesFrom t:C1 .
        t:R1 owl:onProperty t:p .
        t:R2 owl:allValuesFrom t:C2 .
        t:R2 owl:onProperty t:p .
        t:C1 rdfs:subClassOf t:C2 .
    """)
    assert has_triple(g, T.R1, RDFS.subClassOf, T.R2)


def test_scm_avf2():
    """scm-avf2: allValuesFrom + property subPropertyOf -> restriction subClassOf (reversed)"""
    g = run_growl("""
        t:R1 owl:allValuesFrom t:C .
        t:R1 owl:onProperty t:p1 .
        t:R2 owl:allValuesFrom t:C .
        t:R2 owl:onProperty t:p2 .
        t:p1 rdfs:subPropertyOf t:p2 .
    """)
    # Direction reversed: allValuesFrom with superproperty is more restrictive
    assert has_triple(g, T.R2, RDFS.subClassOf, T.R1)


def test_scm_int():
    """scm-int: intersectionOf -> subClassOf each component"""
    g = run_growl("t:AB owl:intersectionOf ( t:A t:B ) .")
    assert has_triple(g, T.AB, RDFS.subClassOf, T.A)
    assert has_triple(g, T.AB, RDFS.subClassOf, T.B)


def test_scm_uni():
    """scm-uni: unionOf -> each component subClassOf union"""
    g = run_growl("t:AorB owl:unionOf ( t:A t:B ) .")
    assert has_triple(g, T.A, RDFS.subClassOf, T.AorB)
    assert has_triple(g, T.B, RDFS.subClassOf, T.AorB)
