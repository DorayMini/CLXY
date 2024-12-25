cmake_minimum_required(VERSION 3.28)

set(PROJECT_NAME CLYX)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
option(ENABLE_DEBUG "Enable debugging" OFF)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

if(ENABLE_DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

set(SOURCES_DIR ${CMAKE_SOURCE_DIR}/src)
set(HEADERS_DIR ${SOURCES_DIR}/private)

file(GLOB SOURCES_FILES "${SOURCES_DIR}/*.cpp")
file(GLOB HEADERS_FILES "${HEADERS_DIR}/*.hpp")

if(NOT SOURCES_FILES)
    message(FATAL_ERROR "No source files found in ${SOURCES_DIR}")
endif()

if(NOT HEADERS_FILES)
    message(WARNING "No header files found in ${HEADERS_DIR}")
endif()

if(BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME} SHARED
        ${SOURCES_FILES}
        ${HEADERS_FILES}
    )
else()
    add_library(${PROJECT_NAME} STATIC
        ${SOURCES_FILES}
        ${HEADERS_FILES}
    )
endif()

set(MAIN_FILE ${CMAKE_SOURCE_DIR}/main.cpp)
if(NOT EXISTS ${MAIN_FILE})
    message(FATAL_ERROR "Main file not found: ${MAIN_FILE}")
endif()

set(PROG_NAME EXEC)
add_executable(${PROG_NAME} ${MAIN_FILE})

target_include_directories(${PROJECT_NAME} PRIVATE ${HEADERS_DIR} ${SOURCES_DIR})
target_include_directories(${PROG_NAME} PRIVATE ${HEADERS_DIR} ${SOURCES_DIR})

target_link_libraries(${PROG_NAME} PRIVATE ${PROJECT_NAME})