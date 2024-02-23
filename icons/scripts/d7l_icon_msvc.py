from PIL import Image, ImageDraw, ImageFont

width, height = 64, 64

icon = Image.new("RGB", (width, height), "black")

draw = ImageDraw.Draw(icon)
font = ImageFont.load_default()
text = "D7L"
text_width, text_height = draw.textsize(text, font=font)
x = (width - text_width) / 2
y = (height - text_height) / 2
draw.text((x, y), text, fill="yellow", font=font)

icon.save("D7L_msvc.ico", format="ICO")
