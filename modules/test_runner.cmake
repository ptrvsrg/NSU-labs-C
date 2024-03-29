if(WIN32)
	set(BUILD_DIR "/${CMAKE_BUILD_TYPE}")
	set(EXE ".exe")
endif(WIN32)

set(TEST_RUNNER_NAME test${PROJECT_NAME}${EXE})
set(TEST_RUNNER_PATH ${CMAKE_CURRENT_SOURCE_DIR}/test/${TEST_RUNNER_NAME})

set(EXE_NAME ${PROJECT_NAME}${EXE})
set(EXE_PATH ${CMAKE_CURRENT_BINARY_DIR}${BUILD_DIR}/${EXE_NAME})

math(EXPR UNLIMITED_MS 60*1000)
math(EXPR UNLIMITED_KB 1024*1024)
option(UNLIMITED "Disable time/memory limits" OFF)

include(valgrind)

include (CTest)
enable_testing()

if (UNLIMITED)
	add_test(
		NAME ${TEST_RUNNER_NAME}
		COMMAND ${TEST_RUNNER_PATH} -m ${UNLIMITED_KB} -t ${UNLIMITED_MS} ${EXE_PATH}
	)
else()
	add_test(
		NAME ${TEST_RUNNER_NAME}
		COMMAND ${TEST_RUNNER_PATH} ${EXE_PATH}
	)
endif()

set_tests_properties(${TEST_RUNNER_NAME} PROPERTIES DEPENDS ${EXE_NAME})
