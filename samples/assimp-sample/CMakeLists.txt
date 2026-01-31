project(ASSIMP_SAMPLE VERSION 1.0)

add_executable(assimp_sample_exec "main.cpp")

target_include_directories(assimp_sample_exec PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(assimp_sample_exec PRIVATE ${PROJECT_CORE_LIB})

file(COPY "assets" DESTINATION  ${PROJECT_BINARY_DIR})
