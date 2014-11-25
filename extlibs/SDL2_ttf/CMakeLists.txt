CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (SDL_ttf)

ADD_SUBDIRECTORY (freetype)
INCLUDE_DIRECTORIES (
	freetype/include
)

ADD_LIBRARY (SDL2_ttf-static STATIC
	SDL_ttf.c
	SDL_ttf.h
)
TARGET_LINK_LIBRARIES (SDL2_ttf-static freetype_static)
