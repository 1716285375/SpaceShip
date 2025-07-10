import os
from pathlib import Path
import json
from PIL import Image
import re


TEXTURE_DIR = Path('../../assets/image')
JSON_DIR = Path('../../data')
def generate_texture_json(texture_dir):
    textures = {}
    for root, dirs, files in os.walk(texture_dir):
        for file in files:
            if file.endswith('.png'):
                print(f"Processing {file}")
                image = Image.open(os.path.join(root, file))
                width, height = image.size
                f = Path(file)
                textures[f"{f.stem}"]= {
                    "file": os.path.abspath(f'{root}/{file}'),
                    "w": width,
                    "h": height
                }
    with open(JSON_DIR / 'texture.json', 'w') as json_file:
        json.dump(textures, json_file, indent=4)
        print(f"Texture JSON generated at {os.path.abspath('texture.json')}")

def generate_font_json(texture_dir):
    textures = {}
    for root, dirs, files in os.walk(texture_dir):
        for file in files:
            if file.endswith('.ttf'):
                print(f"Processing {file}")
                f = Path(file)
                m = re.findall(r'-', file)
                print(m)
                if len(m) > 0:
                    s = int(f.stem.split('-')[-1].replace('px', ''))
                    size = s
                else:
                    size = 16
                textures[f"{f.stem}"]= {
                    "file": os.path.abspath(f'{root}/{file}'),
                    "size": size,
                    "bold": False,
                    "italic": False,
                }
    with open(JSON_DIR / 'font.json', 'w') as json_file:
        json.dump(textures, json_file, indent=4)
        print(f"Texture JSON generated at {os.path.abspath('font.json')}")


if __name__ == '__main__':
    texture_dir = '../../assets/image'
    generate_texture_json(texture_dir)
    font_dir = '../../assets/font'
    generate_font_json(font_dir)