FROM ubuntu:22.04

# Установка зависимостей и PPA
RUN apt update && apt install -y \
    software-properties-common \
    && add-apt-repository ppa:ubuntu-toolchain-r/test -y \
    && apt update && apt install -y \
    g++-13 gcc-13 make cmake git binutils \
    libboost-system-dev libssl-dev zlib1g-dev \
    libcurl4-openssl-dev libpq-dev postgresql-server-dev-all \
    cron

# Установка g++-13 как дефолтного
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 100 && \
    update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-13 100 && \
    ln -sf /usr/bin/g++ /usr/bin/c++ && \
    ln -sf /usr/bin/gcc /usr/bin/cc
    
# Установка tgbot-cpp
WORKDIR /tmp
RUN git clone https://github.com/reo7sp/tgbot-cpp && \
    cd tgbot-cpp && \
    cmake . && make -j$(nproc) && make install

# Рабочая директория твоего проекта
WORKDIR /app
