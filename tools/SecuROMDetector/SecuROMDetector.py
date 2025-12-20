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

# Define a list of valid executable names (case-insensitive)
valid_exes = ["SYSTEM.EXE", "system.exe", "System.EXE", "System.exe", "loader7.exe", "Dev7VM.exe", "SystemEx.exe"]

# Ask the user for the file path
exe_file = input("Enter the name of the EXE file (with .EXE extension): ")

# Check if the input file is valid by matching it against valid EXE names
if exe_file.lower() in (valid_exe.lower() for valid_exe in valid_exes):
    found_pattern = False

    # Check for SecuROM version 4.00.00
    if identify_exe(exe_file, "4.00.00"):
        print("SecuROM 4.00.00")
        found_pattern = True

    # Check for SecuROM version 4.68.00
    if identify_exe(exe_file, "4.68.00"):
        print("SecuROM 4.68.00")
        found_pattern = True

    # Check for SecuROM version 4.77.00
    if identify_exe(exe_file, "4.77.00"):
        print("SecuROM 4.77.00")
        found_pattern = True

    # Check for SecuROM version 4.83.11
    if identify_exe(exe_file, "4.83.11"):
        print("SecuROM 4.83.11")
        found_pattern = True

    # Check for SIntf16.dll pattern
    if identify_exe(exe_file, "SIntf16.dll"):
        print("SIntf16.dll found inside of executable")
        found_pattern = True

    # Check for SIntf32.dll pattern
    if identify_exe(exe_file, "SIntf32.dll"):
        print("SIntf32.dll found inside of executable")
        found_pattern = True

    # Check for SIntfNT.dll pattern
    if identify_exe(exe_file, "SIntfNT.dll"):
        print("SIntfNT.dll found inside of executable")
        found_pattern = True

    # Check for CmdLineExt.DLL pattern
    if identify_exe(exe_file, "CmdLineExt.DLL"):
        print("CmdLineExt.DLL found inside of executable")
        found_pattern = True

    # Check for CmdLineExt02.dll pattern
    if identify_exe(exe_file, "CmdLineExt02.dll"):
        print("CmdLineExt02.dll found inside of executable")
        found_pattern = True

    # Check for SIntfIcn.ani pattern
    if identify_exe(exe_file, "SIntfIcn.ani"):
        print("SIntfIcn.ani found inside of executable")
        found_pattern = True

        # Check for SecuExp.exe pattern
    if identify_exe(exe_file, "SecuExp.exe"):
        print("SecuExp.exe found inside of executable")
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
        print("Maybe this executable uses a different version of SecuROM, "
              "Please contact BJNFNE on Discord")
else:
    print("Invalid EXE file. Please enter a valid executable name.")

input("Press enter to close SecuROMDetector")  # TODO: Add better handling for closing