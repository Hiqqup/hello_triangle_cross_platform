cmake_minimum_required(VERSION 4.0)
project(hello_triangle_cross_platform)

set(CMAKE_CXX_STANDARD 20)

set(EXE_FILE hello_triangle_cross_platform )

option(BROWSER_BUILD "Building for browser or not" OFF)

set(SOURCES
    main.cpp
    Backend.h
        Backend.cpp
        gl_backend.h
)


if(BROWSER_BUILD)
    list(APPEND SOURCES
        BrowserBackend.cpp
        BrowserBackend.h
    )
    set(CMAKE_EXECUTABLE_SUFFIX ".js")
    configure_file(${CMAKE_SOURCE_DIR}/index.html ${CMAKE_BINARY_DIR}/index.html COPYONLY)
else()
    list(APPEND SOURCES
        DesktopBackend.cpp
        DesktopBackend.h
    )
endif()


set(DEPENDENCIES)
if(BROWSER_BUILD)
    list(APPEND DEPENDENCIES
    )
else()

    include(FetchContent)

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
    target_compile_options(${EXE_FILE} PRIVATE
        "-sUSE_WEBGL2=1"
        "-sFULL_ES3=1"
        "-sALLOW_MEMORY_GROWTH=1"
        "-sASSERTIONS=1"
    )
    target_link_options(${EXE_FILE} PRIVATE
        "-sUSE_WEBGL2=1"
        "-sFULL_ES3=1"
        "-sALLOW_MEMORY_GROWTH=1"
        "-sASSERTIONS=1"
    )
    add_custom_target(run_browser
        DEPENDS ${EXE_FILE}
    )
else()
    add_custom_target(default
        DEPENDS ${EXE_FILE}
    )

endif()
