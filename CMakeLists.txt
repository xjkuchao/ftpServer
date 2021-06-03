cmake_minimum_required(VERSION 3.16.0)

# cmake_policy(SET CMP0071 OLD)

project(ftpServer VERSION 1.0.0 LANGUAGES CXX)

#set(CMAKE_VERBOSE_MAKEFILE ON)
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/release)

include(cmake/qt6.cmake)
include(cmake/generate_product_version.cmake)

add_definitions(-DUNICODE)

if (CMAKE_BUILD_TYPE MATCHES "Debug" OR CMAKE_BUILD_TYPE MATCHES "None")
    add_definitions(-DQTSERVICE_DEBUG)
endif()

include_directories(
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src
)

link_directories(
)

if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    find_program(CCACHE_FOUND ccache)
    if (CCACHE_FOUND)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache) # Less useful to do it for linking, see edit2
    endif (CCACHE_FOUND)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    #add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    #add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    #add_compile_options(/wd4251)
endif ()

generate_product_version(
   VersionFilesOutputVariable
   NAME "ftpServer"
   ICON ${CMAKE_SOURCE_DIR}/res/main.ico
   VERSION_MAJOR 1
   VERSION_MINOR 0
   VERSION_PATCH 0
   VERSION_REVISION 1
)

add_executable(
    ${PROJECT_NAME}

    src/main.cpp

    src/qtservice.cpp
    src/qtservice_win.cpp

    src/dataconnection.cpp
    src/ftpcommand.cpp
    src/ftpcontrolconnection.cpp
    src/ftplistcommand.cpp
    src/ftpretrcommand.cpp
    src/ftpserver.cpp
    src/ftpstorcommand.cpp
    src/sslserver.cpp

    src/certificates.qrc

    ${VersionFilesOutputVariable}
)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE

    ${QT6_LIBRARIES}
)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
    OUTPUT_NAME "ftpServer"
)
