cmake_minimum_required( VERSION 2.6 )
project( COLLISIONS )

SET( CMAKE_VERBOSE_MAKEFILE on )

add_subdirectory( Collisions )
add_subdirectory( Tester )

## Compiler flags
if(CMAKE_COMPILER_IS_GNUCXX)
    list(APPEND CMAKE_CXX_FLAGS -Wall -Wextra)
endif()
