project (sample_plugin)

ADD_FILES("${PROJECT_SOURCE_DIR}" "hpp" HEADER_FILES)
ADD_FILES("${PROJECT_SOURCE_DIR}" "cpp" SOURCE_FILES)
ADD_FILE_DIRECTORIES("${PROJECT_SOURCE_DIR}" "hpp" HEADER_DIRS)

include_directories(include ${HEADER_DIRS})
add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS} -lstdc++fs -ldl )
target_compile_options(${PROJECT_NAME} PUBLIC -O0 -g -Wall)

install(FILES ${PROJECT_SOURCE_DIR}/config/${PROJECT_NAME}_info.json DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})