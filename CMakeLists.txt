cmake_minimum_required(VERSION 2.8)

set(project_name action)

project(${project_name})

# set(CMAKE_OSX_ARCHITECTURES i386 CACHE STRING "do not build for 64-bit" FORCE)
# set(ARCH i386)

set(${project_name}_include
  include
  lib/include/mruby
)

file(GLOB_RECURSE ${project_name}_sources src/*.cpp)

include_directories(${${project_name}_include})

# mruby
add_library(mruby STATIC IMPORTED)
set_property(TARGET mruby PROPERTY IMPORTED_LOCATION lib/osx/libmruby.a)

set(${project_name}_libraries
  mruby
)

add_definitions(-std=c++11)
add_executable(${project_name} ${${project_name}_sources})
target_link_libraries(${project_name} ${${project_name}_libraries})
