#include "../runtime/slop_runtime.h"
#include "slop_rdf.h"

rdf_Term rdf_make_iri(slop_arena* arena, slop_string value);
rdf_Term rdf_make_blank(slop_arena* arena, rdf_BlankNodeId id);
rdf_Term rdf_make_literal(slop_arena* arena, slop_string value, slop_option_string datatype, slop_option_string lang);
rdf_TermKind rdf_term_kind(rdf_Term t);
uint8_t rdf_iri_eq(rdf_IRI a, rdf_IRI b);
uint8_t rdf_blank_eq(rdf_BlankNode a, rdf_BlankNode b);
uint8_t rdf_option_string_eq(slop_option_string a, slop_option_string b);
uint8_t rdf_literal_eq(rdf_Literal a, rdf_Literal b);
uint8_t rdf_term_eq(rdf_Term a, rdf_Term b);
rdf_Triple rdf_make_triple(slop_arena* arena, rdf_Term subject, rdf_Term predicate, rdf_Term object);
rdf_Term rdf_triple_subject(rdf_Triple t);
rdf_Term rdf_triple_predicate(rdf_Triple t);
rdf_Term rdf_triple_object(rdf_Triple t);
uint8_t rdf_triple_eq(rdf_Triple a, rdf_Triple b);
rdf_Graph rdf_make_graph(slop_arena* arena);
rdf_Graph rdf_graph_add(slop_arena* arena, rdf_Graph g, rdf_Triple t);
rdf_Graph rdf_graph_add_unchecked(slop_arena* arena, rdf_Graph g, rdf_Triple t);
rdf_Graph rdf_graph_remove(slop_arena* arena, rdf_Graph g, rdf_Triple t);
rdf_GraphSize rdf_graph_size(rdf_Graph g);
uint8_t rdf_graph_contains(rdf_Graph g, rdf_Triple t);
rdf_Graph rdf_graph_match(slop_arena* arena, rdf_Graph g, slop_option_rdf_Term subject, slop_option_rdf_Term predicate, slop_option_rdf_Term object);
void rdf_term_free(rdf_Term* t);
void rdf_triple_free(rdf_Triple* t);
void rdf_graph_free(rdf_Graph* g);

rdf_Term rdf_make_iri(slop_arena* arena, slop_string value) {
    SLOP_PRE(((string_len(value) > 0)), "(> (string-len value) 0)");
    rdf_Term _retval = {0};
    _retval = ((rdf_Term){ .tag = rdf_Term_term_iri, .data.term_iri = ((rdf_IRI){.value = value}) });
    SLOP_POST((({ __auto_type _mv = _retval; uint8_t _mr = {0}; switch (_mv.tag) { case rdf_Term_term_iri: { __auto_type _ = _mv.data.term_iri; _mr = 1; break; } default: { _mr = 0; break; }  } _mr; })), "(match $result ((term-iri _) true) (_ false))");
    return _retval;
}

rdf_Term rdf_make_blank(slop_arena* arena, rdf_BlankNodeId id) {
    SLOP_PRE(((id >= 0)), "(>= id 0)");
    rdf_Term _retval = {0};
    _retval = ((rdf_Term){ .tag = rdf_Term_term_blank, .data.term_blank = ((rdf_BlankNode){.id = id}) });
    SLOP_POST((({ __auto_type _mv = _retval; uint8_t _mr = {0}; switch (_mv.tag) { case rdf_Term_term_blank: { __auto_type _ = _mv.data.term_blank; _mr = 1; break; } default: { _mr = 0; break; }  } _mr; })), "(match $result ((term-blank _) true) (_ false))");
    return _retval;
}

rdf_Term rdf_make_literal(slop_arena* arena, slop_string value, slop_option_string datatype, slop_option_string lang) {
    SLOP_PRE(((string_len(value) >= 0)), "(>= (string-len value) 0)");
    rdf_Term _retval = {0};
    _retval = ((rdf_Term){ .tag = rdf_Term_term_literal, .data.term_literal = ((rdf_Literal){.value = value, .datatype = datatype, .lang = lang}) });
    SLOP_POST((({ __auto_type _mv = _retval; uint8_t _mr = {0}; switch (_mv.tag) { case rdf_Term_term_literal: { __auto_type _ = _mv.data.term_literal; _mr = 1; break; } default: { _mr = 0; break; }  } _mr; })), "(match $result ((term-literal _) true) (_ false))");
    return _retval;
}

rdf_TermKind rdf_term_kind(rdf_Term t) {
    __auto_type _mv_0 = t;
    switch (_mv_0.tag) {
        case rdf_Term_term_iri:
        {
            __auto_type _ = _mv_0.data.term_iri;
            return rdf_TermKind_iri;
        }
        case rdf_Term_term_blank:
        {
            __auto_type _ = _mv_0.data.term_blank;
            return rdf_TermKind_blank;
        }
        case rdf_Term_term_literal:
        {
            __auto_type _ = _mv_0.data.term_literal;
            return rdf_TermKind_literal;
        }
    }
}

uint8_t rdf_iri_eq(rdf_IRI a, rdf_IRI b) {
    uint8_t _retval = {0};
    _retval = string_eq(a.value, b.value);
    SLOP_POST(((_retval == string_eq(a.value, b.value))), "(== $result (string-eq (. a value) (. b value)))");
    return _retval;
}

uint8_t rdf_blank_eq(rdf_BlankNode a, rdf_BlankNode b) {
    uint8_t _retval = {0};
    _retval = (a.id == b.id);
    SLOP_POST(((_retval == (a.id == b.id))), "(== $result (== (. a id) (. b id)))");
    return _retval;
}

uint8_t rdf_option_string_eq(slop_option_string a, slop_option_string b) {
    __auto_type _mv_1 = a;
    if (_mv_1.has_value) {
        __auto_type a_val = _mv_1.value;
        __auto_type _mv_2 = b;
        if (_mv_2.has_value) {
            __auto_type b_val = _mv_2.value;
            return string_eq(a_val, b_val);
        } else if (!_mv_2.has_value) {
            return 0;
        }
    } else if (!_mv_1.has_value) {
        __auto_type _mv_3 = b;
        if (_mv_3.has_value) {
            __auto_type _ = _mv_3.value;
            return 0;
        } else if (!_mv_3.has_value) {
            return 1;
        }
    }
}

uint8_t rdf_literal_eq(rdf_Literal a, rdf_Literal b) {
    uint8_t _retval = {0};
    _retval = (string_eq(a.value, b.value) && (rdf_option_string_eq(a.datatype, b.datatype) && rdf_option_string_eq(a.lang, b.lang)));
    SLOP_POST(((_retval == (string_eq(a.value, b.value) && (rdf_option_string_eq(a.datatype, b.datatype) && rdf_option_string_eq(a.lang, b.lang))))), "(== $result (and (string-eq (. a value) (. b value)) (and (option-string-eq (. a datatype) (. b datatype)) (option-string-eq (. a lang) (. b lang)))))");
    return _retval;
}

uint8_t rdf_term_eq(rdf_Term a, rdf_Term b) {
    __auto_type _mv_4 = a;
    switch (_mv_4.tag) {
        case rdf_Term_term_iri:
        {
            __auto_type a_iri = _mv_4.data.term_iri;
            __auto_type _mv_5 = b;
            switch (_mv_5.tag) {
                case rdf_Term_term_iri:
                {
                    __auto_type b_iri = _mv_5.data.term_iri;
                    return rdf_iri_eq(a_iri, b_iri);
                }
                default: {
                    return 0;
                }
            }
        }
        case rdf_Term_term_blank:
        {
            __auto_type a_blank = _mv_4.data.term_blank;
            __auto_type _mv_6 = b;
            switch (_mv_6.tag) {
                case rdf_Term_term_blank:
                {
                    __auto_type b_blank = _mv_6.data.term_blank;
                    return rdf_blank_eq(a_blank, b_blank);
                }
                default: {
                    return 0;
                }
            }
        }
        case rdf_Term_term_literal:
        {
            __auto_type a_lit = _mv_4.data.term_literal;
            __auto_type _mv_7 = b;
            switch (_mv_7.tag) {
                case rdf_Term_term_literal:
                {
                    __auto_type b_lit = _mv_7.data.term_literal;
                    return rdf_literal_eq(a_lit, b_lit);
                }
                default: {
                    return 0;
                }
            }
        }
    }
}

rdf_Triple rdf_make_triple(slop_arena* arena, rdf_Term subject, rdf_Term predicate, rdf_Term object) {
    rdf_Triple _retval = {0};
    _retval = ((rdf_Triple){.subject = subject, .predicate = predicate, .object = object});
    SLOP_POST((((rdf_term_eq(rdf_triple_subject(_retval), subject)) && (rdf_term_eq(rdf_triple_predicate(_retval), predicate)) && (rdf_term_eq(rdf_triple_object(_retval), object)))), "(and (term-eq (triple-subject $result) subject) (term-eq (triple-predicate $result) predicate) (term-eq (triple-object $result) object))");
    return _retval;
}

rdf_Term rdf_triple_subject(rdf_Triple t) {
    rdf_Term _retval = {0};
    _retval = t.subject;
    SLOP_POST((rdf_term_eq(_retval, t.subject)), "(term-eq $result t.subject)");
    return _retval;
}

rdf_Term rdf_triple_predicate(rdf_Triple t) {
    rdf_Term _retval = {0};
    _retval = t.predicate;
    SLOP_POST((rdf_term_eq(_retval, t.predicate)), "(term-eq $result t.predicate)");
    return _retval;
}

rdf_Term rdf_triple_object(rdf_Triple t) {
    rdf_Term _retval = {0};
    _retval = t.object;
    SLOP_POST((rdf_term_eq(_retval, t.object)), "(term-eq $result t.object)");
    return _retval;
}

uint8_t rdf_triple_eq(rdf_Triple a, rdf_Triple b) {
    uint8_t _retval = {0};
    _retval = (rdf_term_eq(a.subject, b.subject) && (rdf_term_eq(a.predicate, b.predicate) && rdf_term_eq(a.object, b.object)));
    SLOP_POST(((_retval == ((rdf_term_eq(a.subject, b.subject)) && (rdf_term_eq(a.predicate, b.predicate)) && (rdf_term_eq(a.object, b.object))))), "(== $result (and (term-eq a.subject b.subject) (term-eq a.predicate b.predicate) (term-eq a.object b.object)))");
    return _retval;
}

rdf_Graph rdf_make_graph(slop_arena* arena) {
    rdf_Graph _retval = {0};
    _retval = ((rdf_Graph){.triples = ((slop_list_rdf_Triple){ .data = (rdf_Triple*)slop_arena_alloc(arena, 16 * sizeof(rdf_Triple)), .len = 0, .cap = 16 }), .size = 0});
    SLOP_POST(((rdf_graph_size(_retval) == 0)), "(== (graph-size $result) 0)");
    return _retval;
}

rdf_Graph rdf_graph_add(slop_arena* arena, rdf_Graph g, rdf_Triple t) {
    rdf_Graph _retval = {0};
    if (rdf_graph_contains(g, t)) {
        _retval = g;
    } else {
        _retval = ((rdf_Graph){.triples = ({ ({ __auto_type _lst_p = &(g.triples); __auto_type _item = (t); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); g.triples; }), .size = ((rdf_GraphSize)((g.size + 1)))});
    }
    SLOP_POST(((rdf_graph_size(_retval) >= rdf_graph_size(g))), "(>= (graph-size $result) (graph-size g))");
    SLOP_POST((rdf_graph_contains(_retval, t)), "(graph-contains $result t)");
    return _retval;
}

rdf_Graph rdf_graph_add_unchecked(slop_arena* arena, rdf_Graph g, rdf_Triple t) {
    rdf_Graph _retval = {0};
    _retval = ((rdf_Graph){.triples = ({ ({ __auto_type _lst_p = &(g.triples); __auto_type _item = (t); if (_lst_p->len >= _lst_p->cap) { size_t _new_cap = _lst_p->cap == 0 ? 16 : _lst_p->cap * 2; __typeof__(_lst_p->data) _new_data = (__typeof__(_lst_p->data))slop_arena_alloc(arena, _new_cap * sizeof(*_lst_p->data)); if (_lst_p->len > 0) memcpy(_new_data, _lst_p->data, _lst_p->len * sizeof(*_lst_p->data)); _lst_p->data = _new_data; _lst_p->cap = _new_cap; } _lst_p->data[_lst_p->len++] = _item; (void)0; }); g.triples; }), .size = ((rdf_GraphSize)((g.size + 1)))});
    SLOP_POST(((rdf_graph_size(_retval) == (rdf_graph_size(g) + 1))), "(== (graph-size $result) (+ (graph-size g) 1))");
    return _retval;
}

rdf_Graph rdf_graph_remove(slop_arena* arena, rdf_Graph g, rdf_Triple t) {
    rdf_Graph _retval = {0};
    {
        __auto_type result = rdf_make_graph(arena);
        {
            __auto_type _coll = g.triples;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type triple = _coll.data[_i];
                if (!(rdf_triple_eq(triple, t))) {
                    result = rdf_graph_add(arena, result, triple);
                }
            }
        }
        _retval = result;
    }
    SLOP_POST(((rdf_graph_size(_retval) <= rdf_graph_size(g))), "(<= (graph-size $result) (graph-size g))");
    SLOP_POST((!(rdf_graph_contains(_retval, t))), "(not (graph-contains $result t))");
    return _retval;
}

rdf_GraphSize rdf_graph_size(rdf_Graph g) {
    rdf_GraphSize _retval = {0};
    _retval = g.size;
    SLOP_POST(((_retval >= 0)), "(>= $result 0)");
    SLOP_POST(((_retval == ((int64_t)((g.triples).len)))), "(== $result (list-len g.triples))");
    return _retval;
}

uint8_t rdf_graph_contains(rdf_Graph g, rdf_Triple t) {
    {
        uint8_t found = 0;
        {
            __auto_type _coll = g.triples;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type triple = _coll.data[_i];
                if (rdf_triple_eq(triple, t)) {
                    found = 1;
                }
            }
        }
        return found;
    }
}

rdf_Graph rdf_graph_match(slop_arena* arena, rdf_Graph g, slop_option_rdf_Term subject, slop_option_rdf_Term predicate, slop_option_rdf_Term object) {
    rdf_Graph _retval = {0};
    {
        __auto_type result = rdf_make_graph(arena);
        {
            __auto_type _coll = g.triples;
            for (size_t _i = 0; _i < _coll.len; _i++) {
                __auto_type triple = _coll.data[_i];
                {
                    __auto_type s_match = ({ __auto_type _mv = subject; _mv.has_value ? ({ __auto_type s = _mv.value; rdf_term_eq(s, triple.subject); }) : (1); });
                    {
                        __auto_type p_match = ({ __auto_type _mv = predicate; _mv.has_value ? ({ __auto_type p = _mv.value; rdf_term_eq(p, triple.predicate); }) : (1); });
                        {
                            __auto_type o_match = ({ __auto_type _mv = object; _mv.has_value ? ({ __auto_type o = _mv.value; rdf_term_eq(o, triple.object); }) : (1); });
                            if ((s_match && (p_match && o_match))) {
                                result = rdf_graph_add(arena, result, triple);
                            }
                        }
                    }
                }
            }
        }
        _retval = result;
    }
    SLOP_POST(((rdf_graph_size(_retval) <= rdf_graph_size(g))), "(<= (graph-size $result) (graph-size g))");
    return _retval;
}

void rdf_term_free(rdf_Term* t) {
    SLOP_PRE(((t != NULL)), "(!= t nil)");
    __auto_type _mv_8 = (*t);
    switch (_mv_8.tag) {
        case rdf_Term_term_iri:
        {
            __auto_type _ = _mv_8.data.term_iri;
            break;
        }
        case rdf_Term_term_blank:
        {
            __auto_type _ = _mv_8.data.term_blank;
            break;
        }
        case rdf_Term_term_literal:
        {
            __auto_type _ = _mv_8.data.term_literal;
            break;
        }
    }
}

void rdf_triple_free(rdf_Triple* t) {
    SLOP_PRE(((t != NULL)), "(!= t nil)");
    rdf_term_free((&(*t).subject));
    rdf_term_free((&(*t).predicate));
    rdf_term_free((&(*t).object));
}

void rdf_graph_free(rdf_Graph* g) {
    SLOP_PRE(((g != NULL)), "(!= g nil)");
    {
        __auto_type _coll = (*g).triples;
        for (size_t _i = 0; _i < _coll.len; _i++) {
            __auto_type triple = _coll.data[_i];
            rdf_triple_free((&triple));
        }
    }
    (*g).size = 0;
}

