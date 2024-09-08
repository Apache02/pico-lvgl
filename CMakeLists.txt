cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)
include(scripts/functions.cmake)

project(pico-lvgl C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

# Specify path to own LVGL config header
set(LV_CONF_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/lv_conf.h
        CACHE STRING "" FORCE)

add_subdirectory(lib/lvgl)
include_directories(lib)

include(pico_lib_drivers_import.cmake)

add_subdirectory(examples/hello)
