#ifndef SLOP_main_H
#define SLOP_main_H

#include "../runtime/slop_runtime.h"
#include <stdint.h>
#include <stdbool.h>
#include "slop_rdf.h"
#include "slop_index.h"
#include "slop_ttl.h"
#include "slop_common.h"
#include "slop_serialize_ttl.h"
#include "slop_growl.h"
#include <string.h>
#include <slop_runtime.h>

typedef struct main_CliArgs main_CliArgs;

struct main_CliArgs {
    slop_option_string input_file;
    slop_option_string emit_file;
    slop_option_string background_file;
    slop_option_string validate_ns;
    uint8_t quiet;
    uint8_t fast;
    uint8_t complete;
    uint8_t validate;
    uint8_t show_help;
    uint8_t show_version;
};
typedef struct main_CliArgs main_CliArgs;

#ifndef SLOP_OPTION_MAIN_CLIARGS_DEFINED
#define SLOP_OPTION_MAIN_CLIARGS_DEFINED
SLOP_OPTION_DEFINE(main_CliArgs, slop_option_main_CliArgs)
#endif

void main_print_elapsed(slop_arena* arena, int64_t elapsed);
rdf_Term main_remap_blank_term(slop_arena* arena, rdf_Term t, int64_t offset);
int64_t main_max_blank_id_in_graph(index_IndexedGraph ig);
slop_string main_argv_to_string(uint8_t** argv, int64_t index);
main_CliArgs main_parse_args(slop_arena* arena, int64_t argc, uint8_t** argv);
void main_print_usage(void);
int main(int argc, char** _c_argv);

#ifndef SLOP_OPTION_MAIN_CLIARGS_DEFINED
#define SLOP_OPTION_MAIN_CLIARGS_DEFINED
SLOP_OPTION_DEFINE(main_CliArgs, slop_option_main_CliArgs)
#endif


#endif
