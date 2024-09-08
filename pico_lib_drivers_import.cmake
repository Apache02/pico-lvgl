if (DEFINED ENV{PICO_LIB_DRIVERS_PATH} AND (NOT PICO_LIB_DRIVERS_PATH))
    set(PICO_LIB_DRIVERS_PATH $ENV{PICO_LIB_DRIVERS_PATH})
    message("Using PICO_LIB_DRIVERS_PATH from environment ('${PICO_LIB_DRIVERS_PATH}')")
endif ()

if (NOT PICO_LIB_DRIVERS_PATH)
    set(PICO_LIB_DRIVERS_PATH ${PICO_SDK_PATH}/../pico-drivers)
endif ()

if (NOT EXISTS ${PICO_LIB_DRIVERS_PATH})
    message(FATAL_ERROR "Directory '${PICO_LIB_DRIVERS_PATH}' not found")
endif ()

if (NOT EXISTS ${PICO_LIB_DRIVERS_PATH}/drivers)
    message(FATAL_ERROR "Directory '${PICO_LIB_DRIVERS_PATH}/drivers' not found")
endif ()

add_subdirectory(${PICO_LIB_DRIVERS_PATH}/drivers drivers)
target_include_directories(drivers INTERFACE ${PICO_LIB_DRIVERS_PATH})
