cmake_minimum_required(VERSION 3.0.0)
project(udp_mutiplex_server VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

add_executable(udp_mutiplex_server main.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
