include(GrPlatform)
add_library(tools
  src/libtools_server_socket.cc
  src/libtools_ipc_msgq.cc
  src/libtools_helpers.cc
)
include_directories(hdr ${CMAKE_SOURCE_DIR}/cmn_hdr ${CMAKE_SOURCE_DIR}/liblte/hdr ${CMAKE_SOURCE_DIR}/liblte/rrc/EUTRA_RRC_Definitions_a00_gen)
