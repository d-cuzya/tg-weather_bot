cmake_minimum_required(VERSION 3.16)

project(tg-weather_bot LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)
include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

add_executable(tg-weather_bot main.cpp
    .env
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
)

file(STRINGS ".env" ENV_FILE)
foreach(line IN LISTS ENV_FILE)
    if(line MATCHES "^TOKEN=(.*)")
        set(TOKEN "${CMAKE_MATCH_1}")
        target_compile_definitions(tg-weather_bot PRIVATE TOKEN="${CMAKE_MATCH_1}")
    endif()
endforeach()
