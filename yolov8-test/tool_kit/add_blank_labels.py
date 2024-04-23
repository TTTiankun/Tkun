import os
from tqdm import tqdm

def generate_blank_labels(image_folder, labels_folder):
    # 创建标签文件夹
    os.makedirs(labels_folder, exist_ok=True)
    
    # 获取文件夹中所有图片文件
    image_files = [f for f in os.listdir(image_folder) if f.endswith('.jpg') or f.endswith('.png')]

    # 设置进度条
    with tqdm(total=len(image_files), desc="Generating Labels") as pbar:
        # 为每张图片生成空白标签文件
        for image_file in image_files:
            image_name = os.path.splitext(image_file)[0]
            label_file = os.path.join(labels_folder, image_name + '.txt')
            
            # 创建空白标签文件
            with open(label_file, 'w') as f:
                pass
            
            pbar.update(1)

# 使用示例
image_folder = '/home/jason/Desktop/test/unimages'  # 指定图片文件夹的路径
labels_folder = '/home/jason/Desktop/test/unlabels'  # 指定生成的标签文件夹的路径

generate_blank_labels(image_folder, labels_folder)

print("空白标签文件已生成！")