add_definitions("-w")
set(CMAKE_BUILD_TYPE Release) # SFML
set(BUILD_SHARED_LIBS FALSE) # SFML

add_subdirectory(Box2D)
add_subdirectory(SFML)
#add_subdirectory(SDL2)
#add_subdirectory(SDL2_ttf)
