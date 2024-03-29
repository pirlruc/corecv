cmake_minimum_required(VERSION 3.14-3.18)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")

if(NOT DEFINED IMPROC_SUPERPROJECT_VERSION)
  set(IMPROC_SUPERPROJECT_VERSION 1.0.0)
endif()

if(NOT DEFINED IMPROC_CORECV_WITH_TESTS)
  set(IMPROC_CORECV_WITH_TESTS OFF)
endif()

if(IMPROC_WITH_TESTS OR IMPROC_CORECV_WITH_TESTS)
  list(APPEND VCPKG_MANIFEST_FEATURES "tests")
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

  add_subdirectory(${PROJECT_SOURCE_DIR}/modules/infrastructure ${CMAKE_BINARY_DIR}/infrastructure)
  add_subdirectory(${PROJECT_SOURCE_DIR}/modules/services       ${CMAKE_BINARY_DIR}/services)
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
    GIT_TAG         4.9.0
    SOURCE_DIR      ${PROJECT_SOURCE_DIR}/external/opencv
  )
  set(BUILD_opencv_apps     OFF)
  set(BUILD_PERF_TESTS      OFF)
  set(BUILD_TESTS           OFF)
  set(WITH_V4L              OFF)
  set(WITH_WEBP             OFF)
  set(WITH_TBB              ON )
  set(WITH_OPENGL           ON )
  FetchContent_MakeAvailable(opencv)
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

message(STATUS "Build ${PROJECT_NAME} Version: ${PROJECT_VERSION}")
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
  ${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}.pc.in
  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc 
  @ONLY )
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

# CMake config files
set(CONFIG_TARGETS_FILE "${PROJECT_NAME}ConfigTargets.cmake")
set(EXPORT_DESTINATION_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
install(EXPORT ${PROJECT_NAME}_targets FILE ${CONFIG_TARGETS_FILE} DESTINATION ${EXPORT_DESTINATION_DIR})

include(CMakePackageConfigHelpers)
configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}_config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake 
  INSTALL_DESTINATION ${EXPORT_DESTINATION_DIR} )
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  VERSION ${IMPROC_SUPERPROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake 
              ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${EXPORT_DESTINATION_DIR})
