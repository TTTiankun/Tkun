import os
import shutil
from tqdm import tqdm

# 源文件夹路径（已标注的图片所在文件夹）
labeled_images_folder = "/home/jason/Desktop/test/images"

# 标签文件夹路径（已有标签文件的文件夹）
labels_folder = "/home/jason/Desktop/test/labels"

# 目标文件夹路径（没有对应标签文件的图片将会被移动到这里）
destination_folder = "/home/jason/Desktop/test/unimages"

# 获取已标注图片和对应的标签文件
labeled_images = [f for f in os.listdir(labeled_images_folder) if os.path.isfile(os.path.join(labeled_images_folder, f))]
label_files = [f for f in os.listdir(labels_folder) if os.path.isfile(os.path.join(labels_folder, f))]

# 获取已标注图片的名称（不含文件类型后缀）
labeled_image_names = [os.path.splitext(image)[0] for image in labeled_images]

# 检查是否有对应标签文件的图片，如果没有则移动到目标文件夹
os.makedirs(destination_folder, exist_ok=True)
unlabeled_images = []
for image_name in labeled_image_names:
    if image_name + ".txt" not in label_files:
        unlabeled_images.append(image_name)

# 设置进度条
with tqdm(total=len(unlabeled_images), desc="Processing") as pbar:
    for image in unlabeled_images:
        # 查找图片文件
        image_file = None
        for ext in [".jpg", ".png"]:
            if os.path.isfile(os.path.join(labeled_images_folder, image + ext)):
                image_file = os.path.join(labeled_images_folder, image + ext)
                break
        
        # 移动图片
        if image_file:
            shutil.move(image_file, os.path.join(destination_folder, os.path.basename(image_file)))
        pbar.update(1)

print("任务完成！没有对应标签文件的图片已移动到目标文件夹。")

