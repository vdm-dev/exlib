include_directories(
    ${CMAKE_SOURCE_DIR}/include
)


macro(make_test test_name)
  add_executable(${test_name} ${test_name}.c)
  add_test(${test_name} ${test_name})
  target_link_libraries(${test_name} exlib)
endmacro(make_test)

make_test(test-strlcpy)
make_test(test-strlcat)
make_test(test-decstr_from)
make_test(test-decstr_to)
make_test(test-path)
