cmake_minimum_required(VERSION 3.6)
project(galleryGm2R)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        inst/include/GalleryTimer.hh
        src/rcpp_hello.cpp
        src/RcppExports.cpp src/GalleryTimer.cpp inst/include/CaloArtRecordDF.hh inst/include/TrackingActionArtRecordDF.hh inst/include/TrajectoryArtRecordDF.hh inst/include/GhostDetectorArtRecordDF.hh)

include_directories(inst/include)

include_directories(${CMAKE_SOURCE_DIR}/../inst/include)
include_directories(/Users/lyon/Library/R/3.3/library/Rcpp/include)
include_directories(/cvmfs/gm2.opensciencegrid.org/prod7/external/gallery/v1_03_04/include)

add_executable(galleryGm2R ${SOURCE_FILES})