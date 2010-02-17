include_directories( ${COLLISIONS_SOURCE_DIR}/Collisions )
link_directories( ${COLLISIONS_BINARY_DIR}/Collisions )

set( TESTER_SRCS collisions_unittest.cpp  helpers_unittest.cpp  point_unittest.cpp )

add_executable( tester ${TESTER_SRCS} )
target_link_libraries( tester collisions )
