#ifndef SLOP_xsd_H
#define SLOP_xsd_H

#include "../runtime/slop_runtime.h"
#include <stdint.h>
#include <stdbool.h>
#include "slop_rdf.h"
#include "slop_strlib.h"
#include "slop_vocab.h"

typedef struct xsd_XsdValue xsd_XsdValue;

typedef enum {
    xsd_XsdType_xsd_string,
    xsd_XsdType_xsd_integer,
    xsd_XsdType_xsd_decimal,
    xsd_XsdType_xsd_float,
    xsd_XsdType_xsd_double,
    xsd_XsdType_xsd_boolean,
    xsd_XsdType_xsd_unknown
} xsd_XsdType;

typedef enum {
    xsd_XsdError_invalid_lexical_form,
    xsd_XsdError_unsupported_datatype,
    xsd_XsdError_type_mismatch
} xsd_XsdError;

typedef enum {
    xsd_XsdCompareResult_xsd_compare_less,
    xsd_XsdCompareResult_xsd_compare_equal,
    xsd_XsdCompareResult_xsd_compare_greater,
    xsd_XsdCompareResult_xsd_compare_incomparable
} xsd_XsdCompareResult;

typedef enum {
    xsd_XsdValue_xsd_string_val,
    xsd_XsdValue_xsd_integer_val,
    xsd_XsdValue_xsd_decimal_val,
    xsd_XsdValue_xsd_float_val,
    xsd_XsdValue_xsd_double_val,
    xsd_XsdValue_xsd_boolean_val,
    xsd_XsdValue_xsd_unknown_val
} xsd_XsdValue_tag;

struct xsd_XsdValue {
    xsd_XsdValue_tag tag;
    union {
        slop_string xsd_string_val;
        int64_t xsd_integer_val;
        double xsd_decimal_val;
        float xsd_float_val;
        double xsd_double_val;
        uint8_t xsd_boolean_val;
        slop_string xsd_unknown_val;
    } data;
};
typedef struct xsd_XsdValue xsd_XsdValue;

#ifndef SLOP_OPTION_XSD_XSDVALUE_DEFINED
#define SLOP_OPTION_XSD_XSDVALUE_DEFINED
SLOP_OPTION_DEFINE(xsd_XsdValue, slop_option_xsd_XsdValue)
#endif

#ifndef SLOP_RESULT_XSD_XSDVALUE_XSD_XSDERROR_DEFINED
#define SLOP_RESULT_XSD_XSDVALUE_XSD_XSDERROR_DEFINED
typedef struct { bool is_ok; union { xsd_XsdValue ok; xsd_XsdError err; } data; } slop_result_xsd_XsdValue_xsd_XsdError;
#endif

#ifndef SLOP_RESULT_U8_XSD_XSDERROR_DEFINED
#define SLOP_RESULT_U8_XSD_XSDERROR_DEFINED
typedef struct { bool is_ok; union { uint8_t ok; xsd_XsdError err; } data; } slop_result_u8_xsd_XsdError;
#endif

xsd_XsdType xsd_parse_type(slop_string datatype_iri);
slop_result_xsd_XsdValue_xsd_XsdError xsd_parse_value(slop_arena* arena, slop_string lexical, xsd_XsdType dtype);
uint8_t xsd_validate_lexical(slop_string lexical, slop_string datatype_iri);
uint8_t xsd_values_equal(xsd_XsdValue a, xsd_XsdValue b);
uint8_t xsd_types_compatible(xsd_XsdType t1, xsd_XsdType t2);
slop_result_u8_xsd_XsdError xsd_literal_values_equal(slop_arena* arena, rdf_Literal a, rdf_Literal b);
xsd_XsdCompareResult xsd_float_cmp(double a, double b);
xsd_XsdCompareResult xsd_values_compare(xsd_XsdValue a, xsd_XsdValue b);
xsd_XsdCompareResult xsd_compare(slop_arena* arena, rdf_Term a, rdf_Term b);

/* Function name aliases for C interop */
#define xsd_xsd_parse_type xsd_parse_type
#define xsd_xsd_parse_value xsd_parse_value
#define xsd_xsd_validate_lexical xsd_validate_lexical
#define xsd_xsd_values_equal xsd_values_equal
#define xsd_xsd_types_compatible xsd_types_compatible
#define xsd_xsd_values_compare xsd_values_compare
#define xsd_xsd_compare xsd_compare

#ifndef SLOP_OPTION_XSD_XSDVALUE_DEFINED
#define SLOP_OPTION_XSD_XSDVALUE_DEFINED
SLOP_OPTION_DEFINE(xsd_XsdValue, slop_option_xsd_XsdValue)
#endif


#endif
