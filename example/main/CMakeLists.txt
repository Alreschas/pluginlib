project (main)

ADD_FILES("${PROJECT_SOURCE_DIR}" "hpp" HEADER_FILES)
ADD_FILES("${PROJECT_SOURCE_DIR}" "cpp" SOURCE_FILES)
ADD_FILE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src" "hpp" HEADER_DIRS)

include_directories(include ${HEADER_DIRS})
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS} -lstdc++fs -ldl )
target_compile_options(${PROJECT_NAME} PUBLIC -O0 -g -Wall)
