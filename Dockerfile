FROM mariadb:latest as mq

EXPOSE 3306

ENV MYSQL_ALLOW_EMPTY_PASSWORD yes

COPY ./mysql/setup.sh /mysql/setup.sh
COPY ./mysql/schema.sql /mysql/schema.sql
COPY ./mysql/privileges.sql /mysql/privileges.sql

RUN sh /mysql/setup.sh

FROM redis:latest as rs

COPY ./data/redis.conf.orig /usr/local/etc/redis/redis.conf

EXPOSE 6379

RUN redis-server /usr/local/etc/redis/redis.conf


FROM ubuntu:latest as wb
# 构建编译环境
LABEL authors="diam"
MAINTAINER monoliths-uni@outlook.com

RUN apt-get update

# Copy My Work Space To Target
COPY . .


WORKDIR /

ENTRYPOINT ["top", "-b"]

FROM eclipse-mosquitto as mqtt
LABEL authors="diam"



# 构建运行环境
FROM ubuntu:latest as wb



