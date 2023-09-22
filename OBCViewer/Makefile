# Makefile for OBCViewer
# Developed for Linux

# CPP file & object files 
OBCViewer: 
	g++ -o OBCViewer OBCViewer.cpp

installdeps_apt: # for APT users (Ubuntu & Debian based distros)
	sudo apt update # (for avoiding any errors)
	sudo apt install build-essential make

installdeps_yum: # for YUM users (Fedora & RHEL & CentOS based distros)
	yum install gcc gcc-c++ kernel-devel make

# Start OBCViewer over make command
start:
	./OBCViewer
	
# Delete all Objects files
clean: 
	rm *.o
