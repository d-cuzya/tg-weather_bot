# cmake_minimum_required(VERSION 3.16)

# project(tg-weather_bot LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(Threads REQUIRED)
# find_package(OpenSSL REQUIRED)
# find_package(Boost COMPONENTS system REQUIRED)
# find_package(PostgreSQL REQUIRED)
# find_package(CURL)
# include_directories(
#     ${OPENSSL_INCLUDE_DIR}
#     Boost::boost
#     Boost::system
# )
# if (CURL_FOUND)
#     include_directories(${CURL_INCLUDE_DIRS})
#     add_definitions(-DHAVE_CURL)
# endif()

# add_executable(tg-weather_bot main.cpp
#     .env
#     README.md
#     .env.example .gitignore
#     weatherapi.h weatherapi.cpp
#     curleasy.h curleasy.cpp
#     json.hpp
#     postgresclient.h postgresclient.cpp
#     schem.sql
#     reset_count.sql
#     compose.yaml
# )

# include(GNUInstallDirs)
# install(TARGETS tg-weather_bot
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )

# target_link_libraries(tg-weather_bot
#     /usr/local/lib/libTgBot.a
#     ${CMAKE_THREAD_LIBS_INIT}
#     ${OPENSSL_LIBRARIES}
#     ${Boost_LIBRARIES}
#     ${CURL_LIBRARIES}
#     PostgreSQL::PostgreSQL
# )

# file(STRINGS ".env" ENV_FILE)
# foreach(line IN LISTS ENV_FILE)
#     if(line MATCHES "^TG_TOKEN=(.*)")
#         set(TOKEN "${CMAKE_MATCH_1}")
#         target_compile_definitions(tg-weather_bot PRIVATE TG_TOKEN="${CMAKE_MATCH_1}")
#     endif()
#     if(line MATCHES "^WEATHERAPI_KEY=(.*)")
#         set(TOKEN "${CMAKE_MATCH_1}")
#         target_compile_definitions(tg-weather_bot PRIVATE WEATHERAPI_KEY="${CMAKE_MATCH_1}")
#     endif()

#     if(line MATCHES "^DB_HOST=(.*)")
#         set(TOKEN "${CMAKE_MATCH_1}")
#         target_compile_definitions(tg-weather_bot PRIVATE DB_HOST="${CMAKE_MATCH_1}")
#     endif()
#     if(line MATCHES "^DB_NAME=(.*)")
#         set(TOKEN "${CMAKE_MATCH_1}")
#         target_compile_definitions(tg-weather_bot PRIVATE DB_NAME="${CMAKE_MATCH_1}")
#     endif()
#     if(line MATCHES "^DB_USER=(.*)")
#         set(TOKEN "${CMAKE_MATCH_1}")
#         target_compile_definitions(tg-weather_bot PRIVATE DB_USER="${CMAKE_MATCH_1}")
#     endif()
#     if(line MATCHES "^DB_PASSWORD=(.*)")
#         set(TOKEN "${CMAKE_MATCH_1}")
#         target_compile_definitions(tg-weather_bot PRIVATE DB_PASSWORD="${CMAKE_MATCH_1}")
#     endif()
# endforeach()
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

add_executable(tg-weather_bot main.cpp
    .env
    README.md
    .env.example .gitignore
    weatherapi.h weatherapi.cpp
    curleasy.h curleasy.cpp
    json.hpp
    postgresclient.h postgresclient.cpp
    schem.sql
    reset_count.sql
    compose.yaml
    multiQueue.h

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
)

file(STRINGS ".env" ENV_FILE)
foreach(line IN LISTS ENV_FILE)
    if(line MATCHES "^TG_TOKEN=(.*)")
        set(TOKEN "${CMAKE_MATCH_1}")
        target_compile_definitions(tg-weather_bot PRIVATE TG_TOKEN="${CMAKE_MATCH_1}")
    endif()
    if(line MATCHES "^WEATHERAPI_KEY=(.*)")
        set(TOKEN "${CMAKE_MATCH_1}")
        target_compile_definitions(tg-weather_bot PRIVATE WEATHERAPI_KEY="${CMAKE_MATCH_1}")
    endif()

    if(line MATCHES "^DB_HOST=(.*)")
        set(TOKEN "${CMAKE_MATCH_1}")
        target_compile_definitions(tg-weather_bot PRIVATE DB_HOST="${CMAKE_MATCH_1}")
    endif()
    if(line MATCHES "^DB_NAME=(.*)")
        set(TOKEN "${CMAKE_MATCH_1}")
        target_compile_definitions(tg-weather_bot PRIVATE DB_NAME="${CMAKE_MATCH_1}")
    endif()
    if(line MATCHES "^DB_USER=(.*)")
        set(TOKEN "${CMAKE_MATCH_1}")
        target_compile_definitions(tg-weather_bot PRIVATE DB_USER="${CMAKE_MATCH_1}")
    endif()
    if(line MATCHES "^DB_PASSWORD=(.*)")
        set(TOKEN "${CMAKE_MATCH_1}")
        target_compile_definitions(tg-weather_bot PRIVATE DB_PASSWORD="${CMAKE_MATCH_1}")
    endif()
endforeach()
