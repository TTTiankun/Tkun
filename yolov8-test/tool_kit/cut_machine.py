import cv2
import os
from tqdm import tqdm

def extract_frames(video_path, output_folder, num_frames, offset):
    # 打开视频文件
    cap = cv2.VideoCapture(video_path)
    # 获取视频总帧数
    total_frames = int(cap.get(cv2.CAP_PROP_FRAME_COUNT))
    # 获取视频帧率
    fps = int(cap.get(cv2.CAP_PROP_FPS))
    # 计算抽取间隔
    interval = max(total_frames // num_frames, 1)

    # 如果输出文件夹不存在，则创建
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    # 初始化变量
    frame_num = 1
    extracted_frames = 0
    # 创建进度条对象
    pbar = tqdm(total=num_frames, desc=os.path.basename(video_path), unit="frame")

    # 循环读取视频帧
    while True:
        ret, frame = cap.read()
        # 如果视频帧读取完毕，则跳出循环
        if not ret:
            break

        # 检查是否到达抽取间隔
        if frame_num % interval == 0:
            # 生成照片路径并保存
            frame_path = os.path.join(output_folder, f"{offset + extracted_frames + 1}.png")
            cv2.imwrite(frame_path, frame)
            # 更新已抽取照片数量并更新进度条
            extracted_frames += 1
            pbar.update(1)

            # 如果已抽取数量达到要求，结束循环
            if extracted_frames == num_frames:
                break

        # 更新帧编号
        frame_num += 1

    # 关闭进度条和视频流
    pbar.close()
    cap.release()
    return total_frames, extracted_frames

def main():
    # 视频文件夹路径
    video_folder = "/home/jason/Desktop/model2"
    # 输出照片文件夹路径
    output_folder = "/home/jason/Desktop/model2_datasets_images"
    # 需要的照片数量
    num_frames = 60

    # 初始化变量
    total_frames = 0
    total_extracted_frames = 0
    offset = 0

    # 遍历视频文件夹中的视频文件
    for root, dirs, files in os.walk(video_folder):
        for file in files:
            if file.endswith(".mp4") or file.endswith(".avi"):
                video_path = os.path.join(root, file)
                # 调用抽取函数
                video_total_frames, extracted_frames = extract_frames(video_path, output_folder, num_frames, offset)
                # 更新总帧数和已抽取照片数量
                total_frames += video_total_frames
                total_extracted_frames += extracted_frames
                offset += extracted_frames

    # 打印结果信息
    print(f"视频总帧数：{total_frames}")
    print(f"抽取的照片数量：{total_extracted_frames}")
    print(f"抽取比例：{total_extracted_frames / total_frames:.6f}")
    print("自动抽取完成！")

if __name__ == "__main__":
    main()
