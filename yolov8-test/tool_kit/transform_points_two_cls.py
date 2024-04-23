import json
import os
from tqdm import tqdm
from PIL import Image

def get_image_size(image_path):
    with Image.open(image_path) as img:
        return img.size  # 返回 (width, height)

def normalize_point(point, image_width, image_height):
    x = point[0] / image_width
    y = point[1] / image_height
    return x, y

def convert_labelme_to_yolo_keypoints(json_file_path, output_dir, class_map=None):
    with open(json_file_path, 'r') as f:
        data = json.load(f)

    image_path = os.path.abspath(os.path.join(os.path.dirname(json_file_path), data['imagePath']))
    image_width, image_height = get_image_size(image_path)

    yolo_format = []

    for shape in data['shapes']:
        label = shape['label']
        points = shape['points']

        # 如果提供了class_map，则根据映射替换标签名称
        if class_map and label in class_map:
            label_id = class_map[label]
        else:
            label_id = label

        # 归一化关键点坐标
        normalized_points = [normalize_point(point, image_width, image_height) for point in points]

        yolo_format.append((label_id, normalized_points))

    # 处理car_point和armor_point，确保它们在car和armor之后
    for shape in data['shapes']:
        label = shape['label']
        points = shape['points']

        if label == 'car_point' or label == 'armor_point':
            normalized_points = [normalize_point(point, image_width, image_height) for point in points]

            # 找到对应的父标签
            parent_label = label.split('_')[0]
            for idx, item in enumerate(yolo_format):
                if item[0] == parent_label:
                    yolo_format.insert(idx + 1, (label, normalized_points))
                    break

    # 写入YOLO格式
    yolo_file_path = os.path.join(output_dir, os.path.splitext(os.path.basename(json_file_path))[0] + '.txt')
    with open(yolo_file_path, 'w') as f:
        for label, normalized_points in yolo_format:
            line = f"{label} {' '.join([f'{p[0]} {p[1]}' for p in normalized_points])}\n"
            f.write(line)

def convert_labelme_folder_to_yolo_keypoints(input_folder, output_dir, class_map=None):
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    json_files = [f for f in os.listdir(input_folder) if f.endswith('.json')]

    progress_bar = tqdm(total=len(json_files))
    for json_file in json_files:
        convert_labelme_to_yolo_keypoints(os.path.join(input_folder, json_file), output_dir, class_map)
        progress_bar.update(1)
    progress_bar.close()

# 使用示例
input_folder = '/home/jason/Desktop/datasets/test_datatsets/labels'
output_dir = '/home/jason/Desktop/datasets/test_datatsets/labels_plus'
class_map = {'armor': 0, 'car': 1}  # 将标签名称映射到类别ID
convert_labelme_folder_to_yolo_keypoints(input_folder, output_dir, class_map)

print("转换完成！YOLO格式的关键点文件已保存到指定目录。")

