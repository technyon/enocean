cmake_minimum_required(VERSION 3.0.0)

set(ARDUINO_BOARD "ESP32 Dev Module [esp32.esp32]")

project(enocean CXX)

include_directories(${PROJECT_NAME}
        PRIVATE
        lib/NimBLE-Arduino/src
        lib/enocean_PTM215b/src
)

file(GLOB SRCFILES
    lib/enocean_PTM215b/src/enocean_Constants.h
    lib/enocean_PTM215b/src/enocean_PTM215b.cpp
    lib/enocean_PTM215b/src/enocean_utils.h
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
        ARDUHAL_LOG_LEVEL=ARDUHAL_LOG_LEVEL_DEBUG
        CORE_DEBUG_LEVEL=ARDUHAL_LOG_LEVEL_DEBUG
        CONFIG_NIMBLE_CPP_LOG_LEVEL=0
)

#target_link_esp32_sdk(${PROJECT_NAME})

# Arduino.h is included in hello_world.cpp, so link with Arduino core
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

