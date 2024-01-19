CREATE TABLE `user`
(
    `user_id`               int unsigned NOT NULL AUTO_INCREMENT COMMENT '用户ID',
    `user_name`             varchar(100) NOT NULL COMMENT '用户名',
    `user_password`         varchar(100)          DEFAULT NULL COMMENT '密码',
    `user_permission_level` int unsigned NOT NULL DEFAULT '100' COMMENT '操作权限等级',
    PRIMARY KEY (`user_id`)
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_0900_ai_ci COMMENT ='用户';

-- 本质为一个设备对多个topic
CREATE TABLE `device`
(
    `device_id`               int unsigned NOT NULL AUTO_INCREMENT COMMENT '设备ID',
    `device_sn`               varchar(100) NOT NULL COMMENT '设备序列号',
    `device_name`             varchar(100) NOT NULL COMMENT '设备名',
    `device_comment`          varchar(1024)         DEFAULT NULL COMMENT '设备描述',
    `target_permission_level` int unsigned NOT NULL DEFAULT '50' COMMENT '操作权限等级',
    PRIMARY KEY (`device_id`)
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_0900_ai_ci COMMENT ='All设备';

-- Only Receive device topic
CREATE TABLE `topic`
(
    `topic_id`         int unsigned                NOT NULL AUTO_INCREMENT COMMENT '消息id',
    `topic_name`       varchar(255)                NOT NULL COMMENT 'topic名',
    `topic_data`       json                                 DEFAULT NULL COMMENT '消息内容，所有传输均使用json',
    `topic_qos`        enum ('QOS0','QOS1','QOS2') NOT NULL DEFAULT 'QOS2' COMMENT '消息服务质量',
    `target_device_id` int unsigned                NOT NULL COMMENT 'target device id',
    PRIMARY KEY (`topic_id`)
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_0900_ai_ci COMMENT ='所有创建的主题';

-- 用户订阅的设备以及Topic列表id
CREATE TABLE `subscribe_map`
(
    `map_id`           int unsigned NOT NULL AUTO_INCREMENT COMMENT 'id',
    `target_user_id`   int unsigned NOT NULL COMMENT 'User id',
    `target_device_id` int unsigned NOT NULL COMMENT 'Device id',
    `target_topic_id`  int unsigned DEFAULT '0' COMMENT 'topic id zero to all',
    PRIMARY KEY (`map_id`)
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_0900_ai_ci COMMENT ='用户订阅的设备以及Topic列表id';

-- 用户设置的设备别名
CREATE TABLE `user_device_alias_map`
(
    `alias_map_id`     int unsigned NOT NULL AUTO_INCREMENT COMMENT 'id',
    `target_user_id`   int unsigned NOT NULL COMMENT 'User id',
    `target_device_id` int unsigned NOT NULL COMMENT 'Device id',
    `alias_name`       varchar(255) NOT NULL COMMENT 'Alias name',
    PRIMARY KEY (`alias_map_id`)
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_0900_ai_ci COMMENT ='用户设置的设备别名';

-- 用户自定义的操作
CREATE TABLE `user_device_action_map`
(
    `action_map_id`          int unsigned NOT NULL AUTO_INCREMENT COMMENT 'id',
    `target_user_id`         int unsigned NOT NULL COMMENT 'User id',
    `target_device_id`       int unsigned NOT NULL COMMENT 'Device id',
    `action_target_topic_id` int unsigned NOT NULL COMMENT '操作作用到设备的topic节点',
    `action_json`            varchar(255) NOT NULL COMMENT 'Action json data',
    PRIMARY KEY (`action_map_id`)
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_0900_ai_ci COMMENT ='用户自定义的操作';

# admin default admin user
INSERT INTO iot_server.user (user_name, user_password, user_permission_level)
VALUES ('admin', 'admin', 500);

FLUSH
    PRIVILEGES;
