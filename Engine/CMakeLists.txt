set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# Define github dependencies
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/SixArne/glfw.git
)

# Define github dependencies
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/SixArne/glm.git
)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/SixArne/spdlog.git
    GIT_TAG v1.x # or whatever tag or branch you want to use
)

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/SixArne/glad.git
    GIT_TAG main
)

# Fetch dependencies (download and setup include directories)
# glfw does this automatically
FetchContent_MakeAvailable(glfw)

# glm does not, so we have to do it manually
# GetProperties exposes a variable called glm_POPULATED
# and a variable called glm_SOURCE_DIR
FetchContent_GetProperties(glm)

# Get properties for spdlog like include directory
FetchContent_GetProperties(spdlog)

# Get properties for glad like include directory
FetchContent_GetProperties(glad)

if(NOT glm_POPULATED)
  # FetchContent_Populate will download the repo and set the variables
  FetchContent_Populate(glm)

  # Here we overwrite set the include directory to the source directory
  set(glm_INCLUDE_DIR ${glm_SOURCE_DIR})
endif()

if(NOT spdlog_POPULATED)
  # FetchContent_Populate will download the repo and set the variables
  FetchContent_Populate(spdlog)

  # Here we overwrite set the include directory to the source directory
  set(spdlog_INCLUDE_DIR ${spdlog_SOURCE_DIR}/include)
endif()

if(NOT glad_POPULATED)
  # FetchContent_Populate will download the repo and set the variables
  FetchContent_Populate(glad)

  # Here we overwrite set the include directory to the source directory
  set(glad_INCLUDE_DIR ${glad_SOURCE_DIR}/include)
endif()

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

    # glm include directory
    "${glm_INCLUDE_DIR}"

    # spdlog include directory
    "${spdlog_INCLUDE_DIR}"

    # glad include directory
    "${glad_INCLUDE_DIR}"
)
