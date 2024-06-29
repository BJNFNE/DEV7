import hashlib
import os

def calculate_md5(file_path):
    """ Calculate the MD5 hash of a file """
    md5 = hashlib.md5()
    with open(file_path, 'rb') as f:
        for chunk in iter(lambda: f.read(4096), b''):
            md5.update(chunk)
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
    executables = ['LoaderMDO.exe', 'Adibou3.exe', 'Adibou3.EXE', 'adibou3.exe', 'ADI5.EXE', 'ADI5.exe']

    # Convert all executables to lowercase for case insensitivity
    executables_lower = [exe.lower() for exe in executables]

    # Determine which executable files are present in the current folder
    available_executables = [exe for exe in executables if os.path.exists(exe)]

    # Check if LoaderMDO.exe is present and find one of Adibou3.exe or ADI5.exe
    if 'LoaderMDO.exe' in available_executables:
        try:
            # Calculate the MD5 hash of LoaderMDO.exe
            loadermdo_hash = calculate_md5('LoaderMDO.exe')
            print(f"MD5 hash of LoaderMDO.exe: {loadermdo_hash}")

            # Find the available executable (Adibou3.exe or ADI5.exe) and calculate its MD5 hash
            found_executable = False
            for exe in ['LoaderMDO.exe', 'Adibou3.exe', 'Adibou3.EXE', 'adibou3.exe', 'ADI5.EXE', 'ADI5.exe']:
                if exe in available_executables:
                    exe_hash = calculate_md5(exe)
                    print(f"MD5 hash of {exe}: {exe_hash}")
                    found_executable = True

                    # Compare the hashes
                    if exe_hash == loadermdo_hash:
                        print(f"Hashes match between LoaderMDO.exe and {exe}!")
                    else:
                        print(f"Hashes do not match between LoaderMDO.exe and {exe}")
                    break  # Exit loop after finding and processing the first executable

            if not found_executable:
                print("Error: Neither Adibou3.exe nor ADI5.exe found in the folder.")

        except FileNotFoundError:
            print("File not found error occurred.")

    else:
        print("Error: LoaderMDO.exe not found in the folder.")

if __name__ == "__main__":
    main()
