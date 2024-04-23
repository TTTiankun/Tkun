import os
import cv2

def get_total_frames(video_files):
    total_frames = 0
    for video_file in video_files:
        video_path = os.path.join(video_file)
        cap = cv2.VideoCapture(video_path)
        total_frames += int(cap.get(cv2.CAP_PROP_FRAME_COUNT))
        cap.release()
    return total_frames

def concatenate_videos(input_folder, output_video):
    # 获取文件夹中的所有视频文件
    video_files = [f for f in os.listdir(input_folder) if f.endswith('.mp4') or f.endswith('.avi')]
    if not video_files:
        print("文件夹中没有视频文件！")
        return
    
    # 创建视频写入对象
    fourcc = cv2.VideoWriter_fourcc(*'XVID')
    fps = 30  # 设置帧率
    first_video_path = os.path.join(input_folder, video_files[0])
    cap = cv2.VideoCapture(first_video_path)
    frame_width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    frame_height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    out = cv2.VideoWriter(output_video, fourcc, fps, (frame_width, frame_height))

    # 获取总帧数
    total_frames = get_total_frames(video_files)

    # 逐个读取视频文件并写入输出视频
    current_frame = 0
    for video_file in video_files:
        video_path = os.path.join(input_folder, video_file)
        cap = cv2.VideoCapture(video_path)
        while cap.isOpened():
            ret, frame = cap.read()
            if not ret:
                break
            # 将帧写入输出视频
            out.write(frame)
            current_frame += 1
            print(f"当前帧数：{current_frame}")

        cap.release()

    out.release()
    print(f"视频连接完成！合成后视频帧数为: {current_frame}")


def main():
    input_folder = "/home/jason/Desktop/video"  # 输入视频文件夹路径
    output_video = "/home/jason/Desktop/video_plus.avi"  # 输出视频路径

    concatenate_videos(input_folder, output_video)

if __name__ == "__main__":
    main()
