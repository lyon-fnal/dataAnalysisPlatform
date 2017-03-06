# Set up the Rcpp plugin. This will depend on .Renviron being set appropriately


# Construct CPPFlags
incEnvVars <- c("MRB_SOURCE", "BOOST_INC", "CANVAS_INC", "CETLIB_INC",
                "FHICLCPP_INC", "GALLERY_INC", "ROOT_INC",
                "ARTG4_INC", "CLHEP_INC")

CPPFLAGS <- paste( c("", Sys.getenv(incEnvVars)), collapse=" -I ")

# Construct LDFlags
LDFLAGS <- paste( system("root-config --libs", intern=T),
                  "-L", Sys.getenv("CANVAS_LIB"),  "-l canvas_Utilities -l canvas_Persistency_Common -l canvas_Persistency_Provenance",
                  "-L", Sys.getenv("CETLIB_LIB"), "-l cetlib",
                  "-L", Sys.getenv("GALLERY_LIB"), "-l gallery",
                  paste0(system.file("libs", package="galleryGm2R"), "/galleryGm2R.so")
                  )

inlineCxxPlugin <- function(...) {
  plugin <- Rcpp::Rcpp.plugin.maker(
    libs = LDFLAGS,
    package = "galleryGm2R", Makevars = NULL, Makevars.win = NULL
  )

  settings <- plugin()
  settings$env$PKG_CPPFLAGS <- CPPFLAGS
  settings
}
