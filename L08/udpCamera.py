##
# @file 
#  Reads video frames from camera,
#  detects red marker and calculates angle.
#  Measurements are streaming by the UDP server.

import socket
import numpy as np
import cv2 as cv
import math
from picamera import PiCamera
from picamera.array import PiRGBArray
import time

# BEGIN server init #
UDP_IP = "192.168.0.10"
UDP_PORT = 8886

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # UDP
sock.bind(('', UDP_PORT))
# END server init #

# BEGIN camera init #
camera = PiCamera()

camera.resolution = (640, 480)
camera.framerate = 32

rawCapture = PiRGBArray(camera, size=(640, 480))
time.sleep(0.1)
# END camera init #

# BEGIN points init #
point1 = [310, 130]
point2 = [310, 304]
point3 = [0, 0]
pointsList = []


# END points init #

######################################################## #
# Calculates slope of line passing points pt1 and pt2
# @param[in] pt1, pt2 pixel coordinates pt1=[x1,y1], pt2=[x2,y2]
# @return gradient
####################################################### #
def slope(point1, point2):
    if point2[0] == point1[0]:
        point1[0] += 1
    return (point2[1] - point1[1]) / (point2[0] - point1[0])


######################################################## #
# Calculates angle between two lines of slope m1 and m2
# @param[in] pt1, pt2 pixel coordinates pt1=[x1,y1], pt2=[x2,y2]
####################################################### #
def getAngle(pointsLists):
    point1, point2, point3 = pointsList[-3:]  # # Get last three elements from pointLists
    m1 = slope(point1, point2)  # # Calculate slope m1
    m2 = slope(point1, point3)  # # Calculate slope m2

    radiansAngle = math.atan((m2 - m1) / (1 + (m2 * m1)))  # # Calculate angle between lines with slopes m1 and m2
    degreesAngle = round(math.degrees(radiansAngle))

    if (point1[1] >= point3[1]) and (point1[0] < point3[0]):  # # set minimum angle
        degreesAngle = -90
    elif (point3[1] < point1[1]) and (point1[0] > point3[0]):  # # set maximum angle
        degreesAngle = 90
    # # Put text on a screen
    cv.putText(img, str(degreesAngle), (point1[0] - 50, point2[1] - 30), cv.FONT_HERSHEY_SIMPLEX, 1.5, (0, 0, 255), 2)

    # # Send angle tp PC by UDP server
    sock.sendto((degreesAngle + 90).to_bytes(3, 'big'), (UDP_IP, UDP_PORT))


# # Main loop
for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):

    img = frame.array
    hsv_frame = cv.cvtColor(img, cv.COLOR_BGR2HSV)

    # # Set range for red color
    lower_limit_color = np.array([135, 86, 109])  # # lower case of color
    upper_limit_color = np.array([180, 255, 255])  # # upper case of color
    color_range = cv.inRange(hsv_frame, lower_limit_color, upper_limit_color)  # # set range of red color

    kernel_size = np.ones((5, 5))

    color_range = cv.dilate(color_range, kernel_size)
    res_red = cv.bitwise_and(img, img, mask=color_range)

    # # Contur tracking red color
    conturs= cv.findContours(color_range, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)
    for pic, contur in enumerate(conturs):
        area = cv.contourArea(contur)
        if (area > 300) and (area < 1000): # # check size of contur
            x, y, w, h = cv.boundingRect(contur)
            img = cv.rectangle(img, (x, y), (x + w, y + h), (0, 0, 255), 2)
            point3 = [x, y] # # write point3 coordinates
            cv.putText(img, "Red Color", (x, y), cv.FONT_HERSHEY_SIMPLEX, 1.0, (0, 0, 255))

            pointsList = [point1, point2, point3]
    if (len(pointsList) % 3) == 0 and len(pointsList) != 0:
        getAngle(pointsList)

    cv.imshow('frame', img)
    rawCapture.truncate(0)
    if cv.waitKey(1) & 0xFF == ord('q'):
        pointsList = []
