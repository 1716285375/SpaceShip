import os
from pathlib import Path
import json
from PIL import Image
import re


TEXTURE_DIR = Path('../../assets/image')
FONT_DIR = Path('../../assets/font')
SOUND_DIR = Path('../../assets/sound')
MUSIC_DIR = Path('../../assets/music')
ANIMATION_DIR = Path('../../assets/animation')
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

def generate_font_json(font_dir):
    fonts = {}
    for root, dirs, files in os.walk(font_dir):
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
                fonts[f"{f.stem}"]= {
                    "file": os.path.abspath(f'{root}/{file}'),
                    "size": size,
                    "bold": False,
                    "italic": False,
                }
    with open(JSON_DIR / 'font.json', 'w') as json_file:
        json.dump(fonts, json_file, indent=4)
        print(f"Texture JSON generated at {os.path.abspath('font.json')}")


def generate_sound_json(sound_dir):
    """"""
    sounds = {}
    for root, dirs, files in os.walk(sound_dir):
        for file in files:
            if file.endswith(('.mp3', '.wav', '.ogg', '.flac')):
                print(f"Processing {file}")
                f = Path(file)
                sounds[f"{f.stem}"]= {
                    "file": os.path.abspath(f'{root}/{file}'),
                    "volume": 1.0,  # 默认音量
                }
    with open(JSON_DIR /'sound.json', 'w') as json_file:
        json.dump(sounds, json_file, indent=4)
        print(f"Sound JSON generated at {os.path.abspath('sound.json')}")
    pass


def generate_music_json(music_dir):
    """"""
    music = {}
    for root, dirs, files in os.walk(music_dir):
        for file in files:
            if file.endswith(('.mp3', '.wav', '.ogg', '.flac')):
                print(f"Processing {file}")
                f = Path(file)
                music[f"{f.stem}"]= {
                    "file": os.path.abspath(f'{root}/{file}'),
                    "volume": 1.0,  # 默认音量
                }
    with open(JSON_DIR /'music.json', 'w') as json_file:
        json.dump(music, json_file, indent=4)
        print(f"Music JSON generated at {os.path.abspath('music.json')}")
    pass

if __name__ == '__main__':
    generate_texture_json(texture_dir=TEXTURE_DIR)
    generate_font_json(font_dir=FONT_DIR)
    generate_music_json(music_dir=MUSIC_DIR)
    generate_sound_json(sound_dir=SOUND_DIR)