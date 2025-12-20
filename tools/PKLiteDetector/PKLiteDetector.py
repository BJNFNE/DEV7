# PKLiteDetector is based on SecuROMDetector

def identify_exe(exe_path, exe_check):
    try:
        with open(exe_path, 'rb') as file:
            exe_contents = file.read()
            if exe_check.encode() in exe_contents:
                return True
    except FileNotFoundError:
        print(f"File {exe_path} not found.")
    return False

# Define a list of valid executable names (case-insensitive)
valid_exes = ["SYSTEM.EXE", "system.exe", "System.EXE", "System.exe", "loader7.exe", "Dev7VM.exe"]

# Ask the user for the file path
exe_file = input("Enter the name of the EXE file (with .EXE extension): ")

# Check if the input file is valid by matching it against valid EXE names
if exe_file.lower() in (valid_exe.lower() for valid_exe in valid_exes):
    found_pattern = False

    # Check for PKLite v2.1
    if identify_exe(exe_file, "PKlite(R) Copr. 1990-1996 PKWARE Inc. All Rights Reserved"):
        print("PKLite v2.1")
        found_pattern = True
        
    # If no recognized pattern was found
    if not found_pattern:
        print("Maybe this EXE uses a different version of PKLite, "
              "Please contact BJNFNE on Discord")
else:
    print("Invalid EXE file. Please enter a valid executable name.")

input("Press enter to close PKLiteDetector")  # TODO: Add better handling for closing