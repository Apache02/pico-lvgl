add_executable(
        hello
        hello.cpp
)

pico_enable_stdio_usb(hello 1)
pico_enable_stdio_uart(hello 0)

pico_add_extra_outputs(hello)

target_link_libraries(
        hello
        pico_stdlib
        drivers_led
        drivers_io
        drivers_st7789
        lvgl
)

add_deploy_target(hello "${CMAKE_CURRENT_BINARY_DIR}/hello.uf2")
