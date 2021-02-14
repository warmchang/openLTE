# Copyright 2011 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.


########################################################################
# Project setup
########################################################################
cmake_minimum_required(VERSION 2.6)
project(openLTE CXX C)
set(openLTE_version 0.21.0)
enable_testing()

#select the release build type by default to get optimization flags
if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "Release")
   message(STATUS "Build type not specified: defaulting to release.")
endif(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

########################################################################
# Compiler specific setup
########################################################################
if(CMAKE_COMPILER_IS_GNUCXX AND NOT WIN32)
    #http://gcc.gnu.org/wiki/Visibility
    add_definitions(-fvisibility=hidden)
endif()

########################################################################
# Find boost
########################################################################
SET(BOOST_REQUIRED_COMPONENTS
    system
)
if(UNIX AND EXISTS "/usr/lib64")
    list(APPEND BOOST_LIBRARYDIR "/usr/lib64") #fedora 64-bit fix
endif(UNIX AND EXISTS "/usr/lib64")
if(UNIX AND EXISTS "/usr/lib/x86_64-linux-gnu")
    list(APPEND BOOST_LIBRARYDIR "/usr/lib/x86_64-linux-gnu") #fedora 64-bit fix
endif(UNIX AND EXISTS "/usr/lib/x86_64-linux-gnu")
set(Boost_ADDITIONAL_VERSIONS
    "1.35.0" "1.35" "1.36.0" "1.36" "1.37.0" "1.37" "1.38.0" "1.38" "1.39.0" "1.39"
    "1.40.0" "1.40" "1.41.0" "1.41" "1.42.0" "1.42" "1.43.0" "1.43" "1.44.0" "1.44"
    "1.45.0" "1.45" "1.46.0" "1.46" "1.47.0" "1.47" "1.48.0" "1.48" "1.49.0" "1.49"
    "1.50.0" "1.50" "1.51.0" "1.51" "1.52.0" "1.52" "1.53.0" "1.53" "1.54.0" "1.54"
    "1.55.0" "1.55" "1.56.0" "1.56" "1.57.0" "1.57" "1.58.0" "1.58" "1.59.0" "1.59"
    "1.60.0" "1.60" "1.61.0" "1.61" "1.62.0" "1.62" "1.63.0" "1.63" "1.64.0" "1.64"
    "1.65.0" "1.65" "1.66.0" "1.66" "1.67.0" "1.67" "1.68.0" "1.68" "1.69.0" "1.69"
)
find_package(Boost "1.58" COMPONENTS ${BOOST_REQUIRED_COMPONENTS})

Set(Boost_LIBRARIES boost_chrono-mt-x64 boost_date_time-mt-x64 boost_filesystem-mt-x64 boost_program_options-mt-x64 boost_regex-mt-x64 boost_system-mt-x64 boost_unit_test_framework-mt-x64 boost_serialization-mt-x64 boost_thread-mt-x64)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost required to compile openLTE")
endif()

########################################################################
# Find gnuradio build dependencies
########################################################################
find_package(Gnuradio "3.8" REQUIRED COMPONENTS runtime blocks filter pmt fft)
include(GrVersion) #setup version info
find_package(gnuradio-blocks PATHS ${Gnuradio_DIR})
find_package(UHD)
find_package(gnuradio-uhd PATHS ${Gnuradio_DIR})
find_package(Volk REQUIRED)
find_package(GnuradioOsmosdr)
find_package(LibbladeRF)
find_package(FFTW3F)
find_package(Polarssl)

if(NOT Gnuradio_FOUND)
    message(FATAL_ERROR "GNURadio required to compile openLTE")
endif()

if(NOT GNURADIO_OSMOSDR_FOUND)
    message(FATAL_ERROR "GNURadio Osmosdr required to compile openLTE (http://sdr.osmocom.org/trac/wiki/GrOsmoSDR)")
endif()

if(NOT UHD_FOUND)
    message(FATAL_ERROR "UHD required to compile openLTE (http://code.ettus.com/redmine/ettus/projects/uhd/wiki)")
endif()

if(NOT LIBBLADERF_FOUND)
    message(FATAL_ERROR "LibbladeRF required to compile openLTE")
endif()

if(NOT FFTW3F_FOUND)
    message(FATAL_ERROR "FFTW3 required to compile openLTE")
endif()

########################################################################
# Create uninstall target
########################################################################
configure_file(
    ${CMAKE_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
@ONLY)

add_custom_target(uninstall
    ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
)

########################################################################
# Add subdirectories
########################################################################
add_subdirectory(liblte)
add_subdirectory(libtools)
add_subdirectory(LTE_fdd_dl_file_gen)
add_subdirectory(LTE_fdd_dl_file_scan)
add_subdirectory(LTE_fdd_dl_scan)
add_subdirectory(LTE_file_recorder)
add_subdirectory(LTE_fdd_enodeb)
