use growl::{Arena, IndexedGraph, ReasonerConfig, ReasonerResult, Term, Triple};
use growl::{get_types, is_consistent, reason, reason_with_config, filter_annotations};
use growl::{OwnedReasonerResult, OwnedTerm, Reasoner, STANDARD_ANNOTATION_PROPERTIES};

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
        ReasonerResult::Inconsistent { reason, .. } => {
            panic!("expected consistent result, got inconsistency: {}", reason);
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
        ReasonerResult::Inconsistent { reason, .. } => {
            panic!("expected consistent result: {}", reason);
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
        OwnedReasonerResult::Inconsistent { reason, .. } => {
            panic!("expected consistent result, got inconsistency: {}", reason);
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
        OwnedReasonerResult::Inconsistent { reason, .. } => {
            assert!(!reason.is_empty(), "inconsistency reason should not be empty");
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
        OwnedReasonerResult::Inconsistent { reason, .. } => {
            panic!("expected consistent result, got: {}", reason);
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
