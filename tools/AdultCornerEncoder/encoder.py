# Encodes a number into a specific string format.
#
# Encoding Rules:
# - Numbers from 0 to 9 are represented as a 4-character string, 
#   zero-padded to the left (e.g., '0000' for 0, '0001' for 1, ..., '0009' for 9).
#
# Example:
# - Input: 0  -> Output: '0000'
# - Input: 1  -> Output: '0001'
# - Input: 9  -> Output: '0009'

def encode_number(num):
    if not isinstance(num, int) or num < 0 or num > 9:
        raise ValueError("Encoded password must be a non-negative integer between 0 and 9.")
    
    return f"{num:04d}"

if __name__ == "__main__":
    while True:
        try:
            number_input = int(input("Enter a encoded password between 0 and 9 to encode (Exit Decoder with -1): "))
            if number_input == -1:
                print("Exiting the encoder.")
                break
            
            encoded_output = encode_number(number_input)
            print(f"Number: {number_input} -> Encoded: {encoded_output}")
        
        except ValueError as e:
            print(f"Error: {e}")