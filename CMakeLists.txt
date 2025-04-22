cmake_minimum_required(VERSION 3.14-3.18)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0175 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0177 NEW)

if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")
endif()

if(NOT DEFINED IMPROC_SUPERPROJECT_VERSION)
  set(IMPROC_SUPERPROJECT_VERSION 1.0.0)
endif()

if(NOT DEFINED IMPROC_COVERAGE_VERSION)
  if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(IMPROC_COVERAGE_VERSION "17")
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(IMPROC_COVERAGE_VERSION "13")
  else()
    set(IMPROC_COVERAGE_VERSION "17")
  endif()
endif()

if(NOT DEFINED IMPROC_CORECV_WITH_TESTS)
  set(IMPROC_CORECV_WITH_TESTS OFF)
endif()

if(IMPROC_WITH_TESTS OR IMPROC_WITH_COVERAGE OR IMPROC_CORECV_WITH_TESTS)
  list(APPEND VCPKG_MANIFEST_FEATURES "tests")
endif()

project(
  improc-corecv
  VERSION     ${IMPROC_SUPERPROJECT_VERSION}
  LANGUAGES   CXX
)
string(REPLACE "-" "_" PROJECT_NAME_FILE ${PROJECT_NAME})

include(FetchContent)

# Project configuration
option(IMPROC_WITH_TESTS 			     "Building library with tests"          OFF)
option(IMPROC_WITH_COVERAGE  	     "Building library with code coverage"  OFF)
option(BUILD_SHARED_LIBS           "Building shared libraries"            ON)

if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"      CACHE PATH "Archive output dir.")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"      CACHE PATH "Library output dir.")
  set(CMAKE_PDB_OUTPUT_DIRECTORY     "${CMAKE_BINARY_DIR}/bin"      CACHE PATH "PDB (MSVC debug symbol)output dir.")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"      CACHE PATH "Executable/dll output dir.")
  set(CMAKE_DEBUG_POSTFIX d)

  if(IMPROC_WITH_COVERAGE AND NOT IMPROC_WITH_TESTS AND NOT IMPROC_CORECV_WITH_TESTS)
    message(STATUS "Warning: IMPROC_WITH_COVERAGE ON but tests of image processing library is not ON")
    message(STATUS "---------> Setting IMPROC_CORECV_WITH_TESTS = ON")
    set(IMPROC_CORECV_WITH_TESTS ON)
  endif()

  if(DEFINED CMAKE_TOOLCHAIN_FILE)
    find_package(improc-infrastructure CONFIG REQUIRED)
    find_package(improc-services CONFIG REQUIRED)
    add_library(improc::infrastructure ALIAS improc::improc-infrastructure)
    add_library(improc::services ALIAS improc::improc-services)
  else()
    add_subdirectory(${PROJECT_SOURCE_DIR}/modules/infrastructure ${CMAKE_BINARY_DIR}/infrastructure)
    add_subdirectory(${PROJECT_SOURCE_DIR}/modules/services       ${CMAKE_BINARY_DIR}/services)
  endif()
endif()

# Add external dependencies
if(DEFINED CMAKE_TOOLCHAIN_FILE)
  find_package(OpenCV CONFIG REQUIRED)
  set(IMPROC_OPENCV_LIBS          ${OpenCV_LIBS})
else()
  # OPENCV
  FetchContent_Declare(
    opencv
    GIT_REPOSITORY  https://github.com/opencv/opencv
    GIT_TAG         4.11.0
    SOURCE_DIR      ${PROJECT_SOURCE_DIR}/external/opencv
  )
  set(BUILD_opencv_highgui  OFF)
  set(BUILD_opencv_apps     OFF)
  set(BUILD_PERF_TESTS      OFF)
  set(BUILD_TESTS           OFF)
  set(WITH_WEBP             OFF)
  set(WITH_TBB              ON )
  set(WITH_OPENGL           ON )
  FetchContent_MakeAvailable(opencv)

  if (WIN32 OR WINCE)
    target_compile_options(opencv_flann      PRIVATE -Wno-unknown-pragmas)
    target_compile_options(opencv_imgproc    PRIVATE -Wno-unknown-pragmas)
    target_compile_options(opencv_imgcodecs  PRIVATE -Wno-unknown-pragmas)
    target_compile_options(opencv_features2d PRIVATE -Wno-unknown-pragmas)
    target_compile_options(opencv_dnn        PRIVATE -Wno-unknown-pragmas)
    target_compile_options(opencv_calib3d    PRIVATE -Wno-unknown-pragmas)
    target_compile_options(opencv_ml         PRIVATE -Wno-unknown-pragmas)
    target_compile_options(opencv_photo      PRIVATE -Wno-unknown-pragmas)
    target_compile_options(opencv_objdetect  PRIVATE -Wno-unknown-pragmas)
    target_compile_options(opencv_video      PRIVATE -Wno-unknown-pragmas)
    target_compile_options(opencv_stitching  PRIVATE -Wno-unknown-pragmas)
    target_compile_options(opencv_gapi       PRIVATE -Wno-unknown-pragmas)
  endif()

  list(APPEND IMPROC_OPENCV_LIBS opencv_core)
  list(APPEND IMPROC_OPENCV_LIBS opencv_imgproc)
  list(APPEND IMPROC_OPENCV_LIBS opencv_imgcodecs)                                                        # for drawer support
  set(IMPROC_OPENCV_INSTALL_LIBS ${IMPROC_OPENCV_LIBS})  

  target_include_directories(opencv_core      INTERFACE $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
                                                        $<INSTALL_INTERFACE:include> )
  target_include_directories(opencv_core      INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/external/opencv/include>
                                                        $<INSTALL_INTERFACE:include> )
  target_include_directories(opencv_core      INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/external/opencv/modules/core/include>
                                                        $<INSTALL_INTERFACE:include> )
  target_include_directories(opencv_imgproc   INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/external/opencv/modules/imgproc/include>
                                                        $<INSTALL_INTERFACE:include> )
  target_include_directories(opencv_imgcodecs INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/external/opencv/modules/imgcodecs/include>
                                                        $<INSTALL_INTERFACE:include> )
endif()

set(PKG_CONFIG_REQUIRES "improc-services ${IMPROC_OPENCV_LIBS}")
message(STATUS "Build ${PROJECT_NAME} Version: ${PROJECT_VERSION}")
message(STATUS "IMPROC_WITH_TESTS       : ${IMPROC_WITH_TESTS}")
message(STATUS "IMPROC_CORECV_WITH_TESTS: ${IMPROC_CORECV_WITH_TESTS}")
message(STATUS "IMPROC_WITH_COVERAGE    : ${IMPROC_WITH_COVERAGE}")
message(STATUS "IMPROC_COVERAGE_VERSION : ${IMPROC_COVERAGE_VERSION}")
message(STATUS "CMake Toolchain File: ${CMAKE_TOOLCHAIN_FILE}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Install Dir: ${CMAKE_INSTALL_PREFIX}")

set(
  IMPROC_CORECV_LIB_FILES

  ${PROJECT_SOURCE_DIR}/include/improc/corecv/logger_improc.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/corecv/parsers/json_parser.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/corecv/structures/color_space.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/corecv/structures/image_format.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/corecv/structures/interpolation_type.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/corecv/structures/kernel_shape.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/corecv/structures/morphological_oper.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/corecv/structures/rotation_type.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/corecv/structures/threshold_type.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/services/convert_color_space.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/services/resize_image.hpp
  
  ${PROJECT_SOURCE_DIR}/src/color_space.cpp
  ${PROJECT_SOURCE_DIR}/src/image_format.cpp
  ${PROJECT_SOURCE_DIR}/src/image.cpp
  ${PROJECT_SOURCE_DIR}/src/interpolation_type.cpp
  ${PROJECT_SOURCE_DIR}/src/kernel_shape.cpp
  ${PROJECT_SOURCE_DIR}/src/morphological_oper.cpp
  ${PROJECT_SOURCE_DIR}/src/rotation_type.cpp
  ${PROJECT_SOURCE_DIR}/src/threshold_type.cpp
)

if (BUILD_SHARED_LIBS)
  add_library(${PROJECT_NAME} SHARED ${IMPROC_CORECV_LIB_FILES})
else()
  add_library(${PROJECT_NAME} STATIC ${IMPROC_CORECV_LIB_FILES})
endif()
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

# Link dependencies
target_link_libraries       (${PROJECT_NAME}  PRIVATE    improc::services)
target_link_libraries       (${PROJECT_NAME}  PRIVATE    ${IMPROC_OPENCV_LIBS})
target_link_libraries       (${PROJECT_NAME}  INTERFACE  improc::services)
target_link_libraries       (${PROJECT_NAME}  INTERFACE  ${IMPROC_OPENCV_LIBS})

# Tests configuration
if(IMPROC_WITH_TESTS OR IMPROC_CORECV_WITH_TESTS)
  add_subdirectory(${PROJECT_SOURCE_DIR}/test     ${CMAKE_BINARY_DIR}/improc_corecv_test)
endif()

# Install configuration
if (NOT DEFINED CMAKE_INSTALL_LIBDIR)
  set(CMAKE_INSTALL_LIBDIR "lib")
endif()
if (NOT DEFINED CMAKE_INSTALL_BINDIR)
  set(CMAKE_INSTALL_BINDIR "bin")
endif()
if (NOT DEFINED CMAKE_INSTALL_INCLUDEDIR)
  set(CMAKE_INSTALL_INCLUDEDIR "include")
endif()

# Include files
install(
  TARGETS     ${PROJECT_NAME}
  EXPORT      ${PROJECT_NAME}_targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/improc                  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES     ${PROJECT_SOURCE_DIR}/LICENSE                         DESTINATION share/licenses/improc/corecv)
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  install(FILES     ${PROJECT_SOURCE_DIR}/external/opencv/LICENSE       DESTINATION share/licenses/improc/opencv)
endif()

# pkg-config files
if(IS_ABSOLUTE ${CMAKE_INSTALL_INCLUDEDIR})
  set(PKG_CONFIG_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR})
else()
  set(PKG_CONFIG_INCLUDEDIR "\${prefix}/${CMAKE_INSTALL_INCLUDEDIR}")
endif()
if(IS_ABSOLUTE ${CMAKE_INSTALL_LIBDIR})
  set(PKG_CONFIG_LIBDIR ${CMAKE_INSTALL_LIBDIR})
else()
  set(PKG_CONFIG_LIBDIR "\${exec_prefix}/${CMAKE_INSTALL_LIBDIR}")
endif()
configure_file(
  ${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME_FILE}.pc.in
  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc 
  @ONLY )
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

# CMake config files
set(TARGETS_FILE "${PROJECT_NAME}-targets.cmake")
set(EXPORT_DESTINATION_DIR share/${PROJECT_NAME})
install(EXPORT ${PROJECT_NAME}_targets
        FILE ${TARGETS_FILE}
        NAMESPACE improc::
        DESTINATION ${EXPORT_DESTINATION_DIR})
configure_file(
  ${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME_FILE}_config.cmake.in
  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  @ONLY )
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}-config.cmake DESTINATION ${EXPORT_DESTINATION_DIR})
