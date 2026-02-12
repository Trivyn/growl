"""Multi-Rule Interaction Tests for Growl.

Tests that verify the fixpoint engine works correctly when multiple OWL 2 RL
rules interact across iterations — where rule A's output in iteration N becomes
rule B's input in iteration N+1.
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
# Category A: Type Inference Cascades
# ===========================================================================


def test_chain_prp_dom_cls_svf1():
    """prp-dom -> cls-svf1: domain infers type, someValuesFrom consumes it (2 iters)."""
    g = run_growl("""
        t:hasPet rdfs:domain t:PetOwner .
        t:KnowsPetOwner owl:someValuesFrom t:PetOwner .
        t:KnowsPetOwner owl:onProperty t:knows .
        t:alice t:hasPet t:fido .
        t:bob t:knows t:alice .
    """)
    assert has_triple(g, T.bob, RDF.type, T.KnowsPetOwner)


def test_chain_cls_svf1_cax_sco_cls_avf():
    """cls-svf1 -> cax-sco -> cls-avf: longest type-inference chain (3 iters)."""
    g = run_growl("""
        t:DogRestr owl:someValuesFrom t:Dog .
        t:DogRestr owl:onProperty t:owns .
        t:DogRestr rdfs:subClassOf t:AnimalOwner .
        t:AnimalOwner owl:allValuesFrom t:WellCared .
        t:AnimalOwner owl:onProperty t:owns .
        t:alice t:owns t:fido .
        t:fido rdf:type t:Dog .
    """)
    assert has_triple(g, T.fido, RDF.type, T.WellCared)


def test_chain_cls_hv1_cax_sco():
    """cls-hv1 -> cax-sco: hasValue match -> class hierarchy (2 iters)."""
    g = run_growl("""
        t:HasCarRestr owl:onProperty t:owns .
        t:HasCarRestr owl:hasValue t:myCar .
        t:HasCarRestr rdfs:subClassOf t:VehicleOwner .
        t:alice t:owns t:myCar .
    """)
    assert has_triple(g, T.alice, RDF.type, T.VehicleOwner)


def test_chain_cls_int1_cax_sco():
    """cls-int1 -> cax-sco: intersection membership -> class hierarchy (2 iters)."""
    g = run_growl("""
        t:WorkingParent owl:intersectionOf ( t:Worker t:Parent ) .
        t:WorkingParent rdfs:subClassOf t:BusyPerson .
        t:alice rdf:type t:Worker .
        t:alice rdf:type t:Parent .
    """)
    assert has_triple(g, T.alice, RDF.type, T.BusyPerson)


# ===========================================================================
# Category B: Equality-Driven Cascades
# ===========================================================================


def test_chain_prp_fp_eq_rep_o():
    """prp-fp -> eq-rep-o: functional property -> sameAs -> object replacement (2 iters)."""
    g = run_growl("""
        t:mother rdf:type owl:FunctionalProperty .
        t:alice t:mother t:mary .
        t:alice t:mother t:maria .
        t:bob t:likes t:mary .
    """)
    assert has_triple(g, T.bob, T.likes, T.mary)
    assert has_triple(g, T.bob, T.likes, T.maria)


def test_chain_prp_ifp_eq_rep_s():
    """prp-ifp -> eq-rep-s: inverse functional -> sameAs -> subject replacement (2 iters)."""
    g = run_growl("""
        t:ssn rdf:type owl:InverseFunctionalProperty .
        t:john t:ssn t:id123 .
        t:jane t:ssn t:id123 .
        t:john t:worksAt t:acme .
    """)
    assert has_triple(g, T.jane, T.worksAt, T.acme)


def test_chain_prp_key_eq_rep_s():
    """prp-key -> eq-rep-s: key constraint -> sameAs -> subject replacement (2 iters)."""
    g = run_growl("""
        t:Person owl:hasKey ( t:id ) .
        t:john rdf:type t:Person .
        t:jane rdf:type t:Person .
        t:john t:id t:id123 .
        t:jane t:id t:id123 .
        t:john t:worksAt t:acme .
    """)
    assert has_triple(g, T.jane, T.worksAt, T.acme)


def test_chain_cls_maxc2_eq_rep_o():
    """cls-maxc2 -> eq-rep-o: maxCardinality 1 -> sameAs -> object replacement (2 iters)."""
    g = run_growl("""
        t:R owl:onProperty t:p .
        t:R owl:maxCardinality "1"^^xsd:nonNegativeInteger .
        t:x rdf:type t:R .
        t:x t:p t:y .
        t:x t:p t:z .
        t:w t:q t:y .
    """)
    assert has_triple(g, T.w, T.q, T.z)


# ===========================================================================
# Category C: Property Structure Cascades
# ===========================================================================


def test_chain_prp_spo2_prp_dom():
    """prp-spo2 -> prp-dom: property chain -> domain inference (2 iters)."""
    g = run_growl("""
        t:hasGrandparent owl:propertyChainAxiom ( t:hasParent t:hasParent ) .
        t:hasGrandparent rdfs:domain t:GrandchildPerson .
        t:alice t:hasParent t:bob .
        t:bob t:hasParent t:charlie .
    """)
    assert has_triple(g, T.alice, RDF.type, T.GrandchildPerson)


def test_chain_prp_inv1_prp_fp_eq_rep_s():
    """prp-inv1 -> prp-fp -> eq-rep-s: inverse -> functional -> replacement (3 iters)."""
    g = run_growl("""
        t:parentOf owl:inverseOf t:childOf .
        t:childOf rdf:type owl:FunctionalProperty .
        t:alice t:parentOf t:carol .
        t:bob t:parentOf t:carol .
        t:alice t:worksAt t:acme .
    """)
    assert has_triple(g, T.bob, T.worksAt, T.acme)


def test_chain_prp_trp_3hop():
    """prp-trp 3-hop: transitive property needs 2 iterations for full closure."""
    g = run_growl("""
        t:ancestor rdf:type owl:TransitiveProperty .
        t:a t:ancestor t:b .
        t:b t:ancestor t:c .
        t:c t:ancestor t:d .
    """)
    assert has_triple(g, T.a, T.ancestor, T.d)


# ===========================================================================
# Category D: Delayed Inconsistency Detection
# ===========================================================================


def test_chain_prp_fp_eq_diff_inconsistent():
    """prp-fp -> eq-diff1: functional property -> sameAs contradicts differentFrom (2 iters)."""
    run_growl("""
        t:mother rdf:type owl:FunctionalProperty .
        t:alice t:mother t:mary .
        t:alice t:mother t:maria .
        t:mary owl:differentFrom t:maria .
    """, expect_inconsistent=True)


def test_chain_cax_sco_cls_com_inconsistent():
    """cax-sco -> cls-com: type propagation creates complement contradiction (2 iters)."""
    run_growl("""
        t:A owl:complementOf t:B .
        t:C rdfs:subClassOf t:A .
        t:C rdfs:subClassOf t:B .
        t:x rdf:type t:C .
    """, expect_inconsistent=True)


# ===========================================================================
# Category E: Complex Multi-Phase
# ===========================================================================


def test_chain_prp_symp_prp_fp_eq_rep_s():
    """prp-symp -> prp-fp -> eq-rep-s: symmetric -> functional -> replacement (3 iters)."""
    g = run_growl("""
        t:spouse rdf:type owl:SymmetricProperty .
        t:spouse rdf:type owl:FunctionalProperty .
        t:alice t:spouse t:bob .
        t:carol t:spouse t:bob .
        t:alice t:worksAt t:acme .
    """)
    assert has_triple(g, T.carol, T.worksAt, T.acme)


def test_chain_prp_spo2_prp_dom_cls_svf1_cax_sco():
    """prp-spo2 -> prp-dom -> cls-svf1 -> cax-sco: full 4-iteration pipeline."""
    g = run_growl("""
        t:hasUncle owl:propertyChainAxiom ( t:hasParent t:hasBrother ) .
        t:hasUncle rdfs:domain t:PersonWithUncle .
        t:KnowsNephew owl:someValuesFrom t:PersonWithUncle .
        t:KnowsNephew owl:onProperty t:knows .
        t:KnowsNephew rdfs:subClassOf t:FamilyAware .
        t:alice t:hasParent t:bob .
        t:bob t:hasBrother t:charlie .
        t:dave t:knows t:alice .
    """)
    assert has_triple(g, T.dave, RDF.type, T.FamilyAware)
