// Timer class for timing events

#include <Rcpp.h>

#include <chrono>

using namespace std;

class GalleryTimer {
public:
  GalleryTimer() :
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

  void write();

private:
  chrono::system_clock::time_point start_time_;
  vector<chrono::microseconds> times_;
  chrono::system_clock::time_point t0_;
};
