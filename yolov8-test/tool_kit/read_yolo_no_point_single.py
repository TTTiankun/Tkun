import cv2
import os

def draw_boxes_on_image(image_path, label_path, class_map=None):
    image = cv2.imread(image_path)
    image_height, image_width, _ = image.shape

    with open(label_path, 'r') as f:
        lines = f.readlines()

    for line in lines:
        class_id, x_center, y_center, width, height = map(float, line.strip().split())
        class_id = int(class_id)

        # Convert normalized coordinates to absolute coordinates
        x_min = int((x_center - width / 2) * image_width)
        y_min = int((y_center - height / 2) * image_height)
        x_max = int((x_center + width / 2) * image_width)
        y_max = int((y_center + height / 2) * image_height)

        # Draw bounding box
        color = (0, 255, 0)  # Green color
        cv2.rectangle(image, (x_min, y_min), (x_max, y_max), color, 2)

        # Add class label if class map is provided
        if class_map:
            class_label = list(class_map.keys())[list(class_map.values()).index(class_id)]
            cv2.putText(image, class_label, (x_min, y_min - 5), cv2.FONT_HERSHEY_SIMPLEX, 0.5, color, 2)

    cv2.imshow("Image with Bounding Boxes", image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

# Example usage
image_path = '/home/jason/Desktop/baodechun/img/00000031.png'
label_path = '/home/jason/Desktop/new_txt/00000031.txt'
class_map = {}  # Class map for class IDs

draw_boxes_on_image(image_path, label_path, class_map)
