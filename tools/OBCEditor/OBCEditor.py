import os

def display_content(content):
    print("Offset     | Hexadecimal Representation | Printable Text")
    print("----------------------------------------------------------")

    for i in range(0, len(content), 16):
        line = content[i:i+16]
        hex_line = ' '.join(format(b, '02X') for b in line)
        printable_text = ''.join(chr(byte) if 32 <= byte <= 126 else '.' for byte in line)
        print(f"{i:010X} | {hex_line.ljust(48)} | {printable_text}")

def save_changes(filename, content):
    with open(filename, 'wb') as file:
        file.write(content)
    print("Changes saved successfully.")

def main():
    filename = input("Enter OBC file name: ")

    if not os.path.isfile(filename):
        print(f"Error: File '{filename}' not found.")
        return

    with open(filename, 'rb') as file:
        content = bytearray(file.read())

    print("OBC File Editor")
    print("-------------------------")
    print(f"Editing file: {filename}")
    print(f"File size: {len(content)} bytes\n")

    while True:
        print("\nEnter 'modify' to display/edit the OBC Script.")
        print("Enter 'save' to save changes and exit.")
        print("Enter 'quit' to exit without saving.")

        choice = input("Your choice: ").lower()

        if choice == 'modify':
            display_content(content)
            try:
                offset = int(input("Enter offset to modify (in hexadecimal), or press Enter to continue viewing: "), 16)
                if 0 <= offset < len(content):
                    new_value = int(input("Enter new hexadecimal value: "), 16)
                    content[offset] = new_value
                    print("Offset updated successfully.")
            except ValueError:
                print("Error: Invalid input.")
        elif choice == 'save':
            save_changes(filename, content)
            break
        elif choice == 'quit':
            print("Exiting without saving.")
            break
        else:
            print("Error: Invalid choice.")

if __name__ == "__main__":
    main()
