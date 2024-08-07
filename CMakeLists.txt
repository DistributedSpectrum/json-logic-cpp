cmake_minimum_required(VERSION 3.16)
project(jsonlogic VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

set(USE_EXECUTION ON)
try_compile(HAVE_EXECUTION ${CMAKE_BINARY_DIR} ${PROJECT_SOURCE_DIR}/src/executiontest.cpp)
if(NOT HAVE_EXECUTION)
        set(USE_EXECUTION OFF)
        add_compile_definitions(NO_EXECUTION)
endif()

set(SOURCES
	    src/json_logic.cpp
	    src/operations/array/all.cpp
	    src/operations/array/filter.cpp
	    src/operations/array/in.cpp
	    src/operations/array/map.cpp
	    src/operations/array/merge.cpp
	    src/operations/array/none.cpp
	    src/operations/array/some.cpp
	    src/operations/data/missing.cpp
	    src/operations/data/missing_some.cpp
	    src/operations/data/var.cpp
	    src/operations/logic/and.cpp
	    src/operations/logic/different.cpp
	    src/operations/logic/equal.cpp
	    src/operations/logic/if.cpp
	    src/operations/logic/not.cpp
            src/operations/logic/or.cpp
            src/operations/logic/truthy.cpp
	    src/operations/misc/log.cpp
            src/operations/numeric/addition.cpp
	    src/operations/numeric/division.cpp
            src/operations/numeric/gt.cpp
            src/operations/numeric/gte.cpp
            src/operations/numeric/lt.cpp
            src/operations/numeric/lte.cpp
            src/operations/numeric/max.cpp
            src/operations/numeric/min.cpp
	    src/operations/numeric/modulo.cpp
	    src/operations/numeric/multiplication.cpp
	    src/operations/numeric/subtraction.cpp
	    src/operations/string/cat.cpp
	    src/operations/string/substr.cpp
)

if(USE_EXECUTION)
    list(APPEND SOURCES src/operations/array/reduce.cpp)
endif()

add_library(${PROJECT_NAME} ${SOURCES})

#target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
add_library(jsonlogic::jsonlogic ALIAS jsonlogic)

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src/>
    #    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/lib/json/include/nlohmann/>
)

add_subdirectory(test)

install(TARGETS jsonlogic
    COMPONENT jsonlogic
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(FILES src/json_logic.h src/jsonlogic/exception.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/jsonlogic)

SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "nobody")
INCLUDE(CPack)
