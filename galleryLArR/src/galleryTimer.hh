#ifndef GALLERY_TIMER_HH
#define GALLERY_TIMER_HH

#include <Rcpp.h>
#include <chrono>

using namespace std;

// Class for timing
class GalleryTimer {
public:
  GalleryTimer() :
  start_time_(chrono::system_clock::now()),
  times_(),
  t0_()
  {}

  void beginTiming() { t0_ = chrono::system_clock::now();}

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

#endif
