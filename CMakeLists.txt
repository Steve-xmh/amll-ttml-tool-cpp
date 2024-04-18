cmake_minimum_required(VERSION 3.8.0 FATAL_ERROR)

project(amll-ttml-tools)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(SRC_DIRS
    src
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 23)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Core Widgets Network REQUIRED)

foreach(DIR ${SRC_DIRS})
    aux_source_directory(${DIR} SRC_FILES)
endforeach()

add_executable(amll-ttml-tools ${SRC_FILES})

if(WIN32)
    target_link_libraries(amll-ttml-tools Qt6::Core Qt6::Widgets Qt6::Network DbgHelp)
else()
    target_link_libraries(amll-ttml-tools Qt6::Core Qt6::Widgets Qt6::Network)
endif()


if(WIN32)
    # 复制 Qt6 相关的动态库
    add_custom_command(TARGET amll-ttml-tools POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt6::Core> $<TARGET_FILE_DIR:amll-ttml-tools>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt6::Gui> $<TARGET_FILE_DIR:amll-ttml-tools>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt6::Widgets> $<TARGET_FILE_DIR:amll-ttml-tools>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt6::Network> $<TARGET_FILE_DIR:amll-ttml-tools>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt6::QWindowsIntegrationPlugin> $<TARGET_FILE_DIR:amll-ttml-tools>/platforms/$<TARGET_FILE_NAME:Qt6::QWindowsIntegrationPlugin>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt6::QWindowsVistaStylePlugin> $<TARGET_FILE_DIR:amll-ttml-tools>/styles/$<TARGET_FILE_NAME:Qt6::QWindowsVistaStylePlugin>
    )
endif()

# 自动格式化源代码
add_custom_command(
    TARGET amll-ttml-tools PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "正在自动格式化源代码..."
    COMMAND clang-format --style=file -i ./src/*.cpp ./src/*.hpp
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)
