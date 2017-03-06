//
// Created by Adam Lyon on 2/21/17.
//

#ifndef GALLERYGM2R_GHOSTDETECTORDF_HH
#define GALLERYGM2R_GHOSTDETECTORDF_HH

#include <Rcpp.h>

#include <vector>
#include <initializer_list>

#include "canvas/Utilities/InputTag.h"
#include "gallery/Event.h"
#include "gallery/ValidHandle.h"

#include "gm2dataproducts/mc/ghostdetectors/GhostDetectorArtRecord.hh"

using namespace std;

class GhostDetectorArtRecordDF {
public:

  void fill(const gallery::Event& ev, const art::InputTag & tag) {

    using ghostHits_t = vector<gm2truth::GhostDetectorArtRecord>;
    auto const& ghostHits_h = ev.getValidHandle<ghostHits_t>(tag);
    auto const& ghostHits = *(ghostHits_h);

    for ( auto const & aGhostHit : ghostHits) {
      commit(ev, aGhostHit);
    }
  }

  void commit(const gallery::Event& ev, const gm2truth::GhostDetectorArtRecord& ar) {

    eventEntry_.push_back(ev.eventEntry());
    fileEntry_.push_back(ev.fileEntry());

    particleID_.push_back(ar.particleID);
    trackID_.push_back(ar.trackID);
    parentTrackID_.push_back(ar.parentTrackID);
    volumeName_.push_back(ar.volumeName);

    pos_.emplace_back(initializer_list<double>{ar.position.x(),
                                               ar.position.y(),
                                               ar.position.z()});

    mom_.emplace_back(initializer_list<double>{ar.momentum.x(),
                                               ar.momentum.y(),
                                               ar.momentum.z()});

    pol_.emplace_back(initializer_list<double>{ar.spin.x(),
                                               ar.spin.y(),
                                               ar.spin.z()});
    time_.push_back(ar.time);
  }

  Rcpp::List df() {
    return Rcpp::List::create(
        Rcpp::Named("eventEntry") = eventEntry_,
        Rcpp::Named("fileEntry") = fileEntry_,
        Rcpp::Named("particleID") = particleID_,
        Rcpp::Named("trackID") = trackID_,
        Rcpp::Named("parentTrackID") = parentTrackID_,
        Rcpp::Named("volumeName") = volumeName_,
        Rcpp::Named("pos") = pos_,
        Rcpp::Named("mom") = mom_,
        Rcpp::Named("pol") = pol_,
        Rcpp::Named("time") = time_
    );
  }

private:
  vector<int> eventEntry_, fileEntry_;
  vector<int> particleID_, trackID_, parentTrackID_;
  vector<string> volumeName_;
  vector< vector<double> > pos_, mom_, pol_;
  vector<double> time_;
};

#endif //GALLERYGM2R_GHOSTDETECTORDF_HH
