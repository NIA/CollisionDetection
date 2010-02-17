include_directories( ${COLLISIONS_SOURCE_DIR}/Collisions )
link_directories( ${COLLISIONS_BINARY_DIR}/Collisions )

# gtest include files:
include_directories( ../GoogleTestFramework/include )
link_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../_Lib )

set( TESTER_SRCS collisions_unittest.cpp  helpers_unittest.cpp  point_unittest.cpp )

## Compiler flags
if(CMAKE_COMPILER_IS_GNUCXX)
    set( CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wextra")
endif()

add_executable( tester ${TESTER_SRCS} )
target_link_libraries( tester collisions gtest_main )
