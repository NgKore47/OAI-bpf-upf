### oai-core-ebpf-deploy

just run ```make``` for options
```
make NFs
make UERANSIM
make mysql
```

```
sudo mysql -u root -p

# the following commands should run in mysql shell
CREATE DATABASE oai_db;

CREATE USER 'username'@'localhost' IDENTIFIED BY 'password';
GRANT ALL PRIVILEGES ON oai_db.* TO 'username'@'localhost';
FLUSH PRIVILEGES;

# sudo commands should run from outside of the mysql shell
sudo mysql -u username -p oai_db < Database/oai_00101.sql

sudo mysql -u username -p oai_db

SHOW DATABASES;

USE oai_db;
SHOW TABLES;
```

config.yaml is used for all nfs. Change the interface name according to system configuration.<br>
command to run all nfs. Just change nrf with other nfs name 
```
sudo nrf -c config.yaml -o
```
to remove everything
```
make clean
```
