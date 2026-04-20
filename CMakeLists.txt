cmake_minimum_required(VERSION 3.21)

set(GEODE_TARGET_PLATFORM "Android64" CACHE STRING "" FORCE)  # Cambiar a Android32 si necesario
project(improved-editor-tralalero VERSION 1.0.0)

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

setup_geode_mod(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    src/main.cpp
    src/BlockHubPopup.cpp
)