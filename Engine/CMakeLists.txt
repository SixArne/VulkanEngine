set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# //FIXME - Make 3 different ways of fetching content. lib header-only dll
list(APPEND dependencies
    "glm https://github.com/SixArne/glm.git master"
    "spdlog https://github.com/SixArne/spdlog.git v1.x"
    "glad https://github.com/SixArne/glad.git main"
    "stb https://github.com/SixArne/stb.git master"
    "fmod https://github.com/SixArne/FMOD.git test"
)

foreach(dep IN LISTS dependencies)
    string(REPLACE " " ";" DEPENDENCY_ITEM_LIST ${dep})

    list(LENGTH DEPENDENCY_ITEM_LIST len)

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
        message(STATUS "Setting ${dep_name}_INCLUDE_DIR to ${${dep_name}_SOURCE_DIR}")
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

FetchContent_Declare(
    "assimp"
    GIT_REPOSITORY "https://github.com/SixArne/assimp.git"
    GIT_TAG "master"
)

FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(assimp)



add_executable(Engine
    "./src/main.cpp"
    "./src/ecs/GameObject.cpp"
    "./src/ecs/Component.cpp"
    "./src/window/Window.cpp"
    "./src/core/logger/Log.cpp"
    "./src/backends/opengl/OpenGLRenderer.cpp"
    "./src/core/loaders/images/ImageLoader.cpp"
    "./src/core/loaders/meshes/MeshLoader.cpp"

    # glad source file
    "${glad_SOURCE_DIR}/src/glad.c"
)


message(STATUS "Looking for lib files in ${fmod_SOURCE_DIR}/lib/x64")
link_directories(${fmod_SOURCE_DIR}/lib/x64/)
# Link with glfw
target_link_libraries(Engine PUBLIC
    glfw
    assimp::assimp
    opengl32
    ${fmod_SOURCE_DIR}/lib/x64/fmod_vc.lib
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(BUILD_CONFIG "Debug")
else()
    set(BUILD_CONFIG "Release")
endif()

set(RESOURCES_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)
set(RESOURCES_DEST_DIR ${CMAKE_BINARY_DIR}/Engine/${BUILD_CONFIG})

message(STATUS "Copying resources from ${RESOURCES_SOURCE_DIR} to ${RESOURCES_DEST_DIR}")


file(COPY ${RESOURCES_SOURCE_DIR} DESTINATION ${RESOURCES_DEST_DIR})


message(STATUS "${fmod_SOURCE_DIR}/lib/x64)}")
message(STATUS "${fmod_LIBRARY}")

# copy FMOD DLL
message(STATUS "Copying FMOD DLL from ${fmod_LIBRARY} to ${CMAKE_BINARY_DIR}/Engine/${BUILD_CONFIG}")

# Set the FMOD source library directory
set(FMOD_LIBS_DIR ${fmod_SOURCE_DIR}/lib/x64/)

# Set the FMOD DLL output directory
set(FMOD_DLL_OUTPUT ${CMAKE_BINARY_DIR}/Engine/${BUILD_CONFIG})

# Create a list of FMOD DLL files
file(GLOB FMOD_DLL_FILES "${FMOD_LIBS_DIR}/*.dll")

# Copy the FMOD DLL files to the output directory
file(COPY ${FMOD_DLL_FILES} DESTINATION ${FMOD_DLL_OUTPUT})

# Header include directories
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

    # stb include directory
    "${stb_INCLUDE_DIR}"

    # assimp include directory
    "${assimp_INCLUDE_DIR}"

    "${fmod_INCLUDE_DIR}"
)
