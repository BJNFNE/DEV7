import os
import datetime
import argparse

def display_content(content):
    print("Offset     | Hexadecimal Representation | Printable Text")
    print("----------------------------------------------------------")

    for i in range(0, len(content), 16):
        line = content[i:i+16]
        hex_line = ' '.join(format(b, '02X') for b in line)
        printable_text = ''.join(chr(byte) if 32 <= byte <= 126 else '.' for byte in line)
        print(f"{i:010X} | {hex_line.ljust(48)} | {printable_text}")

def display_strings(content):
    print("Strings in the OBC Script:")
    print("--------------------------")
    strings = content.split(b'\x00')
    printed = False
    for string in strings:
        try:
            decoded_string = string.decode('utf-8')
            printable_string = ''.join(c for c in decoded_string if ' ' <= c <= '~')
            if printable_string:
                if printed:
                    print()
                print(printable_string)
                printed = True
        except UnicodeDecodeError:
            pass


def save_changes(filename, content):
    with open(filename, 'wb') as file:
        file.write(content)
    print("Changes saved successfully.")

def search_and_replace(content, old_text, new_text):
    # Convert old and new text to bytes
    old_bytes = old_text.encode('utf-8')
    new_bytes = new_text.encode('utf-8')

    # Check if old text exists in content
    if old_bytes not in content:
        print("Error: The text to be replaced does not exist in the OBC Script.")
        return content

    # Perform search and replace on binary data
    modified_content = content.replace(old_bytes, new_bytes)
    
    return modified_content

def count_occurrences(content, word):
    occurrences = []
    offset = 0
    while True:
        offset = content.find(word.encode('utf-8'), offset)
        if offset == -1:
            break
        occurrences.append(offset)
        offset += len(word)
    return occurrences

def main():
    parser = argparse.ArgumentParser(description='Process OBC script.')
    parser.add_argument('filename', nargs='?', help='OBC script name')
    args = parser.parse_args()

    if args.filename:
        filename = args.filename
    else:
        filename = input("Enter OBC Script name: ")

    if not filename.endswith('.obc'):
        filename += '.obc'

    if not os.path.isfile(filename):
        print(f"Error: Script '{filename}' not found.")
        return

    with open(filename, 'rb') as file:
        content = file.read()

    print("OBCEditor ver. 1.2beta")
    print("-------------------------")
    print(f"Editing Script: {filename}")
    print(f"Script size: {len(content)} bytes")

    while True:
        print("\nEnter 'modify' to display/edit the OBC Script.")
        print("Enter 'replace' to replace printable text.")
        print("Enter 'count' to count occurrences of a word.")
        print("Enter 'strings' to display strings in the OBC Script.")
        print("Enter 'save' to save changes and exit.")
        print("Enter 'help' to display help how to modify OBC Script.")
        print("Enter 'clear' to clear the Console output")
        print("Enter 'exit' to exit without saving.")
        
        choice = input("Your choice: ").lower()

        if choice == 'help':
            print("\nHow to modify OBC Script:")
            print("- Make sure to always make an Backup of the Script you want to modify!")
            print("- If you replace values don't be longer with the new value as the old was.")
            print("- Make sure you not enlarge the Filesize of the OBC Script.")
            print("- Make sure you use version 1.3.0.0 (1.30, 1.30a 1.30b) of DEV7/Loader7 otherwise DEV7 won't able to use the Script and skip it.")

            break
        elif choice == 'modify':
            display_content(content)
            try:
                offset = int(input("Enter offset to modify (in hexadecimal), or press Enter to continue viewing: "), 16)
                if 0 <= offset < len(content):
                    new_value = int(input("Enter new hexadecimal value: "), 16)
                    print("Offset updated successfully.")
            except ValueError:
                print("Error: Invalid input.")
        elif choice == 'replace':
            old_text = input("Enter the text to search for: ")
            new_text = input("Enter the replacement text: ")
            content = search_and_replace(content, old_text, new_text)
            print("Text replaced successfully.")
        elif choice == 'count':
            word = input("Enter the word to count: ")
            occurrences = count_occurrences(content, word)
            print(f"'{word}' is found {len(occurrences)} times in the script.")
            if occurrences:
                print("Offsets:")
                for i, offset in enumerate(occurrences):
                    print(f"{i+1}. 0x{offset:08X}")
        elif choice == 'strings':
            display_strings(content)
        elif choice == 'clear':
            print("\033[2J\033[H")
        elif choice == 'save':
            # Get the current year
            current_year = str(datetime.datetime.now().year)
            
            # Ask user confirmation only if the string is found
            if b'OBC Copyright MDO 1999' in content:
                confirmation = input(f"Do you want to update the year from '1999' to '{current_year}'? (yes/no): ").lower()

                if confirmation == 'yes':
                    # Replace "1999" with the current year in the content
                    content = search_and_replace(content, "1999", current_year)

                    # Save changes
                    save_changes(filename, content)
                    break
                elif confirmation == 'no':
                    print("Year update cancelled.")
                else:
                    print("Invalid choice. Please enter 'yes' or 'no'.")
            else:
                print("The string 'OBC Copyright MDO 1999' was not found.")
                break

        elif choice == 'exit':
            print("Exiting without saving.")
            break
        else:
            print("Error: Invalid choice.")

if __name__ == "__main__":
    main()
