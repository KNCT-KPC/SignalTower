#!/usr/bin/env python
# -*- coding: utf-8 -*-
# cd /usr/local/bin/RPi_Cam_Web_Interface
#./stop.sh
 
from picamera.array import PiRGBArray
from picamera import PiCamera
from time import sleep
import cv2, time
import requests
import os
import sys

# Image pass
pic_file = '/media/pi/5AEF-BA501/picamera_work.jpg'

# LINE Notify token settings
url = "https://notify-api.line.me/api/notify"
access_token = '08YJE21nJR1Rph7MOfzvYysijgRXWw4z6OXdn3M7pPj'
headers = {'Authorization': 'Bearer ' + access_token}


face_classifier = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml"
face_cascade = cv2.CascadeClassifier(face_classifier)
eye_classifier = "/usr/local/share/OpenCV/haarcascades/haarcascade_eye.xml"
eye_cascade = cv2.CascadeClassifier(eye_classifier)

# frame size
FRAME_W = 1008 #624 #320 original
FRAME_H = 624 #384 #192 original
 
# For frontal face detection
cascPath = '/usr/local/share/OpenCV/lbpcascades/lbpcascade_frontalface.xml'
faceCascade = cv2.CascadeClassifier(cascPath)

flag = 0

camera = PiCamera()
camera.resolution = (FRAME_W, FRAME_H)
camera.framerate = 32
rawCapture = PiRGBArray(camera, size=(FRAME_W, FRAME_H))
time.sleep(0.1)
 
for image in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
 
    frame = image.array
    frame = cv2.flip(frame, -1) # Turn over

    
    # Convert to greyscale for detection
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    gray = cv2.equalizeHist( gray )
 
    # Face detection
    faces = faceCascade.detectMultiScale(gray, 1.1, 3, 0, (10, 10))
 
    # Write a frame on the detected face
    for (x, y, w, h) in faces:
        # Wrap the found face in short from
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
 
    frame = cv2.resize(frame, (540,300))
 
    # Display on video 
    cv2.imshow('Video', frame)
    key = cv2.waitKey(1) & 0xFF
 
    rawCapture.truncate(0)

    # LINE Notify
    if key == ord("l"):
        if os.path.exists(pic_file):
            os.remove(pic_file)

        #camera = PiCamera()
        for i in range(3, 0, -1):
            print(i)
            sleep(1)
        camera.capture(pic_file)

        face_classifier = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml"
        face_cascade = cv2.CascadeClassifier(face_classifier)
        eye_classifier = "/usr/local/share/OpenCV/haarcascades/haarcascade_eye.xml"
        eye_cascade = cv2.CascadeClassifier(eye_classifier)

        pic = cv2.imread(pic_file)
        pic = cv2.flip(pic, -1)
        pic_gray = cv2.cvtColor(pic, cv2.COLOR_BGR2GRAY)

        faces = face_cascade.detectMultiScale(
            pic_gray,
            scaleFactor=1.1,
            minNeighbors=5,
            minSize=(30, 30))

        for (x, y, w, h) in faces:
            cv2.rectangle(pic, (x, y), (x + w, y + h), (255, 0, 0), 2)
            roi_gray = pic_gray[y:y+h, x:x+w]
            roi_color = pic[y:y+h, x:x+w]
            eyes = eye_cascade.detectMultiScale(roi_gray)
            for (ex, ey, ew, eh) in eyes:
                cv2.rectangle(roi_color, (ex,ey), (ex+ew,ey+eh), (0,255,0), 2)

        #cv2.imshow("Raspberry pi camera detects {0} faces".format(len(faces)), pic)
        #cv2.waitKey(0)
        #cv2.destroyAllWindows()

        message = 'Hello World'
        image = '/media/pi/5AEF-BA501/picamera_work.jpg'
        payload = {'message': message}
        files = {'imageFile': open(image, 'rb')}
        r = requests.post(url, headers=headers, params=payload, files=files,)
        
    if key == ord("q"):
        break
    
cv2.destroyAllWindows()

    
