cmake_minimum_required(VERSION 3.14-3.18)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")

if(NOT DEFINED IMPROC_SUPERPROJECT_VERSION)
  set(IMPROC_SUPERPROJECT_VERSION 1.0.0)
endif()

project(
  improc_corecv
  VERSION     ${IMPROC_SUPERPROJECT_VERSION}
  LANGUAGES   CXX
)

include(FetchContent)

# Project configuration
if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"      CACHE PATH "Archive output dir.")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"      CACHE PATH "Library output dir.")
  set(CMAKE_PDB_OUTPUT_DIRECTORY     "${CMAKE_BINARY_DIR}/bin"      CACHE PATH "PDB (MSVC debug symbol)output dir.")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"      CACHE PATH "Executable/dll output dir.")
  set(CMAKE_DEBUG_POSTFIX d)
  option(IMPROC_WITH_TESTS 			     "Building library with tests"          OFF)
  option(IMPROC_WITH_COVERAGE  	     "Building library with code coverage"  OFF)
  option(BUILD_SHARED_LIBS           "Building shared libraries"            ON)

  add_subdirectory(${PROJECT_SOURCE_DIR}/../infrastructure ${CMAKE_BINARY_DIR}/infrastructure)
  add_subdirectory(${PROJECT_SOURCE_DIR}/../services       ${CMAKE_BINARY_DIR}/services)
endif()

# Add external dependencies
if(NOT DEFINED IMPROC_OPENCV_DIR)
  # OPENCV
  FetchContent_Declare(
    opencv
    GIT_REPOSITORY  https://github.com/opencv/opencv
    GIT_TAG         4.7.0
    SOURCE_DIR      ${PROJECT_SOURCE_DIR}/external/opencv
  )
  set(BUILD_opencv_apps     OFF)
  set(BUILD_PERF_TESTS      OFF)
  set(BUILD_TESTS           OFF)
  set(WITH_TBB              ON )
  set(WITH_V4L              ON )
  set(WITH_OPENGL           ON )
  FetchContent_MakeAvailable(opencv)
  list(APPEND IMPROC_OPENCV_LIBS opencv_core)
  list(APPEND IMPROC_OPENCV_LIBS opencv_imgproc)
  list(APPEND IMPROC_OPENCV_LIBS opencv_imgcodecs)                                                        # for drawer support
  list(APPEND IMPROC_OPENCV_INCLUDE_DIRS ${CMAKE_BINARY_DIR})
  list(APPEND IMPROC_OPENCV_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/external/opencv/include)
  list(APPEND IMPROC_OPENCV_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/external/opencv/modules/core/include)
  list(APPEND IMPROC_OPENCV_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/external/opencv/modules/imgproc/include)
  list(APPEND IMPROC_OPENCV_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/external/opencv/modules/imgcodecs/include) # for drawer support
else()
  set(OpenCV_DIR ${IMPROC_OPENCV_DIR})
  find_package(OpenCV REQUIRED)
  set(IMPROC_OPENCV_LIBS          ${OpenCV_LIBS})
  set(IMPROC_OPENCV_INCLUDE_DIRS  ${OpenCV_INCLUDE_DIRS})
endif()

# # DLIB
# FetchContent_Declare(
#   dlib
#   GIT_REPOSITORY  https://github.com/davisking/dlib
#   GIT_TAG         v19.22
#   SOURCE_DIR      ${CMAKE_CURRENT_BINARY_DIR}/../external/dlib
# )
# FetchContent_MakeAvailable(dlib)

message(STATUS "Build ${PROJECT_NAME} Version: ${PROJECT_VERSION}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Install Dir: ${CMAKE_INSTALL_PREFIX}")

set(
  IMPROC_CORECV_LIB_FILES

  ${PROJECT_SOURCE_DIR}/include/improc/corecv/logger_improc.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/corecv/structures/color_space.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/corecv/structures/threshold_type.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/corecv/structures/kernel_shape.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/corecv/structures/interpolation_type.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/corecv/structures/morphological_oper.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/corecv/structures/image_format.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/services/convert_color_space.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/services/resize_image.hpp
  
  ${PROJECT_SOURCE_DIR}/src/color_space.cpp
  ${PROJECT_SOURCE_DIR}/src/threshold_type.cpp
  ${PROJECT_SOURCE_DIR}/src/kernel_shape.cpp
  ${PROJECT_SOURCE_DIR}/src/interpolation_type.cpp
  ${PROJECT_SOURCE_DIR}/src/morphological_oper.cpp
  ${PROJECT_SOURCE_DIR}/src/image_format.cpp
  ${PROJECT_SOURCE_DIR}/src/image.cpp
)

add_library(${PROJECT_NAME} SHARED ${IMPROC_CORECV_LIB_FILES})
add_library(improc::corecv ALIAS ${PROJECT_NAME})
add_dependencies(${PROJECT_NAME} improc::services ${IMPROC_OPENCV_LIBS})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD           17)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD_REQUIRED  TRUE)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE        CXX)
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION                ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX          ${CMAKE_DEBUG_POSTFIX})

target_include_directories  (${PROJECT_NAME}  PRIVATE   ${PROJECT_SOURCE_DIR}/include)
target_include_directories  (${PROJECT_NAME}  INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                              $<INSTALL_INTERFACE:include> )

target_include_directories  (${PROJECT_NAME}  PRIVATE   ${IMPROC_OPENCV_INCLUDE_DIRS})
target_include_directories  (${PROJECT_NAME}  INTERFACE ${IMPROC_OPENCV_INCLUDE_DIRS})
                                              
# Link dependencies
target_link_libraries       (${PROJECT_NAME}  PRIVATE    improc::services)
target_link_libraries       (${PROJECT_NAME}  PRIVATE    ${IMPROC_OPENCV_LIBS})
target_link_libraries       (${PROJECT_NAME}  INTERFACE  improc::services)
target_link_libraries       (${PROJECT_NAME}  INTERFACE  ${IMPROC_OPENCV_LIBS})

# Tests configuration
if(IMPROC_WITH_TESTS)
  add_subdirectory(${PROJECT_SOURCE_DIR}/test     ${CMAKE_BINARY_DIR}/improc_corecv_test)
endif()

# Install configuration
set(${PROJECT_NAME}_libs ${PROJECT_NAME} improc_services ${IMPROC_OPENCV_LIBS})
install(
  TARGETS     ${${PROJECT_NAME}_libs}
  DESTINATION lib
  EXPORT      ${PROJECT_NAME}_target 
)
install(FILES     ${PROJECT_SOURCE_DIR}/external/opencv/LICENSE DESTINATION share/licenses/improc/opencv)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/improc          DESTINATION include)
