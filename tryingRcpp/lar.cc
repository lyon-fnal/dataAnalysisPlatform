#include <Rcpp.h>

#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

// [[Rcpp::plugins(lar)]]

#include "canvas/Utilities/InputTag.h"
#include "gallery/Event.h"
#include "gallery/ValidHandle.h"
#include "lardataobj/RecoBase/Cluster.h"
#include "lardataobj/RecoBase/Vertex.h"
#include "nusimdata/SimulationBase/MCTruth.h"

#include "canvas/Persistency/Common/FindMany.h"

using namespace std;

// [[Rcpp::export]]
void getArtEvents(vector<string> files) {
  
  // Do we have enough files to process?
  if ( files.size() < 1) {
    Rcpp::stop("You must specify at least one file to process");
  }
  
  // Setup the input tags
  art::InputTag const mctruths_tag{"generator"};
  art::InputTag const vertex_tag{"linecluster"};
  art::InputTag const assns_tag{"linecluster"};
  
  // Let's keep track of time
  auto const start_time = chrono::system_clock::now();
  vector<chrono::microseconds> times;
  
  Rcpp::Rcout << "Running Events" << "\n";
  for ( gallery::Event ev(files); !ev.atEnd(); ev.next() ) {
    Rcpp::Rcout << "Viewing event " << ev.eventEntry() << "\n";
    auto const t0 = chrono::system_clock::now();
    
    using vertices_t = vector<recob::Vertex>;
    auto const& vertices_h = ev.getValidHandle<vertices_t>(vertex_tag);
    art::FindMany<recob::Cluster, unsigned short> clusters_for_vertex(vertices_h, ev,
                                                                      assns_tag);
    
    for (size_t i = 0, sz = vertices_h->size(); i != sz; ++i) {
      vector<recob::Cluster const*> clusters;
      clusters_for_vertex.get(i, clusters);
      Rcpp::Rcout << "There are " << clusters.size() << " clusters" << endl;

      for (auto pclus : clusters) {
        if (!pclus) continue; // skip null pointers
        Rcpp::Rcout << "There are " << pclus->NHits() << " hits" << endl;
      }
    }
    times.push_back(chrono::duration_cast<chrono::microseconds>(
      chrono::system_clock::now() - t0));
  }
  
  auto const elapsed_time = chrono::duration_cast<chrono::milliseconds>(
    chrono::system_clock::now() - start_time);
  auto const sum_times =
    accumulate(begin(times), end(times), chrono::microseconds(0));
  
  Rcpp::Rcout << "Processed " << times.size() << " events in an average of "
       << sum_times.count() / times.size() << " microseconds/event\n";
  Rcpp::Rcout << "Total processing time (including file opening) was "
       << elapsed_time.count() << " milliseconds\n";
}
