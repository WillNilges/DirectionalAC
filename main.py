'''
This code (as of now) is largely based on
a tutorial from the OpenCV Wiki. I did
not write most of this, but will be using
this code as a basis for this project.
https://docs.opencv.org/master/db/d28/tutorial_cascade_classifier.html
'''

from __future__ import print_function
import cv2 as cv
import argparse

def detectAndDisplay(frame):
    frame_gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
    frame_gray = cv.equalizeHist(frame_gray)

    #-- Draw rectangle on screen. If the face is outside of that rectangle,
    # then the fan must be moved.
    # height, width, number of channels in image
    height = frame.shape[0]
    width = frame.shape[1]
    channels = frame.shape[2]
    rectangle_size = 100
    cv.rectangle(frame,(width//2-rectangle_size,height//2-rectangle_size),(width//2+rectangle_size,height//2+rectangle_size),(0,0,255),3)

    #-- Detect faces:
    faces = face_cascade.detectMultiScale(frame_gray)
    for (x,y,w,h) in faces:
        center = (x + w//2, y + h//2)
        frame = cv.ellipse(frame, center, (w//2, h//2), 0, 0, 360, (0, 255, 0), 4)

        faceROI = frame_gray[y:y+h,x:x+w]
        #-- In each face, detect eyes
        eyes = eyes_cascade.detectMultiScale(faceROI)
        for (x2,y2,w2,h2) in eyes:
            eye_center = (x + x2 + w2//2, y + y2 + h2//2)
            radius = int(round((w2 + h2)*0.25))
            frame = cv.circle(frame, eye_center, radius, (255, 0, 0 ), 4)

        #-- Check if the face is within the rectangle.
        width_ok = False
        height_ok = False
        font = cv.FONT_HERSHEY_SIMPLEX

        upper_width_bound =  width//2+rectangle_size
        lower_width_bound =  width//2-rectangle_size
        upper_height_bound = height//2+rectangle_size
        lower_height_bound = height//2-rectangle_size

        if (center[0] < upper_width_bound and center[0] > lower_width_bound):
            width_ok = True
            cv.putText(frame,'Face is within width of rect.',(10, height-50), font, 0.5,(255,255,255),2,cv.LINE_AA)
        elif (center[0] > upper_width_bound):
            cv.putText(frame,'MOVE RIGHT.',(10, height-50), font, 0.5,(0,0,255),2,cv.LINE_AA)
        elif (center[0] < lower_width_bound):
            cv.putText(frame,'MOVE LEFT.',(10, height-50), font, 0.5,(0,0,255),2,cv.LINE_AA)
        if (center[1] < upper_height_bound and center[1] > lower_height_bound):
            height_ok = True
            cv.putText(frame,'Face is within height of rect.',(10, height-25), font, 0.5,(255,255,255),2,cv.LINE_AA)
        elif (center[1] > upper_height_bound):
            cv.putText(frame,'MOVE UP.',(10, height-25), font, 0.5,(0,0,255),2,cv.LINE_AA)
        elif (center[1] < lower_height_bound):
            cv.putText(frame,'MOVE DOWN.',(10, height-25), font, 0.5,(0,0,255),2,cv.LINE_AA)

        if (width_ok and height_ok):
            cv.putText(frame,'Face OK',(10, 25), font, 1,(0,255,0),2,cv.LINE_AA)

    cv.imshow('Capture - Face detection', frame)

parser = argparse.ArgumentParser(description='Code for Cascade Classifier tutorial.')
parser.add_argument('--face_cascade', help='Path to face cascade.', default='data/haarcascades/haarcascade_frontalface_alt.xml')
parser.add_argument('--eyes_cascade', help='Path to eyes cascade.', default='data/haarcascades/haarcascade_eye_tree_eyeglasses.xml')
parser.add_argument('--camera', help='Camera devide number.', type=int, default=0)
args = parser.parse_args()

face_cascade_name = args.face_cascade
eyes_cascade_name = args.eyes_cascade

face_cascade = cv.CascadeClassifier()
eyes_cascade = cv.CascadeClassifier()

#-- 1. Load the cascades
if not face_cascade.load(cv.samples.findFile(face_cascade_name)):
    print('--(!)Error loading face cascade')
    exit(0)
if not eyes_cascade.load(cv.samples.findFile(eyes_cascade_name)):
    print('--(!)Error loading eyes cascade')
    exit(0)

camera_device = args.camera
#-- 2. Read the video stream
cap = cv.VideoCapture(camera_device)
if not cap.isOpened:
    print('--(!)Error opening video capture')
    exit(0)

while True:
    ret, frame = cap.read()
    if frame is None:
        print('--(!) No captured frame -- Break!')
        break

    detectAndDisplay(frame)

    if cv.waitKey(10) == 27:
        break

