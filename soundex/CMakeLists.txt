aux_source_directory(./src SOURCE)
aux_source_directory(./test TEST_SOURCE)
include_directories(./include)

add_library(soundex OBJECT ${SOURCE})

link_libraries(gtest_main gtest pthread gmock gmock_main CppUTest CppUTestExt)

add_executable(soundex_test  ${TEST_SOURCE} $<TARGET_OBJECTS:soundex>)
add_test(NAME soundex_test COMMAND soundex_test)