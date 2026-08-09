use std::env;
use std::path::Path;

fn main() {
    let csrc = Path::new("csrc/src");
    let runtime = Path::new("csrc/runtime");

    // Shared rdf/std headers + symbols now come from the -sys crates.
    let rdf_inc = env::var("DEP_SLOP_RDF_INCLUDE").expect("slop-rdf-sys must be a dependency");
    let std_inc = env::var("DEP_SLOP_STD_INCLUDE").expect("slop-std-sys must be a dependency");

    // Only growl's own modules; shared modules come from libslop_rdf.a / libslop_std.a.
    let sources = [
        "slop_cax.c", "slop_cls.c", "slop_dt.c", "slop_engine.c", "slop_eq.c",
        "slop_filter.c", "slop_growl.c", "slop_prp.c", "slop_scm.c", "slop_types.c",
    ];

    let mut build = cc::Build::new();
    build
        .include(runtime)
        .include(csrc)
        .include(&rdf_inc)
        .include(&std_inc)
        .define("SLOP_ARENA_NO_CAP", None)
        .define("SLOP_INTERN_THREADSAFE", None)
        .opt_level(2)
        .warnings(false);
    for src in &sources { build.file(csrc.join(src)); }
    build.file("csrc_shim.c");   // keeps growl_arena_* + growl_layout_* ABI probes
    build.compile("growl_c");

    println!("cargo:rustc-link-lib=pthread");
    println!("cargo:rerun-if-changed=csrc_shim.c");
    for src in &sources { println!("cargo:rerun-if-changed={}", csrc.join(src).display()); }
    println!("cargo:rerun-if-changed={}", runtime.join("slop_runtime.h").display());
}
