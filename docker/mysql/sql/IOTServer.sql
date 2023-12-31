CREATE TABLE `users` (
                         `user_id` int unsigned NOT NULL AUTO_INCREMENT COMMENT '用户ID',
                         `user_name` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '用户名',
                         `user_password` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL COMMENT '密码',
                         `user_permission_id` int unsigned NOT NULL DEFAULT '0' COMMENT '操作权限ID，对应权限表',
                         PRIMARY KEY (`user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci COMMENT='用户';


CREATE TABLE `topics` (
                          `topic_id` int unsigned NOT NULL AUTO_INCREMENT COMMENT '消息id',
                          `topic_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT 'topic',
                          `topic_data` json DEFAULT NULL COMMENT '消息内容，所有传输均使用json',
                          `topic_qos` enum('QOS0','QOS1','QOS2') NOT NULL DEFAULT 'QOS2' COMMENT '消息服务质量',
                          `topic_permission_level` int unsigned NOT NULL DEFAULT '255' COMMENT '操作权限等级，对应权限表等级',
                          PRIMARY KEY (`topic_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci COMMENT='所有创建的主题';


CREATE TABLE `permissions` (
                               `permission_id` int unsigned NOT NULL AUTO_INCREMENT COMMENT '权限ID',
                               `permission_level` int unsigned NOT NULL DEFAULT '100' COMMENT '权限值',
                               `permission_comment` varchar(1024) DEFAULT NULL COMMENT '权限描述',
                               PRIMARY KEY (`permission_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

FLUSH PRIVILEGES;
