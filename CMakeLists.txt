# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()

set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)

if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_BOARD pico_w CACHE STRING "Board type")
include(pico_sdk_import.cmake)
project(counting-matrix C CXX ASM)
pico_sdk_init()
add_executable(counting-matrix counting-matrix.c )
# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(counting-matrix 0)
pico_enable_stdio_usb(counting-matrix 1)

pico_generate_pio_header(counting-matrix ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio)

target_sources(counting-matrix PRIVATE
    counting-matrix.c
    modules/ws2812b.c
    modules/rgb_led.c
    modules/push_button.c
)
target_link_libraries(counting-matrix PRIVATE
    pico_stdlib
    hardware_pio
    hardware_clocks
    hardware_pwm
    hardware_timer
)
pico_add_extra_outputs(counting-matrix)