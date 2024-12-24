import os
import sys

print("git_updater version 1.0\n")

print("Git fetching the latest commits\n")
os.system("git fetch --all")

print("Git pulling latest commits down to local repository\n")
os.system("git pull --all")

sys.exit(0)
