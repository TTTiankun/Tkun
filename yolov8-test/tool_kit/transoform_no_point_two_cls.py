from PIL import Image
import json
import os
from tqdm import tqdm

def get_image_size(image_path):
    with Image.open(image_path) as img:
        return img.size  # 返回 (width, height)

def convert_labelme_to_yolo(json_file_path, output_dir, class_map=None):
    with open(json_file_path, 'r') as f:
        data = json.load(f)

    image_path = os.path.abspath(os.path.join(os.path.dirname(json_file_path), data['imagePath']))
    image_width, image_height = get_image_size(image_path)

    for shape in data['shapes']:
        label = shape['label']
        points = shape['points']

        # 计算边界框坐标
        x_min = min(points[0][0], points[1][0])
        y_min = min(points[0][1], points[1][1])
        x_max = max(points[0][0], points[1][0])
        y_max = max(points[0][1], points[1][1])

        # 归一化坐标
        x_center = (x_min + x_max) / (2 * image_width)
        y_center = (y_min + y_max) / (2 * image_height)
        width = (x_max - x_min) / image_width
        height = (y_max - y_min) / image_height

        # 写入YOLO格式
        if class_map and label in class_map:
            class_id = class_map[label]
        else:
            class_id = 0  # 如果没有提供映射，则默认为类别0

        yolo_format = f"{class_id} {x_center} {y_center} {width} {height}\n"

        # 保存到文件
        output_file_path = os.path.join(output_dir, os.path.splitext(os.path.basename(json_file_path))[0] + '.txt')
        with open(output_file_path, 'a') as out_file:
            out_file.write(yolo_format)

def convert_labelme_folder_to_yolo(input_folder, output_dir, class_map=None):
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    json_files = [f for f in os.listdir(input_folder) if f.endswith('.json')]

    progress_bar = tqdm(total=len(json_files))
    for json_file in json_files:
        convert_labelme_to_yolo(os.path.join(input_folder, json_file), output_dir, class_map)
        progress_bar.update(1)
    progress_bar.close()

# 使用示例
input_folder = '/home/jason/Desktop/伊里斯计划/model_datasets/model2_labels_json'
output_dir = '/home/jason/Desktop/伊里斯计划/model_datasets/model2_labels'
class_map = {'tumor': 0, 'knife': 1}  # 将标签名称映射到类别ID

convert_labelme_folder_to_yolo(input_folder, output_dir, class_map)

print("转换完成！YOLO格式的标签文件已保存到指定目录。")



