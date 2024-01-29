# Fork from Drogon

FROM archlinux:latest as drogon

RUN pacman -Syu --noconfirm && pacman -S wget sudo cmake make git gcc jsoncpp postgresql mariadb-clients hiredis --noconfirm

ENV LANG=en_US.UTF-8 \
    LANGUAGE=en_US:en \
    LC_ALL=en_US.UTF-8 \
    CC=gcc \
    CXX=g++ \
    AR=gcc-ar \
    RANLIB=gcc-ranlib \
    IROOT=/install

ENV DROGON_ROOT="$IROOT/drogon"

#ADD https://api.github.com/repos/an-tao/drogon/git/refs/heads/master $IROOT/version.json
RUN git clone https://github.com/drogonframework/drogon $DROGON_ROOT

WORKDIR $DROGON_ROOT

RUN ./build.sh


FROM archlinux:latest as iotserver

RUN pacman -Syu --noconfirm && pacman -S  --noconfirm

ENV SERVER_ROOT="$IROOT/IOTServer"

RUN git clone https://github.com/Diam2023/IOTServer $SERVER_ROOT

LABEL authors="diam"

WORKDIR $SERVER_ROOT

RUN ./build.sh

CMD [ "/install/IOTServer/build/IOTServer" ]
