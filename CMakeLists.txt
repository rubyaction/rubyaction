cmake_minimum_required(VERSION 2.8)

set(project_name action)
project(${project_name})

set(CMAKE_CXX_FLAGS "-std=c++0x -stdlib=libc++")
set(CMAKE_OSX_ARCHITECTURES x86_64 CACHE STRING "build for 64-bit only" FORCE)
set(ARCH x86_64)

set(${project_name}_include
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/extlibs/
  ${PROJECT_SOURCE_DIR}/extlibs/mruby
  ${PROJECT_SOURCE_DIR}/extlibs/stb_image
  ${PROJECT_SOURCE_DIR}/extlibs/SDL2/include
  ${PROJECT_SOURCE_DIR}/extlibs/SDL2_ttf
)

include_directories(${${project_name}_include})

add_subdirectory(extlibs)

file(GLOB_RECURSE ${project_name}_sources src/*.cpp)

# mruby
add_library(mruby_static STATIC IMPORTED)
set_property(TARGET mruby_static PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/extlibs/mruby/prebuilt/osx/libmruby.a)

# frameworks
find_library(opengl OpenGL)

set(${project_name}_libraries
  mruby_static
  Box2D_static
  SDL2-static
  SDL2_ttf-static
  ${opengl}
)

add_executable(${project_name} ${${project_name}_sources})
target_link_libraries(${project_name} ${${project_name}_libraries})
