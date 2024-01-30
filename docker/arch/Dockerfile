FROM manjarolinux/base

ENV CC=gcc \
    CXX=g++ \
    AR=gcc-ar \
    RANLIB=gcc-ranlib \
    IROOT=/install

RUN pacman -Syu --noconfirm && pacman -S --needed base-devel git yay --noconfirm

# yay
#
#ENV YAY_ROOT="$IROOT/yay"
#
#RUN git clone https://aur.archlinux.org/yay.git $YAY_ROOT
#
#WORKDIR $YAY_ROOT
#
#RUN makepkg -si
#
RUN yay --version

# Drogon

RUN yay -Syyu --noconfirm && yay -S drogon --noconfirm

#    LANG=en_US.UTF-8 \
#    LANGUAGE=en_US:en \
#    LC_ALL=en_US.UTF-8 \

CMD [ "drogon_ctl version" ]

ENV SERVER_ROOT="$IROOT/IOTServer"

RUN git clone https://github.com/Diam2023/IOTServer $SERVER_ROOT

WORKDIR $SERVER_ROOT

RUN ./build.sh

CMD [ "/install/IOTServer/build/IOTServer" ]
