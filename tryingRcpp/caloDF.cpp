#include <Rcpp.h>
#include <vector>
#include <string>

// [[Rcpp::depends(galleryGm2R)]]

#include "canvas/Utilities/InputTag.h"
#include "gallery/Event.h"
#include "gallery/ValidHandle.h"

#include "CaloArtRecordDF.hh"
#include "GalleryTimer.hh"

using namespace std;

// [[Rcpp::export]]
Rcpp::DataFrame getCalo(vector<string> files) {
  if ( files.size() < 1) { Rcpp::stop("You must specify at least one file to process"); }

  // Input tags
  art::InputTag const calo_tag{"artg4:calorimeter"};

  // Timer
  GalleryTimer timer;

  // Dataframe
  CaloDF caloDF;

  // Loop over events
  for ( gallery::Event ev(files); !ev.atEnd(); ev.next() ) {
    timer.beginTiming();

    using caloHits_t = vector<gm2truth::CaloArtRecord>;
    auto const& caloHits_h = ev.getValidHandle<caloHits_t>(calo_tag);
    auto const& calos = *(caloHits_h);

    // Loop over hits
    for (size_t i = 0, sz = calos.size(); i != sz; ++i) {
      caloDF.commit(ev, calos[i]);
    }
    timer.endTiming();
  }

  timer.write();

  return caloDF.df();
}
