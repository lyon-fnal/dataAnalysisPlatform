# inline.R

upsArea <- '~/larsoftobj'
upsUmbrella <- 'larsoftobj'
upsUmbrellaVersion <- 'v1_08_02'
upsUmbrellaQuals <- "+e10:prof"

makeListWithNames <- function(bigList, prefix="-I ") {
  # Helper function to get a list in the form we want.
  # bigList has entries of the form...
  #  [[1]] BLA_INC
  #  [[2]] /path/to/inc
  #  Convert this to list with names=[[1]] and values=[[2]]

  theList  <- lapply(bigList, function(x) paste(prefix, x[2], sep=""))
  theNames <- sapply(bigList, function(x) x[1])
  names(theList) <- theNames
  theList
}

# Build the command for source, like
# source ~/larsoftobj/setup ; setup -B larsoftobj v1_08_02 -q e10:prof ; env | grep _LIB
sourceCommand <- function(grepArg) {
  paste0("source ", upsArea, "/setup ; setup -B ",
                    upsUmbrella, " ", upsUmbrellaVersion, " -q ",
                    upsUmbrellaQuals, " ; env | grep ", grepArg)
}

CPPFlags <- function() {
  system( sourceCommand("_INC"), intern=T) %>%
    str_split("=") %>%
    makeListWithNames(prefix="-I ") -> incPaths

  CPPFlags <- paste(incPaths$BOOST_INC, incPaths$CANVAS_INC, incPaths$CETLIB_INC, incPaths$FHICLCPP_INC,
                    incPaths$GALLERY_INC, incPaths$LARCOREOBJ_INC, incPaths$LARDATAOBJ_INC,
                    incPaths$NUSIMDATA_INC, incPaths$ROOT_INC, sep=" ")

  CPPFlags
}

LDFlags <- function() {
  system( sourceCommand("_LIB"), intern=T) %>%
    str_split("=") %>%
    makeListWithNames(prefix="-L ") -> libPaths

  rootLDFLAGS <- system("root-config --libs", intern=T)

  LDFLAGS <- paste(rootLDFLAGS,
                   libPaths$CANVAS_LIB,
                  "-l canvas_Utilities -l canvas_Persistency_Common -l canvas_Persistency_Provenance",
                  libPaths$CETLIB_LIB, "-l cetlib",
                  libPaths$GALLERY_LIB, "-l gallery",
                  libPaths$NUSIMDATA_LIB, "-l nusimdata_SimulationBase",
                   libPaths$LARCOREOBJ_LIB, "-l larcoreobj_SummaryData",
                   libPaths$LARDATAOBJ_LIB, "-l lardataobj_RecoBase")
  LDFLAGS
}

inlineCxxPlugin <- function(...) {
  plugin <- Rcpp::Rcpp.plugin.maker(libs = LDFlags, package="galleryLArR")

  settings <- plugin()
  settings$env$PKG_CPPFLAGS <- CPPFlags
  settings
}
