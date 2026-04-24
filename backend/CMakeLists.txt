cmake_minimum_required(VERSION 3.20)
project(backend)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Crow CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(libpqxx CONFIG REQUIRED)

add_executable(server src/main.cpp "src/domain/Book.hpp")

add_compile_options(/std:c++latest)

target_link_libraries(server PRIVATE Crow::Crow nlohmann_json::nlohmann_json libpqxx::pqxx)

add_custom_command(TARGET server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/config.json
    $<TARGET_FILE_DIR:server>
)