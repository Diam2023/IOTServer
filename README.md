# IOT Server Project

---

## Community API

### Http

> root dir `/api/`

#### User Api

> base dir `user/`

| Path     | Request Type | Request Body                                                                                 | Header               | Status                                                | Response                                                                                                                                                        |
|----------|--------------|----------------------------------------------------------------------------------------------|----------------------|-------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------|
| register | PUT          | <pre lang="json"><code>{<br/>  "user_name": "",<br/>  "user_password": ""<br/>}</code></pre> | NAN                  | 200 Successful<br/>500                                |                                                                                                                                                                 |
| login    | POST         | <pre lang="json"><code>{<br/>  "key": "name/id",<br/>  "pwd": "pwd" <br/>}</pre></code>      | NAN                  | 203 Need Authorize<br/>200 Successful<br/>401         | token                                                                                                                                                           |
| info     | GET          | NAN                                                                                          | Authorization: token | 203 Need Authorize<br/>200 Successful<br/>401<br/>400 | <pre><code lang="json">{<br/>  "user_id": 2,<br/>  "user_name": "testUser10",<br/>  "user_password": "",<br/>  "user_permission_level": 100 <br/>}</code></pre> |
| logout   | DELETE       | NAN                                                                                          | Authorization: token | 200 Successful<br/>500                                |                                                                                                                                                                 |

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
