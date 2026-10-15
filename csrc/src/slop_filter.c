#include "../runtime/slop_runtime.h"
#include "slop_filter.h"

slop_map* growl_collect_annotation_properties(slop_arena* arena, slop_rdf_rdf_Graph g);
slop_rdf_index_IndexedGraph growl_graph_to_indexed(slop_arena* arena, slop_rdf_rdf_Graph g, slop_map* annot_set);
slop_rdf_rdf_Graph growl_indexed_to_graph(slop_arena* arena, slop_rdf_index_IndexedGraph ig);
slop_rdf_index_IndexedGraph growl_filter_annotations(slop_arena* arena, slop_rdf_index_IndexedGraph ig);

slop_map* growl_collect_annotation_properties(slop_arena* arena, slop_rdf_rdf_Graph g) {
    {
        __auto_type annot_set = ({ static const slop_map_desc _d = SLOP_SET_DESC(slop_rdf_rdf_Term, slop_hash_slop_rdf_rdf_Term, slop_eq_slop_rdf_rdf_Term, SLOP_KEY_HASHED); slop_map_new_ptr(arena, 0, &_d); });
        __auto_type props = ((slop_list_string){ .data = NULL, .len = 0, .cap = 0, .arena = arena });
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_RDFS_LABEL); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_RDFS_COMMENT); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_RDFS_SEE_ALSO); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_RDFS_IS_DEFINED_BY); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_OWL_DEPRECATED); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_OWL_VERSION_INFO); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_OWL_PRIOR_VERSION); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_OWL_BACKWARD_COMPATIBLE_WITH); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_OWL_INCOMPATIBLE_WITH); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_SKOS_PREF_LABEL); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_SKOS_ALT_LABEL); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_SKOS_HIDDEN_LABEL); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_SKOS_DEFINITION); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_SKOS_NOTE); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_SKOS_SCOPE_NOTE); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_SKOS_EXAMPLE); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_SKOS_HISTORY_NOTE); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_SKOS_EDITORIAL_NOTE); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_SKOS_CHANGE_NOTE); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_DC_TITLE); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_DC_CREATOR); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_DC_SUBJECT); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_DC_DESCRIPTION); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_DCTERMS_TITLE); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_DCTERMS_CREATOR); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_DCTERMS_DESCRIPTION); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        (void)(({ __auto_type _lst_p = &(props); __auto_type _item = (slop_rdf_vocab_DCTERMS_ABSTRACT); if (_lst_p->len >= _lst_p->cap) { _lst_p->data = (__typeof__(_lst_p->data))slop_list_grow_raw(_lst_p->arena, _lst_p->data, &_lst_p->cap, _lst_p->len, sizeof(*_lst_p->data)); } _lst_p->data[_lst_p->len++] = _item; (void)0; }));
        {
            __auto_type _coll = props;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type p = _coll.data[_i];
                {
                    __auto_type term = rdf_make_iri(arena, p);
                    (void)(({ slop_map_put(NULL, annot_set, &(term), NULL, 0); }));
                }
            }
        }
        {
            __auto_type type_term = rdf_make_iri(arena, slop_rdf_vocab_RDF_TYPE);
            __auto_type annot_class = rdf_make_iri(arena, slop_rdf_vocab_OWL_ANNOTATION_PROPERTY);
            {
                __auto_type _coll = g.triples;
                for (size_t _i = 0; _i < _coll.len; _i++) {
                    __auto_type t = _coll.data[_i];
                    {
                        __auto_type pred = t.predicate;
                        __auto_type obj = t.object;
                        __auto_type subj = t.subject;
                        if (rdf_term_eq(pred, type_term) && rdf_term_eq(obj, annot_class)) {
                            (void)(({ slop_map_put(NULL, annot_set, &(subj), NULL, 0); }));
                        }
                    }
                }
            }
        }
        return annot_set;
    }
}

slop_rdf_index_IndexedGraph growl_graph_to_indexed(slop_arena* arena, slop_rdf_rdf_Graph g, slop_map* annot_set) {
    {
        __auto_type ig = rdf_indexed_graph_create(arena);
        {
            __auto_type _coll = g.triples;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                {
                    __auto_type pred = t.predicate;
                    if (!(slop_map_has(annot_set, &(pred)))) {
                        ig = rdf_indexed_graph_add(arena, ig, t);
                    }
                }
            }
        }
        return ig;
    }
}

slop_rdf_rdf_Graph growl_indexed_to_graph(slop_arena* arena, slop_rdf_index_IndexedGraph ig) {
    return ((slop_rdf_rdf_Graph){.triples = ig.triples, .size = ((slop_rdf_rdf_GraphSize)(rdf_indexed_graph_size(ig)))});
}

slop_rdf_index_IndexedGraph growl_filter_annotations(slop_arena* arena, slop_rdf_index_IndexedGraph ig) {
    {
        __auto_type g = growl_indexed_to_graph(arena, ig);
        __auto_type annot_set = growl_collect_annotation_properties(arena, g);
        __auto_type result = rdf_indexed_graph_create(arena);
        {
            __auto_type _coll = ig.triples;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type t = _coll.data[_i];
                if (!(slop_map_has(annot_set, &(t.predicate)))) {
                    result = rdf_indexed_graph_add(arena, result, t);
                }
            }
        }
        return result;
    }
}

