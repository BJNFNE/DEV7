from PIL import Image, ImageDraw, ImageFont
import os

# Define image size
width = 150
height = 150
text_color = (0, 0, 128)  # Dark blue
background_color = (255, 255, 255, 0)  # Transparent background

# Prompt the user to input the full path to the TTF file
ttf_file_path = input("Enter the full path to your TTF font file: ")

# Check if the font file exists
if not os.path.isfile(ttf_file_path):
    raise FileNotFoundError(f"Font file '{ttf_file_path}' not found.")

# Create a new RGBA image with a transparent background
image = Image.new('RGBA', (width, height), background_color)

# Initialize the drawing context
draw = ImageDraw.Draw(image)

# Use the selected font file
font = ImageFont.truetype(ttf_file_path, size=24)

# Calculate text size and position
text = "DEV7"
text_width, text_height = draw.textsize(text, font=font)
text_x = (width - text_width) // 2
text_y = (height - text_height) // 2

# Draw the text on the image
draw.text((text_x, text_y), text, fill=text_color, font=font)

# Save the image as a PNG file with transparent background
image.save("DEV7_github_logo.png", format="PNG")

print("Logo created successfully!")

