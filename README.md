# IOT Server Project

## Pre Config
* config/config.yaml
  * https://github.com/drogonframework/drogon/wiki/ENG-10-Configuration-Filehttps://github.com/drogonframework/drogon/wiki/ENG-10-Configuration-Filehttps://github.com/drogonframework/drogon/wiki/ENG-10-Configuration-File
* docker/cqhttp/cqconf/config.yml
  * https://docs.go-cqhttp.org/guide/config.html
* docker/mosquitto/mosquitto.conf

## Use Docker
```shell

git clone -b docker https://github.com/Diam2023/IOTServer
# Or switch to
cd docker 
docker compose run *
# use -d if need
# docker compose stop

```

## Manual Install

Request
* MySQL (MariaDB)
* Redis
* yaml-cpp

### Yaml-Cpp
#### Arch
```shell
yay -S yaml-cpp
```

#### Debian
```shell
sudo apt install libyaml-cpp-dev
```


### Install QtMqtt

> https://github.com/KurtPattyn/QtMqtt

#### Arch 
```shell
yay -S qt5-mqtt
```

#### Debian
```shell

git clone -b 5.12.3 git://code.qt.io/qt/qtmqtt.git qtmqtt

cd qtmqtt

mkdir build

cd build

qmake ..

make

sudo make install

```

### Install Drogon

> https://github.com/drogonframework/drogon/wiki/ENG-02-Installation

#### Arch
```shell
yay -S drogon
```
#### Debian

```shell

git clone https://github.com/drogonframework/drogon

cd drogon

./build
```
### Install Drogon

> https://github.com/drogonframework/drogon/wiki/ENG-02-Installation

#### Arch
```shell
yay -S drogon
```
#### Debian

```shell

git clone https://github.com/drogonframework/drogon

cd drogon

./build
```
## Community API

### GoCQHttp

#### User Interface

All Command: config/config.yaml:240

Or send "help" to Bot

[//]: # (TODO)

| command              | action    |
|----------------------|-----------|
| 登入{usr} {pwd}        | LoginAPI  |
| 登出                   | LogoutAPI |
| 添加设备{name} {sn}      |           |
| 删除设备{name}           |           |
| 查看所有设备               |           |
| 订阅设备{name} {`topic`} |           |
| 取消订阅{name} {`topic`} |           |
| 查看所有订阅消息             |           |
| 查看所有设备别名             |           |
| 设备别名{name}           |           |
| 添加别名{name}           |           |
| 删除别名{name}           |           |

#### Custom Define Action

> 定义操作 {操作名} {设备名/别名} {subtopic} {JSON数据}

It will publish JSON data to device topic When call {操作名}

| command   | announcement |
|-----------|--------------|
| 定义操作{}    |              |
| 删除操作{操作名} |              |

### Http

> root dir `/api/`

#### User Api

> base dir `user/`

| Path     | Request Type | Request Body                                                                                 | Header               | Status                                                | Response Body                                                                                                                                                   |
|----------|--------------|----------------------------------------------------------------------------------------------|----------------------|-------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------|
| register | PUT          | <pre lang="json"><code>{<br/>  "user_name": "",<br/>  "user_password": ""<br/>}</code></pre> | NAN                  | 200 Successful<br/>500                                |                                                                                                                                                                 |
| login    | POST         | <pre lang="json"><code>{<br/>  "key": "name/id",<br/>  "pwd": "pwd" <br/>}</code></pre>      | NAN                  | 203 Need Authorize<br/>200 Successful<br/>401         | <pre><code lang="json">{<br/>  "token": ""<br/>}</code></pre>                                                                                                   |
| info     | GET          | NAN                                                                                          | Authorization: token | 203 Need Authorize<br/>200 Successful<br/>401<br/>400 | <pre><code lang="json">{<br/>  "user_id": 2,<br/>  "user_name": "testUser10",<br/>  "user_password": "",<br/>  "user_permission_level": 100 <br/>}</code></pre> |
| logout   | DELETE       | NAN                                                                                          | Authorization: token | 200 Successful<br/>500                                |                                                                                                                                                                 |

#### Device Api

> base dir `device/`

| Path   | Request Type | Request Body                                                                                                                                                                       | Header               | Status                                                                 | Response Body                                                                                                                                                  |
|--------|--------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|----------------------|------------------------------------------------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------|
| new    | PUT          | <pre lang="json"><code>{<br/>  "device_sn": "DTESTSNDATA",<br/>  "device_name": "TD"<br/>,<br/>  "device_comment": "TestComment",<br/>  "target_permission_level": 1}</code></pre> | Authorization: token | 203 Need Authorize<br/>200 Successful<br/>400 Request Body Err<br/>500 |                                                                                                                                                                |
| delete | DELETE       | <pre lang="json"><code>{<br/>  "device_sn": "DTESTSNDATA"<br/>}</code></pre>                                                                                                       | Authorization: token | 203 Need Authorize<br/>200 Successful<br/>400 Request Body Err<br/>500 |                                                                                                                                                                |
| info   | GET          | <pre lang="json"><code>{<br/>  "device_sn": "DTESTSNDATA"<br/>}</code></pre>                                                                                                       | Authorization: token | 203 Need Authorize<br/>200 Successful<br/>400 Request Body Err<br/>500 | <pre><code lang="json">{<br/>  "device_id": 2,<br/>  "device_name": "Name",<br/>  "device_sn": "",<br/>  "target_permission_level": 50 <br/>}</code></pre>     |
| all    | GET          | NAN                                                                                                                                                                                | Authorization: token | 203 Need Authorize<br/>200 Successful<br/>500                          | <pre><code lang="json">\[{<br/>  "device_id": 2,<br/>  "device_name": "Name",<br/>  "device_sn": "",<br/>  "target_permission_level": 50 <br/>}\]</code></pre> |

#### Subscribe Api

> base dir `subscribe/`

| Path   | Request Type | Request Body                                                                                           | Header               | Status                                                                 | Response Body                                                                       |
|--------|--------------|--------------------------------------------------------------------------------------------------------|----------------------|------------------------------------------------------------------------|-------------------------------------------------------------------------------------|
| new    | PUT          | <pre lang="json"><code>{<br/>  "device_sn": "TESESNDDT",<br/>  "topic": "TestTopic"<br/>}</code></pre> | Authorization: token | 203 Need Authorize<br/>200 Successful<br/>400 Request Body Err<br/>500 |                                                                                     |
| delete | DELETE       | <pre lang="json"><code>{<br/>  "device_sn": "TESESNDDT",<br/>  "topic": "TestTopic"<br/>}</code></pre> | Authorization: token | 203 Need Authorize<br/>200 Successful<br/>400 Request Body Err<br/>500 |                                                                                     |
| all    | GET          | NAN                                                                                                    | Authorization: token | 203 Need Authorize<br/>200 Successful<br/>500                          | <pre><code lang="json">\{<br/>  "devices":[],<br/>  "aliases":[]<br/>}</code></pre> |

#### Alias Api

> base dir `alias/`

| Path   | Request Type | Request Body                                                                                             | Header               | Status                                                                 | Response Body                                                                       |
|--------|--------------|----------------------------------------------------------------------------------------------------------|----------------------|------------------------------------------------------------------------|-------------------------------------------------------------------------------------|
| new    | PUT          | <pre lang="json"><code>{<br/>  "device_sn": "DTESTSNDATA",<br/>  "alias": "testAlias"<br/>}</code></pre> | Authorization: token | 203 Need Authorize<br/>200 Successful<br/>400 Request Body Err<br/>500 |                                                                                     |
| delete | DELETE       | <pre lang="json"><code>{<br/>  "alias": "MyRoom"<br/>}</code></pre>                                      | Authorization: token | 203 Need Authorize<br/>200 Successful<br/>400 Request Body Err<br/>500 |                                                                                     |
| all    | GET          | NAN                                                                                                      | Authorization: token | 203 Need Authorize<br/>200 Successful<br/>500                          | <pre><code lang="json">\{<br/>  "devices":[],<br/>  "aliases":[]<br/>}</code></pre> |

#### Action Api

> base dir `action/`

| Path   | Request Type | Request Body                                                                                                                                                         | Header               | Status                                                                 | Response Body                                                                                           |
|--------|--------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------|----------------------|------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------|
| new    | PUT          | <pre lang="json"><code>{<br/>  "action_name": "TA1",<br/>  "device_sn": "TESESNDDT",<br/>  "topic_name": "testTopic1",<br/>  "action_json": {...}<br/>}</code></pre> | Authorization: token | 203 Need Authorize<br/>200 Successful<br/>400 Request Body Err<br/>500 |                                                                                                         |
| delete | DELETE       | <pre lang="json"><code>{<br/>  "action_name": "TA1"<br/>}</code></pre>                                                                                               | Authorization: token | 203 Need Authorize<br/>200 Successful<br/>400 Request Body Err<br/>500 |                                                                                                         |
| all    | GET          | NAN                                                                                                                                                                  | Authorization: token | 203 Need Authorize<br/>200 Successful<br/>500                          | <pre><code lang="json">\{<br/>  "devices":[],<br/>  "aliases":[],<br/>  "actions":[]<br/>}</code></pre> |
| call   | PUT          | <pre lang="json"><code>{<br/>  "action": "TA1"<br/>}</code></pre>                                                                                                    | Authorization: token | 203 Need Authorize<br/>200 Successful<br/>404                          | NAN                                                                                                     |

### Gotify

### 數據庫

* Mysql
* Redis

### Mqtt

* mosquitto

---
