cmake_minimum_required(VERSION 3.16)

project(tg-weather_bot LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(CURL)
include_directories(
    ${OPENSSL_INCLUDE_DIR}
    Boost::boost
    Boost::system
)
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

include(FetchContent)
FetchContent_Declare(
  dotenv-cpp
  GIT_REPOSITORY https://github.com/laserpants/dotenv-cpp.git
  GIT_TAG master
)
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG master
)
set(CPR_USE_SYSTEM_CURL ON)
set(CPR_USE_SYSTEM_LIB_PSL ON)
FetchContent_Declare(
  cpr
  GIT_REPOSITORY https://github.com/libcpr/cpr.git
  GIT_TAG da40186618909b1a7363d4e4495aa899c6e0eb75
)
FetchContent_MakeAvailable(
  dotenv-cpp
  json
  cpr
)

add_executable(tg-weather_bot main.cpp
    .env.example
    weatherapi.h weatherapi.cpp
    curleasy.h curleasy.cpp
    json.hpp
    postgresclient.h postgresclient.cpp
    multiQueue.h
    .env
    mytgbot.h mytgbot.cpp

)

include(GNUInstallDirs)
install(TARGETS tg-weather_bot
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_link_libraries(tg-weather_bot
    /usr/local/lib/libTgBot.a
    ${CMAKE_THREAD_LIBS_INIT}
    ${OPENSSL_LIBRARIES}
    ${Boost_LIBRARIES}
    ${CURL_LIBRARIES}
    PostgreSQL::PostgreSQL
    cpr::cpr
)

target_include_directories(tg-weather_bot PRIVATE
  ${dotenv-cpp_SOURCE_DIR}/include/laserpants/dotenv/
  ${json_SOURCE_DIR}/single_include/nlohmann
  ${cpr_SOURCE_DIR}/include/
)
