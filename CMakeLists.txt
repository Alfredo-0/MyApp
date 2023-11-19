cmake_minimum_required(VERSION 3.22.1)

project(App0)

set( project_sources
    src/main.cpp
    src/Renderer.cpp
    src/IndexBuffer.cpp
    src/Shader.cpp
    src/VertexBuffer.cpp 
    src/VertexArray.cpp
)

add_executable(${PROJECT_NAME} ${project_sources})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

add_subdirectory(external/glfw)
add_subdirectory(external/glew)

target_include_directories(${PROJECT_NAME} 
    PUBLIC external/glfw/include
    PUBLIC external/glew/include
)

target_link_directories(${PROJECT_NAME}
    PRIVATE external/glfw/src
    PRIVATE external/glew/src
)

target_link_libraries(${PROJECT_NAME}
    glfw
    libglew_static
)