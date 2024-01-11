cmake_minimum_required(VERSION 3.5)
project(knn_cpp CXX)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.11.0
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(matplotplusplus
        GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus
        GIT_TAG origin/master)

FetchContent_GetProperties(matplotplusplus)
if(NOT matplotplusplus_POPULATED)
  FetchContent_Populate(matplotplusplus)
  add_subdirectory(${matplotplusplus_SOURCE_DIR} ${matplotplusplus_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

function(knn_cpp_test TEST_NAME TEST_SOURCE)
  add_executable(${TEST_NAME} ${TEST_SOURCE})

  target_link_libraries(${TEST_NAME} PUBLIC matplot)

  aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/../lib LIB_SOURCES)

  target_link_libraries(${TEST_NAME} PRIVATE gtest gtest_main gmock gmock_main)

  target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../)

  target_sources(${TEST_NAME} PRIVATE ${LIB_SOURCES} )

  include(GoogleTest)
  gtest_discover_tests(${TEST_NAME})

endfunction()

knn_cpp_test(LinearAlgebraTest la_test.cc)
knn_cpp_test(KnnTest knn_test.cc)
knn_cpp_test(UtilsTest utils_test.cc)
