set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenRaider_CXX_FLAGS} -DUNIT_TEST")
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OpenRaider_CXX_FLAGS_DEBUG} -DUNIT_TEST")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OpenRaider_CXX_FLAGS_RELEASE} -DUNIT_TEST")

add_custom_target (check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)

# Add GLM Library
find_package (GLM REQUIRED)
if (GLM_FOUND)
    include_directories (SYSTEM  ${GLM_INCLUDE_DIRS})
endif (GLM_FOUND)

#################################################################

add_executable (tester_binary EXCLUDE_FROM_ALL
    "binary.cpp" "../src/utils/binary.cpp"
)
add_dependencies (check tester_binary)
add_test (NAME test_binary COMMAND tester_binary)

#################################################################

add_executable (tester_script EXCLUDE_FROM_ALL
    "Script.cpp" "ScriptPayload.h" "ScriptTest.h"
    "../src/Script.cpp" "../src/utils/binary.cpp"
)

find_package (ZLIB REQUIRED)
include_directories (SYSTEM ${ZLIB_INCLUDE_DIRS})
target_link_libraries (tester_script ${ZLIB_LIBRARIES})

add_dependencies (check tester_script)
add_test (NAME test_script COMMAND tester_script)

#################################################################

