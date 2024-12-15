# SecuROMDetector is based on IMGIdentifier

def identify_exe(exe_path, exe_check):
    try:
        with open(exe_path, 'rb') as file:
            exe_contents = file.read()
            if exe_check.encode() in exe_contents:
                return True
    except FileNotFoundError:
        print(f"File {exe_path} not found.")
    return False

# Ask the user for the file path
exe_file = input("Enter the name of the EXE file (with .EXE extension): ")

# Check if the input file has a valid .exe extension
if exe_file.lower().endswith((".exe")):
    found_pattern = False

    # Check for SecuROM version 4.00.00
    if identify_exe(exe_file, "4.00.00"):
        print("SecuROM 4.00.00")
        found_pattern = True

    # Check for SecuROM version 4.77.00
    if identify_exe(exe_file, "4.77.00"):
        print("SecuROM 4.77.00")
        found_pattern = True

    # Check for SecuROM version 4.83.11
    if identify_exe(exe_file, "4.83.11"):
        print("SecuROM 4.83.11")
        found_pattern = True
    
    # Check for .cms_t pattern
    if identify_exe(exe_file, ".cms_t"):
        print("SecuROM code found inside the executable (.cms_t)")
        found_pattern = True
    
    # Check for .cms_d pattern
    if identify_exe(exe_file, ".cms_d"):
        print("SecuROM data found inside the executable (.cms_d)")
        found_pattern = True
    
    # If no recognized pattern was found
    if not found_pattern:
        print("Maybe this EXE uses a different version of SecuROM, "
              "Please contact BJNFNE on Discord")
else:
    print("Invalid EXE file extension. Please add the .exe extension as well.")

input("Press enter to close SecuROMDetector")
