SHELL := /bin/bash

.PHONY: help NFs mysql

help:
	@echo "make [target] [NFs/UERANSIM/clean/mysql]"

NFs:
	/bin/sh -c ./setup/NF.sh
	@echo "NFs build completed successfully"

mysql:
	sudo apt update
	sudo apt install mysql-server -y
	sudo mysql_secure_installation
	sudo systemctl start mysql
	sudo systemctl enable mysql

	/bin/sh -c ./setup/datasetup.sh

UERANSIM:
	cd UERANSIM-OAI && rm -rf ./cmake-build-release/* && make
	@echo "UERASANIM build completed successfully"
