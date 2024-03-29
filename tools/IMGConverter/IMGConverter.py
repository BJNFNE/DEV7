from PIL import Image
import os
import sys

ALLOWED_FORMATS = {".jpg", ".jpeg", ".png", ".bmp", ".tga", ".gif"}

def is_valid_image_file(file_path):
    _, file_extension = os.path.splitext(file_path)
    return file_extension.lower() in ALLOWED_FORMATS

def convert_to_tga(input_path, output_path, resolution):
    image = Image.open(input_path)

    # Check if input image resolution is larger than output resolution
    if image.size[0] > resolution[0] or image.size[1] > resolution[1]:
        # Print warning to infrom the user that the input picture is using an larger resolsution instead of the output picture.
        print("Warning: Input image resolution is larger than the output resolution. Resizing to fit within the resolution.\n")
        # Calculate the aspect ratio of the original image
        aspect_ratio = image.size[0] / image.size[1]

        # Calculate the new dimensions to fit within the specified resolution
        new_width = min(resolution[0], int(resolution[1] * aspect_ratio))
        new_height = min(resolution[1], int(resolution[0] / aspect_ratio))

        # Resize the image while maintaining the aspect ratio
        image = image.resize((new_width, new_height), Image.ANTIALIAS)

    else:
        print("Resizing image to fit within the specified resolution.\n")
        # Resize the image to the chosen resolution
        image = image.resize(resolution, Image.ANTIALIAS)

    # Calculate bits per pixel based on the image mode
    bpp = image.bits if hasattr(image, 'bits') else len(image.getbands()) * 8

    image.save(output_path, format="TGA")
    return bpp

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
            print(f"Error: Input file not found\b")
            sys.exit(1)

        # Check if the input file has an allowed extension
        if not is_valid_image_file(input_image_path):
            print(f"Error: Unsupported file format.\b")
            sys.exit(1)

        # Extract the input filename and extension
        input_filename, input_extension = os.path.splitext(os.path.basename(input_image_path))

        # Get the original resolution and BPP
        image = Image.open(input_image_path)
        resolution_original = image.size
        bpp_original = image.bits if hasattr(image, 'bits') else len(image.getbands()) * 8
        print(f"Original Resolution: {resolution_original[0]}x{resolution_original[1]}")
        print(f"Bits per pixel (BPP): {bpp_original}\b")

        # Choose screen resolution
        resolution_choice = input("Choose screen resolution (max 800x600): ")

        if resolution_choice:
            width, height = map(int, resolution_choice.split('x'))
            resolution = (width, height)

            # Check if the resolution is valid
            is_resolution_valid(resolution)

            # Convert to TGA (temporary format)
            temp_output_path = f"{input_filename}_temp.tga"
            bpp = convert_to_tga(input_image_path, temp_output_path, resolution)

            # Choose the output filename for IMG
            img_output_filename = input("Enter the desired output filename for IMG (without extension): ")
            img_output_path = f"{img_output_filename}.img"

            # Check if the output file already exists
            if os.path.exists(img_output_path):
                overwrite = input("Warning: Output file already exists. Do you want to overwrite? (y/n): ")
                if overwrite.lower() != 'y':
                    print("Program terminated - Output file won't get overwritten.\b")
                    sys.exit(0)

            os.rename(temp_output_path, img_output_path)
            print(f"\b")
            print(f"Image converted successfully - {img_output_path}")
            print(f"Resolution: {resolution[0]}x{resolution[1]}")
            print(f"Bits per pixel (BPP): {bpp}\b")
        else:
            print("Please enter a valid resolution.\b")
    except KeyboardInterrupt:
        print("\nProgram terminated by the user.\b")
        sys.exit(1)
    except FileNotFoundError:
        print(f"Error: File not found\b")
        sys.exit(1)
    except AssertionError as e:
        print(f"Error: {e}\b")
        sys.exit(1)

if __name__ == "__main__":
    main()
