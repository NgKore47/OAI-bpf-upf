#!/bin/bash

# Run sudo mysql to enter the MySQL shell
sudo mysql -u root -p << EOF
    # Execute commands in the MySQL shell
    CREATE DATABASE oai_db;

    CREATE USER 'username'@'localhost' IDENTIFIED BY 'password';
    GRANT ALL PRIVILEGES ON oai_db.* TO 'username'@'localhost';
    FLUSH PRIVILEGES;
EOF

# Run sudo mysql to import SQL file
sudo mysql -u username -p oai_db < Database/oai_00101.sql

# Run sudo mysql to enter the MySQL shell again
sudo mysql -u username -p oai_db << EOF
    # Execute commands in the MySQL shell
    SHOW DATABASES;
    USE oai_db;
    SHOW TABLES;
EOF

