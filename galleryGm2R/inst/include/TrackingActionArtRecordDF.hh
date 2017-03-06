//
// Created by Adam Lyon on 2/21/17.
//

#ifndef GALLERYGM2R_TRACKINGACTIONARTRECORDDF_HH
#define GALLERYGM2R_TRACKINGACTIONARTRECORDDF_HH

#include <Rcpp.h>

#include <vector>

#include "canvas/Utilities/InputTag.h"
#include "gallery/Event.h"
#include "gallery/ValidHandle.h"

#include "gm2dataproducts/mc/actions/track/TrackingActionArtRecord.hh"

using namespace std;

class TrackingActionArtRecordDF {

public:

  void fill(const gallery::Event& ev, const art::InputTag & tag) {

    using ta_t = vector<gm2truth::TrackingActionArtRecord>;
    auto const& ta_h = ev.getValidHandle<ta_t>(tag);
    auto const& tracks = *(ta_h);

    for ( auto const & aTrack : tracks) {
      commit(ev, aTrack);
    }
  }

  void commit(const gallery::Event& ev, const gm2truth::TrackingActionArtRecord& ar) {

    eventEntry_.push_back(ev.eventEntry());
    fileEntry_.push_back(ev.fileEntry());

    trackType_.push_back(ar.trackType);
    trackID_.push_back(ar.trackID);
    eventNumInFill_.push_back(ar.eventNumInFill);
    parentTrackID_.push_back(ar.parentTrackID);
    turn_.push_back(ar.turn);
    volumeUID_.push_back(ar.volumeUID);
    status_.push_back(ar.status);
    time_.push_back(ar.time);
    t0_.push_back(ar.t0);
    p_.push_back(ar.p);
    e_.push_back(ar.e);

    pos_.emplace_back(initializer_list<double>{ar.x, ar.y, ar.z});
    mom_.emplace_back(initializer_list<double>{ar.px, ar.py, ar.pz});
    pol_.emplace_back(initializer_list<double>{ar.polx, ar.poly, ar.polz});
    hat_.emplace_back(initializer_list<double>{ar.rhat, ar.vhat, ar.theta});

}

  Rcpp::List df() {
    return Rcpp::List::create(
        Rcpp::Named("eventEntry") = eventEntry_,
        Rcpp::Named("fileEntry")  = fileEntry_,
        Rcpp::Named("trackType") = trackType_,
        Rcpp::Named("trackID") = trackID_,
        Rcpp::Named("eventNumInFill") = eventNumInFill_,
        Rcpp::Named("parentTrackID") = parentTrackID_,
        Rcpp::Named("turn") = turn_,
        Rcpp::Named("volumeUID") = volumeUID_,
        Rcpp::Named("status") = status_,
        Rcpp::Named("time") = time_,
        Rcpp::Named("t0") = t0_,
        Rcpp::Named("p") = p_,
        Rcpp::Named("e") = e_,
        Rcpp::Named("pos") = pos_,
        Rcpp::Named("mom") = mom_,
        Rcpp::Named("pol") = pol_,
        Rcpp::Named("hat") = hat_

    );
  }

private:

  vector<int> eventEntry_, fileEntry_;
  vector<string> trackType_;
  vector<int> trackID_, eventNumInFill_, parentTrackID_, turn_, volumeUID_, status_;
  vector<double> time_, t0_, p_, e_;
  vector< vector<double> > pos_;
  vector< vector<double> > mom_;
  vector< vector<double> > pol_;
  vector< vector<double> > hat_;
};

#endif //GALLERYGM2R_TRACKINGACTIONARTRECORDDF_HH
