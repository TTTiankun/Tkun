import cv2
import os
from tqdm import tqdm

def draw_boxes_on_images(image_folder, label_folder, output_folder, class_map=None):
    image_files = os.listdir(image_folder)
    label_files = os.listdir(label_folder)

    # 创建输出文件夹
    os.makedirs(output_folder, exist_ok=True)

    for image_file in tqdm(image_files, desc='处理图像中', unit='图像'):
        image_path = os.path.join(image_folder, image_file)
        label_file = image_file.split('.')[0] + '.txt'
        label_path = os.path.join(label_folder, label_file)

        if not os.path.exists(label_path):
            continue

        image = cv2.imread(image_path)
        image_height, image_width, _ = image.shape

        with open(label_path, 'r') as f:
            lines = f.readlines()

        for line in lines:
            class_id, x_center, y_center, width, height = map(float, line.strip().split())
            class_id = int(class_id)

            # 将归一化的坐标转换为绝对坐标
            x_min = int((x_center - width / 2) * image_width)
            y_min = int((y_center - height / 2) * image_height)
            x_max = int((x_center + width / 2) * image_width)
            y_max = int((y_center + height / 2) * image_height)

            # 绘制边界框
            color = (0, 255, 0)  # 绿色
            cv2.rectangle(image, (x_min, y_min), (x_max, y_max), color, 2)

            # 如果提供了类别映射，则添加类别标签
            if class_map:
                class_label = list(class_map.keys())[list(class_map.values()).index(class_id)]
                cv2.putText(image, class_label, (x_min, y_min - 5), cv2.FONT_HERSHEY_SIMPLEX, 0.5, color, 2)

        # 将转换后的图像保存到输出文件夹
        output_image_path = os.path.join(output_folder, image_file)
        cv2.imwrite(output_image_path, image)

# 示例用法
image_folder = '/home/jason/Desktop/datasets/stomach_datasets/train/images'
label_folder = '/home/jason/Desktop/datasets/stomach_datasets/train/labels'
output_folder = '/home/jason/Desktop/datasets/stomach_datasets/train/out'
class_map = {

}

draw_boxes_on_images(image_folder, label_folder, output_folder, class_map)

