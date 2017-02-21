#include <Rcpp.h>

#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

// Use the lar plugin for build instructions
// [[Rcpp::plugins(lar)]]

#include "canvas/Utilities/InputTag.h"
#include "gallery/Event.h"
#include "gallery/ValidHandle.h"
#include "lardataobj/RecoBase/Cluster.h"
#include "lardataobj/RecoBase/Vertex.h"
#include "nusimdata/SimulationBase/MCTruth.h"

#include "canvas/Persistency/Common/FindMany.h"

using namespace std;

// Class for timing
class Timer {
public:
  Timer() :
    start_time_(chrono::system_clock::now()),
    times_(),
    t0_()
  {}
  
  void beginTiming() {
    t0_ = chrono::system_clock::now();
  }
  
  void endTiming() {
    times_.push_back(chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now() - t0_));
  }
  
  
  void write() {
    auto const elapsed_time = chrono::duration_cast<chrono::milliseconds>(
      chrono::system_clock::now() - start_time_);
    auto const sum_times =
      accumulate(begin(times_), end(times_), chrono::microseconds(0));
    
    Rcpp::Rcout << "Processed " << times_.size() << " events in an average of "
                << sum_times.count() / times_.size() << " microseconds/event\n";
    Rcpp::Rcout << "Total processing time (including file opening) was "
                << elapsed_time.count() << " milliseconds\n";
  }
  
private:
  chrono::system_clock::time_point start_time_;
  vector<chrono::microseconds> times_; 
  chrono::system_clock::time_point t0_;
};

// Class for vertexDF
class VertexDF {
public: 
  void commit(const gallery::Event& ev, const recob::Vertex& v) {
    eventEntry_.push_back(ev.eventEntry());
    fileEntry_.push_back(ev.fileEntry());

    id_.push_back(v.ID());
    
    double xyz[3];
    v.XYZ(xyz);
    x_.push_back(xyz[0]);
    y_.push_back(xyz[1]);
    z_.push_back(xyz[2]);
  }
  
  Rcpp::DataFrame df() {
    return Rcpp::DataFrame::create(
      Rcpp::Named("eventEntry") = eventEntry_,
      Rcpp::Named("fileEntry")  = fileEntry_,
      Rcpp::Named("id") = id_,
      Rcpp::Named("x") = x_,
      Rcpp::Named("y") = y_,
      Rcpp::Named("z") = z_
    );
  }

private:
  vector<int> eventEntry_;
  vector<int> fileEntry_;
  vector<int> id_;
  vector<double> x_, y_, z_;
};


// [[Rcpp::export]]
Rcpp::DataFrame getArtEvents(vector<string> files) {
  
  // Do we have enough files to process?
  if ( files.size() < 1) { Rcpp::stop("You must specify at least one file to process"); }
  
  // Setup the input tags
  art::InputTag const mctruths_tag{"generator"};
  art::InputTag const vertex_tag{"linecluster"};
  art::InputTag const assns_tag{"linecluster"};
  
  // Let's keep track of time
  Timer timer;
  
  // Data frame for storage
  VertexDF vdf;
  
  // Loop over all events
  for ( gallery::Event ev(files); !ev.atEnd(); ev.next() ) {
    timer.beginTiming();
    
    using vertices_t = vector<recob::Vertex>;
    auto const& vertices_h = ev.getValidHandle<vertices_t>(vertex_tag);
    auto const& vertices = *(vertices_h);
    
    // Loop over vertices
    for (size_t i = 0, sz = vertices.size(); i != sz; ++i) {
      vdf.commit(ev, vertices[i]);
    }
    timer.endTiming();
  }
  
  timer.write();
  
  return vdf.df();
}