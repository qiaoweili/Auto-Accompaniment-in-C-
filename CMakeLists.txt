cmake_minimum_required(VERSION 3.19)
project(CLion)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.76.0 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

#find_package(FFTW3 REQUIRED)
#if(NOT FFTW3_FOUND)
#    message(AUTHOR, "The FFTW Library not found!")
#endif(NOT FFTW3_FOUND)
#include_directories(include ${FFTW3_INCLUDE_DIRS})
find_package(PkgConfig REQUIRED)
pkg_search_module(FFTW REQUIRED fftw3 IMPORTED_TARGET)
include_directories(PkgConfig::FFTW)
link_libraries(PkgConfig::FFTW)


add_executable(CLion main.cpp)
add_executable(CLion_Calc calc.cpp)
add_executable(miditest miditest1.cpp)
add_executable(acco accompaniment.cpp)
add_executable(scorefollow score_following.cpp)
add_executable(AubioTest aubio_test.cpp)
add_executable(AudioTest audio_test.cpp)
add_executable(FFTWtest fftw_test.cpp)
add_executable(all_files main.cpp calc.cpp miditest1.cpp accompaniment.cpp score_following.cpp global_config.cpp)

include_directories(includes/aubio.framework)
include_directories (includes/rtmidi)
include_directories(includes/NumCpp)
include_directories(includes)

target_link_libraries(all_files ${Boost_LIBRARIES})
#target_link_libraries( ${FFTW3_LIBRARIES})
