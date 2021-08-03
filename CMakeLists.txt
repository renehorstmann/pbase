cmake_minimum_required(VERSION 3.0)
project(pbase)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -march=native)  # march=native for best performance
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-long-long -pedantic -Wno-unused-function")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -march=native)  # march=native for best performance
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -Wno-unused-function")

# list all C source files
set(LIB_SOURCE_C
		src/rhc_impl.c
        src/types/cloud.c
		src/types/indices.c
#        src/types/indiceslist.c
#        src/types/meshindices.c
#        src/types/vector.c
#        src/types/matrix.c
        )

# list all CXX source files
set(LIB_SOURCE_CXX

	)



add_library(pbase SHARED ${LIB_SOURCE_C} ${LIB_SOURCE_CXX} )
set_target_properties(pbase PROPERTIES LINKER_LANGUAGE C)

set_property(TARGET pbase PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(pbase
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )

#
# link here
#
target_link_libraries(pbase PUBLIC m pthread)

# C-Libs

# C-XX-Libs


#
# install:
#
install(TARGETS pbase
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )
install(DIRECTORY include/ DESTINATION include)


#
# Testing
#

# Enables ctest (after "make", test with "ctest" or "ctest -V")
enable_testing()

# Define the executable test
add_executable(main tests/main.c)

# link to the library
target_link_libraries(main pbase)


# add the executable as test

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

