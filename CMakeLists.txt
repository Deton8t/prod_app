cmake_minimum_required(VERSION 3.24)
project(prod_app)

set(SOURCE_FILES
    main.c
    terminal.c
)
find_package(raylib REQUIRED)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(prod_app PRIVATE raylib m GL pthread dl rt X11 )
