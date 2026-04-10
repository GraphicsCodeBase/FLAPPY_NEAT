cmake_minimum_required(VERSION 3.20)
project(FlappyNEAT CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/deps.cmake)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(FlappyNEAT ${SOURCES})

target_include_directories(FlappyNEAT PRIVATE
    src/
)

target_link_libraries(FlappyNEAT PRIVATE
    glfw
    glad::glad
    glm::glm
    OpenGL::GL
)

# Copy shaders and assets next to the executable after build
add_custom_command(TARGET FlappyNEAT POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:FlappyNEAT>/shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:FlappyNEAT>/assets
)
