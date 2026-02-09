use std::path::Path;

fn main() {
    let csrc = Path::new("../csrc/src");
    let runtime = Path::new("../csrc/runtime");

    let sources = [
        "slop_cax.c",
        "slop_cls.c",
        "slop_common.c",
        "slop_dt.c",
        "slop_engine.c",
        "slop_eq.c",
        "slop_file.c",
        "slop_filter.c",
        "slop_growl.c",
        "slop_index.c",
        "slop_list.c",
        "slop_prp.c",
        "slop_rdf.c",
        "slop_scm.c",
        "slop_serialize_ttl.c",
        "slop_strlib.c",
        "slop_thread.c",
        "slop_ttl.c",
        "slop_types.c",
        "slop_vocab.c",
        "slop_xsd.c",
    ];

    let mut build = cc::Build::new();
    build
        .include(runtime)
        .include(csrc)
        .define("SLOP_ARENA_NO_CAP", None)
        .define("SLOP_INTERN_THREADSAFE", None)
        .opt_level(2)
        .warnings(false);

    for src in &sources {
        build.file(csrc.join(src));
    }
    build.file("csrc_shim.c");

    build.compile("growl_c");

    println!("cargo:rustc-link-lib=pthread");

    // Rerun if any C source changes
    println!("cargo:rerun-if-changed=csrc_shim.c");
    for src in &sources {
        println!("cargo:rerun-if-changed={}", csrc.join(src).display());
    }
    println!("cargo:rerun-if-changed={}", runtime.join("slop_runtime.h").display());
}
