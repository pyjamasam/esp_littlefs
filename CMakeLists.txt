cmake_minimum_required(VERSION 3.10)

file(GLOB SOURCES src/littlefs/*.c)
list(APPEND SOURCES src/esp_littlefs.c src/littlefs_api.c src/lfs_config.c)

if(IDF_VERSION_MAJOR GREATER_EQUAL 5)
    list(APPEND pr esp_partition)
endif()

idf_component_register(
    SRCS ${SOURCES}
    INCLUDE_DIRS include src
    PRIV_INCLUDE_DIRS src
    PRIV_REQUIRES ${pr} esptool_py spi_flash vfs
)

set_source_files_properties(
    ${SOURCES}
    PROPERTIES COMPILE_FLAGS "-DLFS_CONFIG=lfs_config.h"
)
