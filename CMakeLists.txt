cmake_minimum_required(VERSION 3.22.1)

project(App0)

add_executable(${PROJECT_NAME} main.cpp)

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