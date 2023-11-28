from PIL import Image
import os
print(f"\b")
print(f"Currently IMGConverter only can convert IMG's that are based on TGA.\f")

# Prompt the user for the input image file path
img_input = input("Enter the path of the input image file: ")

# Define the valid output formats
valid_formats = ['PNG', 'JPG', 'TGA']

# Prompt the user for the desired output format
while True:
    output_format = input("Enter the desired output format (PNG, JPG, or TGA): ").upper()
    if output_format in valid_formats:
        break
    else:
        print("Invalid format. Please enter a valid format.")

# Extract the file name (without extension) from the input path
input_filename, _ = os.path.splitext(os.path.basename(img_input))

# Generate the output file path using the input file name and chosen format
output_image = f"{input_filename}.{output_format}"

# Open the image in its original format (IMG)
original_image = Image.open(img_input)

# Save the image in the specified format
original_image.save(output_image)

print(f"Image converted from {img_input} to {output_image} successfully.")

