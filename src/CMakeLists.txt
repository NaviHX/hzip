aux_source_directory(. SRC_LIST)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(hzip ${SRC_LIST})
add_executable(debug ${SRC_LIST})

target_compile_definitions(debug PUBLIC -DDEBUG)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)