set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/SixArne/glfw.git
)

FetchContent_MakeAvailable(glfw)

add_executable(Engine
    "./src/main.cpp"
    "./src/ecs/GameObject.cpp"
    "./src/ecs/Component.cpp"
)

target_link_libraries(Engine PUBLIC
    glfw
)

message(STATUS "include directory ${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(Engine PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
