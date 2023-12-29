cmake_minimum_required(VERSION 3.22.1)

project(App0)

file(GLOB project_sources 
    "src/*.cpp"
    "src/vendor/stb_image/*.cpp"
    "src/vendor/imgui/*.cpp"
    "src/tests/*.cpp"
)

add_executable(${PROJECT_NAME} ${project_sources})

target_sources(${PROJECT_NAME} PRIVATE ${project_headers})

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

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/res/")