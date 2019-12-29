

project(increment_leds)

file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
                       "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
                       "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

add_executable(${PROJECT_NAME} ${SRCS})

include_directories(${PROJECT_NAME} ${socsys_SOURCE_DIR})
include_directories(${PROJECT_NAME} ${memtool_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} memtool)

