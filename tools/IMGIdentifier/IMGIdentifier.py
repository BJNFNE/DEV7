def identify_img(img_path, img_check):
    try:
        with open(img_path, 'rb') as file:
            img_contents = file.read()
            if img_check.encode() in img_contents:
                return True
    except FileNotFoundError:
        pass
    return False

print("\b")
img_file = input("Enter the name of the IMG file (with .IMG extension): ")

if img_file.lower().endswith((".img", ".IMG")):
    if identify_img(img_file, "TRUEVISION-XFILE"):
        print("It's a TGA file")
    elif identify_img(img_file, "IMG10"):
        print("\b")
        print("IMG using version 1.0")
        print("\b")
    elif identify_img(img_file, "IMG1.0.1"):
        print("\b")
        print("IMG using version 1.0.1")
        print("\b")
    else:
        print("\b")
        print("IMG format not recognized")
        print("\b")
        print("Maybe this IMG uses an different format / newer or older version, "
              "Please contact BJNFNE on Discord")
        print("\b")
else:
    print("Invalid IMG file extension. Please add the .img extension aswell")
input("Press enter to close IMGIdentifier")
