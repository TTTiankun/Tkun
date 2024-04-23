import os
import cv2
from tqdm import tqdm

# 定义函数用于读取图片尺寸信息
def read_image_sizes(image_folder):
    image_sizes = {}
    image_files = sorted(os.listdir(image_folder))
    for image_file in image_files:
        if image_file.endswith('.jpg') or image_file.endswith('.png'):
            image_path = os.path.join(image_folder, image_file)
            image = cv2.imread(image_path)
            height, width, _ = image.shape
            image_sizes[image_file] = (width, height)
    return image_sizes

# 定义函数用于读取图片标注信息
def read_annotations(annotations_file):
    annotations = []
    with open(annotations_file, 'r') as f:
        for line in f:
            annotation = list(map(float, line.strip().split(',')))
            # 将第一个通道设为0
            annotation.insert(0, 0)
            annotations.append(annotation)
    return annotations

# 创建文件夹保存标注信息
output_folder = '/media/jason/实验室2号/跟踪/train_img/train/labels'
os.makedirs(output_folder, exist_ok=True)

# 设置文件夹和文件路径
image_folder = '/media/jason/实验室2号/跟踪/train_img/chenguoji/img'  # 假设图片都存储在一个名为 'images' 的文件夹中
annotations_file = '/media/jason/实验室2号/跟踪/train_img/chenguoji/groundtruth_rect_1.txt'

# 读取图片尺寸信息和标注信息
image_sizes = read_image_sizes(image_folder)
annotations = read_annotations(annotations_file)

# 确保图片数量和标注数量一致
assert len(image_sizes) == len(annotations), "图片数量和标注数量不一致！"

# 使用 tqdm 创建进度条
with tqdm(total=len(image_sizes), desc='处理图片和标注') as pbar:
    # 循环保存标注信息到文件夹中
    for image_file, annotation in zip(image_sizes.keys(), annotations):
        width, height = image_sizes[image_file]
        # 归一化坐标
        annotation[1] /= width
        annotation[2] /= height
        annotation[3] /= width
        annotation[4] /= height
        
        image_name, _ = os.path.splitext(image_file)
        image_annotation_path = os.path.join(output_folder, f'{image_name}.txt')  # 使用照片文件夹的照片名字
        with open(image_annotation_path, 'w') as f:
            f.write(' '.join(map(str, annotation)))
        pbar.update(1)  # 更新进度条

print("标注信息已保存到文件夹:", output_folder)
