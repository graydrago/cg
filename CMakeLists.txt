cmake_minimum_required(VERSION 3.5)

project(cg)

function(add_flag flag)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
endfunction()

set(SOURCE_EXE ./src/main.cpp)

add_executable( ${PROJECT_NAME} ${SOURCE_EXE} )

add_flag("-std=c++11")
add_flag("-Wall")
add_flag("-g")

target_link_libraries( ${PROJECT_NAME} SDL2 SDL2_mixer GL GLEW)

