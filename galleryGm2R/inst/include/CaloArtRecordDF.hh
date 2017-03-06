//
// Created by Adam Lyon on 2/21/17.
//

#ifndef GALLERYGM2R_CALOARTRECORDDF_HH
#define GALLERYGM2R_CALOARTRECORDDF_HH

#include <Rcpp.h>

#include <vector>

#include "gallery/Event.h"
#include "gm2dataproducts/mc/calo/CaloArtRecord.hh"

using namespace std;

class CaloArtRecordDF {
public:
  void commit(const gallery::Event& ev, const gm2truth::CaloArtRecord& calo) {
    eventEntry_.push_back(ev.eventEntry());
    fileEntry_.push_back(ev.fileEntry());

    turn_.push_back(calo.turn);
    caloNum_.push_back(calo.caloNum);
    parentID_.push_back(calo.parent_ID);
    particleName_.push_back(calo.particle_name);
    x_.push_back(calo.x);
    y_.push_back(calo.y);
    z_.push_back(calo.z);
    px_.push_back(calo.px);
    py_.push_back(calo.py);
    pz_.push_back(calo.pz);
    energy_.push_back(calo.energy);
    time_.push_back(calo.time);
  }

  Rcpp::DataFrame df() {
    return Rcpp::DataFrame::create(
        Rcpp::Named("eventEntry") = eventEntry_,
        Rcpp::Named("fileEntry")  = fileEntry_,
        Rcpp::Named("turn") = turn_,
        Rcpp::Named("caloNum") = caloNum_,
        Rcpp::Named("parentID") = parentID_,
        Rcpp::Named("particleName") = particleName_,
        Rcpp::Named("x") = x_,
        Rcpp::Named("y") = y_,
        Rcpp::Named("z") = z_,
        Rcpp::Named("px") = px_,
        Rcpp::Named("py") = py_,
        Rcpp::Named("pz") = pz_,
        Rcpp::Named("time") = time_,
        Rcpp::Named("energy") = energy_
    );
  }

private:
  vector<int> eventEntry_;
  vector<int> fileEntry_;
  vector<int> turn_, caloNum_, parentID_;
  vector<string> particleName_;
  vector<double> x_, y_, z_, px_, py_, pz_, time_, energy_;
};

#endif //GALLERYGM2R_CALOARTRECORDDF_HH
