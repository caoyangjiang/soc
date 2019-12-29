
project(memtool)

file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.h" 
                       "${CMAKE_CURRENT_SOURCE_DIR}/*.c" 
                       "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
message(${SRCS})

add_library(${PROJECT_NAME} STATIC ${SRCS})


