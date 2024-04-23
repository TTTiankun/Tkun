import os
import random
import shutil
from tqdm import tqdm

def split_dataset(image_train_dir, label_train_dir, image_val_dir, label_val_dir, split_ratio):
    # 创建验证集目录
    if not os.path.exists(image_val_dir):
        os.makedirs(image_val_dir)
    if not os.path.exists(label_val_dir):
        os.makedirs(label_val_dir)

    # 获取训练集中的所有图片文件名
    image_files = [f for f in os.listdir(image_train_dir) if f.endswith('.jpg') or f.endswith('.png')]

    # 计算需要抽取的图片数量
    num_val_images = int(len(image_files) * split_ratio)

    # 随机抽取图片文件名
    val_image_files = random.sample(image_files, num_val_images)

    # 复制抽取的图片到验证集目录，并复制对应的标签文件
    for image_file in tqdm(val_image_files, desc="Copying images and labels to validation set"):
        # 复制图片文件
        shutil.copy(os.path.join(image_train_dir, image_file), os.path.join(image_val_dir, image_file))
        # 复制对应的标签文件
        label_file = image_file.replace('.jpg', '.txt').replace('.png', '.txt')
        if os.path.exists(os.path.join(label_train_dir, label_file)):
            shutil.copy(os.path.join(label_train_dir, label_file), os.path.join(label_val_dir, label_file))

    print(f"{num_val_images} images and labels copied to the validation set.")

# 设置训练集图片目录、标签目录、验证集图片目录、验证集标签目录和抽取比例
image_train_dir = '/home/jason/Desktop/stomach_datasets/train/images'
label_train_dir = '/home/jason/Desktop/stomach_datasets/train/labels'
image_val_dir = '/home/jason/Desktop/stomach_datasets/val/images/'
label_val_dir = '/home/jason/Desktop/stomach_datasets/val/labels/'
split_ratio = 0.4  # 验证集占总训练集的比例

# 执行划分数据集操作
split_dataset(image_train_dir, label_train_dir, image_val_dir, label_val_dir, split_ratio)

