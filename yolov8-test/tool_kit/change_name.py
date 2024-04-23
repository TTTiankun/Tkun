import os
from tqdm import tqdm

def rename_files(folder_path, start_index=0):
    # 获取指定文件夹中的所有文件
    files = [f for f in os.listdir(folder_path) if os.path.isfile(os.path.join(folder_path, f))]
    # 过滤出 txt、png 和 jpg 格式的文件
    files = [f for f in files if f.lower().endswith(('.txt', '.png', '.jpg'))]

    # 进度条设置
    progress_bar = tqdm(total=len(files), desc="重命名文件")

    index = start_index
    for filename in files:
        # 获取文件扩展名
        _, ext = os.path.splitext(filename)
        # 构造新文件名
        new_filename = f"{index:06d}{ext}"
        # 构造完整的文件路径
        old_filepath = os.path.join(folder_path, filename)
        new_filepath = os.path.join(folder_path, new_filename)
        # 重命名文件
        os.rename(old_filepath, new_filepath)
        # 更新进度条
        progress_bar.update(1)
        index += 1

    # 完成后关闭进度条
    progress_bar.close()

# 指定文件夹路径和起始索引（可选，默认为 0）
folder_path = "/media/jason/实验室2号/跟踪/train_img/eyongwei/img"
start_index = 14000

# 执行重命名操作
rename_files(folder_path, start_index)
