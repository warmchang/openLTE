cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pg -Wall")

add_library(EUTRA_UE_Variables_a00_lib
  VarLogMeasConfig.cc
  VarLogMeasReport.cc
  VarMeasConfig.cc
  VarMeasReportList.cc
  VarMeasReport.cc
  CellsTriggeredList.cc
  VarShortMAC_Input.cc
)
include_directories(../EUTRA_RRC_Definitions_a00_gen)
