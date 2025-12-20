import os
import shutil
import sys

def copy_datas_folder(source_dir, destination_parent_dir):
    # Check if source directory exists
    if not os.path.exists(source_dir):
        print(f"Error: The source directory '{source_dir}' does not exist. Please check the path and try again.")
        sys.exit(1)

    # Ensure the destination parent directory exists
    os.makedirs(destination_parent_dir, exist_ok=True)

    # Define destination path for datas folder inside destination_parent_dir
    destination_dir = os.path.join(destination_parent_dir, os.path.basename(source_dir))

    try:
        shutil.copytree(source_dir, destination_dir, dirs_exist_ok=True)
        print(f"Copied entire folder: {source_dir} to {destination_dir}")
    except Exception as e:
        print(f"Error copying folder: {e}")

def main():
    source_path = r"D:\datas"  # Use D by default
    destination_path = r"C:\coktel\Adibou3" # French version, if you need for German/English version change to Adiboo3

    copy_datas_folder(source_path, destination_path)

    print("Copy operation completed.")

if __name__ == "__main__":
    main()