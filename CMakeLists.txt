cmake_minimum_required(VERSION 3.10)
project(VideoPlatformBackend)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-D_WIN32_WINNT=0x0A00)

include_directories(
    libs/crow/include
    libs/asio/include
    "C:/Program Files/MySQL/MySQL Server 8.0/include"
)

add_executable(backend
    src/main.cpp
    src/db.cpp
)

target_link_libraries(backend
    "C:/Program Files/MySQL/MySQL Server 8.0/lib/libmysql.lib"
)
