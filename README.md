# IOT Server Project

---

## Community API

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

### Gotify

### 數據庫

* Mysql
* Redis

### Mqtt

* mosquitto

---
