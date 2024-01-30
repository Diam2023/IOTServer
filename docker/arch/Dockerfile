FROM manjarolinux/base

ENV CC=gcc \
    CXX=g++ \
    AR=gcc-ar \
    RANLIB=gcc-ranlib \
    IROOT=/install

RUN pacman -Syu --noconfirm && pacman -S --needed base-devel cmake git c-ares hiredis jsoncpp mariadb yay --noconfirm

# Drogon

ENV DROGON_ROOT="$IROOT/drogon"

RUN git clone https://github.com/drogonframework/drogon $DROGON_ROOT

WORKDIR $DROGON_ROOT

RUN ./build.sh

RUN drogon_ctl version


# IOTServer

ENV SERVER_ROOT="$IROOT/IOTServer"

RUN git clone https://github.com/Diam2023/IOTServer $SERVER_ROOT

WORKDIR $SERVER_ROOT

RUN ./build.sh

CMD [ "/install/IOTServer/build/IOTServer" ]
