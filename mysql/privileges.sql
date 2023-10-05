-- Create waterbox user for mysql
CREATE USER 'waterbox'@'localhost' IDENTIFIED BY 'y2A@kw9&';
-- Upgrade
GRANT CREATE, ALTER, DROP, INSERT, UPDATE, DELETE, SELECT, REFERENCES, RELOAD ON *.* TO 'waterbox'@'localhost' WITH GRANT OPTION;

FLUSH PRIVILEGES;
