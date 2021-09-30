include_directories(${CMAKE_SOURCE_DIR}/include)

set(EXLIB_SOURCES
	exlib/strings/base.c
        exlib/strings/decstr_from.c
        exlib/strings/decstr_to.c
        exlib/strings/hexstr_from.c
        exlib/strings/substrings.c
)

add_library(exlib ${EXLIB_SOURCES})
