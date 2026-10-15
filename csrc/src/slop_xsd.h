#ifndef SLOP_xsd_H
#define SLOP_xsd_H

#include "../runtime/slop_runtime.h"
#ifndef SLOP_RUNTIME_ABI
#error "this module was generated for SLOP runtime ABI 2026-1 (SLOP_RUNTIME_ABI 202601), but slop_runtime.h predates runtime ABI versioning: use the slop_runtime.h of the SLOP release that generated this code"
#elif SLOP_RUNTIME_ABI != 202601
#error "this module was generated for SLOP runtime ABI 2026-1 (SLOP_RUNTIME_ABI 202601), which this slop_runtime.h does not provide (SLOP_RUNTIME_ABI differs): regenerate the C with the SLOP release that matches the runtime, or use the slop_runtime.h of the release that generated it"
#endif
#include <stdint.h>
#include <stdbool.h>
#include "slop_rdf.h"
#include "slop_strlib.h"
#include "slop_vocab.h"

typedef struct slop_rdf_xsd_XsdValue slop_rdf_xsd_XsdValue;

typedef enum {
    slop_rdf_xsd_XsdType_xsd_string,
    slop_rdf_xsd_XsdType_xsd_integer,
    slop_rdf_xsd_XsdType_xsd_decimal,
    slop_rdf_xsd_XsdType_xsd_float,
    slop_rdf_xsd_XsdType_xsd_double,
    slop_rdf_xsd_XsdType_xsd_boolean,
    slop_rdf_xsd_XsdType_xsd_unknown
} slop_rdf_xsd_XsdType;

typedef enum {
    slop_rdf_xsd_XsdError_invalid_lexical_form,
    slop_rdf_xsd_XsdError_unsupported_datatype,
    slop_rdf_xsd_XsdError_type_mismatch
} slop_rdf_xsd_XsdError;

typedef enum {
    slop_rdf_xsd_XsdCompareResult_xsd_compare_less,
    slop_rdf_xsd_XsdCompareResult_xsd_compare_equal,
    slop_rdf_xsd_XsdCompareResult_xsd_compare_greater,
    slop_rdf_xsd_XsdCompareResult_xsd_compare_incomparable
} slop_rdf_xsd_XsdCompareResult;

typedef enum {
    slop_rdf_xsd_XsdValue_xsd_string_val,
    slop_rdf_xsd_XsdValue_xsd_integer_val,
    slop_rdf_xsd_XsdValue_xsd_decimal_val,
    slop_rdf_xsd_XsdValue_xsd_float_val,
    slop_rdf_xsd_XsdValue_xsd_double_val,
    slop_rdf_xsd_XsdValue_xsd_boolean_val,
    slop_rdf_xsd_XsdValue_xsd_unknown_val
} slop_rdf_xsd_XsdValue_tag;

struct slop_rdf_xsd_XsdValue {
    slop_rdf_xsd_XsdValue_tag tag;
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
typedef struct slop_rdf_xsd_XsdValue slop_rdf_xsd_XsdValue;

#ifndef SLOP_OPTION_SLOP_RDF_XSD_XSDVALUE_DEFINED
#define SLOP_OPTION_SLOP_RDF_XSD_XSDVALUE_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_xsd_XsdValue, slop_option_slop_rdf_xsd_XsdValue)
#endif

#ifndef SLOP_RESULT_SLOP_RDF_XSD_XSDVALUE_SLOP_RDF_XSD_XSDERROR_DEFINED
#define SLOP_RESULT_SLOP_RDF_XSD_XSDVALUE_SLOP_RDF_XSD_XSDERROR_DEFINED
typedef struct { bool is_ok; union { slop_rdf_xsd_XsdValue ok; slop_rdf_xsd_XsdError err; } data; } slop_result_slop_rdf_xsd_XsdValue_slop_rdf_xsd_XsdError;
#endif

#ifndef SLOP_RESULT_U8_SLOP_RDF_XSD_XSDERROR_DEFINED
#define SLOP_RESULT_U8_SLOP_RDF_XSD_XSDERROR_DEFINED
typedef struct { bool is_ok; union { uint8_t ok; slop_rdf_xsd_XsdError err; } data; } slop_result_u8_slop_rdf_xsd_XsdError;
#endif

slop_rdf_xsd_XsdType xsd_parse_type(slop_string datatype_iri);
slop_result_slop_rdf_xsd_XsdValue_slop_rdf_xsd_XsdError xsd_parse_value(slop_arena* arena, slop_string lexical, slop_rdf_xsd_XsdType dtype);
uint8_t xsd_validate_lexical(slop_string lexical, slop_string datatype_iri);
uint8_t xsd_values_equal(slop_rdf_xsd_XsdValue a, slop_rdf_xsd_XsdValue b);
uint8_t xsd_types_compatible(slop_rdf_xsd_XsdType t1, slop_rdf_xsd_XsdType t2);
slop_result_u8_slop_rdf_xsd_XsdError xsd_literal_values_equal(slop_arena* arena, slop_rdf_rdf_Literal a, slop_rdf_rdf_Literal b);
slop_rdf_xsd_XsdCompareResult xsd_float_cmp(double a, double b);
slop_rdf_xsd_XsdCompareResult xsd_values_compare(slop_rdf_xsd_XsdValue a, slop_rdf_xsd_XsdValue b);
slop_rdf_xsd_XsdCompareResult xsd_compare(slop_arena* arena, slop_rdf_rdf_Term a, slop_rdf_rdf_Term b);

/* Function name aliases for C interop */
#define slop_rdf_xsd_xsd_parse_type xsd_parse_type
#define slop_rdf_xsd_xsd_parse_value xsd_parse_value
#define slop_rdf_xsd_xsd_validate_lexical xsd_validate_lexical
#define slop_rdf_xsd_xsd_values_equal xsd_values_equal
#define slop_rdf_xsd_xsd_types_compatible xsd_types_compatible
#define slop_rdf_xsd_literal_values_equal xsd_literal_values_equal
#define slop_rdf_xsd_float_cmp xsd_float_cmp
#define slop_rdf_xsd_xsd_values_compare xsd_values_compare
#define slop_rdf_xsd_xsd_compare xsd_compare

#ifndef SLOP_OPTION_SLOP_RDF_XSD_XSDVALUE_DEFINED
#define SLOP_OPTION_SLOP_RDF_XSD_XSDVALUE_DEFINED
SLOP_OPTION_DEFINE(slop_rdf_xsd_XsdValue, slop_option_slop_rdf_xsd_XsdValue)
#endif


#endif
