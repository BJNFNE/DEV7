from PIL import Image
import os

def convert_to_tga(input_path, output_path, resolution):
    image = Image.open(input_path)
    # Resize the image to the chosen resolution
    image = image.resize(resolution, Image.ANTIALIAS)
    image.save(output_path, format="TGA")

def main():
    # Input path from user input
    input_image_path = input("Enter the path to the input image: ")

    # Extract the input filename and extension
    input_filename, input_extension = os.path.splitext(os.path.basename(input_image_path))

    # Choose screen resolution
    resolution_choice = input("Choose screen resolution (e.g., 1920x1080): ")
    width, height = map(int, resolution_choice.split('x'))
    resolution = (width, height)

    # Convert to TGA (temporary format)
    temp_output_path = f"{input_filename}_temp.tga"
    convert_to_tga(input_image_path, temp_output_path, resolution)
    print(f"Image converted to TGA with resolution {resolution}: {temp_output_path}")

    # Choose the output filename for IMG
    img_output_filename = input("Enter the desired output filename for IMG (without extension): ")
    img_output_path = f"{img_output_filename}.img"
    os.rename(temp_output_path, img_output_path)
    print(f"TGA renamed to IMG: {img_output_path}")

if __name__ == "__main__":
    main()
