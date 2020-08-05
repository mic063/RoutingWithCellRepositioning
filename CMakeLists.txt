cmake_minimum_required(VERSION 3.1)

project(cell_move_router)
set(BIN_NAME "cell_move_router")
message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_BUILD_TYPE Debug)

# Print info on build
if( CMAKE_BUILD_TYPE MATCHES "[Dd][Ee][Bb][Uu][Gg]" )
        message( "INFO: DEBUG BUILD" )
        # for debug type builds, turn on verbose makefiles
        set(CMAKE_VERBOSE_MAKEFILE ON)

        # Tell other CMake files that we're doing a debug build
        set(DEBUG_BUILD 1)

        # Tell C/C++ that we're doing a debug build
        add_definitions(-DDEBUG)
endif()
if( CMAKE_BUILD_TYPE MATCHES "[Rr][Ee][Ll][Ee][Aa][Ss][Ee]" )
        message( "INFO: RELEASE BUILD" )
endif()

set(BUILD_TCL OFF CACHE BOOL "Build TCL SWIG module" FORCE)

add_subdirectory(third_party/fastroute)
add_subdirectory(third_party/flute3)
add_subdirectory(third_party/pdrev)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(${BIN_NAME} ${SRC_FILES})

target_include_directories(${BIN_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/fastroute/include
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/flute
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

target_link_libraries(${BIN_NAME}
        FastRoute4.1
        flute
        )
