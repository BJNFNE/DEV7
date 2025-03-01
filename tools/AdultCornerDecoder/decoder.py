# This script decodes an encoded password based on specific encoding rules.
# The password is checked in the Game over B3_ADULTCORNER::CheckChildPassword function.
#
# Encoding Rules:
# Numeric Encoding:
# - If the number is from 0 to 9, it is represented as a 4-character string (e.g., '0001' for 1).
# - If the number is from 10 to 99, it is represented as a 5-character string (e.g., '00010' for 10).
# - If the number is from 100 to 999, it is represented as a 6-character string (e.g., '000100' for 100).
# - If the number is from 1000 and above, it is represented as a 7-character string (e.g., '0001000' for 1000).
#
# Alphabetic Encoding:
# - Each letter is represented by a specific numeric code.
# - For example, 'a' is represented as '0003', 'b' as '0001', and other letters remain as themselves.
# - If the input is a single character, it is returned directly without further processing.

import sys

def decode_password(encoded_str):
    """Decodes an encoded password back into plaintext."""
    
    # If the input is a single character, return it directly
    if len(encoded_str) == 1:
        return encoded_str
    else:
        print("Password is longer as an single character!")
        sys.exit(0)
    
    decoded_chars = []
    
    # Process the encoded string
    i = 0
    while i < len(encoded_str):
        # Check for a 4-character segment for numbers (0-9)
        if i + 3 < len(encoded_str) and encoded_str[i:i+4].isdigit():
            num_value = int(encoded_str[i:i+4])
            if num_value == 3:
                decoded_chars.append('a')  # '0003' corresponds to 'a'
            elif num_value == 1:
                decoded_chars.append('b')  # '0001' corresponds to 'b'
            else:
                decoded_chars.append(str(num_value))  # Append the number as is
            i += 4  # Move to the next segment
        # Check for a 5-character segment for numbers (10-99)
        elif i + 4 < len(encoded_str) and encoded_str[i:i+5].isdigit():
            num_value = int(encoded_str[i:i+5])
            decoded_chars.append(str(num_value))  # Append the number as is
            i += 5  # Move to the next segment
        # Check for a 6-character segment for numbers (100-999)
        elif i + 5 < len(encoded_str) and encoded_str[i:i+6].isdigit():
            num_value = int(encoded_str[i:i+6])
            decoded_chars.append(str(num_value))  # Append the number as is
            i += 6  # Move to the next segment
        # Check for a 7-character segment for numbers (1000 and above)
        elif i + 6 < len(encoded_str) and encoded_str[i:i+7].isdigit():
            num_value = int(encoded_str[i:i+7])
            decoded_chars.append(str(num_value))  # Append the number as is
            i += 7  # Move to the next segment
        # Check for single letters (a-z)
        elif encoded_str[i].isalpha():
            decoded_chars.append(encoded_str[i])  # Directly append the letter
            i += 1  # Move to the next character
        else:
            decoded_chars.append('?')  # Unknown character
    
    return "".join(decoded_chars)

# Main function to run the decoding process
if __name__ == "__main__":
    # Prompt the user for the encoded password
    encoded_input = input("Enter the encoded password: ")
    
    # Decode the input and print the result
    decoded_output = decode_password(encoded_input)
    print(f"Encoded: {encoded_input} -> Decoded: {decoded_output}")