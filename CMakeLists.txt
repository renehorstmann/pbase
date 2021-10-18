cmake_minimum_required(VERSION 3.0)
project(pbase)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -march=native)  # march=native for best performance
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-long-long -pedantic -Wno-unused-function")

include_directories(
		${PROJECT_SOURCE_DIR}/include
)
file(GLOB SRCS
		"${PROJECT_SOURCE_DIR}/src/*"
		"${PROJECT_SOURCE_DIR}/src/types/*"
		"${PROJECT_SOURCE_DIR}/src/io/*"
		"${PROJECT_SOURCE_DIR}/src/meshprimitives/*"
		)

add_library(pbase SHARED ${SRCS})
set_target_properties(pbase PROPERTIES LINKER_LANGUAGE C)

set_property(TARGET pbase PROPERTY POSITION_INDEPENDENT_CODE ON)

add_definitions(-DOPTION_SOCKET)

#
# link here
#
target_link_libraries(pbase PUBLIC m pthread)
if(MINGW)
	target_link_libraries(pbase PUBLIC ws2_32)
endif()

# C-Libs

# C-XX-Libs


#
# install:
#

if (MINGW)
	set(INSTALL_LIB "C:/Libraries/lib")
	set(INSTALL_INCLUDE "C:/Libraries/include")
	add_definitions(-DP_RHC_LOG_DO_NOT_USE_COLOR)
	add_definitions(-DMATHC_NO_PRINT_COLOR)
else()
	set(INSTALL_LIB lib)
	set(INSTALL_INCLUDE include)
endif()

install(TARGETS pbase
		LIBRARY DESTINATION ${INSTALL_LIB}
		ARCHIVE DESTINATION ${INSTALL_LIB}
		RUNTIME DESTINATION ${INSTALL_LIB}
		)
install(DIRECTORY include/ DESTINATION ${INSTALL_INCLUDE})

# install python
set(PYTHON_LIB_INSTALL_DIR $ENV{PYTHON_LIB_INSTALL_DIR})
if(PYTHON_LIB_INSTALL_DIR)
	set(PYTHON_LIB_INSTALL_DIR ${PYTHON_LIB_INSTALL_DIR} /pbase)
	string(REPLACE "\\" "/" PYTHON_LIB_INSTALL_DIR ${PYTHON_LIB_INSTALL_DIR})
 	install(DIRECTORY python/pbase/ DESTINATION ${PYTHON_LIB_INSTALL_DIR})
else()
	message(AUTHOR_WARNING "env variable PYTHON_LIB_INSTALL_DIR not set, not installing python modules")
endif()

#
# Testing
#

# Enables ctest (after "make", test with "ctest" or "ctest -V")
enable_testing()

# Define the executable test
add_executable(main tests/main.c)
add_executable(example_convert tests/example_convert.c)
add_executable(test_io tests/test_io.c)

# link to the library
target_link_libraries(main pbase)
target_link_libraries(example_convert pbase)
target_link_libraries(test_io pbase)

# add the executable as test
add_test(Test_io test_io)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

