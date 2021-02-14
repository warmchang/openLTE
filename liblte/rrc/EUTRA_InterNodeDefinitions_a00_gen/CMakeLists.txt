cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pg -Wall")

add_library(EUTRA_InterNodeDefinitions_a00_lib
  HandoverCommand.cc
  HandoverCommand_r8_IEs.cc
  HandoverPreparationInformation.cc
  HandoverPreparationInformation_r8_IEs.cc
  HandoverPreparationInformation_v920_IEs.cc
  UERadioAccessCapabilityInformation.cc
  UERadioAccessCapabilityInformation_r8_IEs.cc
  AS_Config.cc
  AS_Context.cc
  ReestablishmentInfo.cc
  AdditionalReestabInfoList.cc
  AdditionalReestabInfo.cc
  Key_eNodeB_Star.cc
  RRM_Config.cc
  CandidateCellInfoList_r10.cc
  CandidateCellInfo_r10.cc
)
include_directories(../EUTRA_RRC_Definitions_a00_gen)
