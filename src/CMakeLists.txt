include_directories(${CMAKE_SOURCE_DIR}/include)

set(EXLIB_SOURCES
        exlib/hashes/crc32.c
        exlib/path/pathbase.c
        exlib/path/pathlinux.c
        exlib/strings/decstr_from.c
        exlib/strings/decstr_to.c
        exlib/strings/hexstr_from.c
        exlib/strings/hexstr_to.c
        exlib/strings/safe_decstr_to.c
        exlib/strings/safe_dump.c
        exlib/strings/safe_hexstr_to.c
        exlib/strings/safe_strbase.c
        exlib/strings/strbase.c
        exlib/strings/substrings.c
)

add_library(exlib ${EXLIB_SOURCES})
