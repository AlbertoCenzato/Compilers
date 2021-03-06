cmake_minimum_required(VERSION 2.8.3)
project(f_compiler)

add_definitions(-std=gnu99)

find_package(BISON REQUIRED)
find_package(FLEX  REQUIRED)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(include)

BISON_TARGET(parser grammar/sintactF.y ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/parser.tab.c COMPILE_FLAGS -d)
FLEX_TARGET(lexer grammar/lexF1.fl ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/lexer.yy.c)
ADD_FLEX_BISON_DEPENDENCY(lexer parser)

MESSAGE(STATUS "BISON_parser_OUTPUT: " ${BISON_parser_OUTPUTS})
MESSAGE(STATUS "FLEX_lexer_OUTPUT: "   ${FLEX_lexer_OUTPUTS})

## Declare a C++ library
#add_library(compiler_code)

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS})

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
add_executable(${PROJECT_NAME} 
	${BISON_parser_OUTPUTS}  
	${FLEX_lexer_OUTPUTS}
	src/code_gen.c
	src/fract.c
	src/bool.c
	src/code_list.c
	src/symbol_table.c
	src/tac.c
	src/ctrl_flow.c
	src/backend.c
)

## Compiler flags
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-O0 -g")        ## Optimize
endif()