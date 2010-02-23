set( COLLISIONS_SRCS collision.cpp )

## Compiler flags
if(CMAKE_COMPILER_IS_GNUCXX)
    set( CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wextra")
endif()

add_library( collisions ${COLLISIONS_SRCS} )
