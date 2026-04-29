cmake_minimum_required(VERSION 3.20)
project(backend)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

find_package(Crow CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(libpqxx CONFIG REQUIRED)
find_package(unofficial-argon2 CONFIG REQUIRED)
find_package(jwt-cpp CONFIG REQUIRED)

add_compile_definitions(_WIN32_WINNT=0x0A00)

add_executable(server src/main.cpp "src/domain/Book.hpp" "src/security/PasswordHasher.cpp"  "src/config/ConfigLoader.cpp")

add_compile_options(/std:c++latest)

target_link_libraries(server PRIVATE 
    Crow::Crow 
    nlohmann_json::nlohmann_json 
    libpqxx::pqxx
    unofficial::argon2::libargon2
    jwt-cpp::jwt-cpp
)

add_custom_command(TARGET server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/../config.json
    $<TARGET_FILE_DIR:server>
)