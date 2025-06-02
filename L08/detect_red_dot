import cv2 as cv
import numpy as np
import time

class Target:
    def __init__(self):
        self.capture = cv.VideoCapture(0)
        if not self.capture.isOpened():
            raise Exception("Could not open video device")
        self.counter = 1

    def save_image(self, img, x, y, w, h):
        boxed_img = img.copy()
        cv.rectangle(boxed_img, (x, y), (x + w, y + h), (0, 255, 0), 2)
        filename = f"capture_{self.counter:03d}.jpg"
        cv.imwrite(filename, boxed_img)
        print(f"Image saved: {filename}")
        self.counter += 1

    def run(self):
        try:
            while True:
                ret, img = self.capture.read()
                if not ret:
                    print("Failed to capture image")
                    break

                hsv_img = cv.cvtColor(img, cv.COLOR_BGR2HSV)

                # Red thresholds (split HSV ranges for red)
                threshold_red_low = cv.inRange(hsv_img, (0, 135, 40), (10, 210, 80))
                threshold_red_high = cv.inRange(hsv_img, (160, 135, 40), (180, 210, 80))
                threshold_red = cv.add(threshold_red_low, threshold_red_high)

                contours, _ = cv.findContours(threshold_red, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_SIMPLE)

                if contours:
                    largest = max(contours, key=cv.contourArea)
                    area = cv.contourArea(largest)
                    if area > 100:
                        x, y, w, h = cv.boundingRect(largest)
                        print(f"Red target at: ({x + w//2}, {y + h//2}), area: {int(area)}")
                        self.save_image(img, x, y, w, h)  # Auto-save when red detected

                time.sleep(1)

        except KeyboardInterrupt:
            print("\nExiting...")
        finally:
            self.capture.release()
            print("Camera released.")

if __name__ == "__main__":
    t = Target()
    t.run()
