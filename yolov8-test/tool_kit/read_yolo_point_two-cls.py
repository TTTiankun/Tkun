import cv2

def draw_boxes_and_keypoints(image_path, data_path):
    image = cv2.imread(image_path)
    
    with open(data_path, 'r') as f:
        lines = f.readlines()

    for line in lines:
        data = list(map(float, line.strip().split()))
        class_id = int(data[0])
        x_min, y_min, x_max, y_max = map(int, [data[1]*image.shape[1], data[2]*image.shape[0], data[3]*image.shape[1], data[4]*image.shape[0]])

        # 绘制边界框
        color = (0, 255, 0)  # 绿色
        cv2.rectangle(image, (x_min, y_min), (x_max, y_max), color, 2)

        # 绘制关键点
        for i in range(5, len(data), 2):
            x = int(data[i] * image.shape[1])
            y = int(data[i + 1] * image.shape[0])
            cv2.circle(image, (x, y), 4, (0, 0, 255), -1)  # 红色表示关键点

    cv2.imshow("image", image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

# 例子
image_path = '/home/jason/Desktop/2023-2-28--20-17-17-41_0.png'
data_path = '/home/jason/Desktop/2023-2-28--20-17-17-41_0.txt'

draw_boxes_and_keypoints(image_path, data_path)



