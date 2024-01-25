cmake_minimum_required(VERSION 3.28)
project(udp_mutiplex_server VERSION 0.1.0 LANGUAGES C)

# ###########################################################
# Create a library
# ###########################################################

# Generate the static library from the library sources
add_library(socket_utils STATIC
    lib/socket_utils/socket_utils.c
)
target_include_directories(socket_utils
    PUBLIC
    ${PROJECT_SOURCE_DIR}/inc
)

# set sources
set(SOURCES
    src/main.c
    src/udp_web_server.c)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}/inc
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    socket_utils
)
