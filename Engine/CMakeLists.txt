set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

list(APPEND dependencies
    "glm https://github.com/SixArne/glm.git master"
    "spdlog https://github.com/SixArne/spdlog.git v1.x"
    "glad https://github.com/SixArne/glad.git main"
)

foreach(dep IN LISTS dependencies)
    string(REPLACE " " ";" DEPENDENCY_ITEM_LIST ${dep})
    message(STATUS "string = ${DEPENDENCY_ITEM_LIST}")

    list(LENGTH DEPENDENCY_ITEM_LIST len)
    message(STATUS "len = ${len}")
    # len = 3

    list(GET DEPENDENCY_ITEM_LIST 0 dep_name)
    list(GET DEPENDENCY_ITEM_LIST 1 dep_url)
    list(GET DEPENDENCY_ITEM_LIST 2 dep_branch)

    # Fetch the dependency
    FetchContent_Declare(
        ${dep_name}
        GIT_REPOSITORY "${dep_url}"
        GIT_TAG "${dep_branch}"
    )

    message(STATUS "Fetching ${dep_name} from ${dep_url} on branch ${dep_branch}")

    # Get properties
    FetchContent_GetProperties(${dep_name})

    # If the dependency is not populated, populate it
    if(NOT ${dep_name}_POPULATED)
        FetchContent_Populate(${dep_name})

        # Make include directories available
        set(${dep_name}_INCLUDE_DIR ${${dep_name}_SOURCE_DIR})
    endif()

endforeach()

# Fetch dependencies (download and setup include directories)
# glfw does this automatically
FetchContent_Declare(
    "glfw"
    GIT_REPOSITORY "https://github.com/SixArne/glfw.git"
    GIT_TAG "master"
)

FetchContent_MakeAvailable(glfw)

add_executable(Engine
    "./src/main.cpp"
    "./src/ecs/GameObject.cpp"
    "./src/ecs/Component.cpp"
    "./src/window/Window.cpp"
    "./src/core/logger/Log.cpp"
    "./src/backends/opengl/OpenGLRenderer.cpp"

    # glad source file
    "${glad_SOURCE_DIR}/src/glad.c"
)

# Link with glfw
target_link_libraries(Engine PUBLIC
    glfw
    opengl32
)

message(STATUS "include directory ${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(Engine PUBLIC
    # Self include root directory
    "${CMAKE_CURRENT_SOURCE_DIR}/src"

    # glfw include directory
    "${glfw_INCLUDE_DIR}/include"

    # glm include directory
    "${glm_INCLUDE_DIR}"

    # spdlog include directory
    "${spdlog_INCLUDE_DIR}/include"

    # glad include directory
    "${glad_INCLUDE_DIR}/include"
)
