### oai-core-ebpf-deploy
<details><summary>Host Deployment </summary>

go to [Core-NFs](https://github.com/evershalik/OAI-bpf-upf/tree/main/Core-NFs) directory and just run ```make``` for options
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
command to run all nfs. Just change ```<nf name>``` with nfs name.
```
sudo <nf name> -c config.yaml -o
```
</details>

<details><summary>Docker compose</summary>

first clone this repo :
```bash
git clone https://github.com/evershalik/OAI-bpf-upf
cd OAI-bpf-upf
```
then move to docker compose directory :
```bash
cd docker-compose/oai-cn5g-fed/docker-compose
```
now just deploy oai-core with ebpf-upf :
```bash
docker compose -f docker-compose-basic-nrf-ebpf.yaml up -d
```

now check oai-upf logs to check it's running or not:
```bash
docker logs oai-upf
```
now deploy gnbsim :
```bash
docker compose -f docker-compose-gnbsim-ebpf.yaml up -d
```
now exec gnbsim container :
```bash
docker exec -it gnbsim-ebpf bash
```

to check internet ping google.com or 8.8.8.8 :
```bash
ping -I 12.1.1.2 8.8.8.8
```

</details>
