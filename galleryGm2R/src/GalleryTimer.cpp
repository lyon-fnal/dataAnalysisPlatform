//
// Created by Adam Lyon on 2/21/17.
//

#include <GalleryTimer.hh>

void GalleryTimer::write() {
  auto const elapsed_time = chrono::duration_cast<chrono::milliseconds>(
      chrono::system_clock::now() - start_time_);
  auto const sum_times =
      accumulate(begin(times_), end(times_), chrono::microseconds(0));

  Rcpp::Rcout << "Processed " << times_.size() << " events in an average of "
              << sum_times.count() / times_.size() << " microseconds/event\n";
  Rcpp::Rcout << "Total processing time (including file opening) was "
              << elapsed_time.count() << " milliseconds\n";
}

