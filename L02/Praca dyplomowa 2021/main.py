# import numpy as np
# import argparse
# import cv2 as cv
# import math
#
# capture = cv.VideoCapture(0)
#
# # path = 'test.JPG'
# # frame = cv.imread(path)
#
# point1 = [501, 402]
# point2 = [503, 554]
# point3 = [406, 405]
# pointsList = [point1, point2,point3]
# frame_height = int(capture.get(cv.CAP_PROP_FRAME_HEIGHT))
# frame_width = int(capture.get(cv.CAP_PROP_FRAME_WIDTH))
#
# threshold_img1 = np.zeros((frame_height, frame_width, 1), dtype=np.uint8)
# pointsList = []
# def mousePoints(event, x, y, flags, params):
#     if event == cv.EVENT_LBUTTONDOWN:
#         size = len(pointsList)
#         if size != 0 and size % 3 != 0:
#             cv.line(frame, tuple(pointsList[round((size - 1) / 3) * 3]), (x, y), (0, 0, 255, 2))
#         cv.circle(frame, (x, y), 5, (0, 0, 255), cv.FILLED)
#         pointsList.append([x, y])
#         print(pointsList)
#         # print(x,y)
#
#
# def gradient(pt1, pt2):
#     return (pt2[1] - pt1[1]) / (pt2[0] - pt1[0])
#
#
# def getAngle(pointsLists):
#     pt1, pt2, pt3 = pointsLists[-3:]
#     # print(pt1,pt2,pt3)
#     m1 = gradient(pt1, pt2)
#     m2 = gradient(pt1, pt3)
#     angR = math.atan((m2 - m1) / (1 + (m2 * m1)))
#     angD = round(math.degrees((angR)))
#     cv.putText(frame, str(angD), (pt1[0] - 40, pt2[1] - 20), cv.FONT_HERSHEY_SIMPLEX, 1.5, (0, 0, 255), 2)
#     print(angD)
#
#
# while True:
#     ret,frame=capture.read(0)
#
#     hsv_img = cv.cvtColor(frame, cv.COLOR_BGR2HSV)
#     cv.inRange(hsv_img, (1, 163, 255), (5, 211, 255), threshold_img1)  # red
#     moments1=cv.moments(threshold_img1)
#     area=moments1['m00']
#
#
#     if (area>200):
#         x1=int(moments1['m10'])
#         y1=int(moments1['m01'])
#         # draw circle
#         cv.circle(frame, (x1, y1), 2, (0, 255, 0), 20)
#         print(str(x1)+', '+str(y1))
#     #print(frame_height)
#     #print(frame_width)
#     if (len(pointsList) % 3) == 0 and len(pointsList) != 0:
#        getAngle(pointsList)
#     #getAngle(pointsList)
#     cv.imshow('Image', frame)
#     cv.setMouseCallback('Image', mousePoints)
#     if cv.waitKey(1) & 0xFF == ord('q'):
#         pointsList = []
#

import numpy as np
import argparse
import cv2 as cv
import math
from picamera import PiCamera
from picamera.array import PiRGBArray

from time import sleep
import time

capture = cv.VideoCapture(0)
camera = PiCamera()
rawCapture = PiRGBArray(camera, size=(640, 480))
time.sleep(0.1)

# path = 'test.JPG'
# img = cv.imread(path)

point1 = [301, 102]
point2 = [303, 304]
point3 = [406, 405]
point4=[0,0]
pointsList = []


def mousePoints(event, x, y, flags, params):
    if event == cv.EVENT_LBUTTONDOWN:
        size = len(pointsList)
        if size != 0 and size % 3 != 0:
            cv.line(frame, tuple(pointsList[round((size - 1) / 3) * 3]), (x, y), (0, 0, 255, 2))
        cv.circle(frame, (x, y), 5, (0, 0, 255), cv.FILLED)
        pointsList.append([x, y])
        print(pointsList)
        # print(x,y)


def gradient(pt1, pt2):
    return (pt2[1] - pt1[1]) / (pt2[0] - pt1[0])


def getAngle(pointsLists):
    pt1, pt2, pt3 = pointsLists[-3:]
    # print(pt1,pt2,pt3)
    m1 = gradient(pt1, pt2)
    m2 = gradient(pt1, pt3)
    angR = math.atan((m2 - m1) / (1 + (m2 * m1)))
    angD = round(math.degrees((angR)))
    cv.putText(frame, str(angD), (pt1[0] - 40, pt2[1] - 20), cv.FONT_HERSHEY_SIMPLEX, 1.5, (0, 0, 255), 2)
    print(angD)


for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
    #ret,frame=capture.read(0)

    img = frame.array
    hsv_frame=cv.cvtColor(img,cv.COLOR_BGR2HSV)
    #hsv_frame = cv.cvtColor(frame, cv.COLOR_BGR2HSV)

    # Set range for red color and
    # define mask
    red_lower = np.array([136, 87, 111], np.uint8)
    red_upper = np.array([180, 255, 255], np.uint8)
    red_mask = cv.inRange(hsv_frame, red_lower, red_upper)

    # Morphological Transform, Dilation
    # for each color and bitwise_and operator
    # between imageFrame and mask determines
    # to detect only that particular color
    kernal = np.ones((5, 5), "uint8")

    # For red color
    red_mask = cv.dilate(red_mask, kernal)
    res_red = cv.bitwise_and(frame, frame, mask = red_mask)
    # Creating contour to track red color
    contours, hierarchy = cv.findContours(red_mask, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)
    for pic, contour in enumerate(contours):
        area = cv.contourArea(contour)
        if (area > 300):
            x, y, w, h = cv.boundingRect(contour)
            img = cv.rectangle(img, (x, y),(x + w, y + h),(0, 0, 255), 2)
            point4=[x,y]
            cv.putText(img, "Red Colour", (x, y),cv.FONT_HERSHEY_SIMPLEX, 1.0,(0, 0, 255))
            print(str(point4[0])+', '+str(point4[1]))
            pointsList=[point1,point2,point4]
    if (len(pointsList) % 3) == 0 and len(pointsList) != 0:
        getAngle(pointsList)
    cv.imshow('Image', img)
    # cv.setMouseCallback('Image', mousePoints)
    if cv.waitKey(1) & 0xFF == ord('q'):
        pointsList = []

