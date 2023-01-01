cmake_minimum_required(VERSION 3.15)

project(
    clob
    VERSION 1.1.0
    LANGUAGES C CXX)

add_library(${PROJECT_NAME})
add_library(clob:clob ALIAS ${PROJECT_NAME})

option(CLOB_BUILD_TESTING "Build testing for clog")
option(CLOB_DEBUG_BRZ "Enable debug logs for BRZ module")
option(CLOB_BUILD_EXAMPLES "Build clob examples")

if(CLOB_DEBUG_BRZ)
    message(STATUS "Build with clob debug logs")
    target_compile_definitions(${PROJECT_NAME} PRIVATE _CLOB_DEBUG_BRZ_)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
            "Default build type: Release" FORCE)
endif()

add_subdirectory(src)
add_subdirectory(include)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")


if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR CLOB_BUILD_TESTING) AND BUILD_TESTING)
    message(STATUS "Build testing")
    add_subdirectory(tests)
    include(GoogleTest)
    add_subdirectory(extern/googletest)
endif()

if(CLOB_BUILD_EXAMPLES)
    message(STATUS "Build clob examples")
    add_subdirectory(examples)
endif()
