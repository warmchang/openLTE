include(GrPlatform)
add_subdirectory(rrc/EUTRA_RRC_Definitions_a00_gen)
add_library(lte
  src/liblte_common.cc
  src/liblte_interface.cc
  src/liblte_phy.cc
  src/liblte_mac.cc
  src/liblte_rlc.cc
  src/liblte_pdcp.cc
  src/liblte_mme.cc
  src/liblte_security.cc
  src/liblte_fdd_dl_scan_block.cc
)
include_directories(hdr rrc/EUTRA_RRC_Definitions_a00_gen ${CMAKE_SOURCE_DIR}/cmn_hdr)

add_executable(liblte_common_test
  tests/liblte_common_tests.cc
  src/liblte_common.cc
)
add_test(liblte_common_test liblte_common_test)
add_executable(liblte_interface_test
  tests/liblte_interface_tests.cc
  src/liblte_interface.cc
)
add_test(liblte_interface_test liblte_interface_test)
add_executable(liblte_mac_test
  tests/liblte_mac_tests.cc
  src/liblte_mac.cc
  src/liblte_common.cc
)
add_test(liblte_mac_test liblte_mac_test)
add_executable(liblte_mme_test
  tests/liblte_mme_tests.cc
  src/liblte_mme.cc
  src/liblte_common.cc
  src/liblte_security.cc
)
add_test(liblte_mme_test liblte_mme_test)
target_link_libraries(liblte_mme_test ${POLARSSL_LIBRARIES} EUTRA_RRC_Definitions_a00_lib)
add_executable(liblte_pdcp_test
  tests/liblte_pdcp_tests.cc
  src/liblte_pdcp.cc
  src/liblte_common.cc
  src/liblte_security.cc
)
add_test(liblte_pdcp_test liblte_pdcp_test)
target_link_libraries(liblte_pdcp_test ${POLARSSL_LIBRARIES} EUTRA_RRC_Definitions_a00_lib)
add_executable(liblte_phy_test
  tests/liblte_phy_tests.cc
  src/liblte_phy.cc
  src/liblte_common.cc
)
add_test(liblte_phy_test liblte_phy_test)
target_link_libraries(liblte_phy_test fftw3f EUTRA_RRC_Definitions_a00_lib)
add_executable(liblte_rlc_test
  tests/liblte_rlc_tests.cc
  src/liblte_rlc.cc
  src/liblte_common.cc
)
add_test(liblte_rlc_test liblte_rlc_test)
add_executable(liblte_security_test
  tests/liblte_security_tests.cc
  src/liblte_security.cc
)
add_test(liblte_security_test liblte_security_test)
target_link_libraries(liblte_security_test ${POLARSSL_LIBRARIES} EUTRA_RRC_Definitions_a00_lib)
