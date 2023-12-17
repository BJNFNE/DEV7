from PIL import Image
import os
import sys

ALLOWED_FORMATS = {".jpg", ".jpeg", ".png", ".bmp"}

def is_valid_image_file(file_path):
    _, file_extension = os.path.splitext(file_path)
    return file_extension.lower() in ALLOWED_FORMATS

def convert_to_tga(input_path, output_path, resolution):
    image = Image.open(input_path)
    # Resize the image to the chosen resolution
    image = image.resize(resolution, Image.ANTIALIAS)
    image.save(output_path, format="TGA")

def is_resolution_valid(resolution):
    max_width = 800
    max_height = 600

    width, height = resolution
    assert width <= max_width and height <= max_height, f"The maximum resolution is {max_width}x{max_height}"

def main():
    try:
        # Enter Input file from user input
        input_image_path = input("Enter the path to the input image: ")

        # Check if the input file exists
        if not os.path.exists(input_image_path):
            print(f"Error: Input file not found")
            sys.exit(1)

        # Check if the input file has an allowed extension
        if not is_valid_image_file(input_image_path):
            print(f"Error: Unsupported file format.")
            sys.exit(1)

        # Extract the input filename and extension
        input_filename, input_extension = os.path.splitext(os.path.basename(input_image_path))

        # Choose screen resolution
        resolution_choice = input("Choose screen resolution: ")

        if resolution_choice:
            width, height = map(int, resolution_choice.split('x'))
            resolution = (width, height)

            # Check if the resolution is valid
            is_resolution_valid(resolution)

            # Convert to TGA (temporary format)
            temp_output_path = f"{input_filename}_temp.tga"
            convert_to_tga(input_image_path, temp_output_path, resolution)
            print(f"Image converted to TGA with resolution {resolution[0]}x{resolution[1]}: {temp_output_path}")

            # Choose the output filename for IMG
            img_output_filename = input("Enter the desired output filename for IMG (without extension): ")
            img_output_path = f"{img_output_filename}.img"

            # Check if the output file already exists
            if os.path.exists(img_output_path):
                overwrite = input("Warning: Output file already exists. Do you want to overwrite? (y/n): ")
                if overwrite.lower() != 'y':
                    print("Program terminated - Output file won't get overwritten.")
                    sys.exit(0)

            os.rename(temp_output_path, img_output_path)
            print(f"Converted successfully to {img_output_path}")
        else:
            print("Please enter a valid resolution.")
    except KeyboardInterrupt:
        print("\nProgram terminated by the user.")
        sys.exit(1)
    except FileNotFoundError:
        print(f"Error: File not found")
        sys.exit(1)
    except AssertionError as e:
        print(f"Error: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
