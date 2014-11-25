cmake_minimum_required(VERSION 2.8)

set(project_name action)

project(${project_name})

set(CMAKE_CXX_FLAGS "-std=c++0x -stdlib=libc++")

set(CMAKE_OSX_ARCHITECTURES x86_64 CACHE STRING "build for 64-bit only" FORCE)
set(ARCH x86_64)

set(${project_name}_include
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/lib/include
  ${PROJECT_SOURCE_DIR}/lib/include/mruby
  ${PROJECT_SOURCE_DIR}/lib/include/Box2D
  ${PROJECT_SOURCE_DIR}/lib/include/SDL2
  ${PROJECT_SOURCE_DIR}/lib/include/SDL2_gfx
  ${PROJECT_SOURCE_DIR}/lib/include/SDL2_ttf
  ${PROJECT_SOURCE_DIR}/lib/include/stb_image
)

file(GLOB_RECURSE ${project_name}_sources src/*.cpp)

include_directories(${${project_name}_include})

# mruby
add_library(mruby STATIC IMPORTED)
set_property(TARGET mruby PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/osx/libmruby.a)

# Box2D
add_library(box2d STATIC IMPORTED)
set_property(TARGET box2d PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/osx/libBox2D.a)

# FreeType
add_library(freetype STATIC IMPORTED)
set_property(TARGET freetype PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/osx/libfreetype.a)

# BZip2
add_library(bzip STATIC IMPORTED)
set_property(TARGET bzip PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/osx/libbz2.a)

# ZLib
add_library(zlib STATIC IMPORTED)
set_property(TARGET zlib PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/osx/libz.a)

# libPNG
add_library(png STATIC IMPORTED)
set_property(TARGET png PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/osx/libpng.a)

# stb_image
add_library(stb_image STATIC IMPORTED)
set_property(TARGET stb_image PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/osx/libSTB_Image.a)

# SDL2
add_library(sdl2 STATIC IMPORTED)
set_property(TARGET sdl2 PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/osx/libSDL2.a)

# SDL2_gfx
add_library(sdl2_gfx STATIC IMPORTED)
set_property(TARGET sdl2_gfx PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/osx/libSDL2_gfx.a)

# SDL2_ttf
add_library(sdl2_ttf STATIC IMPORTED)
set_property(TARGET sdl2_ttf PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/osx/libSDL2_ttf.a)

# frameworks
find_library(cocoa Cocoa)
find_library(carbon Carbon)
find_library(iokit IOKit)
find_library(opengl OpenGL)
find_library(audiotoolbox AudioToolbox)
find_library(audiounit AudioUnit)
find_library(coreaudio CoreAudio)
find_library(forcefeedback ForceFeedback)
find_library(system system)
find_library(crypto crypto)
find_library(ssl ssl)
find_library(iconv iconv)

set(${project_name}_libraries
  mruby
  box2d
  freetype
  bzip
  zlib
  png
  stb_image
  sdl2
  sdl2_gfx
  sdl2_ttf
  ${cocoa}
  ${carbon}
  ${iokit}
  ${opengl}
  ${audiotoolbox}
  ${audiounit}
  ${coreaudio}
  ${forcefeedback}
  ${system}
  ${crypto}
  ${ssl}
  ${iconv}
)

add_executable(${project_name} ${${project_name}_sources})
target_link_libraries(${project_name} ${${project_name}_libraries})
