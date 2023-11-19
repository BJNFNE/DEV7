# Makefile for OBCViewer
# Works on Linux & MacOS

# CPP file & object files
OBCViewer:
	g++ -o OBCViewer OBCViewer.cpp -O2 -g -Wall -Wextra -pipe -std=c++20

verbose:
	g++ -o OBCViewer OBCViewer.cpp -O2 -g -Wall -Wextra -pipe -std=c++20 -v

installdeps_apt: # for APT users (Ubuntu & Debian based distros)
	sudo apt update # (for avoiding any errors)
	sudo apt install build-essential make

installdeps_yum: # for YUM users (Fedora & RHEL & CentOS based distros)
	sudo yum install gcc gcc-c++ kernel-devel make

installdeps_brew: # for BREW users (MacOS)
	sudo brew install gcc
	sudo brew install make

# Start OBCViewer over make command
start:
	./OBCViewer

# Delete all Object files (if there exists)
clean:
	rm *.o

# Clean all Objects (OBC) from the Directory
clean_obc:
	rm *.obc

# Clean all TXT files created by OBCViewer
clean_txt:
	rm *.txt

credits:
	@echo "Credits:\n"
	@echo "BJNFNE (Main developer)"
	@echo "rzil (BLooperZ) (Thanks for helping out)"

delete:
	rm OBCViewer
