# How Run?
## Install dependencies on Debian/Ubuntu
```
sudo apt install g++ make binutils cmake libboost-system-dev libssl-dev zlib1g-dev libcurl4-openssl-dev
```
## Install tgbot-cpp
```
git clone https://github.com/reo7sp/tgbot-cpp
cd tgbot-cpp
cmake .
make -j4
sudo make install
```
## Install the ".env" file
Replace ".env.example" with ".env" and change the values in it
## Build & Run project
```
cmake -B build
cmake --build build
./build/tg-weather_bot
```
