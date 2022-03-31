set(TARGET_NAME PicoPixel)

if(NOT DEFINED MYHTTPSERVER_DIR)
    set(MYHTTPSERVER_DIR ${CMAKE_CURRENT_LIST_DIR}/httpserver)
    message(STATUS "MYHTTPSERVER_DIR = ${MYHTTPSERVER_DIR}")
endif()

if(NOT DEFINED MYDHCP_DIR)
    set(MYDHCP_DIR ${CMAKE_CURRENT_LIST_DIR}/Internet)
    message(STATUS "MYDHCP_DIR = ${MYDHCP_DIR}")
endif()


add_executable(${TARGET_NAME}
        ${TARGET_NAME}.c
        )

# generate the header file into the source tree as it is included in the RP2040 datasheet
pico_generate_pio_header(${TARGET_NAME} ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)

# HTTP Server
add_library(MYHTTPSERVER_FILES STATIC)
add_library(MYDHCP_FILES STATIC)

target_sources(MYHTTPSERVER_FILES PUBLIC
        ${MYHTTPSERVER_DIR}/httpParser.c
        ${MYHTTPSERVER_DIR}/httpServer.c
        ${MYHTTPSERVER_DIR}/httpUtil.c
        )

target_sources(MYDHCP_FILES PUBLIC
        ${MYDHCP_DIR}/dhcp.c
        )

target_include_directories(MYHTTPSERVER_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${MYHTTPSERVER_DIR}
        )

target_include_directories(MYDHCP_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${MYDHCP_DIR}
        )

target_link_libraries(MYHTTPSERVER_FILES PRIVATE
        hardware_watchdog
        )

target_sources(${TARGET_NAME} PUBLIC
        PicoPixel.c
        userHandler.c	
        networkManager.c
        zcpp_implementation.c
        acn.c
        netutil.c
        outputManager.c
        eepromManager.c
        )

target_link_libraries(${TARGET_NAME} PRIVATE
        pico_stdlib
        hardware_spi
        hardware_dma
        hardware_pio
        hardware_flash
        hardware_watchdog
        pico_multicore
        pico_unique_id
        ETHERNET_FILES
        SPI_FILES
        MYHTTPSERVER_FILES
        MYDHCP_FILES
        )

pico_enable_stdio_usb(${TARGET_NAME} 1)
pico_enable_stdio_uart(${TARGET_NAME} 0)

pico_add_extra_outputs(${TARGET_NAME})