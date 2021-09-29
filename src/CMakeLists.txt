include_directories (${CMAKE_SOURCE_DIR}/include)

set (EXLIB_SOURCES
	exlib/strings/base.c
)

add_library (exlib ${EXLIB_SOURCES})
