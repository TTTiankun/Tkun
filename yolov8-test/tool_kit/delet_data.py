import os
import shutil
from tqdm import tqdm

def filter_bbox_by_class(input_folder, output_folder, allowed_ids):

    # 确保输出文件夹存在
    os.makedirs(output_folder, exist_ok=True)

    # 获取输入文件夹中的所有文件
    files = os.listdir(input_folder)

    # 遍历每个文件
    for file_name in tqdm(files, desc='处理文件中', unit='文件'):
        input_file_path = os.path.join(input_folder, file_name)
        output_file_path = os.path.join(output_folder, file_name)

        # 读取文件内容并处理
        with open(input_file_path, 'r') as input_file:
            lines = input_file.readlines()

        # 筛选出指定ID的目标检测边界框数据
        filtered_lines = [line for line in lines if int(line.split()[0]) in allowed_ids]

        # 将处理好的数据写入到输出文件中
        with open(output_file_path, 'w') as output_file:
            for line in filtered_lines:
                output_file.write(line)

# 示例用法
input_folder = '/home/jason/Desktop/yolov8-test/datasets/rx_datasets_plus/test'
output_folder = '/home/jason/Desktop/yolov8-test/datasets/rx_datasets_plus'
allowed_ids = [0]  # 允许保留的类别ID列表

filter_bbox_by_class(input_folder, output_folder, allowed_ids)

print("处理完成！过滤后的数据集已保存到指定目录。")
