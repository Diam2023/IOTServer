#!/bin/bash
set -e

# Search status
service mysql status

service mysql start
sleep 3

service mysql status

mysql < ./mysql/schema.sql

service mysql status

mysql < /mysql/privileges.sql

tail -f /dev/null
