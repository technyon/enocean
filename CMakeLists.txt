cmake_minimum_required(VERSION 3.0.0)

set(ARDUINO_BOARD "ESP32 Dev Module [esp32.esp32]")
set(LOG_LEVEL ARDUHAL_LOG_LEVEL_INFO)

# ARDUHAL_LOG_LEVEL_NONE
# ARDUHAL_LOG_LEVEL_ERROR
# ARDUHAL_LOG_LEVEL_WARN
# ARDUHAL_LOG_LEVEL_INFO
# ARDUHAL_LOG_LEVEL_DEBUG
# ARDUHAL_LOG_LEVEL_VERBOSE

project(enocean CXX)

include_directories(${PROJECT_NAME}
        PRIVATE
        lib/NimBLE-Arduino/src
        lib/EnOceanBleDevices/src
)

file(GLOB SRCFILES
        lib/EnOceanBleDevices/src/EnOceanBLEScannerSubscriber.cpp
        lib/EnOceanBleDevices/src/EnOceanConstants.h
        lib/EnOceanBleDevices/src/EnOceanDataTypes.h
        lib/EnOceanBleDevices/src/EnOceanUtils.cpp
        lib/EnOceanBleDevices/src/MultiData/EnOceanDataEventAdapter.cpp
        lib/EnOceanBleDevices/src/MultiData/EnOceanDataEventHandler.cpp
        lib/EnOceanBleDevices/src/PTM215/EnOceanPTM215EventAdapter.cpp
        lib/EnOceanBleDevices/src/PTM215/EnOceanPTM215EventHandler.cpp
        lib/EnOceanBleDevices/src/BLEScanner/BleInterfaces.h
        lib/EnOceanBleDevices/src/BLEScanner/BleScanner.cpp
)

file(GLOB_RECURSE SRCFILESREC
        lib/NimBLE-Arduino/src/*.c
        lib/NimBLE-Arduino/src/*.cpp
        lib/NimBLE-Arduino/src/*.h
)


add_executable(${PROJECT_NAME}
        main.cpp
        ${SRCFILES}
        ${SRCFILESREC}
)

target_compile_definitions(${PROJECT_NAME}
        PRIVATE
        ARDUHAL_LOG_LEVEL=${LOG_LEVEL}
        CORE_DEBUG_LEVEL=${LOG_LEVEL}
        CONFIG_NIMBLE_CPP_LOG_LEVEL=0
)

#target_link_esp32_sdk(${PROJECT_NAME})

target_link_arduino_libraries(${PROJECT_NAME}
    PRIVATE
        core
#        WiFi
#        Update
#        WebServer
#        DNSServer
#        Preferences
#        SPIFFS
        Wire
#        FS
)

#target_link_arduino_libraries(DNSServer PUBLIC WiFi)

# This is needed for the generation of HEX binary and uploading it
target_enable_arduino_upload(${PROJECT_NAME})

