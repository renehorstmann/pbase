cmake_minimum_required(VERSION 3.0)
project(pbase)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -march=native)  # march=native for best performance
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-long-long -pedantic -Wno-unused-function")

#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -march=native)  # march=native for best performance
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -Wno-unused-function")


include_directories(
		${PROJECT_SOURCE_DIR}/include
		${PROJECT_SOURCE_DIR}/src
)
file(GLOB SRCS
		"${PROJECT_SOURCE_DIR}/include/*"
		"${PROJECT_SOURCE_DIR}/include/types/*"
		"${PROJECT_SOURCE_DIR}/src/*"
		"${PROJECT_SOURCE_DIR}/src/types/*"
		)

add_library(pbase SHARED ${SRCS})
set_target_properties(pbase PROPERTIES LINKER_LANGUAGE C)

set_property(TARGET pbase PROPERTY POSITION_INDEPENDENT_CODE ON)

#
# link here
#
target_link_libraries(pbase PUBLIC m pthread)

# C-Libs

# C-XX-Libs


#
# install:
#

if (MINGW)
	set(INSTALL_LIB "C:/Libraries/lib")
	set(INSTALL_INCLUDE "C:/Libraries/include")
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

# link to the library
target_link_libraries(main pbase)


# add the executable as test

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

