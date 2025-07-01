# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/d-cuzya/Рабочий стол/tg-weather_bot/src/build/Desktop-Debug/_deps/cpr-src"
  "/home/d-cuzya/Рабочий стол/tg-weather_bot/src/build/Desktop-Debug/_deps/cpr-build"
  "/home/d-cuzya/Рабочий стол/tg-weather_bot/src/build/Desktop-Debug/_deps/cpr-subbuild/cpr-populate-prefix"
  "/home/d-cuzya/Рабочий стол/tg-weather_bot/src/build/Desktop-Debug/_deps/cpr-subbuild/cpr-populate-prefix/tmp"
  "/home/d-cuzya/Рабочий стол/tg-weather_bot/src/build/Desktop-Debug/_deps/cpr-subbuild/cpr-populate-prefix/src/cpr-populate-stamp"
  "/home/d-cuzya/Рабочий стол/tg-weather_bot/src/build/Desktop-Debug/_deps/cpr-subbuild/cpr-populate-prefix/src"
  "/home/d-cuzya/Рабочий стол/tg-weather_bot/src/build/Desktop-Debug/_deps/cpr-subbuild/cpr-populate-prefix/src/cpr-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/d-cuzya/Рабочий стол/tg-weather_bot/src/build/Desktop-Debug/_deps/cpr-subbuild/cpr-populate-prefix/src/cpr-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/d-cuzya/Рабочий стол/tg-weather_bot/src/build/Desktop-Debug/_deps/cpr-subbuild/cpr-populate-prefix/src/cpr-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
