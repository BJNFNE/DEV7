##############################################
# Makefile for ModelPathDumper	             #
# Works on Linux & MacOS					           #
##############################################

# CPP file & object files
OBCViewer:
	g++ -o ModelPathDumper ModelPathDumper.cpp -O2 -g -Wall -Wextra -pipe -std=c++20

verbose:
	g++ -o ModelPathDumper ModelPathDumper.cpp -O2 -g -Wall -Wextra -pipe -std=c++20 -v

installdeps_apt: # for APT users (Ubuntu & Debian based distros)
	sudo apt update # (for avoiding any errors)
	sudo apt install build-essential make -y

installdeps_yum: # for YUM users (Fedora & RHEL & CentOS based distros)
	sudo yum install gcc gcc-c++ kernel-devel make -y

installdeps_brew: # for BREW users (MacOS Homebrew)
	sudo brew install gcc
	sudo brew install make

# Delete all Object files (if there exists)
clean:
	rm *.o

# Clean all EXO files from the Directory
clean_exo:
	rm *.exo

# Clean all TXT files created by ModelPathDumper
clean_txt:
	rm *.txt

credits:
	@echo "Credits:\n"
	@echo "BJNFNE (Main developer)"
