use growl::{Arena, IndexedGraph, ReasonerConfig, ReasonerResult, Term, Triple};
use growl::{get_types, is_consistent, reason, reason_with_config, validate, validate_with_ns, filter_annotations};
use growl::{OwnedReasonerResult, OwnedTerm, Reasoner, STANDARD_ANNOTATION_PROPERTIES};
use growl::{ValidateResult, OwnedValidateResult};

const OWL: &str = "http://www.w3.org/2002/07/owl#";
const RDF: &str = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";
const RDFS: &str = "http://www.w3.org/2000/01/rdf-schema#";
const EX: &str = "http://example.org/";

fn rdf_type(arena: &Arena) -> growl::ffi::RdfTerm {
    arena.make_iri(&format!("{}type", RDF))
}

fn rdfs_subclass(arena: &Arena) -> growl::ffi::RdfTerm {
    arena.make_iri(&format!("{}subClassOf", RDFS))
}

fn owl_class(arena: &Arena) -> growl::ffi::RdfTerm {
    arena.make_iri(&format!("{}Class", OWL))
}

#[test]
fn empty_graph() {
    let arena = Arena::new(1024 * 1024);
    let graph = IndexedGraph::new(&arena);
    assert_eq!(graph.size(), 0);
    assert!(is_consistent(&arena, &graph));
}

#[test]
fn add_and_query() {

    let arena = Arena::new(1024 * 1024);
    let mut graph = IndexedGraph::new(&arena);

    let s = arena.make_iri(&format!("{}fido", EX));
    let p = rdf_type(&arena);
    let o = arena.make_iri(&format!("{}Dog", EX));

    let triple = arena.make_triple(s, p, o);
    graph.add_triple(triple);

    assert_eq!(graph.size(), 1);
    assert!(graph.contains_triple(triple));
}

#[test]
fn subclass_inference() {

    let arena = Arena::new(4 * 1024 * 1024);
    let mut graph = IndexedGraph::new(&arena);

    let dog = arena.make_iri(&format!("{}Dog", EX));
    let animal = arena.make_iri(&format!("{}Animal", EX));
    let fido = arena.make_iri(&format!("{}fido", EX));
    let a = rdf_type(&arena);
    let sub = rdfs_subclass(&arena);
    let cls = owl_class(&arena);

    // Dog subClassOf Animal
    graph.add_triple(arena.make_triple(dog, sub, animal));
    // fido a Dog
    graph.add_triple(arena.make_triple(fido, a, dog));
    // Declare classes
    graph.add_triple(arena.make_triple(dog, a, cls));
    graph.add_triple(arena.make_triple(animal, a, cls));

    let result = reason(&arena, &graph);
    match result {
        ReasonerResult::Success {
            graph: result_graph,
            inferred_count,
            ..
        } => {
            assert!(inferred_count > 0, "should infer at least one triple");

            // fido should now be typed Animal
            let types = get_types(&arena, &result_graph, fido);
            let has_animal = types.iter().any(|t| {
                matches!(t, Term::Iri(v) if *v == format!("{}Animal", EX))
            });
            assert!(has_animal, "fido should be inferred as Animal, got: {:?}", types);
        }
        ReasonerResult::Inconsistent { reports } => {
            panic!("expected consistent result, got inconsistency: {}", reports[0].reason);
        }
    }
}

#[test]
fn reason_with_custom_config() {

    let arena = Arena::new(4 * 1024 * 1024);
    let mut graph = IndexedGraph::new(&arena);

    let dog = arena.make_iri(&format!("{}Dog", EX));
    let fido = arena.make_iri(&format!("{}fido", EX));
    let a = rdf_type(&arena);
    let cls = owl_class(&arena);

    graph.add_triple(arena.make_triple(fido, a, dog));
    graph.add_triple(arena.make_triple(dog, a, cls));

    let config = ReasonerConfig::new().verbose(false).fast(true);
    let result = reason_with_config(&arena, &graph, &config);
    match result {
        ReasonerResult::Success { .. } => {}
        ReasonerResult::Inconsistent { reports } => {
            panic!("expected consistent result: {}", reports[0].reason);
        }
    }
}

#[test]
fn inconsistency_detection() {

    let arena = Arena::new(4 * 1024 * 1024);
    let mut graph = IndexedGraph::new(&arena);

    // Match the known-working disjoint-violation.ttl fixture:
    // Cat disjointWith Dog, fido typed as both → inconsistent
    let cat = arena.make_iri(&format!("{}Cat", EX));
    let dog = arena.make_iri(&format!("{}Dog", EX));
    let fido = arena.make_iri(&format!("{}fido", EX));
    let a = rdf_type(&arena);
    let disjoint = arena.make_iri(&format!("{}disjointWith", OWL));

    graph.add_triple(arena.make_triple(cat, disjoint, dog));
    graph.add_triple(arena.make_triple(fido, a, cat));
    graph.add_triple(arena.make_triple(fido, a, dog));

    let result = reason(&arena, &graph);
    match result {
        ReasonerResult::Inconsistent { .. } => {
            // Expected
        }
        ReasonerResult::Success { .. } => {
            panic!("expected inconsistency for disjoint class violation");
        }
    }
}

#[test]
fn match_pattern() {

    let arena = Arena::new(1024 * 1024);
    let mut graph = IndexedGraph::new(&arena);

    let fido = arena.make_iri(&format!("{}fido", EX));
    let rex = arena.make_iri(&format!("{}rex", EX));
    let dog = arena.make_iri(&format!("{}Dog", EX));
    let a = rdf_type(&arena);

    graph.add_triple(arena.make_triple(fido, a, dog));
    graph.add_triple(arena.make_triple(rex, a, dog));

    // Match all triples with predicate rdf:type and object Dog
    let matches = graph.match_pattern(None, Some(a), Some(dog));
    assert_eq!(matches.len(), 2);
}

#[test]
fn graph_objects_and_subjects() {

    let arena = Arena::new(1024 * 1024);
    let mut graph = IndexedGraph::new(&arena);

    let fido = arena.make_iri(&format!("{}fido", EX));
    let rex = arena.make_iri(&format!("{}rex", EX));
    let dog = arena.make_iri(&format!("{}Dog", EX));
    let cat = arena.make_iri(&format!("{}Cat", EX));
    let a = rdf_type(&arena);

    graph.add_triple(arena.make_triple(fido, a, dog));
    graph.add_triple(arena.make_triple(fido, a, cat));
    graph.add_triple(arena.make_triple(rex, a, dog));

    // Objects of fido rdf:type ?
    let objs = graph.objects(fido, a);
    assert_eq!(objs.len(), 2);

    // Subjects of ? rdf:type Dog
    let subjs = graph.subjects(a, dog);
    assert_eq!(subjs.len(), 2);
}

#[test]
fn literal_terms() {

    let arena = Arena::new(1024 * 1024);
    let mut graph = IndexedGraph::new(&arena);

    let fido = arena.make_iri(&format!("{}fido", EX));
    let name = arena.make_iri(&format!("{}name", EX));
    let val = arena.make_literal("Fido", None, Some("en"));
    let triple = arena.make_triple(fido, name, val);
    graph.add_triple(triple);

    assert_eq!(graph.size(), 1);

    let t = Triple::from_ffi(triple);
    assert_eq!(
        t.object,
        Term::Literal {
            value: "Fido",
            datatype: None,
            lang: Some("en"),
        }
    );
}

#[test]
fn blank_node_terms() {

    let arena = Arena::new(1024 * 1024);
    let mut graph = IndexedGraph::new(&arena);

    let b = arena.make_blank(42);
    let a = rdf_type(&arena);
    let dog = arena.make_iri(&format!("{}Dog", EX));

    graph.add_triple(arena.make_triple(b, a, dog));
    assert_eq!(graph.size(), 1);

    let t = Term::from_ffi(b);
    assert_eq!(t, Term::Blank(42));
}

// ---------------------------------------------------------------------------
// Reasoner high-level API tests
// ---------------------------------------------------------------------------

#[test]
fn reasoner_subclass_inference() {

    let mut reasoner = Reasoner::with_capacity(4 * 1024 * 1024);

    let rdf_type_iri = format!("{}type", RDF);
    let rdfs_sub_iri = format!("{}subClassOf", RDFS);
    let owl_class_iri = format!("{}Class", OWL);
    let dog_iri = format!("{}Dog", EX);
    let animal_iri = format!("{}Animal", EX);
    let fido_iri = format!("{}fido", EX);

    // Dog subClassOf Animal
    reasoner.add_iri_triple(&dog_iri, &rdfs_sub_iri, &animal_iri);
    // fido a Dog
    reasoner.add_iri_triple(&fido_iri, &rdf_type_iri, &dog_iri);
    // Declare classes
    reasoner.add_iri_triple(&dog_iri, &rdf_type_iri, &owl_class_iri);
    reasoner.add_iri_triple(&animal_iri, &rdf_type_iri, &owl_class_iri);

    assert_eq!(reasoner.triple_count(), 4);

    match reasoner.reason() {
        OwnedReasonerResult::Success {
            triples,
            inferred_count,
            ..
        } => {
            assert!(inferred_count > 0, "should infer at least one triple");

            // fido should now be typed Animal in the result triples
            let has_animal = triples.iter().any(|t| {
                t.subject == OwnedTerm::Iri(fido_iri.clone())
                    && t.predicate == OwnedTerm::Iri(rdf_type_iri.clone())
                    && t.object == OwnedTerm::Iri(animal_iri.clone())
            });
            assert!(
                has_animal,
                "fido should be inferred as Animal in result triples"
            );
        }
        OwnedReasonerResult::Inconsistent { reports } => {
            panic!("expected consistent result, got inconsistency: {}", reports[0].reason);
        }
    }
}

#[test]
fn reasoner_inconsistency() {

    let mut reasoner = Reasoner::with_capacity(4 * 1024 * 1024);

    let rdf_type_iri = format!("{}type", RDF);
    let disjoint_iri = format!("{}disjointWith", OWL);
    let cat_iri = format!("{}Cat", EX);
    let dog_iri = format!("{}Dog", EX);
    let fido_iri = format!("{}fido", EX);

    reasoner.add_iri_triple(&cat_iri, &disjoint_iri, &dog_iri);
    reasoner.add_iri_triple(&fido_iri, &rdf_type_iri, &cat_iri);
    reasoner.add_iri_triple(&fido_iri, &rdf_type_iri, &dog_iri);

    match reasoner.reason() {
        OwnedReasonerResult::Inconsistent { reports } => {
            assert!(!reports[0].reason.is_empty(), "inconsistency reason should not be empty");
        }
        OwnedReasonerResult::Success { .. } => {
            panic!("expected inconsistency for disjoint class violation");
        }
    }
}

#[test]
fn reasoner_is_consistent() {

    let mut reasoner = Reasoner::with_capacity(4 * 1024 * 1024);

    let rdf_type_iri = format!("{}type", RDF);
    let owl_class_iri = format!("{}Class", OWL);
    let dog_iri = format!("{}Dog", EX);
    let fido_iri = format!("{}fido", EX);

    reasoner.add_iri_triple(&fido_iri, &rdf_type_iri, &dog_iri);
    reasoner.add_iri_triple(&dog_iri, &rdf_type_iri, &owl_class_iri);

    assert!(reasoner.is_consistent(), "simple graph should be consistent");
}

#[test]
fn reasoner_add_triple_with_owned_terms() {

    let mut reasoner = Reasoner::new();

    let s = OwnedTerm::Iri(format!("{}fido", EX));
    let p = OwnedTerm::Iri(format!("{}name", EX));
    let o = OwnedTerm::Literal {
        value: "Fido".to_string(),
        datatype: None,
        lang: Some("en".to_string()),
    };

    reasoner.add_triple(&s, &p, &o);
    assert_eq!(reasoner.triple_count(), 1);
    assert!(reasoner.is_consistent());
}

// ---------------------------------------------------------------------------
// Annotation filtering tests
// ---------------------------------------------------------------------------

#[test]
fn filter_annotations_removes_labels() {
    let arena = Arena::new(4 * 1024 * 1024);
    let mut graph = IndexedGraph::new(&arena);

    let dog = arena.make_iri(&format!("{}Dog", EX));
    let a = rdf_type(&arena);
    let cls = owl_class(&arena);
    let label = arena.make_iri("http://www.w3.org/2000/01/rdf-schema#label");
    let comment = arena.make_iri("http://www.w3.org/2000/01/rdf-schema#comment");
    let dog_label = arena.make_literal("Dog", None, Some("en"));
    let dog_comment = arena.make_literal("A domesticated canine", None, None);

    // 1 semantic triple + 2 annotation triples
    graph.add_triple(arena.make_triple(dog, a, cls));
    graph.add_triple(arena.make_triple(dog, label, dog_label));
    graph.add_triple(arena.make_triple(dog, comment, dog_comment));
    assert_eq!(graph.size(), 3);

    let filtered = filter_annotations(&arena, &graph);
    assert_eq!(filtered.size(), 1, "annotation triples should be removed");
}

#[test]
fn filter_annotations_keeps_semantic_triples() {
    let arena = Arena::new(4 * 1024 * 1024);
    let mut graph = IndexedGraph::new(&arena);

    let dog = arena.make_iri(&format!("{}Dog", EX));
    let animal = arena.make_iri(&format!("{}Animal", EX));
    let a = rdf_type(&arena);
    let sub = rdfs_subclass(&arena);
    let cls = owl_class(&arena);

    graph.add_triple(arena.make_triple(dog, sub, animal));
    graph.add_triple(arena.make_triple(dog, a, cls));
    graph.add_triple(arena.make_triple(animal, a, cls));
    assert_eq!(graph.size(), 3);

    let filtered = filter_annotations(&arena, &graph);
    assert_eq!(filtered.size(), 3, "no triples should be removed");
}

#[test]
fn filter_annotations_removes_user_declared() {
    let arena = Arena::new(4 * 1024 * 1024);
    let mut graph = IndexedGraph::new(&arena);

    let dog = arena.make_iri(&format!("{}Dog", EX));
    let my_note = arena.make_iri(&format!("{}myNote", EX));
    let a = rdf_type(&arena);
    let cls = owl_class(&arena);
    let annot_prop = arena.make_iri(&format!("{}AnnotationProperty", OWL));
    let note_val = arena.make_literal("some note", None, None);

    // Declare myNote as annotation property
    graph.add_triple(arena.make_triple(my_note, a, annot_prop));
    // Semantic triple
    graph.add_triple(arena.make_triple(dog, a, cls));
    // Annotation triple using user-declared property
    graph.add_triple(arena.make_triple(dog, my_note, note_val));
    assert_eq!(graph.size(), 3);

    let filtered = filter_annotations(&arena, &graph);
    // myNote declaration stays (pred is rdf:type), but dog myNote "..." is removed
    assert_eq!(filtered.size(), 2);
}

#[test]
fn reasoner_filter_annotations_produces_complete_results() {
    let mut reasoner = Reasoner::with_capacity(4 * 1024 * 1024).filter_annotations(true);

    let rdf_type_iri = format!("{}type", RDF);
    let rdfs_sub_iri = format!("{}subClassOf", RDFS);
    let owl_class_iri = format!("{}Class", OWL);
    let dog_iri = format!("{}Dog", EX);
    let animal_iri = format!("{}Animal", EX);
    let fido_iri = format!("{}fido", EX);
    let rdfs_label = "http://www.w3.org/2000/01/rdf-schema#label";

    // Semantic triples
    reasoner.add_iri_triple(&dog_iri, &rdfs_sub_iri, &animal_iri);
    reasoner.add_iri_triple(&fido_iri, &rdf_type_iri, &dog_iri);
    reasoner.add_iri_triple(&dog_iri, &rdf_type_iri, &owl_class_iri);
    reasoner.add_iri_triple(&animal_iri, &rdf_type_iri, &owl_class_iri);

    // Annotation triples (should be filtered for reasoning, restored in result)
    let s = OwnedTerm::Iri(dog_iri.clone());
    let p = OwnedTerm::Iri(rdfs_label.to_string());
    let o = OwnedTerm::Literal {
        value: "Dog".to_string(),
        datatype: None,
        lang: Some("en".to_string()),
    };
    reasoner.add_triple(&s, &p, &o);

    match reasoner.reason() {
        OwnedReasonerResult::Success { triples, inferred_count, .. } => {
            assert!(inferred_count > 0, "should infer triples");

            // The annotation triple should be in the result (restored)
            let has_label = triples.iter().any(|t| {
                t.predicate == OwnedTerm::Iri(rdfs_label.to_string())
            });
            assert!(has_label, "annotation triple should be restored in result");

            // fido should be inferred as Animal
            let has_animal = triples.iter().any(|t| {
                t.subject == OwnedTerm::Iri(fido_iri.clone())
                    && t.predicate == OwnedTerm::Iri(rdf_type_iri.clone())
                    && t.object == OwnedTerm::Iri(animal_iri.clone())
            });
            assert!(has_animal, "fido should be inferred as Animal");
        }
        OwnedReasonerResult::Inconsistent { reports } => {
            panic!("expected consistent result, got: {}", reports[0].reason);
        }
    }
}

#[test]
fn standard_annotation_properties_count() {
    assert_eq!(STANDARD_ANNOTATION_PROPERTIES.len(), 27);
    // Spot check a few
    assert!(STANDARD_ANNOTATION_PROPERTIES.contains(&"http://www.w3.org/2000/01/rdf-schema#label"));
    assert!(STANDARD_ANNOTATION_PROPERTIES.contains(&"http://purl.org/dc/terms/abstract"));
}

// ---------------------------------------------------------------------------
// Validate mode tests
// ---------------------------------------------------------------------------

/// Build a TBox-only graph: Animal disjointWith Plant, Triffid subClassOf both.
/// This is unsatisfiable — Triffid can't have instances.
fn build_unsat_tbox(arena: &Arena) -> IndexedGraph<'_> {
    let mut graph = IndexedGraph::new(arena);

    let animal = arena.make_iri(&format!("{}Animal", EX));
    let plant = arena.make_iri(&format!("{}Plant", EX));
    let triffid = arena.make_iri(&format!("{}Triffid", EX));
    let a = rdf_type(arena);
    let cls = owl_class(arena);
    let sub = rdfs_subclass(arena);
    let disjoint = arena.make_iri(&format!("{}disjointWith", OWL));

    graph.add_triple(arena.make_triple(animal, a, cls));
    graph.add_triple(arena.make_triple(plant, a, cls));
    graph.add_triple(arena.make_triple(triffid, a, cls));
    graph.add_triple(arena.make_triple(animal, disjoint, plant));
    graph.add_triple(arena.make_triple(triffid, sub, animal));
    graph.add_triple(arena.make_triple(triffid, sub, plant));

    graph
}

#[test]
fn validate_detects_unsatisfiable_class() {
    let arena = Arena::new(4 * 1024 * 1024);
    let graph = build_unsat_tbox(&arena);

    match validate(&arena, &graph) {
        ValidateResult::Unsatisfiable { reports } => {
            assert_eq!(
                reports[0].entity,
                Term::Iri(&format!("{}Triffid", EX)),
                "should identify Triffid as unsatisfiable"
            );
            assert!(
                reports[0].reason.contains("Unsatisfiable class"),
                "reason should contain 'Unsatisfiable class', got: {}",
                reports[0].reason
            );
        }
        ValidateResult::Satisfiable => {
            panic!("validate should detect unsatisfiable class Triffid");
        }
    }
}

#[test]
fn validate_passes_clean_tbox() {
    let arena = Arena::new(4 * 1024 * 1024);
    let mut graph = IndexedGraph::new(&arena);

    let animal = arena.make_iri(&format!("{}Animal", EX));
    let dog = arena.make_iri(&format!("{}Dog", EX));
    let plant = arena.make_iri(&format!("{}Plant", EX));
    let a = rdf_type(&arena);
    let cls = owl_class(&arena);
    let sub = rdfs_subclass(&arena);
    let disjoint = arena.make_iri(&format!("{}disjointWith", OWL));

    graph.add_triple(arena.make_triple(animal, a, cls));
    graph.add_triple(arena.make_triple(dog, a, cls));
    graph.add_triple(arena.make_triple(plant, a, cls));
    graph.add_triple(arena.make_triple(dog, sub, animal));
    graph.add_triple(arena.make_triple(animal, disjoint, plant));

    match validate(&arena, &graph) {
        ValidateResult::Satisfiable => {
            // Expected: all classes are satisfiable
        }
        ValidateResult::Unsatisfiable { reports } => {
            panic!("clean TBox should pass validation, got: {}", reports[0].reason);
        }
    }
}

#[test]
fn unsat_tbox_passes_without_validate() {
    let arena = Arena::new(4 * 1024 * 1024);
    let graph = build_unsat_tbox(&arena);

    // Without validate, TBox-only should be consistent (no instances to trigger cax-dw)
    match reason(&arena, &graph) {
        ReasonerResult::Success { .. } => {
            // Expected
        }
        ReasonerResult::Inconsistent { reports } => {
            panic!(
                "TBox-only should be consistent without validate, got: {}",
                reports[0].reason
            );
        }
    }
}

#[test]
fn validate_config_builder() {
    let arena = Arena::new(4 * 1024 * 1024);
    let graph = build_unsat_tbox(&arena);

    let config = ReasonerConfig::new().verbose(false).validate(true);
    match reason_with_config(&arena, &graph, &config) {
        ReasonerResult::Inconsistent { reports } => {
            assert!(
                reports[0].reason.contains("Unsatisfiable class"),
                "reason should contain 'Unsatisfiable class', got: {}",
                reports[0].reason
            );
        }
        ReasonerResult::Success { .. } => {
            panic!("validate via config builder should detect unsatisfiable class");
        }
    }
}

#[test]
fn reasoner_validate_method() {
    let mut reasoner = Reasoner::with_capacity(4 * 1024 * 1024);

    let rdf_type_iri = format!("{}type", RDF);
    let rdfs_sub_iri = format!("{}subClassOf", RDFS);
    let owl_class_iri = format!("{}Class", OWL);
    let disjoint_iri = format!("{}disjointWith", OWL);

    let animal_iri = format!("{}Animal", EX);
    let plant_iri = format!("{}Plant", EX);
    let triffid_iri = format!("{}Triffid", EX);

    reasoner.add_iri_triple(&animal_iri, &rdf_type_iri, &owl_class_iri);
    reasoner.add_iri_triple(&plant_iri, &rdf_type_iri, &owl_class_iri);
    reasoner.add_iri_triple(&triffid_iri, &rdf_type_iri, &owl_class_iri);
    reasoner.add_iri_triple(&animal_iri, &disjoint_iri, &plant_iri);
    reasoner.add_iri_triple(&triffid_iri, &rdfs_sub_iri, &animal_iri);
    reasoner.add_iri_triple(&triffid_iri, &rdfs_sub_iri, &plant_iri);

    match reasoner.validate() {
        OwnedValidateResult::Unsatisfiable { reports } => {
            assert_eq!(
                reports[0].entity,
                OwnedTerm::Iri(triffid_iri),
                "should identify Triffid as unsatisfiable"
            );
            assert!(
                reports[0].reason.contains("Unsatisfiable class"),
                "reason should contain 'Unsatisfiable class', got: {}",
                reports[0].reason
            );
        }
        OwnedValidateResult::Satisfiable => {
            panic!("Reasoner.validate() should detect unsatisfiable Triffid class");
        }
    }
}

#[test]
fn reasoner_validate_clean() {
    let mut reasoner = Reasoner::with_capacity(4 * 1024 * 1024);

    let rdf_type_iri = format!("{}type", RDF);
    let rdfs_sub_iri = format!("{}subClassOf", RDFS);
    let owl_class_iri = format!("{}Class", OWL);

    let animal_iri = format!("{}Animal", EX);
    let dog_iri = format!("{}Dog", EX);

    reasoner.add_iri_triple(&animal_iri, &rdf_type_iri, &owl_class_iri);
    reasoner.add_iri_triple(&dog_iri, &rdf_type_iri, &owl_class_iri);
    reasoner.add_iri_triple(&dog_iri, &rdfs_sub_iri, &animal_iri);

    match reasoner.validate() {
        OwnedValidateResult::Satisfiable => {
            // Expected
        }
        OwnedValidateResult::Unsatisfiable { reports } => {
            panic!("clean ontology should pass validation, got: {}", reports[0].reason);
        }
    }
}

// ---------------------------------------------------------------------------
// Property validation tests
// ---------------------------------------------------------------------------

/// Build a TBox with a property declared as both Symmetric and Asymmetric.
fn build_unsat_property_graph(arena: &Arena) -> IndexedGraph<'_> {
    let mut graph = IndexedGraph::new(arena);

    let has_enemy = arena.make_iri(&format!("{}hasEnemy", EX));
    let a = rdf_type(arena);
    let obj_prop = arena.make_iri(&format!("{}ObjectProperty", OWL));
    let sym_prop = arena.make_iri(&format!("{}SymmetricProperty", OWL));
    let asym_prop = arena.make_iri(&format!("{}AsymmetricProperty", OWL));

    graph.add_triple(arena.make_triple(has_enemy, a, obj_prop));
    graph.add_triple(arena.make_triple(has_enemy, a, sym_prop));
    graph.add_triple(arena.make_triple(has_enemy, a, asym_prop));

    graph
}

#[test]
fn validate_detects_unsatisfiable_property() {
    let arena = Arena::new(4 * 1024 * 1024);
    let graph = build_unsat_property_graph(&arena);

    match validate(&arena, &graph) {
        ValidateResult::Unsatisfiable { reports } => {
            assert_eq!(
                reports[0].entity,
                Term::Iri(&format!("{}hasEnemy", EX)),
                "should identify hasEnemy as unsatisfiable"
            );
            assert!(
                reports[0].reason.contains("Unsatisfiable property usage"),
                "reason should contain 'Unsatisfiable property usage', got: {}",
                reports[0].reason
            );
        }
        ValidateResult::Satisfiable => {
            panic!("validate should detect unsatisfiable property hasEnemy");
        }
    }
}

#[test]
fn reasoner_validate_property() {
    let mut reasoner = Reasoner::with_capacity(4 * 1024 * 1024);

    let rdf_type_iri = format!("{}type", RDF);
    let has_enemy_iri = format!("{}hasEnemy", EX);
    let obj_prop_iri = format!("{}ObjectProperty", OWL);
    let sym_prop_iri = format!("{}SymmetricProperty", OWL);
    let asym_prop_iri = format!("{}AsymmetricProperty", OWL);

    reasoner.add_iri_triple(&has_enemy_iri, &rdf_type_iri, &obj_prop_iri);
    reasoner.add_iri_triple(&has_enemy_iri, &rdf_type_iri, &sym_prop_iri);
    reasoner.add_iri_triple(&has_enemy_iri, &rdf_type_iri, &asym_prop_iri);

    match reasoner.validate() {
        OwnedValidateResult::Unsatisfiable { reports } => {
            assert_eq!(
                reports[0].entity,
                OwnedTerm::Iri(has_enemy_iri),
                "should identify hasEnemy as unsatisfiable"
            );
            assert!(
                reports[0].reason.contains("Unsatisfiable property usage"),
                "reason should contain 'Unsatisfiable property usage', got: {}",
                reports[0].reason
            );
        }
        OwnedValidateResult::Satisfiable => {
            panic!("Reasoner.validate() should detect unsatisfiable hasEnemy property");
        }
    }
}

#[test]
fn validate_property_domain_reports_class() {
    // Property hasScore with domain MeteoriteLandings.
    // MeteoriteLandings subClassOf Animal and Plant, which are disjoint.
    // The domain class is unsatisfiable — validate should report the CLASS, not the property.
    let arena = Arena::new(4 * 1024 * 1024);
    let mut graph = IndexedGraph::new(&arena);

    let animal = arena.make_iri(&format!("{}Animal", EX));
    let plant = arena.make_iri(&format!("{}Plant", EX));
    let meteorite = arena.make_iri(&format!("{}MeteoriteLandings", EX));
    let has_score = arena.make_iri(&format!("{}hasScore", EX));
    let a = rdf_type(&arena);
    let cls = owl_class(&arena);
    let sub = rdfs_subclass(&arena);
    let disjoint = arena.make_iri(&format!("{}disjointWith", OWL));
    let obj_prop = arena.make_iri(&format!("{}ObjectProperty", OWL));
    let rdfs_domain = arena.make_iri(&format!("{}domain", RDFS));

    // Declare classes
    graph.add_triple(arena.make_triple(animal, a, cls));
    graph.add_triple(arena.make_triple(plant, a, cls));
    graph.add_triple(arena.make_triple(meteorite, a, cls));

    // Animal disjointWith Plant
    graph.add_triple(arena.make_triple(animal, disjoint, plant));

    // MeteoriteLandings subClassOf both → unsatisfiable
    graph.add_triple(arena.make_triple(meteorite, sub, animal));
    graph.add_triple(arena.make_triple(meteorite, sub, plant));

    // hasScore is a property with domain MeteoriteLandings
    graph.add_triple(arena.make_triple(has_score, a, obj_prop));
    graph.add_triple(arena.make_triple(has_score, rdfs_domain, meteorite));

    match validate(&arena, &graph) {
        ValidateResult::Unsatisfiable { reports } => {
            // Should report the CLASS, not the property
            assert_eq!(
                reports[0].entity,
                Term::Iri(&format!("{}MeteoriteLandings", EX)),
                "should identify MeteoriteLandings as unsatisfiable, not hasScore. reason: {}",
                reports[0].reason
            );
            assert!(
                reports[0].reason.contains("Unsatisfiable class"),
                "reason should contain 'Unsatisfiable class', got: {}",
                reports[0].reason
            );
        }
        ValidateResult::Satisfiable => {
            panic!("validate should detect unsatisfiable MeteoriteLandings via property domain");
        }
    }
}

#[test]
fn reasoner_validate_property_domain_reports_class() {
    // Same scenario as above but via Reasoner high-level API
    let mut reasoner = Reasoner::with_capacity(4 * 1024 * 1024);

    let rdf_type_iri = format!("{}type", RDF);
    let rdfs_sub_iri = format!("{}subClassOf", RDFS);
    let owl_class_iri = format!("{}Class", OWL);
    let disjoint_iri = format!("{}disjointWith", OWL);
    let obj_prop_iri = format!("{}ObjectProperty", OWL);
    let rdfs_domain_iri = format!("{}domain", RDFS);

    let animal_iri = format!("{}Animal", EX);
    let plant_iri = format!("{}Plant", EX);
    let meteorite_iri = format!("{}MeteoriteLandings", EX);
    let has_score_iri = format!("{}hasScore", EX);

    reasoner.add_iri_triple(&animal_iri, &rdf_type_iri, &owl_class_iri);
    reasoner.add_iri_triple(&plant_iri, &rdf_type_iri, &owl_class_iri);
    reasoner.add_iri_triple(&meteorite_iri, &rdf_type_iri, &owl_class_iri);
    reasoner.add_iri_triple(&animal_iri, &disjoint_iri, &plant_iri);
    reasoner.add_iri_triple(&meteorite_iri, &rdfs_sub_iri, &animal_iri);
    reasoner.add_iri_triple(&meteorite_iri, &rdfs_sub_iri, &plant_iri);
    reasoner.add_iri_triple(&has_score_iri, &rdf_type_iri, &obj_prop_iri);
    reasoner.add_iri_triple(&has_score_iri, &rdfs_domain_iri, &meteorite_iri);

    match reasoner.validate() {
        OwnedValidateResult::Unsatisfiable { reports } => {
            assert_eq!(
                reports[0].entity,
                OwnedTerm::Iri(meteorite_iri),
                "should identify MeteoriteLandings as unsatisfiable, not hasScore. reason: {}",
                reports[0].reason
            );
            assert!(
                reports[0].reason.contains("Unsatisfiable class"),
                "reason should contain 'Unsatisfiable class', got: {}",
                reports[0].reason
            );
        }
        OwnedValidateResult::Satisfiable => {
            panic!("Reasoner.validate() should detect unsatisfiable MeteoriteLandings via property domain");
        }
    }
}

#[test]
fn validate_clean_properties_pass() {
    let arena = Arena::new(4 * 1024 * 1024);
    let mut graph = IndexedGraph::new(&arena);

    let has_friend = arena.make_iri(&format!("{}hasFriend", EX));
    let a = rdf_type(&arena);
    let obj_prop = arena.make_iri(&format!("{}ObjectProperty", OWL));
    let sym_prop = arena.make_iri(&format!("{}SymmetricProperty", OWL));

    // Only symmetric, no asymmetric — no contradiction
    graph.add_triple(arena.make_triple(has_friend, a, obj_prop));
    graph.add_triple(arena.make_triple(has_friend, a, sym_prop));

    match validate(&arena, &graph) {
        ValidateResult::Satisfiable => {
            // Expected: symmetric-only property is satisfiable
        }
        ValidateResult::Unsatisfiable { reports } => {
            panic!("symmetric-only property should pass validation, got: {}", reports[0].reason);
        }
    }
}

// ---------------------------------------------------------------------------
// Namespace scoping tests (validate-ns)
// ---------------------------------------------------------------------------

const TLO: &str = "http://tlo.org/";

/// Build a combined graph: TLO classes (tlo:Animal, tlo:Plant disjoint) + domain class (ex:Bad subclassof both).
fn build_combined_tlo_domain(arena: &Arena) -> IndexedGraph<'_> {
    let mut graph = IndexedGraph::new(arena);

    let animal = arena.make_iri(&format!("{}Animal", TLO));
    let plant = arena.make_iri(&format!("{}Plant", TLO));
    let bad = arena.make_iri(&format!("{}Bad", EX));
    let a = rdf_type(arena);
    let cls = owl_class(arena);
    let sub = rdfs_subclass(arena);
    let disjoint = arena.make_iri(&format!("{}disjointWith", OWL));

    // TLO classes
    graph.add_triple(arena.make_triple(animal, a, cls));
    graph.add_triple(arena.make_triple(plant, a, cls));
    graph.add_triple(arena.make_triple(animal, disjoint, plant));

    // Domain class: Bad subClassOf both → unsatisfiable
    graph.add_triple(arena.make_triple(bad, a, cls));
    graph.add_triple(arena.make_triple(bad, sub, animal));
    graph.add_triple(arena.make_triple(bad, sub, plant));

    graph
}

#[test]
fn validate_ns_scopes_to_domain() {
    let arena = Arena::new(4 * 1024 * 1024);
    let graph = build_combined_tlo_domain(&arena);

    // With ns scoping to example.org, only ex:Bad gets synthetic instances
    match validate_with_ns(&arena, &graph, EX) {
        ValidateResult::Unsatisfiable { reports } => {
            assert_eq!(
                reports[0].entity,
                Term::Iri(&format!("{}Bad", EX)),
                "should identify ex:Bad as unsatisfiable"
            );
            assert!(
                reports[0].reason.contains("Unsatisfiable class"),
                "reason should contain 'Unsatisfiable class', got: {}",
                reports[0].reason
            );
        }
        ValidateResult::Satisfiable => {
            panic!("validate_with_ns should detect unsatisfiable ex:Bad");
        }
    }
}

#[test]
fn validate_ns_filters_tlo_entities() {
    let arena = Arena::new(4 * 1024 * 1024);
    let mut graph = IndexedGraph::new(&arena);

    // Only TLO classes, no domain entities
    let animal = arena.make_iri(&format!("{}Animal", TLO));
    let plant = arena.make_iri(&format!("{}Plant", TLO));
    let a = rdf_type(&arena);
    let cls = owl_class(&arena);
    let disjoint = arena.make_iri(&format!("{}disjointWith", OWL));

    graph.add_triple(arena.make_triple(animal, a, cls));
    graph.add_triple(arena.make_triple(plant, a, cls));
    graph.add_triple(arena.make_triple(animal, disjoint, plant));

    // With ns=http://example.org/, no synthetic instances → should pass
    match validate_with_ns(&arena, &graph, EX) {
        ValidateResult::Satisfiable => {
            // Expected: TLO entities not validated
        }
        ValidateResult::Unsatisfiable { reports } => {
            panic!("TLO-only graph with ns scoping should pass, got: {}", reports[0].reason);
        }
    }
}

#[test]
fn reasoner_validate_ns() {
    let mut reasoner = Reasoner::with_capacity(4 * 1024 * 1024);

    let rdf_type_iri = format!("{}type", RDF);
    let rdfs_sub_iri = format!("{}subClassOf", RDFS);
    let owl_class_iri = format!("{}Class", OWL);
    let disjoint_iri = format!("{}disjointWith", OWL);

    let animal_iri = format!("{}Animal", TLO);
    let plant_iri = format!("{}Plant", TLO);
    let bad_iri = format!("{}Bad", EX);

    // TLO
    reasoner.add_iri_triple(&animal_iri, &rdf_type_iri, &owl_class_iri);
    reasoner.add_iri_triple(&plant_iri, &rdf_type_iri, &owl_class_iri);
    reasoner.add_iri_triple(&animal_iri, &disjoint_iri, &plant_iri);

    // Domain
    reasoner.add_iri_triple(&bad_iri, &rdf_type_iri, &owl_class_iri);
    reasoner.add_iri_triple(&bad_iri, &rdfs_sub_iri, &animal_iri);
    reasoner.add_iri_triple(&bad_iri, &rdfs_sub_iri, &plant_iri);

    match reasoner.validate_ns(EX) {
        OwnedValidateResult::Unsatisfiable { reports } => {
            assert_eq!(
                reports[0].entity,
                OwnedTerm::Iri(bad_iri),
                "should identify Bad as unsatisfiable"
            );
            assert!(
                reports[0].reason.contains("Unsatisfiable class"),
                "reason should contain 'Unsatisfiable class', got: {}",
                reports[0].reason
            );
        }
        OwnedValidateResult::Satisfiable => {
            panic!("Reasoner.validate_ns should detect unsatisfiable Bad class");
        }
    }
}

#[test]
fn validate_ns_config_builder() {
    let arena = Arena::new(4 * 1024 * 1024);
    let graph = build_combined_tlo_domain(&arena);

    let config = ReasonerConfig::new()
        .verbose(false)
        .validate(true)
        .validate_ns(EX);

    match reason_with_config(&arena, &graph, &config) {
        ReasonerResult::Inconsistent { reports } => {
            assert!(
                reports[0].reason.contains("Unsatisfiable class"),
                "reason should contain 'Unsatisfiable class', got: {}",
                reports[0].reason
            );
        }
        ReasonerResult::Success { .. } => {
            panic!("validate_ns via config builder should detect unsatisfiable class");
        }
    }
}
