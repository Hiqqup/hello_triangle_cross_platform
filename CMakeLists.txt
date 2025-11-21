cmake_minimum_required(VERSION 4.0)
project(cross_platform_game_engine)

set(CMAKE_CXX_STANDARD 20)

set(EXE_FILE cross_platform_game_engine)

option(BROWSER_BUILD "Building for browser or not" OFF)

#sources
set(SOURCES
    main.cpp
        platform/Platform.h
        platform/Platform.cpp
    gl_backend.h
    Image.cpp
    Image.h
)


#dependencies
include(FetchContent)
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
)
FetchContent_GetProperties(stb)
if (NOT stb_POPULATED)
    FetchContent_MakeAvailable(stb)
    add_library(stb INTERFACE)
    target_include_directories(stb INTERFACE ${stb_SOURCE_DIR})
endif()

set(DEPENDENCIES
    stb
)


if(BROWSER_BUILD)
    #sources
    list(APPEND SOURCES
            platform/browser/PlatformBrowser.cpp
            platform/browser/PlatformBrowser.h
    )
    set(CMAKE_EXECUTABLE_SUFFIX ".js")
    configure_file(${CMAKE_SOURCE_DIR}/platform/browser/index.html ${CMAKE_BINARY_DIR}/index.html COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/platform/browser/favicon.ico ${CMAKE_BINARY_DIR}/favicon.ico COPYONLY)
    #Dependencies
    list(APPEND DEPENDENCIES
    )
else()
    #sources
    list(APPEND SOURCES
            platform/desktop/PlatformDesktop.cpp
            platform/desktop/PlatformDesktop.h
    )
    # Dependencies
    FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG master
    )
    FetchContent_MakeAvailable(glad)
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG master
    )
    FetchContent_MakeAvailable(glfw)


    list(APPEND DEPENDENCIES
        glad
        glfw
    )
endif()

add_executable(${EXE_FILE} ${SOURCES} )
target_link_libraries(${EXE_FILE} PRIVATE ${DEPENDENCIES})

if(BROWSER_BUILD)
    # linker flags
    target_compile_options(${EXE_FILE} PRIVATE
        "-sUSE_WEBGL2=1"
        "-sFULL_ES3=1"
        "-sALLOW_MEMORY_GROWTH=1"
        "-sASSERTIONS=1"
        "-sUSE_GLFW=3"
    )
    target_link_options(${EXE_FILE} PRIVATE
        "-sUSE_WEBGL2=1"
        "-sUSE_GLFW=3"
         "--preload-file"
         "${CMAKE_CURRENT_SOURCE_DIR}/assets/@/assets"
    )
    # build target
    add_custom_target(run_browser
        DEPENDS ${EXE_FILE}
    )
else()
    # build target
    add_custom_target(default
        DEPENDS ${EXE_FILE}
    )

endif()

# asset copying
add_custom_target(copy_assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${EXE_FILE}>/assets )
add_dependencies(${EXE_FILE} copy_assets)

