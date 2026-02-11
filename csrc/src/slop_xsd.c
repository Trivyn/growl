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
    __auto_type _mv_49 = dtype;
    switch (_mv_49) {
        case xsd_XsdType_xsd_string: {
            return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = true, .data.ok = ((xsd_XsdValue){ .tag = xsd_XsdValue_xsd_string_val, .data.xsd_string_val = lexical }) });
            break;
        }
        case xsd_XsdType_xsd_integer: {
            __auto_type _mv_50 = strlib_parse_int(lexical);
            if (_mv_50.is_ok) {
                __auto_type val = _mv_50.data.ok;
                return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = true, .data.ok = ((xsd_XsdValue){ .tag = xsd_XsdValue_xsd_integer_val, .data.xsd_integer_val = val }) });
            } else if (!_mv_50.is_ok) {
                __auto_type _ = _mv_50.data.err;
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
            __auto_type _mv_51 = strlib_parse_float(lexical);
            if (_mv_51.is_ok) {
                __auto_type val = _mv_51.data.ok;
                return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = true, .data.ok = ((xsd_XsdValue){ .tag = xsd_XsdValue_xsd_decimal_val, .data.xsd_decimal_val = val }) });
            } else if (!_mv_51.is_ok) {
                __auto_type _ = _mv_51.data.err;
                return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = false, .data.err = xsd_XsdError_invalid_lexical_form });
            }
            break;
        }
        case xsd_XsdType_xsd_float: {
            __auto_type _mv_52 = strlib_parse_float(lexical);
            if (_mv_52.is_ok) {
                __auto_type val = _mv_52.data.ok;
                return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = true, .data.ok = ((xsd_XsdValue){ .tag = xsd_XsdValue_xsd_float_val, .data.xsd_float_val = ((float)(val)) }) });
            } else if (!_mv_52.is_ok) {
                __auto_type _ = _mv_52.data.err;
                return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = false, .data.err = xsd_XsdError_invalid_lexical_form });
            }
            break;
        }
        case xsd_XsdType_xsd_double: {
            __auto_type _mv_53 = strlib_parse_float(lexical);
            if (_mv_53.is_ok) {
                __auto_type val = _mv_53.data.ok;
                return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = true, .data.ok = ((xsd_XsdValue){ .tag = xsd_XsdValue_xsd_double_val, .data.xsd_double_val = val }) });
            } else if (!_mv_53.is_ok) {
                __auto_type _ = _mv_53.data.err;
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
        __auto_type _mv_54 = strlib_parse_int(lexical);
        if (_mv_54.is_ok) {
            __auto_type _ = _mv_54.data.ok;
            return 1;
        } else if (!_mv_54.is_ok) {
            __auto_type _ = _mv_54.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_BOOLEAN)) {
        return ((string_eq(lexical, SLOP_STR("true"))) || (string_eq(lexical, SLOP_STR("false"))) || (string_eq(lexical, SLOP_STR("1"))) || (string_eq(lexical, SLOP_STR("0"))));
    } else if (string_eq(datatype_iri, vocab_XSD_DECIMAL)) {
        __auto_type _mv_55 = strlib_parse_float(lexical);
        if (_mv_55.is_ok) {
            __auto_type _ = _mv_55.data.ok;
            return 1;
        } else if (!_mv_55.is_ok) {
            __auto_type _ = _mv_55.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_FLOAT)) {
        __auto_type _mv_56 = strlib_parse_float(lexical);
        if (_mv_56.is_ok) {
            __auto_type _ = _mv_56.data.ok;
            return 1;
        } else if (!_mv_56.is_ok) {
            __auto_type _ = _mv_56.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_DOUBLE)) {
        __auto_type _mv_57 = strlib_parse_float(lexical);
        if (_mv_57.is_ok) {
            __auto_type _ = _mv_57.data.ok;
            return 1;
        } else if (!_mv_57.is_ok) {
            __auto_type _ = _mv_57.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_LONG)) {
        __auto_type _mv_58 = strlib_parse_int(lexical);
        if (_mv_58.is_ok) {
            __auto_type _ = _mv_58.data.ok;
            return 1;
        } else if (!_mv_58.is_ok) {
            __auto_type _ = _mv_58.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_INT)) {
        __auto_type _mv_59 = strlib_parse_int(lexical);
        if (_mv_59.is_ok) {
            __auto_type v = _mv_59.data.ok;
            return ((v >= -2147483648) && (v <= 2147483647));
        } else if (!_mv_59.is_ok) {
            __auto_type _ = _mv_59.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_SHORT)) {
        __auto_type _mv_60 = strlib_parse_int(lexical);
        if (_mv_60.is_ok) {
            __auto_type v = _mv_60.data.ok;
            return ((v >= -32768) && (v <= 32767));
        } else if (!_mv_60.is_ok) {
            __auto_type _ = _mv_60.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_BYTE)) {
        __auto_type _mv_61 = strlib_parse_int(lexical);
        if (_mv_61.is_ok) {
            __auto_type v = _mv_61.data.ok;
            return ((v >= -128) && (v <= 127));
        } else if (!_mv_61.is_ok) {
            __auto_type _ = _mv_61.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_UNSIGNED_LONG)) {
        __auto_type _mv_62 = strlib_parse_int(lexical);
        if (_mv_62.is_ok) {
            __auto_type v = _mv_62.data.ok;
            return (v >= 0);
        } else if (!_mv_62.is_ok) {
            __auto_type _ = _mv_62.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_UNSIGNED_INT)) {
        __auto_type _mv_63 = strlib_parse_int(lexical);
        if (_mv_63.is_ok) {
            __auto_type v = _mv_63.data.ok;
            return ((v >= 0) && (v <= 4294967295));
        } else if (!_mv_63.is_ok) {
            __auto_type _ = _mv_63.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_UNSIGNED_SHORT)) {
        __auto_type _mv_64 = strlib_parse_int(lexical);
        if (_mv_64.is_ok) {
            __auto_type v = _mv_64.data.ok;
            return ((v >= 0) && (v <= 65535));
        } else if (!_mv_64.is_ok) {
            __auto_type _ = _mv_64.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_UNSIGNED_BYTE)) {
        __auto_type _mv_65 = strlib_parse_int(lexical);
        if (_mv_65.is_ok) {
            __auto_type v = _mv_65.data.ok;
            return ((v >= 0) && (v <= 255));
        } else if (!_mv_65.is_ok) {
            __auto_type _ = _mv_65.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_NON_NEGATIVE_INTEGER)) {
        __auto_type _mv_66 = strlib_parse_int(lexical);
        if (_mv_66.is_ok) {
            __auto_type v = _mv_66.data.ok;
            return (v >= 0);
        } else if (!_mv_66.is_ok) {
            __auto_type _ = _mv_66.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_POSITIVE_INTEGER)) {
        __auto_type _mv_67 = strlib_parse_int(lexical);
        if (_mv_67.is_ok) {
            __auto_type v = _mv_67.data.ok;
            return (v >= 1);
        } else if (!_mv_67.is_ok) {
            __auto_type _ = _mv_67.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_NEGATIVE_INTEGER)) {
        __auto_type _mv_68 = strlib_parse_int(lexical);
        if (_mv_68.is_ok) {
            __auto_type v = _mv_68.data.ok;
            return (v <= -1);
        } else if (!_mv_68.is_ok) {
            __auto_type _ = _mv_68.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_XSD_NON_POSITIVE_INTEGER)) {
        __auto_type _mv_69 = strlib_parse_int(lexical);
        if (_mv_69.is_ok) {
            __auto_type v = _mv_69.data.ok;
            return (v <= 0);
        } else if (!_mv_69.is_ok) {
            __auto_type _ = _mv_69.data.err;
            return 0;
        }
    } else if (string_eq(datatype_iri, vocab_RDF_LANG_STRING)) {
        return 1;
    } else {
        return 1;
    }
}

uint8_t xsd_values_equal(xsd_XsdValue a, xsd_XsdValue b) {
    __auto_type _mv_70 = a;
    switch (_mv_70.tag) {
        case xsd_XsdValue_xsd_string_val:
        {
            __auto_type s1 = _mv_70.data.xsd_string_val;
            __auto_type _mv_71 = b;
            switch (_mv_71.tag) {
                case xsd_XsdValue_xsd_string_val:
                {
                    __auto_type s2 = _mv_71.data.xsd_string_val;
                    return string_eq(s1, s2);
                }
                default: {
                    return 0;
                }
            }
        }
        case xsd_XsdValue_xsd_integer_val:
        {
            __auto_type i1 = _mv_70.data.xsd_integer_val;
            __auto_type _mv_72 = b;
            switch (_mv_72.tag) {
                case xsd_XsdValue_xsd_integer_val:
                {
                    __auto_type i2 = _mv_72.data.xsd_integer_val;
                    return (i1 == i2);
                }
                case xsd_XsdValue_xsd_decimal_val:
                {
                    __auto_type d2 = _mv_72.data.xsd_decimal_val;
                    return (((double)(i1)) == d2);
                }
                case xsd_XsdValue_xsd_float_val:
                {
                    __auto_type f2 = _mv_72.data.xsd_float_val;
                    return (((double)(i1)) == ((double)(f2)));
                }
                case xsd_XsdValue_xsd_double_val:
                {
                    __auto_type d2 = _mv_72.data.xsd_double_val;
                    return (((double)(i1)) == d2);
                }
                default: {
                    return 0;
                }
            }
        }
        case xsd_XsdValue_xsd_decimal_val:
        {
            __auto_type d1 = _mv_70.data.xsd_decimal_val;
            __auto_type _mv_73 = b;
            switch (_mv_73.tag) {
                case xsd_XsdValue_xsd_integer_val:
                {
                    __auto_type i2 = _mv_73.data.xsd_integer_val;
                    return (d1 == ((double)(i2)));
                }
                case xsd_XsdValue_xsd_decimal_val:
                {
                    __auto_type d2 = _mv_73.data.xsd_decimal_val;
                    return (d1 == d2);
                }
                case xsd_XsdValue_xsd_float_val:
                {
                    __auto_type f2 = _mv_73.data.xsd_float_val;
                    return (d1 == ((double)(f2)));
                }
                case xsd_XsdValue_xsd_double_val:
                {
                    __auto_type d2 = _mv_73.data.xsd_double_val;
                    return (d1 == d2);
                }
                default: {
                    return 0;
                }
            }
        }
        case xsd_XsdValue_xsd_float_val:
        {
            __auto_type f1 = _mv_70.data.xsd_float_val;
            __auto_type _mv_74 = b;
            switch (_mv_74.tag) {
                case xsd_XsdValue_xsd_integer_val:
                {
                    __auto_type i2 = _mv_74.data.xsd_integer_val;
                    return (((double)(f1)) == ((double)(i2)));
                }
                case xsd_XsdValue_xsd_decimal_val:
                {
                    __auto_type d2 = _mv_74.data.xsd_decimal_val;
                    return (((double)(f1)) == d2);
                }
                case xsd_XsdValue_xsd_float_val:
                {
                    __auto_type f2 = _mv_74.data.xsd_float_val;
                    return (f1 == f2);
                }
                case xsd_XsdValue_xsd_double_val:
                {
                    __auto_type d2 = _mv_74.data.xsd_double_val;
                    return (((double)(f1)) == d2);
                }
                default: {
                    return 0;
                }
            }
        }
        case xsd_XsdValue_xsd_double_val:
        {
            __auto_type d1 = _mv_70.data.xsd_double_val;
            __auto_type _mv_75 = b;
            switch (_mv_75.tag) {
                case xsd_XsdValue_xsd_integer_val:
                {
                    __auto_type i2 = _mv_75.data.xsd_integer_val;
                    return (d1 == ((double)(i2)));
                }
                case xsd_XsdValue_xsd_decimal_val:
                {
                    __auto_type d2 = _mv_75.data.xsd_decimal_val;
                    return (d1 == d2);
                }
                case xsd_XsdValue_xsd_float_val:
                {
                    __auto_type f2 = _mv_75.data.xsd_float_val;
                    return (d1 == ((double)(f2)));
                }
                case xsd_XsdValue_xsd_double_val:
                {
                    __auto_type d2 = _mv_75.data.xsd_double_val;
                    return (d1 == d2);
                }
                default: {
                    return 0;
                }
            }
        }
        case xsd_XsdValue_xsd_boolean_val:
        {
            __auto_type b1 = _mv_70.data.xsd_boolean_val;
            __auto_type _mv_76 = b;
            switch (_mv_76.tag) {
                case xsd_XsdValue_xsd_boolean_val:
                {
                    __auto_type b2 = _mv_76.data.xsd_boolean_val;
                    return (b1 == b2);
                }
                default: {
                    return 0;
                }
            }
        }
        case xsd_XsdValue_xsd_unknown_val:
        {
            __auto_type u1 = _mv_70.data.xsd_unknown_val;
            __auto_type _mv_77 = b;
            switch (_mv_77.tag) {
                case xsd_XsdValue_xsd_unknown_val:
                {
                    __auto_type u2 = _mv_77.data.xsd_unknown_val;
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
    __auto_type _mv_78 = a.lang;
    if (_mv_78.has_value) {
        __auto_type lang_a = _mv_78.value;
        __auto_type _mv_79 = b.lang;
        if (_mv_79.has_value) {
            __auto_type lang_b = _mv_79.value;
            if (string_eq(lang_a, lang_b)) {
                return ((slop_result_u8_xsd_XsdError){ .is_ok = true, .data.ok = string_eq(a.value, b.value) });
            } else {
                return ((slop_result_u8_xsd_XsdError){ .is_ok = true, .data.ok = 0 });
            }
        } else if (!_mv_79.has_value) {
            return ((slop_result_u8_xsd_XsdError){ .is_ok = true, .data.ok = 0 });
        }
    } else if (!_mv_78.has_value) {
        __auto_type _mv_80 = a.datatype;
        if (_mv_80.has_value) {
            __auto_type dt_a = _mv_80.value;
            __auto_type _mv_81 = b.datatype;
            if (_mv_81.has_value) {
                __auto_type dt_b = _mv_81.value;
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
            } else if (!_mv_81.has_value) {
                return ((slop_result_u8_xsd_XsdError){ .is_ok = true, .data.ok = 0 });
            }
        } else if (!_mv_80.has_value) {
            __auto_type _mv_82 = b.datatype;
            if (_mv_82.has_value) {
                __auto_type dt_b = _mv_82.value;
                return ((slop_result_u8_xsd_XsdError){ .is_ok = true, .data.ok = 0 });
            } else if (!_mv_82.has_value) {
                return ((slop_result_u8_xsd_XsdError){ .is_ok = true, .data.ok = string_eq(a.value, b.value) });
            }
        }
    }
}

xsd_XsdCompareResult xsd_float_cmp(double a, double b) {
    if ((a < b)) {
        return xsd_XsdCompareResult_xsd_compare_less;
    } else {
        if ((a > b)) {
            return xsd_XsdCompareResult_xsd_compare_greater;
        } else {
            return xsd_XsdCompareResult_xsd_compare_equal;
        }
    }
}

xsd_XsdCompareResult xsd_values_compare(xsd_XsdValue a, xsd_XsdValue b) {
    __auto_type _mv_83 = a;
    switch (_mv_83.tag) {
        case xsd_XsdValue_xsd_integer_val:
        {
            __auto_type i1 = _mv_83.data.xsd_integer_val;
            {
                __auto_type d1 = ((double)(i1));
                __auto_type _mv_84 = b;
                switch (_mv_84.tag) {
                    case xsd_XsdValue_xsd_integer_val:
                    {
                        __auto_type i2 = _mv_84.data.xsd_integer_val;
                        return xsd_float_cmp(d1, ((double)(i2)));
                    }
                    case xsd_XsdValue_xsd_decimal_val:
                    {
                        __auto_type d2 = _mv_84.data.xsd_decimal_val;
                        return xsd_float_cmp(d1, d2);
                    }
                    case xsd_XsdValue_xsd_float_val:
                    {
                        __auto_type f2 = _mv_84.data.xsd_float_val;
                        return xsd_float_cmp(d1, ((double)(f2)));
                    }
                    case xsd_XsdValue_xsd_double_val:
                    {
                        __auto_type d2 = _mv_84.data.xsd_double_val;
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
            __auto_type d1 = _mv_83.data.xsd_decimal_val;
            __auto_type _mv_85 = b;
            switch (_mv_85.tag) {
                case xsd_XsdValue_xsd_integer_val:
                {
                    __auto_type i2 = _mv_85.data.xsd_integer_val;
                    return xsd_float_cmp(d1, ((double)(i2)));
                }
                case xsd_XsdValue_xsd_decimal_val:
                {
                    __auto_type d2 = _mv_85.data.xsd_decimal_val;
                    return xsd_float_cmp(d1, d2);
                }
                case xsd_XsdValue_xsd_float_val:
                {
                    __auto_type f2 = _mv_85.data.xsd_float_val;
                    return xsd_float_cmp(d1, ((double)(f2)));
                }
                case xsd_XsdValue_xsd_double_val:
                {
                    __auto_type d2 = _mv_85.data.xsd_double_val;
                    return xsd_float_cmp(d1, d2);
                }
                default: {
                    return xsd_XsdCompareResult_xsd_compare_incomparable;
                }
            }
        }
        case xsd_XsdValue_xsd_float_val:
        {
            __auto_type f1 = _mv_83.data.xsd_float_val;
            {
                __auto_type d1 = ((double)(f1));
                __auto_type _mv_86 = b;
                switch (_mv_86.tag) {
                    case xsd_XsdValue_xsd_integer_val:
                    {
                        __auto_type i2 = _mv_86.data.xsd_integer_val;
                        return xsd_float_cmp(d1, ((double)(i2)));
                    }
                    case xsd_XsdValue_xsd_decimal_val:
                    {
                        __auto_type d2 = _mv_86.data.xsd_decimal_val;
                        return xsd_float_cmp(d1, d2);
                    }
                    case xsd_XsdValue_xsd_float_val:
                    {
                        __auto_type f2 = _mv_86.data.xsd_float_val;
                        return xsd_float_cmp(d1, ((double)(f2)));
                    }
                    case xsd_XsdValue_xsd_double_val:
                    {
                        __auto_type d2 = _mv_86.data.xsd_double_val;
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
            __auto_type d1 = _mv_83.data.xsd_double_val;
            __auto_type _mv_87 = b;
            switch (_mv_87.tag) {
                case xsd_XsdValue_xsd_integer_val:
                {
                    __auto_type i2 = _mv_87.data.xsd_integer_val;
                    return xsd_float_cmp(d1, ((double)(i2)));
                }
                case xsd_XsdValue_xsd_decimal_val:
                {
                    __auto_type d2 = _mv_87.data.xsd_decimal_val;
                    return xsd_float_cmp(d1, d2);
                }
                case xsd_XsdValue_xsd_float_val:
                {
                    __auto_type f2 = _mv_87.data.xsd_float_val;
                    return xsd_float_cmp(d1, ((double)(f2)));
                }
                case xsd_XsdValue_xsd_double_val:
                {
                    __auto_type d2 = _mv_87.data.xsd_double_val;
                    return xsd_float_cmp(d1, d2);
                }
                default: {
                    return xsd_XsdCompareResult_xsd_compare_incomparable;
                }
            }
        }
        case xsd_XsdValue_xsd_string_val:
        {
            __auto_type s1 = _mv_83.data.xsd_string_val;
            __auto_type _mv_88 = b;
            switch (_mv_88.tag) {
                case xsd_XsdValue_xsd_string_val:
                {
                    __auto_type s2 = _mv_88.data.xsd_string_val;
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
            __auto_type b1 = _mv_83.data.xsd_boolean_val;
            __auto_type _mv_89 = b;
            switch (_mv_89.tag) {
                case xsd_XsdValue_xsd_boolean_val:
                {
                    __auto_type b2 = _mv_89.data.xsd_boolean_val;
                    if ((b1 == b2)) {
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
            __auto_type _ = _mv_83.data.xsd_unknown_val;
            return xsd_XsdCompareResult_xsd_compare_incomparable;
        }
    }
}

xsd_XsdCompareResult xsd_compare(slop_arena* arena, rdf_Term a, rdf_Term b) {
    __auto_type _mv_90 = a;
    switch (_mv_90.tag) {
        case rdf_Term_term_literal:
        {
            __auto_type lit_a = _mv_90.data.term_literal;
            __auto_type _mv_91 = b;
            switch (_mv_91.tag) {
                case rdf_Term_term_literal:
                {
                    __auto_type lit_b = _mv_91.data.term_literal;
                    {
                        __auto_type dt_a = ({ __auto_type _mv = lit_a.datatype; _mv.has_value ? ({ __auto_type d = _mv.value; d; }) : (vocab_XSD_STRING); });
                        __auto_type dt_b = ({ __auto_type _mv = lit_b.datatype; _mv.has_value ? ({ __auto_type d = _mv.value; d; }) : (vocab_XSD_STRING); });
                        {
                            __auto_type type_a = xsd_parse_type(dt_a);
                            __auto_type type_b = xsd_parse_type(dt_b);
                            if (!(xsd_types_compatible(type_a, type_b))) {
                                return xsd_XsdCompareResult_xsd_compare_incomparable;
                            } else {
                                __auto_type _mv_92 = xsd_parse_value(arena, lit_a.value, type_a);
                                if (_mv_92.is_ok) {
                                    __auto_type val_a = _mv_92.data.ok;
                                    __auto_type _mv_93 = xsd_parse_value(arena, lit_b.value, type_b);
                                    if (_mv_93.is_ok) {
                                        __auto_type val_b = _mv_93.data.ok;
                                        return xsd_values_compare(val_a, val_b);
                                    } else if (!_mv_93.is_ok) {
                                        __auto_type _ = _mv_93.data.err;
                                        return xsd_XsdCompareResult_xsd_compare_incomparable;
                                    }
                                } else if (!_mv_92.is_ok) {
                                    __auto_type _ = _mv_92.data.err;
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

