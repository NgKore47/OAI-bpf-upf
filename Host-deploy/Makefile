SHELL := /bin/bash

.PHONY: help

help:
	@echo "make [target] [NFs/UERASANIM/clean/mysql]"

NFs:
	export MAKEFLAGS="-B" >> ~/.bashrc && export MAKEFLAGS="-B" >> ~/.zshrc
	/bin/sh -c ./setup/NF.sh
	@echo "NFs build completed successfully"

mysql:
	sudo apt update
	sudo apt install mysql-server -y
	sudo mysql_secure_installation
	sudo systemctl start mysql
	sudo systemctl enable mysql

UERANSIM:
	cd UERANSIM-OAI && make
	@echo "UERASANIM build completed successfully"
