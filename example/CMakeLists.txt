cmake_minimum_required(VERSION 3.10)
project (example)

ADD_FILES("${PROJECT_SOURCE_DIR}/plugin_interface" "cpp" SOURCE_FILES)
ADD_FILES("${PROJECT_SOURCE_DIR}/plugin_interface" "hpp" HEADER_FILES)
ADD_FILE_DIRECTORIES("${PROJECT_SOURCE_DIR}/plugin_interface" "hpp" HEADER_DIRS)

message(${HEADER_DIRS})

add_subdirectory(main)
add_subdirectory(plugin)