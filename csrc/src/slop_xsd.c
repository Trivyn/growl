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
    __auto_type _mv_120 = dtype;
    switch (_mv_120) {
        case xsd_XsdType_xsd_string: {
            return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = true, .data.ok = ((xsd_XsdValue){ .tag = xsd_XsdValue_xsd_string_val, .data.xsd_string_val = lexical }) });
            break;
        }
        case xsd_XsdType_xsd_integer: {
            __auto_type _mv_121 = strlib_parse_int(lexical);
            if (_mv_121.is_ok) {
                __auto_type val = _mv_121.data.ok;
                return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = true, .data.ok = ((xsd_XsdValue){ .tag = xsd_XsdValue_xsd_integer_val, .data.xsd_integer_val = val }) });
            } else if (!_mv_121.is_ok) {
                __auto_type _ = _mv_121.data.err;
                return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = false, .data.err = xsd_XsdError_invalid_lexical_form });
            }
            SLOP_UNREACHABLE();
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
            __auto_type _mv_122 = strlib_parse_float(lexical);
            if (_mv_122.is_ok) {
                __auto_type val = _mv_122.data.ok;
                return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = true, .data.ok = ((xsd_XsdValue){ .tag = xsd_XsdValue_xsd_decimal_val, .data.xsd_decimal_val = val }) });
            } else if (!_mv_122.is_ok) {
                __auto_type _ = _mv_122.data.err;
                return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = false, .data.err = xsd_XsdError_invalid_lexical_form });
            }
            SLOP_UNREACHABLE();
            break;
        }
        case xsd_XsdType_xsd_float: {
            __auto_type _mv_123 = strlib_parse_float(lexical);
            if (_mv_123.is_ok) {
                __auto_type val = _mv_123.data.ok;
                return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = true, .data.ok = ((xsd_XsdValue){ .tag = xsd_XsdValue_xsd_float_val, .data.xsd_float_val = ((float)(val)) }) });
            } else if (!_mv_123.is_ok) {
                __auto_type _ = _mv_123.data.err;
                return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = false, .data.err = xsd_XsdError_invalid_lexical_form });
            }
            SLOP_UNREACHABLE();
            break;
        }
        case xsd_XsdType_xsd_double: {
            __auto_type _mv_124 = strlib_parse_float(lexical);
            if (_mv_124.is_ok) {
                __auto_type val = _mv_124.data.ok;
                return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = true, .data.ok = ((xsd_XsdValue){ .tag = xsd_XsdValue_xsd_double_val, .data.xsd_double_val = val }) });
            } else if (!_mv_124.is_ok) {
                __auto_type _ = _mv_124.data.err;
                return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = false, .data.err = xsd_XsdError_invalid_lexical_form });
            }
            SLOP_UNREACHABLE();
            break;
        }
        case xsd_XsdType_xsd_unknown: {
            return ((slop_result_xsd_XsdValue_xsd_XsdError){ .is_ok = true, .data.ok = ((xsd_XsdValue){ .tag = xsd_XsdValue_xsd_unknown_val, .data.xsd_unknown_val = lexical }) });
            break;
        }
    }
    SLOP_UNREACHABLE();
}

uint8_t xsd_validate_lexical(slop_string lexical, slop_string datatype_iri) {
    if (string_eq(datatype_iri, vocab_XSD_STRING)) {
        return 1;
    } else if (string_eq(datatype_iri, vocab_XSD_INTEGER)) {
        __auto_type _mv_125 = strlib_parse_int(lexical);
        if (_mv_125.is_ok) {
            __auto_type _ = _mv_125.data.ok;
            return 1;
        } else if (!_mv_125.is_ok) {
            __auto_type _ = _mv_125.data.err;
            return 0;
        }
        SLOP_UNREACHABLE();
    } else if (string_eq(datatype_iri, vocab_XSD_BOOLEAN)) {
        return ((string_eq(lexical, SLOP_STR("true"))) || (string_eq(lexical, SLOP_STR("false"))) || (string_eq(lexical, SLOP_STR("1"))) || (string_eq(lexical, SLOP_STR("0"))));
    } else if (string_eq(datatype_iri, vocab_XSD_DECIMAL)) {
        __auto_type _mv_126 = strlib_parse_float(lexical);
        if (_mv_126.is_ok) {
            __auto_type _ = _mv_126.data.ok;
            return 1;
        } else if (!_mv_126.is_ok) {
            __auto_type _ = _mv_126.data.err;
            return 0;
        }
        SLOP_UNREACHABLE();
    } else if (string_eq(datatype_iri, vocab_XSD_FLOAT)) {
        __auto_type _mv_127 = strlib_parse_float(lexical);
        if (_mv_127.is_ok) {
            __auto_type _ = _mv_127.data.ok;
            return 1;
        } else if (!_mv_127.is_ok) {
            __auto_type _ = _mv_127.data.err;
            return 0;
        }
        SLOP_UNREACHABLE();
    } else if (string_eq(datatype_iri, vocab_XSD_DOUBLE)) {
        __auto_type _mv_128 = strlib_parse_float(lexical);
        if (_mv_128.is_ok) {
            __auto_type _ = _mv_128.data.ok;
            return 1;
        } else if (!_mv_128.is_ok) {
            __auto_type _ = _mv_128.data.err;
            return 0;
        }
        SLOP_UNREACHABLE();
    } else if (string_eq(datatype_iri, vocab_XSD_LONG)) {
        __auto_type _mv_129 = strlib_parse_int(lexical);
        if (_mv_129.is_ok) {
            __auto_type _ = _mv_129.data.ok;
            return 1;
        } else if (!_mv_129.is_ok) {
            __auto_type _ = _mv_129.data.err;
            return 0;
        }
        SLOP_UNREACHABLE();
    } else if (string_eq(datatype_iri, vocab_XSD_INT)) {
        __auto_type _mv_130 = strlib_parse_int(lexical);
        if (_mv_130.is_ok) {
            __auto_type v = _mv_130.data.ok;
            return ((v >= -2147483648) && (v <= 2147483647));
        } else if (!_mv_130.is_ok) {
            __auto_type _ = _mv_130.data.err;
            return 0;
        }
        SLOP_UNREACHABLE();
    } else if (string_eq(datatype_iri, vocab_XSD_SHORT)) {
        __auto_type _mv_131 = strlib_parse_int(lexical);
        if (_mv_131.is_ok) {
            __auto_type v = _mv_131.data.ok;
            return ((v >= -32768) && (v <= 32767));
        } else if (!_mv_131.is_ok) {
            __auto_type _ = _mv_131.data.err;
            return 0;
        }
        SLOP_UNREACHABLE();
    } else if (string_eq(datatype_iri, vocab_XSD_BYTE)) {
        __auto_type _mv_132 = strlib_parse_int(lexical);
        if (_mv_132.is_ok) {
            __auto_type v = _mv_132.data.ok;
            return ((v >= -128) && (v <= 127));
        } else if (!_mv_132.is_ok) {
            __auto_type _ = _mv_132.data.err;
            return 0;
        }
        SLOP_UNREACHABLE();
    } else if (string_eq(datatype_iri, vocab_XSD_UNSIGNED_LONG)) {
        __auto_type _mv_133 = strlib_parse_int(lexical);
        if (_mv_133.is_ok) {
            __auto_type v = _mv_133.data.ok;
            return (v >= 0);
        } else if (!_mv_133.is_ok) {
            __auto_type _ = _mv_133.data.err;
            return 0;
        }
        SLOP_UNREACHABLE();
    } else if (string_eq(datatype_iri, vocab_XSD_UNSIGNED_INT)) {
        __auto_type _mv_134 = strlib_parse_int(lexical);
        if (_mv_134.is_ok) {
            __auto_type v = _mv_134.data.ok;
            return ((v >= 0) && (v <= 4294967295));
        } else if (!_mv_134.is_ok) {
            __auto_type _ = _mv_134.data.err;
            return 0;
        }
        SLOP_UNREACHABLE();
    } else if (string_eq(datatype_iri, vocab_XSD_UNSIGNED_SHORT)) {
        __auto_type _mv_135 = strlib_parse_int(lexical);
        if (_mv_135.is_ok) {
            __auto_type v = _mv_135.data.ok;
            return ((v >= 0) && (v <= 65535));
        } else if (!_mv_135.is_ok) {
            __auto_type _ = _mv_135.data.err;
            return 0;
        }
        SLOP_UNREACHABLE();
    } else if (string_eq(datatype_iri, vocab_XSD_UNSIGNED_BYTE)) {
        __auto_type _mv_136 = strlib_parse_int(lexical);
        if (_mv_136.is_ok) {
            __auto_type v = _mv_136.data.ok;
            return ((v >= 0) && (v <= 255));
        } else if (!_mv_136.is_ok) {
            __auto_type _ = _mv_136.data.err;
            return 0;
        }
        SLOP_UNREACHABLE();
    } else if (string_eq(datatype_iri, vocab_XSD_NON_NEGATIVE_INTEGER)) {
        __auto_type _mv_137 = strlib_parse_int(lexical);
        if (_mv_137.is_ok) {
            __auto_type v = _mv_137.data.ok;
            return (v >= 0);
        } else if (!_mv_137.is_ok) {
            __auto_type _ = _mv_137.data.err;
            return 0;
        }
        SLOP_UNREACHABLE();
    } else if (string_eq(datatype_iri, vocab_XSD_POSITIVE_INTEGER)) {
        __auto_type _mv_138 = strlib_parse_int(lexical);
        if (_mv_138.is_ok) {
            __auto_type v = _mv_138.data.ok;
            return (v >= 1);
        } else if (!_mv_138.is_ok) {
            __auto_type _ = _mv_138.data.err;
            return 0;
        }
        SLOP_UNREACHABLE();
    } else if (string_eq(datatype_iri, vocab_XSD_NEGATIVE_INTEGER)) {
        __auto_type _mv_139 = strlib_parse_int(lexical);
        if (_mv_139.is_ok) {
            __auto_type v = _mv_139.data.ok;
            return (v <= -1);
        } else if (!_mv_139.is_ok) {
            __auto_type _ = _mv_139.data.err;
            return 0;
        }
        SLOP_UNREACHABLE();
    } else if (string_eq(datatype_iri, vocab_XSD_NON_POSITIVE_INTEGER)) {
        __auto_type _mv_140 = strlib_parse_int(lexical);
        if (_mv_140.is_ok) {
            __auto_type v = _mv_140.data.ok;
            return (v <= 0);
        } else if (!_mv_140.is_ok) {
            __auto_type _ = _mv_140.data.err;
            return 0;
        }
        SLOP_UNREACHABLE();
    } else if (string_eq(datatype_iri, vocab_RDF_LANG_STRING)) {
        return 1;
    } else {
        return 1;
    }
}

uint8_t xsd_values_equal(xsd_XsdValue a, xsd_XsdValue b) {
    __auto_type _mv_141 = a;
    switch (_mv_141.tag) {
        case xsd_XsdValue_xsd_string_val:
        {
            __auto_type s1 = _mv_141.data.xsd_string_val;
            __auto_type _mv_142 = b;
            switch (_mv_142.tag) {
                case xsd_XsdValue_xsd_string_val:
                {
                    __auto_type s2 = _mv_142.data.xsd_string_val;
                    return string_eq(s1, s2);
                }
                default: {
                    return 0;
                }
            }
        }
        case xsd_XsdValue_xsd_integer_val:
        {
            __auto_type i1 = _mv_141.data.xsd_integer_val;
            __auto_type _mv_143 = b;
            switch (_mv_143.tag) {
                case xsd_XsdValue_xsd_integer_val:
                {
                    __auto_type i2 = _mv_143.data.xsd_integer_val;
                    return (i1 == i2);
                }
                case xsd_XsdValue_xsd_decimal_val:
                {
                    __auto_type d2 = _mv_143.data.xsd_decimal_val;
                    return (((double)(i1)) == d2);
                }
                case xsd_XsdValue_xsd_float_val:
                {
                    __auto_type f2 = _mv_143.data.xsd_float_val;
                    return (((double)(i1)) == ((double)(f2)));
                }
                case xsd_XsdValue_xsd_double_val:
                {
                    __auto_type d2 = _mv_143.data.xsd_double_val;
                    return (((double)(i1)) == d2);
                }
                default: {
                    return 0;
                }
            }
        }
        case xsd_XsdValue_xsd_decimal_val:
        {
            __auto_type d1 = _mv_141.data.xsd_decimal_val;
            __auto_type _mv_144 = b;
            switch (_mv_144.tag) {
                case xsd_XsdValue_xsd_integer_val:
                {
                    __auto_type i2 = _mv_144.data.xsd_integer_val;
                    return (d1 == ((double)(i2)));
                }
                case xsd_XsdValue_xsd_decimal_val:
                {
                    __auto_type d2 = _mv_144.data.xsd_decimal_val;
                    return (d1 == d2);
                }
                case xsd_XsdValue_xsd_float_val:
                {
                    __auto_type f2 = _mv_144.data.xsd_float_val;
                    return (d1 == ((double)(f2)));
                }
                case xsd_XsdValue_xsd_double_val:
                {
                    __auto_type d2 = _mv_144.data.xsd_double_val;
                    return (d1 == d2);
                }
                default: {
                    return 0;
                }
            }
        }
        case xsd_XsdValue_xsd_float_val:
        {
            __auto_type f1 = _mv_141.data.xsd_float_val;
            __auto_type _mv_145 = b;
            switch (_mv_145.tag) {
                case xsd_XsdValue_xsd_integer_val:
                {
                    __auto_type i2 = _mv_145.data.xsd_integer_val;
                    return (((double)(f1)) == ((double)(i2)));
                }
                case xsd_XsdValue_xsd_decimal_val:
                {
                    __auto_type d2 = _mv_145.data.xsd_decimal_val;
                    return (((double)(f1)) == d2);
                }
                case xsd_XsdValue_xsd_float_val:
                {
                    __auto_type f2 = _mv_145.data.xsd_float_val;
                    return (f1 == f2);
                }
                case xsd_XsdValue_xsd_double_val:
                {
                    __auto_type d2 = _mv_145.data.xsd_double_val;
                    return (((double)(f1)) == d2);
                }
                default: {
                    return 0;
                }
            }
        }
        case xsd_XsdValue_xsd_double_val:
        {
            __auto_type d1 = _mv_141.data.xsd_double_val;
            __auto_type _mv_146 = b;
            switch (_mv_146.tag) {
                case xsd_XsdValue_xsd_integer_val:
                {
                    __auto_type i2 = _mv_146.data.xsd_integer_val;
                    return (d1 == ((double)(i2)));
                }
                case xsd_XsdValue_xsd_decimal_val:
                {
                    __auto_type d2 = _mv_146.data.xsd_decimal_val;
                    return (d1 == d2);
                }
                case xsd_XsdValue_xsd_float_val:
                {
                    __auto_type f2 = _mv_146.data.xsd_float_val;
                    return (d1 == ((double)(f2)));
                }
                case xsd_XsdValue_xsd_double_val:
                {
                    __auto_type d2 = _mv_146.data.xsd_double_val;
                    return (d1 == d2);
                }
                default: {
                    return 0;
                }
            }
        }
        case xsd_XsdValue_xsd_boolean_val:
        {
            __auto_type b1 = _mv_141.data.xsd_boolean_val;
            __auto_type _mv_147 = b;
            switch (_mv_147.tag) {
                case xsd_XsdValue_xsd_boolean_val:
                {
                    __auto_type b2 = _mv_147.data.xsd_boolean_val;
                    return (b1 == b2);
                }
                default: {
                    return 0;
                }
            }
        }
        case xsd_XsdValue_xsd_unknown_val:
        {
            __auto_type u1 = _mv_141.data.xsd_unknown_val;
            __auto_type _mv_148 = b;
            switch (_mv_148.tag) {
                case xsd_XsdValue_xsd_unknown_val:
                {
                    __auto_type u2 = _mv_148.data.xsd_unknown_val;
                    return string_eq(u1, u2);
                }
                default: {
                    return 0;
                }
            }
        }
    }
    SLOP_UNREACHABLE();
}

uint8_t xsd_types_compatible(xsd_XsdType t1, xsd_XsdType t2) {
    return ((t1 == t2) || ((((t1 == xsd_XsdType_xsd_integer)) || ((t1 == xsd_XsdType_xsd_decimal)) || ((t1 == xsd_XsdType_xsd_float)) || ((t1 == xsd_XsdType_xsd_double))) && (((t2 == xsd_XsdType_xsd_integer)) || ((t2 == xsd_XsdType_xsd_decimal)) || ((t2 == xsd_XsdType_xsd_float)) || ((t2 == xsd_XsdType_xsd_double)))));
}

slop_result_u8_xsd_XsdError xsd_literal_values_equal(slop_arena* arena, rdf_Literal a, rdf_Literal b) {
    __auto_type _mv_149 = a.lang;
    if (_mv_149.has_value) {
        __auto_type lang_a = _mv_149.value;
        __auto_type _mv_150 = b.lang;
        if (_mv_150.has_value) {
            __auto_type lang_b = _mv_150.value;
            if (string_eq(lang_a, lang_b)) {
                return ((slop_result_u8_xsd_XsdError){ .is_ok = true, .data.ok = string_eq(a.value, b.value) });
            } else {
                return ((slop_result_u8_xsd_XsdError){ .is_ok = true, .data.ok = 0 });
            }
        } else if (!_mv_150.has_value) {
            return ((slop_result_u8_xsd_XsdError){ .is_ok = true, .data.ok = 0 });
        }
        SLOP_UNREACHABLE();
    } else if (!_mv_149.has_value) {
        __auto_type _mv_151 = a.datatype;
        if (_mv_151.has_value) {
            __auto_type dt_a = _mv_151.value;
            __auto_type _mv_152 = b.datatype;
            if (_mv_152.has_value) {
                __auto_type dt_b = _mv_152.value;
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
            } else if (!_mv_152.has_value) {
                return ((slop_result_u8_xsd_XsdError){ .is_ok = true, .data.ok = 0 });
            }
            SLOP_UNREACHABLE();
        } else if (!_mv_151.has_value) {
            __auto_type _mv_153 = b.datatype;
            if (_mv_153.has_value) {
                __auto_type dt_b = _mv_153.value;
                return ((slop_result_u8_xsd_XsdError){ .is_ok = true, .data.ok = 0 });
            } else if (!_mv_153.has_value) {
                return ((slop_result_u8_xsd_XsdError){ .is_ok = true, .data.ok = string_eq(a.value, b.value) });
            }
            SLOP_UNREACHABLE();
        }
        SLOP_UNREACHABLE();
    }
    SLOP_UNREACHABLE();
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
    __auto_type _mv_154 = a;
    switch (_mv_154.tag) {
        case xsd_XsdValue_xsd_integer_val:
        {
            __auto_type i1 = _mv_154.data.xsd_integer_val;
            {
                __auto_type d1 = ((double)(i1));
                __auto_type _mv_155 = b;
                switch (_mv_155.tag) {
                    case xsd_XsdValue_xsd_integer_val:
                    {
                        __auto_type i2 = _mv_155.data.xsd_integer_val;
                        return xsd_float_cmp(d1, ((double)(i2)));
                    }
                    case xsd_XsdValue_xsd_decimal_val:
                    {
                        __auto_type d2 = _mv_155.data.xsd_decimal_val;
                        return xsd_float_cmp(d1, d2);
                    }
                    case xsd_XsdValue_xsd_float_val:
                    {
                        __auto_type f2 = _mv_155.data.xsd_float_val;
                        return xsd_float_cmp(d1, ((double)(f2)));
                    }
                    case xsd_XsdValue_xsd_double_val:
                    {
                        __auto_type d2 = _mv_155.data.xsd_double_val;
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
            __auto_type d1 = _mv_154.data.xsd_decimal_val;
            __auto_type _mv_156 = b;
            switch (_mv_156.tag) {
                case xsd_XsdValue_xsd_integer_val:
                {
                    __auto_type i2 = _mv_156.data.xsd_integer_val;
                    return xsd_float_cmp(d1, ((double)(i2)));
                }
                case xsd_XsdValue_xsd_decimal_val:
                {
                    __auto_type d2 = _mv_156.data.xsd_decimal_val;
                    return xsd_float_cmp(d1, d2);
                }
                case xsd_XsdValue_xsd_float_val:
                {
                    __auto_type f2 = _mv_156.data.xsd_float_val;
                    return xsd_float_cmp(d1, ((double)(f2)));
                }
                case xsd_XsdValue_xsd_double_val:
                {
                    __auto_type d2 = _mv_156.data.xsd_double_val;
                    return xsd_float_cmp(d1, d2);
                }
                default: {
                    return xsd_XsdCompareResult_xsd_compare_incomparable;
                }
            }
        }
        case xsd_XsdValue_xsd_float_val:
        {
            __auto_type f1 = _mv_154.data.xsd_float_val;
            {
                __auto_type d1 = ((double)(f1));
                __auto_type _mv_157 = b;
                switch (_mv_157.tag) {
                    case xsd_XsdValue_xsd_integer_val:
                    {
                        __auto_type i2 = _mv_157.data.xsd_integer_val;
                        return xsd_float_cmp(d1, ((double)(i2)));
                    }
                    case xsd_XsdValue_xsd_decimal_val:
                    {
                        __auto_type d2 = _mv_157.data.xsd_decimal_val;
                        return xsd_float_cmp(d1, d2);
                    }
                    case xsd_XsdValue_xsd_float_val:
                    {
                        __auto_type f2 = _mv_157.data.xsd_float_val;
                        return xsd_float_cmp(d1, ((double)(f2)));
                    }
                    case xsd_XsdValue_xsd_double_val:
                    {
                        __auto_type d2 = _mv_157.data.xsd_double_val;
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
            __auto_type d1 = _mv_154.data.xsd_double_val;
            __auto_type _mv_158 = b;
            switch (_mv_158.tag) {
                case xsd_XsdValue_xsd_integer_val:
                {
                    __auto_type i2 = _mv_158.data.xsd_integer_val;
                    return xsd_float_cmp(d1, ((double)(i2)));
                }
                case xsd_XsdValue_xsd_decimal_val:
                {
                    __auto_type d2 = _mv_158.data.xsd_decimal_val;
                    return xsd_float_cmp(d1, d2);
                }
                case xsd_XsdValue_xsd_float_val:
                {
                    __auto_type f2 = _mv_158.data.xsd_float_val;
                    return xsd_float_cmp(d1, ((double)(f2)));
                }
                case xsd_XsdValue_xsd_double_val:
                {
                    __auto_type d2 = _mv_158.data.xsd_double_val;
                    return xsd_float_cmp(d1, d2);
                }
                default: {
                    return xsd_XsdCompareResult_xsd_compare_incomparable;
                }
            }
        }
        case xsd_XsdValue_xsd_string_val:
        {
            __auto_type s1 = _mv_154.data.xsd_string_val;
            __auto_type _mv_159 = b;
            switch (_mv_159.tag) {
                case xsd_XsdValue_xsd_string_val:
                {
                    __auto_type s2 = _mv_159.data.xsd_string_val;
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
            __auto_type b1 = _mv_154.data.xsd_boolean_val;
            __auto_type _mv_160 = b;
            switch (_mv_160.tag) {
                case xsd_XsdValue_xsd_boolean_val:
                {
                    __auto_type b2 = _mv_160.data.xsd_boolean_val;
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
            __auto_type _ = _mv_154.data.xsd_unknown_val;
            return xsd_XsdCompareResult_xsd_compare_incomparable;
        }
    }
    SLOP_UNREACHABLE();
}

xsd_XsdCompareResult xsd_compare(slop_arena* arena, rdf_Term a, rdf_Term b) {
    __auto_type _mv_161 = a;
    switch (_mv_161.tag) {
        case rdf_Term_term_literal:
        {
            __auto_type lit_a = _mv_161.data.term_literal;
            __auto_type _mv_162 = b;
            switch (_mv_162.tag) {
                case rdf_Term_term_literal:
                {
                    __auto_type lit_b = _mv_162.data.term_literal;
                    {
                        __auto_type dt_a = ({ __auto_type _mv = lit_a.datatype; _mv.has_value ? ({ __auto_type d = _mv.value; d; }) : (vocab_XSD_STRING); });
                        __auto_type dt_b = ({ __auto_type _mv = lit_b.datatype; _mv.has_value ? ({ __auto_type d = _mv.value; d; }) : (vocab_XSD_STRING); });
                        {
                            __auto_type type_a = xsd_parse_type(dt_a);
                            __auto_type type_b = xsd_parse_type(dt_b);
                            if (!(xsd_types_compatible(type_a, type_b))) {
                                return xsd_XsdCompareResult_xsd_compare_incomparable;
                            } else {
                                __auto_type _mv_163 = xsd_parse_value(arena, lit_a.value, type_a);
                                if (_mv_163.is_ok) {
                                    __auto_type val_a = _mv_163.data.ok;
                                    __auto_type _mv_164 = xsd_parse_value(arena, lit_b.value, type_b);
                                    if (_mv_164.is_ok) {
                                        __auto_type val_b = _mv_164.data.ok;
                                        return xsd_values_compare(val_a, val_b);
                                    } else if (!_mv_164.is_ok) {
                                        __auto_type _ = _mv_164.data.err;
                                        return xsd_XsdCompareResult_xsd_compare_incomparable;
                                    }
                                    SLOP_UNREACHABLE();
                                } else if (!_mv_163.is_ok) {
                                    __auto_type _ = _mv_163.data.err;
                                    return xsd_XsdCompareResult_xsd_compare_incomparable;
                                }
                                SLOP_UNREACHABLE();
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

