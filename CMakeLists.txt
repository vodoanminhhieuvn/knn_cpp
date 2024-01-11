cmake_minimum_required(VERSION 3.5)
project(knn_cpp CXX)

# Set up C++ version and properties
include(CheckIncludeFileCXX)

check_include_file_cxx(any HAS_ANY)
check_include_file_cxx(string_view HAS_STRING_VIEW)
check_include_file_cxx(coroutine HAS_COROUTINE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Copy data file to build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/iris.data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Download library usinng FetchContent
include(FetchContent)

FetchContent_Declare(matplotplusplus
        GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus
        GIT_TAG origin/master)

FetchContent_GetProperties(matplotplusplus)
if(NOT matplotplusplus_POPULATED)
  FetchContent_Populate(matplotplusplus)
  add_subdirectory(${matplotplusplus_SOURCE_DIR} ${matplotplusplus_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG        7.1.3  # Adjust the version as needed
)

FetchContent_MakeAvailable(fmt)

# Add executable and link project libraries and folders
add_executable(${PROJECT_NAME} main.cc)

target_link_libraries(${PROJECT_NAME} PUBLIC matplot fmt::fmt)

aux_source_directory(lib LIB_SRC)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(${PROJECT_NAME} PRIVATE ${LIB_SRC})

add_subdirectory(tests)
