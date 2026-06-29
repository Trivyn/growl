#include "../runtime/slop_runtime.h"
#include "slop_xsd.h"

xsd_XsdType xsd_parse_type(slop_string datatype_iri);
slop_result_xsd_XsdValue_xsd_XsdError xsd_parse_value(slop_arena* arena, slop_string lexical, xsd_XsdType dtype);
uint8_t xsd_validate_lexical(slop_string lexical, slop_string datatype_iri);
uint8_t xsd_values_equal(xsd_XsdValue a, xsd_XsdValue b);
uint8_t xsd_types_compatible(xsd_XsdType t1, xsd_XsdType t2);
slop_result_u8_xsd_XsdError xsd_literal_values_equal(slop_arena* arena, rdf_Literal a, rdf_Literal b);
xsd_XsdCompareResult xsd_float_cmp(double a, double b);
xsd_XsdCompareResult xsd_values_compare(xsd_XsdValue a, xsd_XsdValue b);
xsd_XsdCompareResult xsd_compare(slop_arena* arena, rdf_Term a, rdf_Term b);

xsd_XsdType xsd_parse_type(slop_string datatype_iri) {
    if (string_eq(datatype_iri, vocab_XSD_STRING)) {
        return xsd_XsdType_xsd_string;
    } else if (string_eq(datatype_iri, vocab_XSD_INTEGER)) {
        return xsd_XsdType_xsd_integer;
    } else if (string_eq(datatype_iri, vocab_XSD_BOOLEAN)) {
        return xsd_XsdType_xsd_boolean;
    } else if (string_eq(datatype_iri, vocab_XSD_DECIMAL)) {
        return xsd_XsdType_xsd_decimal;
    } else if (string_eq(datatype_iri, vocab_XSD_FLOAT)) {
        return xsd_XsdType_xsd_float;
    } else if (string_eq(datatype_iri, vocab_XSD_DOUBLE)) {
        return xsd_XsdType_xsd_double;
    } else {
        return xsd_XsdType_xsd_unknown;
    }
}

slop_result_xsd_XsdValue_xsd_XsdError xsd_parse_value(slop_arena* arena, slop_string lexical, xsd_XsdType dtype) {
    __auto_type _mv_57 = dtype;
    switch (_mv_57) {
        case xsd_XsdType_xsd_string: {
            return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = true, .data.ok = ((xsd_XsdValue){ .tag = xsd_XsdValue_xsd_string_val, .data.xsd_string_val = lexical }) });
            break;
        }
        case xsd_XsdType_xsd_integer: {
            __auto_type _mv_58 = strlib_parse_int(lexical);
            if (_mv_58.is_ok) {
                __auto_type val = _mv_58.data.ok;
                return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = true, .data.ok = ((xsd_XsdValue){ .tag = xsd_XsdValue_xsd_integer_val, .data.xsd_integer_val = val }) });
            } else if (!_mv_58.is_ok) {
                __auto_type _ = _mv_58.data.err;
                return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = false, .data.err = xsd_XsdError_invalid_lexical_form });
            }
            break;
        }
        case xsd_XsdType_xsd_boolean: {
            if (string_eq(lexical, SLOP_STR("true"))) {
                return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = true, .data.ok = ((xsd_XsdValue){ .tag = xsd_XsdValue_xsd_boolean_val, .data.xsd_boolean_val = 1 }) });
            } else {
                if (string_eq(lexical, SLOP_STR("false"))) {
                    return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = true, .data.ok = ((xsd_XsdValue){ .tag = xsd_XsdValue_xsd_boolean_val, .data.xsd_boolean_val = 0 }) });
                } else {
                    return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = false, .data.err = xsd_XsdError_invalid_lexical_form });
                }
            }
            break;
        }
        case xsd_XsdType_xsd_decimal: {
            __auto_type _mv_59 = strlib_parse_float(lexical);
            if (_mv_59.is_ok) {
                __auto_type val = _mv_59.data.ok;
                return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = true, .data.ok = ((xsd_XsdValue){ .tag = xsd_XsdValue_xsd_decimal_val, .data.xsd_decimal_val = val }) });
            } else if (!_mv_59.is_ok) {
                __auto_type _ = _mv_59.data.err;
                return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = false, .data.err = xsd_XsdError_invalid_lexical_form });
            }
            break;
        }
        case xsd_XsdType_xsd_float: {
            __auto_type _mv_60 = strlib_parse_float(lexical);
            if (_mv_60.is_ok) {
                __auto_type val = _mv_60.data.ok;
                return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = true, .data.ok = ((xsd_XsdValue){ .tag = xsd_XsdValue_xsd_float_val, .data.xsd_float_val = ((float)(val)) }) });
            } else if (!_mv_60.is_ok) {
                __auto_type _ = _mv_60.data.err;
                return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = false, .data.err = xsd_XsdError_invalid_lexical_form });
            }
            break;
        }
        case xsd_XsdType_xsd_double: {
            __auto_type _mv_61 = strlib_parse_float(lexical);
            if (_mv_61.is_ok) {
                __auto_type val = _mv_61.data.ok;
                return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = true, .data.ok = ((xsd_XsdValue){ .tag = xsd_XsdValue_xsd_double_val, .data.xsd_double_val = val }) });
            } else if (!_mv_61.is_ok) {
                __auto_type _ = _mv_61.data.err;
                return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = false, .data.err = xsd_XsdError_invalid_lexical_form });
            }
            break;
        }
        case xsd_XsdType_xsd_unknown: {
            return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = true, .data.ok = ((xsd_XsdValue){ .tag = xsd_XsdValue_xsd_unknown_val, .data.xsd_unknown_val = lexical }) });
            break;
        }
    }
}

uint8_t xsd_validate_lexical(slop_string lexical, slop_string datatype_iri) {
    if (string_eq(datatype_iri, vocab_XSD_STRING)) {
        return 1;
    } else if (string_eq(datatype_iri, vocab_XSD_INTEGER)) {
        __auto_type _mv_62 = strlib_parse_int(lexical);
        if (_mv_62.is_ok) {
            __auto_type _ = _mv_62.data.ok;
            return 1;
        } else if (!_mv_62.is_ok) {
            __auto_type _ = _mv_62.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_BOOLEAN)) {
        return ((string_eq(lexical, SLOP_STR("true"))) || (string_eq(lexical, SLOP_STR("false"))) || (string_eq(lexical, SLOP_STR("1"))) || (string_eq(lexical, SLOP_STR("0"))));
    } else if (string_eq(datatype_iri, vocab_XSD_DECIMAL)) {
        __auto_type _mv_63 = strlib_parse_float(lexical);
        if (_mv_63.is_ok) {
            __auto_type _ = _mv_63.data.ok;
            return 1;
        } else if (!_mv_63.is_ok) {
            __auto_type _ = _mv_63.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_FLOAT)) {
        __auto_type _mv_64 = strlib_parse_float(lexical);
        if (_mv_64.is_ok) {
            __auto_type _ = _mv_64.data.ok;
            return 1;
        } else if (!_mv_64.is_ok) {
            __auto_type _ = _mv_64.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_DOUBLE)) {
        __auto_type _mv_65 = strlib_parse_float(lexical);
        if (_mv_65.is_ok) {
            __auto_type _ = _mv_65.data.ok;
            return 1;
        } else if (!_mv_65.is_ok) {
            __auto_type _ = _mv_65.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_LONG)) {
        __auto_type _mv_66 = strlib_parse_int(lexical);
        if (_mv_66.is_ok) {
            __auto_type _ = _mv_66.data.ok;
            return 1;
        } else if (!_mv_66.is_ok) {
            __auto_type _ = _mv_66.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_INT)) {
        __auto_type _mv_67 = strlib_parse_int(lexical);
        if (_mv_67.is_ok) {
            __auto_type v = _mv_67.data.ok;
            return ((v >= -2147483648) && (v <= 2147483647));
        } else if (!_mv_67.is_ok) {
            __auto_type _ = _mv_67.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_SHORT)) {
        __auto_type _mv_68 = strlib_parse_int(lexical);
        if (_mv_68.is_ok) {
            __auto_type v = _mv_68.data.ok;
            return ((v >= -32768) && (v <= 32767));
        } else if (!_mv_68.is_ok) {
            __auto_type _ = _mv_68.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_BYTE)) {
        __auto_type _mv_69 = strlib_parse_int(lexical);
        if (_mv_69.is_ok) {
            __auto_type v = _mv_69.data.ok;
            return ((v >= -128) && (v <= 127));
        } else if (!_mv_69.is_ok) {
            __auto_type _ = _mv_69.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_UNSIGNED_LONG)) {
        __auto_type _mv_70 = strlib_parse_int(lexical);
        if (_mv_70.is_ok) {
            __auto_type v = _mv_70.data.ok;
            return (v >= 0);
        } else if (!_mv_70.is_ok) {
            __auto_type _ = _mv_70.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_UNSIGNED_INT)) {
        __auto_type _mv_71 = strlib_parse_int(lexical);
        if (_mv_71.is_ok) {
            __auto_type v = _mv_71.data.ok;
            return ((v >= 0) && (v <= 4294967295));
        } else if (!_mv_71.is_ok) {
            __auto_type _ = _mv_71.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_UNSIGNED_SHORT)) {
        __auto_type _mv_72 = strlib_parse_int(lexical);
        if (_mv_72.is_ok) {
            __auto_type v = _mv_72.data.ok;
            return ((v >= 0) && (v <= 65535));
        } else if (!_mv_72.is_ok) {
            __auto_type _ = _mv_72.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_UNSIGNED_BYTE)) {
        __auto_type _mv_73 = strlib_parse_int(lexical);
        if (_mv_73.is_ok) {
            __auto_type v = _mv_73.data.ok;
            return ((v >= 0) && (v <= 255));
        } else if (!_mv_73.is_ok) {
            __auto_type _ = _mv_73.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_NON_NEGATIVE_INTEGER)) {
        __auto_type _mv_74 = strlib_parse_int(lexical);
        if (_mv_74.is_ok) {
            __auto_type v = _mv_74.data.ok;
            return (v >= 0);
        } else if (!_mv_74.is_ok) {
            __auto_type _ = _mv_74.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_POSITIVE_INTEGER)) {
        __auto_type _mv_75 = strlib_parse_int(lexical);
        if (_mv_75.is_ok) {
            __auto_type v = _mv_75.data.ok;
            return (v >= 1);
        } else if (!_mv_75.is_ok) {
            __auto_type _ = _mv_75.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_NEGATIVE_INTEGER)) {
        __auto_type _mv_76 = strlib_parse_int(lexical);
        if (_mv_76.is_ok) {
            __auto_type v = _mv_76.data.ok;
            return (v <= -1);
        } else if (!_mv_76.is_ok) {
            __auto_type _ = _mv_76.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_NON_POSITIVE_INTEGER)) {
        __auto_type _mv_77 = strlib_parse_int(lexical);
        if (_mv_77.is_ok) {
            __auto_type v = _mv_77.data.ok;
            return (v <= 0);
        } else if (!_mv_77.is_ok) {
            __auto_type _ = _mv_77.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_RDF_LANG_STRING)) {
        return 1;
    } else {
        return 1;
    }
}

uint8_t xsd_values_equal(xsd_XsdValue a, xsd_XsdValue b) {
    __auto_type _mv_78 = a;
    switch (_mv_78.tag) {
        case xsd_XsdValue_xsd_string_val:
        {
            __auto_type s1 = _mv_78.data.xsd_string_val;
            __auto_type _mv_79 = b;
            switch (_mv_79.tag) {
                case xsd_XsdValue_xsd_string_val:
                {
                    __auto_type s2 = _mv_79.data.xsd_string_val;
                    return string_eq(s1, s2);
                }
                default: {
                    return 0;
                }
            }
        }
        case xsd_XsdValue_xsd_integer_val:
        {
            __auto_type i1 = _mv_78.data.xsd_integer_val;
            __auto_type _mv_80 = b;
            switch (_mv_80.tag) {
                case xsd_XsdValue_xsd_integer_val:
                {
                    __auto_type i2 = _mv_80.data.xsd_integer_val;
                    return (i1 == i2);
                }
                case xsd_XsdValue_xsd_decimal_val:
                {
                    __auto_type d2 = _mv_80.data.xsd_decimal_val;
                    return (((double)(i1)) == d2);
                }
                case xsd_XsdValue_xsd_float_val:
                {
                    __auto_type f2 = _mv_80.data.xsd_float_val;
                    return (((double)(i1)) == ((double)(f2)));
                }
                case xsd_XsdValue_xsd_double_val:
                {
                    __auto_type d2 = _mv_80.data.xsd_double_val;
                    return (((double)(i1)) == d2);
                }
                default: {
                    return 0;
                }
            }
        }
        case xsd_XsdValue_xsd_decimal_val:
        {
            __auto_type d1 = _mv_78.data.xsd_decimal_val;
            __auto_type _mv_81 = b;
            switch (_mv_81.tag) {
                case xsd_XsdValue_xsd_integer_val:
                {
                    __auto_type i2 = _mv_81.data.xsd_integer_val;
                    return (d1 == ((double)(i2)));
                }
                case xsd_XsdValue_xsd_decimal_val:
                {
                    __auto_type d2 = _mv_81.data.xsd_decimal_val;
                    return (d1 == d2);
                }
                case xsd_XsdValue_xsd_float_val:
                {
                    __auto_type f2 = _mv_81.data.xsd_float_val;
                    return (d1 == ((double)(f2)));
                }
                case xsd_XsdValue_xsd_double_val:
                {
                    __auto_type d2 = _mv_81.data.xsd_double_val;
                    return (d1 == d2);
                }
                default: {
                    return 0;
                }
            }
        }
        case xsd_XsdValue_xsd_float_val:
        {
            __auto_type f1 = _mv_78.data.xsd_float_val;
            __auto_type _mv_82 = b;
            switch (_mv_82.tag) {
                case xsd_XsdValue_xsd_integer_val:
                {
                    __auto_type i2 = _mv_82.data.xsd_integer_val;
                    return (((double)(f1)) == ((double)(i2)));
                }
                case xsd_XsdValue_xsd_decimal_val:
                {
                    __auto_type d2 = _mv_82.data.xsd_decimal_val;
                    return (((double)(f1)) == d2);
                }
                case xsd_XsdValue_xsd_float_val:
                {
                    __auto_type f2 = _mv_82.data.xsd_float_val;
                    return (f1 == f2);
                }
                case xsd_XsdValue_xsd_double_val:
                {
                    __auto_type d2 = _mv_82.data.xsd_double_val;
                    return (((double)(f1)) == d2);
                }
                default: {
                    return 0;
                }
            }
        }
        case xsd_XsdValue_xsd_double_val:
        {
            __auto_type d1 = _mv_78.data.xsd_double_val;
            __auto_type _mv_83 = b;
            switch (_mv_83.tag) {
                case xsd_XsdValue_xsd_integer_val:
                {
                    __auto_type i2 = _mv_83.data.xsd_integer_val;
                    return (d1 == ((double)(i2)));
                }
                case xsd_XsdValue_xsd_decimal_val:
                {
                    __auto_type d2 = _mv_83.data.xsd_decimal_val;
                    return (d1 == d2);
                }
                case xsd_XsdValue_xsd_float_val:
                {
                    __auto_type f2 = _mv_83.data.xsd_float_val;
                    return (d1 == ((double)(f2)));
                }
                case xsd_XsdValue_xsd_double_val:
                {
                    __auto_type d2 = _mv_83.data.xsd_double_val;
                    return (d1 == d2);
                }
                default: {
                    return 0;
                }
            }
        }
        case xsd_XsdValue_xsd_boolean_val:
        {
            __auto_type b1 = _mv_78.data.xsd_boolean_val;
            __auto_type _mv_84 = b;
            switch (_mv_84.tag) {
                case xsd_XsdValue_xsd_boolean_val:
                {
                    __auto_type b2 = _mv_84.data.xsd_boolean_val;
                    return (b1 == b2);
                }
                default: {
                    return 0;
                }
            }
        }
        case xsd_XsdValue_xsd_unknown_val:
        {
            __auto_type u1 = _mv_78.data.xsd_unknown_val;
            __auto_type _mv_85 = b;
            switch (_mv_85.tag) {
                case xsd_XsdValue_xsd_unknown_val:
                {
                    __auto_type u2 = _mv_85.data.xsd_unknown_val;
                    return string_eq(u1, u2);
                }
                default: {
                    return 0;
                }
            }
        }
    }
}

uint8_t xsd_types_compatible(xsd_XsdType t1, xsd_XsdType t2) {
    return ((t1 == t2) || ((((t1 == xsd_XsdType_xsd_integer)) || ((t1 == xsd_XsdType_xsd_decimal)) || ((t1 == xsd_XsdType_xsd_float)) || ((t1 == xsd_XsdType_xsd_double))) && (((t2 == xsd_XsdType_xsd_integer)) || ((t2 == xsd_XsdType_xsd_decimal)) || ((t2 == xsd_XsdType_xsd_float)) || ((t2 == xsd_XsdType_xsd_double)))));
}

slop_result_u8_xsd_XsdError xsd_literal_values_equal(slop_arena* arena, rdf_Literal a, rdf_Literal b) {
    __auto_type _mv_86 = a.lang;
    if (_mv_86.has_value) {
        __auto_type lang_a = _mv_86.value;
        __auto_type _mv_87 = b.lang;
        if (_mv_87.has_value) {
            __auto_type lang_b = _mv_87.value;
            if (string_eq(lang_a, lang_b)) {
                return ((slop_result_u8_xsd_XsdError){ .is_ok = true, .data.ok = string_eq(a.value, b.value) });
            } else {
                return ((slop_result_u8_xsd_XsdError){ .is_ok = true, .data.ok = 0 });
            }
        } else if (!_mv_87.has_value) {
            return ((slop_result_u8_xsd_XsdError){ .is_ok = true, .data.ok = 0 });
        }
    } else if (!_mv_86.has_value) {
        __auto_type _mv_88 = a.datatype;
        if (_mv_88.has_value) {
            __auto_type dt_a = _mv_88.value;
            __auto_type _mv_89 = b.datatype;
            if (_mv_89.has_value) {
                __auto_type dt_b = _mv_89.value;
                {
                    __auto_type type_a = xsd_parse_type(dt_a);
                    {
                        __auto_type type_b = xsd_parse_type(dt_b);
                        {
                            __auto_type val_a = ({ __auto_type _tmp = xsd_parse_value(arena, a.value, type_a); if (!_tmp.is_ok) return ((slop_result_u8_xsd_XsdError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                            {
                                __auto_type val_b = ({ __auto_type _tmp = xsd_parse_value(arena, b.value, type_b); if (!_tmp.is_ok) return ((slop_result_u8_xsd_XsdError){ .is_ok = false, .data.err = _tmp.data.err }); _tmp.data.ok; });
                                return ((slop_result_u8_xsd_XsdError){ .is_ok = true, .data.ok = xsd_values_equal(val_a, val_b) });
                            }
                        }
                    }
                }
            } else if (!_mv_89.has_value) {
                return ((slop_result_u8_xsd_XsdError){ .is_ok = true, .data.ok = 0 });
            }
        } else if (!_mv_88.has_value) {
            __auto_type _mv_90 = b.datatype;
            if (_mv_90.has_value) {
                __auto_type dt_b = _mv_90.value;
                return ((slop_result_u8_xsd_XsdError){ .is_ok = true, .data.ok = 0 });
            } else if (!_mv_90.has_value) {
                return ((slop_result_u8_xsd_XsdError){ .is_ok = true, .data.ok = string_eq(a.value, b.value) });
            }
        }
    }
}

xsd_XsdCompareResult xsd_float_cmp(double a, double b) {
    if (a < b) {
        return xsd_XsdCompareResult_xsd_compare_less;
    } else {
        if (a > b) {
            return xsd_XsdCompareResult_xsd_compare_greater;
        } else {
            return xsd_XsdCompareResult_xsd_compare_equal;
        }
    }
}

xsd_XsdCompareResult xsd_values_compare(xsd_XsdValue a, xsd_XsdValue b) {
    __auto_type _mv_91 = a;
    switch (_mv_91.tag) {
        case xsd_XsdValue_xsd_integer_val:
        {
            __auto_type i1 = _mv_91.data.xsd_integer_val;
            {
                __auto_type d1 = ((double)(i1));
                __auto_type _mv_92 = b;
                switch (_mv_92.tag) {
                    case xsd_XsdValue_xsd_integer_val:
                    {
                        __auto_type i2 = _mv_92.data.xsd_integer_val;
                        return xsd_float_cmp(d1, ((double)(i2)));
                    }
                    case xsd_XsdValue_xsd_decimal_val:
                    {
                        __auto_type d2 = _mv_92.data.xsd_decimal_val;
                        return xsd_float_cmp(d1, d2);
                    }
                    case xsd_XsdValue_xsd_float_val:
                    {
                        __auto_type f2 = _mv_92.data.xsd_float_val;
                        return xsd_float_cmp(d1, ((double)(f2)));
                    }
                    case xsd_XsdValue_xsd_double_val:
                    {
                        __auto_type d2 = _mv_92.data.xsd_double_val;
                        return xsd_float_cmp(d1, d2);
                    }
                    default: {
                        return xsd_XsdCompareResult_xsd_compare_incomparable;
                    }
                }
            }
        }
        case xsd_XsdValue_xsd_decimal_val:
        {
            __auto_type d1 = _mv_91.data.xsd_decimal_val;
            __auto_type _mv_93 = b;
            switch (_mv_93.tag) {
                case xsd_XsdValue_xsd_integer_val:
                {
                    __auto_type i2 = _mv_93.data.xsd_integer_val;
                    return xsd_float_cmp(d1, ((double)(i2)));
                }
                case xsd_XsdValue_xsd_decimal_val:
                {
                    __auto_type d2 = _mv_93.data.xsd_decimal_val;
                    return xsd_float_cmp(d1, d2);
                }
                case xsd_XsdValue_xsd_float_val:
                {
                    __auto_type f2 = _mv_93.data.xsd_float_val;
                    return xsd_float_cmp(d1, ((double)(f2)));
                }
                case xsd_XsdValue_xsd_double_val:
                {
                    __auto_type d2 = _mv_93.data.xsd_double_val;
                    return xsd_float_cmp(d1, d2);
                }
                default: {
                    return xsd_XsdCompareResult_xsd_compare_incomparable;
                }
            }
        }
        case xsd_XsdValue_xsd_float_val:
        {
            __auto_type f1 = _mv_91.data.xsd_float_val;
            {
                __auto_type d1 = ((double)(f1));
                __auto_type _mv_94 = b;
                switch (_mv_94.tag) {
                    case xsd_XsdValue_xsd_integer_val:
                    {
                        __auto_type i2 = _mv_94.data.xsd_integer_val;
                        return xsd_float_cmp(d1, ((double)(i2)));
                    }
                    case xsd_XsdValue_xsd_decimal_val:
                    {
                        __auto_type d2 = _mv_94.data.xsd_decimal_val;
                        return xsd_float_cmp(d1, d2);
                    }
                    case xsd_XsdValue_xsd_float_val:
                    {
                        __auto_type f2 = _mv_94.data.xsd_float_val;
                        return xsd_float_cmp(d1, ((double)(f2)));
                    }
                    case xsd_XsdValue_xsd_double_val:
                    {
                        __auto_type d2 = _mv_94.data.xsd_double_val;
                        return xsd_float_cmp(d1, d2);
                    }
                    default: {
                        return xsd_XsdCompareResult_xsd_compare_incomparable;
                    }
                }
            }
        }
        case xsd_XsdValue_xsd_double_val:
        {
            __auto_type d1 = _mv_91.data.xsd_double_val;
            __auto_type _mv_95 = b;
            switch (_mv_95.tag) {
                case xsd_XsdValue_xsd_integer_val:
                {
                    __auto_type i2 = _mv_95.data.xsd_integer_val;
                    return xsd_float_cmp(d1, ((double)(i2)));
                }
                case xsd_XsdValue_xsd_decimal_val:
                {
                    __auto_type d2 = _mv_95.data.xsd_decimal_val;
                    return xsd_float_cmp(d1, d2);
                }
                case xsd_XsdValue_xsd_float_val:
                {
                    __auto_type f2 = _mv_95.data.xsd_float_val;
                    return xsd_float_cmp(d1, ((double)(f2)));
                }
                case xsd_XsdValue_xsd_double_val:
                {
                    __auto_type d2 = _mv_95.data.xsd_double_val;
                    return xsd_float_cmp(d1, d2);
                }
                default: {
                    return xsd_XsdCompareResult_xsd_compare_incomparable;
                }
            }
        }
        case xsd_XsdValue_xsd_string_val:
        {
            __auto_type s1 = _mv_91.data.xsd_string_val;
            __auto_type _mv_96 = b;
            switch (_mv_96.tag) {
                case xsd_XsdValue_xsd_string_val:
                {
                    __auto_type s2 = _mv_96.data.xsd_string_val;
                    if (string_eq(s1, s2)) {
                        return xsd_XsdCompareResult_xsd_compare_equal;
                    } else {
                        return xsd_XsdCompareResult_xsd_compare_incomparable;
                    }
                }
                default: {
                    return xsd_XsdCompareResult_xsd_compare_incomparable;
                }
            }
        }
        case xsd_XsdValue_xsd_boolean_val:
        {
            __auto_type b1 = _mv_91.data.xsd_boolean_val;
            __auto_type _mv_97 = b;
            switch (_mv_97.tag) {
                case xsd_XsdValue_xsd_boolean_val:
                {
                    __auto_type b2 = _mv_97.data.xsd_boolean_val;
                    if (b1 == b2) {
                        return xsd_XsdCompareResult_xsd_compare_equal;
                    } else {
                        if (b2) {
                            return xsd_XsdCompareResult_xsd_compare_less;
                        } else {
                            return xsd_XsdCompareResult_xsd_compare_greater;
                        }
                    }
                }
                default: {
                    return xsd_XsdCompareResult_xsd_compare_incomparable;
                }
            }
        }
        case xsd_XsdValue_xsd_unknown_val:
        {
            __auto_type _ = _mv_91.data.xsd_unknown_val;
            return xsd_XsdCompareResult_xsd_compare_incomparable;
        }
    }
}

xsd_XsdCompareResult xsd_compare(slop_arena* arena, rdf_Term a, rdf_Term b) {
    __auto_type _mv_98 = a;
    switch (_mv_98.tag) {
        case rdf_Term_term_literal:
        {
            __auto_type lit_a = _mv_98.data.term_literal;
            __auto_type _mv_99 = b;
            switch (_mv_99.tag) {
                case rdf_Term_term_literal:
                {
                    __auto_type lit_b = _mv_99.data.term_literal;
                    {
                        __auto_type dt_a = ({ __auto_type _mv = lit_a.datatype; _mv.has_value ? ({ __auto_type d = _mv.value; d; }) : (vocab_XSD_STRING); });
                        __auto_type dt_b = ({ __auto_type _mv = lit_b.datatype; _mv.has_value ? ({ __auto_type d = _mv.value; d; }) : (vocab_XSD_STRING); });
                        {
                            __auto_type type_a = xsd_parse_type(dt_a);
                            __auto_type type_b = xsd_parse_type(dt_b);
                            if (!(xsd_types_compatible(type_a, type_b))) {
                                return xsd_XsdCompareResult_xsd_compare_incomparable;
                            } else {
                                __auto_type _mv_100 = xsd_parse_value(arena, lit_a.value, type_a);
                                if (_mv_100.is_ok) {
                                    __auto_type val_a = _mv_100.data.ok;
                                    __auto_type _mv_101 = xsd_parse_value(arena, lit_b.value, type_b);
                                    if (_mv_101.is_ok) {
                                        __auto_type val_b = _mv_101.data.ok;
                                        return xsd_values_compare(val_a, val_b);
                                    } else if (!_mv_101.is_ok) {
                                        __auto_type _ = _mv_101.data.err;
                                        return xsd_XsdCompareResult_xsd_compare_incomparable;
                                    }
                                } else if (!_mv_100.is_ok) {
                                    __auto_type _ = _mv_100.data.err;
                                    return xsd_XsdCompareResult_xsd_compare_incomparable;
                                }
                            }
                        }
                    }
                }
                default: {
                    return xsd_XsdCompareResult_xsd_compare_incomparable;
                }
            }
        }
        default: {
            return xsd_XsdCompareResult_xsd_compare_incomparable;
        }
    }
}

