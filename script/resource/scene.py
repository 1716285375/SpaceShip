import os
from pathlib import Path


def generate_mene_scene(scene_path, asset_path):
    """
    """
    scene_path = Path(scene_path)
    if not scene_path.exists():
        os.makedirs(scene_path)
    # TODO: generate mene scene
    menu_assets = []
    for root, dirs, files in os.walk(asset_path):
        for file in files:
            f = Path(file).stem
            menu_assets.append(f)
 
    with open(scene_path, 'w') as f:
        for i, menu_asset in enumerate(menu_assets):
            f.write(menu_asset)
            if i < len(menu_assets) - 1:
                f.write('\n')


if __name__ == '__main__':
    generate_mene_scene('../../data/scenes/menu_scene.txt', '../../assets/image/ui/menu')