# IOT Server Project

---

## Community API

### Http

> base dir `/api/`

| path          | type   | json                                                      | header               | response |
|---------------|--------|-----------------------------------------------------------|----------------------|----------|
| user/register | Put    | { <br/> "user_name": "", <br/> "user_password": "" <br/>} | NAN                  |          |
| user/login    | POST   | { <br/> "key": "name/id", <br/> "pwd": "pwd" <br/>}       | NAN                  | token    |
| user/info     | GET    | NAN                                                       | Authorization: token |          |
| user/logout   | DELETE | NAN                                                       | Authorization: token |          |

### GoCQHttp

#### User Interface

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

### Gotify

### 數據庫

* Mysql
* Redis

### Mqtt

* mosquitto

---
