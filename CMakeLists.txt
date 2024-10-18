cmake_minimum_required(VERSION 3.16)
project("${PROJECT_NAME}" VERSION 0.1 LANGUAGES C)

set(PROJECT_NAME "lt-brow")
#set(CEF_VERSION "cef_binary_127.3.5+g114ea2a+chromium-127.0.6533.120_linux64_minimal")
#set(CEF_VERSION "cef_binary_129.0.12+gf09539f+chromium-129.0.6668.101_linux64_minimal")
#set(CEF_VERSION "cef_binary_130.1.3%2Bg06c1602%2Bchromium-130.0.6723.59_linux64_minimal")
set(CEF_VERSION "cef_binary_130.1.7%2Bg59f3b14%2Bchromium-130.0.6723.59_linux64_minimal")
#set(CEF_VERSION "cef_binary_130.1.9%2Bgfc42567%2Bchromium-130.0.6723.70_windows64_minimal")
set(CEF_DOWNLOAD_URL "https://cef-builds.spotifycdn.com/${CEF_VERSION}.tar.bz2")
set(BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build/")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_DIR}/Release/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BUILD_DIR}/Release/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BUILD_DIR}/Release/")

file(MAKE_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")


##############################
# LSP config
##############################
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_definitions(-DSOME_DEFINITION)
file(GLOB_RECURSE sources
        "${CMAKE_SOURCE_DIR}/src/*.c"
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
        )


##############################
# DOWNLOAD CEF
##############################
string(REGEX REPLACE "%2B" "+" output "${BUILD_DIR}/${CEF_VERSION}/")
cmake_path(GET output PARENT_PATH base_name)
file(RELATIVE_PATH CEF_DIR "${BUILD_DIR}" "${base_name}")

if(NOT EXISTS "${output}/")
  Set(FETCHCONTENT_QUIET FALSE)
  execute_process (
    COMMAND wget ${CEF_DOWNLOAD_URL} --progress=bar:force:noscroll -O cef_minimal.tar.bz2 -q --show-progress
    WORKING_DIRECTORY ${BUILD_DIR}
  )
  execute_process (
    COMMAND tar xvf ./cef_minimal.tar.bz2
    WORKING_DIRECTORY ${BUILD_DIR}
  )
  execute_process (
    COMMAND cmake .
    WORKING_DIRECTORY ${BUILD_DIR}/cef_minimal/
  )
endif()

execute_process (
  COMMAND readlink -f cef_minimal
  WORKING_DIRECTORY ${BUILD_DIR}
  OUTPUT_VARIABLE CEF_LINK_TARGET
)
if(NOT ${CEF_LINK_TARGET} STREQUAL ${base_name})
  execute_process (
    COMMAND rm cef_minimal
    WORKING_DIRECTORY ${BUILD_DIR}
  )
  execute_process (
    COMMAND ln -sf ${CEF_DIR} cef_minimal
    WORKING_DIRECTORY ${BUILD_DIR}
  )
  execute_process (
    COMMAND rm -rf Release/*
    WORKING_DIRECTORY ${BUILD_DIR}
  )
  file(GLOB TXT_FILES "${BUILD_DIR}/cef_minimal/Release/*")
  file(COPY ${TXT_FILES} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
  file(GLOB TXT_FILES "${BUILD_DIR}/cef_minimal/Resources/*")
  file(COPY ${TXT_FILES} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()


##############################
# BIN INFO
##############################

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED IMPORTED_TARGET gtk+-3.0 x11 gdk-x11-3.0)
#pkg_check_modules(GTK3 REQUIRED "gtk+-3.0")
#include_directories(${GTK3_INCLUDE_DIRS})
#link_directories(${GTK3_LIBRARY_DIRS})
#add_definitions(${GTK3_CFLAGS_OTHER})

include_directories(./includes ./build/cef_minimal/)
link_directories(./build/Release/)


add_executable("${PROJECT_NAME}"
  ./src/main.c
  ./src/keybindings.c
  ./src/ui/ui.c
  ./src/ui/status_bar.c
  ./src/ui/css.c
)

target_link_libraries("${PROJECT_NAME}" PUBLIC
  PkgConfig::GTK3
  cef
)

add_custom_target(run
    COMMAND lt-brow
    DEPENDS lt-brow
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

#target_compile_options(${PROJECT_NAME} PRIVATE
#  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
#  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
#)

#target_link_libraries("${PROJECT_NAME}" PUBLIC
#  cef -static
#)

