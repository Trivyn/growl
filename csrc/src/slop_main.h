#ifndef SLOP_main_H
#define SLOP_main_H

#include "../runtime/slop_runtime.h"
#ifndef SLOP_RUNTIME_ABI
#error "this module was generated for SLOP runtime ABI 2026-1 (SLOP_RUNTIME_ABI 202601), but slop_runtime.h predates runtime ABI versioning: use the slop_runtime.h of the SLOP release that generated this code"
#elif SLOP_RUNTIME_ABI != 202601
#error "this module was generated for SLOP runtime ABI 2026-1 (SLOP_RUNTIME_ABI 202601), which this slop_runtime.h does not provide (SLOP_RUNTIME_ABI differs): regenerate the C with the SLOP release that matches the runtime, or use the slop_runtime.h of the release that generated it"
#endif
#include <stdint.h>
#include <stdbool.h>
#include "slop_rdf.h"
#include "slop_index.h"
#include "slop_ttl.h"
#include "slop_common.h"
#include "slop_serialize_ttl.h"
#include "slop_growl.h"
#include "slop_strlib.h"
#include <string.h>
#include "../runtime/slop_runtime.h"

typedef struct growl_cli_main_CliArgs growl_cli_main_CliArgs;

struct growl_cli_main_CliArgs {
    slop_option_string input_file;
    slop_option_string emit_file;
    slop_option_string background_file;
    slop_option_string validate_ns;
    uint8_t quiet;
    uint8_t fast;
    uint8_t complete;
    uint8_t enrich;
    uint8_t validate;
    uint8_t show_help;
    uint8_t show_version;
    int64_t max_triples;
};
typedef struct growl_cli_main_CliArgs growl_cli_main_CliArgs;

#ifndef SLOP_OPTION_GROWL_CLI_MAIN_CLIARGS_DEFINED
#define SLOP_OPTION_GROWL_CLI_MAIN_CLIARGS_DEFINED
SLOP_OPTION_DEFINE(growl_cli_main_CliArgs, slop_option_growl_cli_main_CliArgs)
#endif

void growl_cli_main_print_elapsed(slop_arena* arena, int64_t elapsed);
slop_string growl_cli_main_argv_to_string(uint8_t** argv, int64_t index);
growl_cli_main_CliArgs growl_cli_main_parse_args(slop_arena* arena, int64_t argc, uint8_t** argv);
void growl_cli_main_print_usage(void);
int main(int argc, char** _c_argv);

#ifndef SLOP_OPTION_GROWL_CLI_MAIN_CLIARGS_DEFINED
#define SLOP_OPTION_GROWL_CLI_MAIN_CLIARGS_DEFINED
SLOP_OPTION_DEFINE(growl_cli_main_CliArgs, slop_option_growl_cli_main_CliArgs)
#endif


#endif
