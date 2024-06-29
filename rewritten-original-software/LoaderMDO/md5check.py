import hashlib
import os

def calculate_md5(file_path):
    """ Calculate the MD5 hash of a file """
    md5 = hashlib.md5()
    try:
        with open(file_path, 'rb') as f:
            for chunk in iter(lambda: f.read(4096), b''):
                md5.update(chunk)
    except FileNotFoundError:
        print(f"Error: File '{file_path}' not found.")
    return md5.hexdigest()

def read_expected_md5_from_file(file_name):
    """ Read and parse MD5 hashes from md5.txt """
    expected_hashes = {}
    try:
        with open(file_name, 'r') as f:
            for line in f:
                parts = line.strip().split()
                if len(parts) == 2:
                    file_name = parts[0].strip().lower()  # Convert to lowercase for case insensitivity
                    md5_hash = parts[1].strip()
                    if file_name.endswith('.exe'):
                        expected_hashes[file_name] = md5_hash
                elif len(parts) > 0:
                    print(f"Warning: Incorrect format in {file_name}: {line.strip()}")
                else:
                    print(f"Warning: Empty line found in {file_name}")
    except FileNotFoundError:
        print(f"Error: File '{file_name}' not found.")
    return expected_hashes

def main():
    md5_file = 'md5.txt'  # Name of the file containing the expected MD5 hashes

    # Read expected MD5 hashes from md5.txt
    expected_hashes = read_expected_md5_from_file(md5_file)

    if not expected_hashes:
        return

    # List of executable files to check
    executables = ['LoaderMDO.exe', 'Adibou3.exe', 'adibou3.exe', 'ADI5.EXE', 'ADI5.exe']

    # Convert all executables to lowercase for case insensitivity
    executables_lower = [exe.lower() for exe in executables]

    # Determine which executable files are present in the current folder
    available_executables = [exe for exe in executables if os.path.exists(exe)]

    # Check if LoaderMDO.exe is present and find one of Adibou3.exe or ADI5.exe
    if 'LoaderMDO.exe' in available_executables:
        try:
            # Find the available executable (Adibou3.exe or ADI5.exe) and calculate its MD5 hash
            found_executable = None
            for exe in available_executables:
                if exe.lower() in expected_hashes:
                    found_executable = exe
                    break

            if found_executable:
                # Calculate the MD5 hash of LoaderMDO.exe
                loadermdo_hash = calculate_md5('LoaderMDO.exe')
                print(f"MD5 hash of LoaderMDO.exe: {loadermdo_hash}")

                # Calculate the MD5 hash of the found executable
                found_exe_hash = calculate_md5(found_executable)
                print(f"MD5 hash of {found_executable}: {found_exe_hash}")

                # Compare the hashes
                #if found_exe_hash == expected_hashes[found_executable.lower()]:
                 #   print(f"Hashes match between LoaderMDO.exe and {found_executable}!")
                #else:
                 #   print(f"Hashes do not match between LoaderMDO.exe and {found_executable}")

            else:
                print("Error: Neither Adibou3.exe nor ADI5.exe found in the folder or not listed in md5.txt.")

        except FileNotFoundError as e:
            print(f"File not found error occurred: {e}")

    else:
        print("Error: LoaderMDO.exe not found in the folder.")

if __name__ == "__main__":
    main()
