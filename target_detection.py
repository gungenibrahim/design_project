import numpy as np
import cv2
import argparse
import serial
import imutils

cap = cv2.VideoCapture(0)
cap.set(3,360)
cap.set(4,360)
#ap = argparse.ArgumentParser()
#args = vars(ap.parse_args())

w=0
x=0
dirX=0
c=0
cnts=0
h=0
while(True):
   
    ret, frame = cap.read()
    
   
    #ret, tresh = cv2.threshold(frame,127, 255, 0)
    #im2, contours, h = cv2.findContours(tresh,1,2)
    #cnt = contours(0)
    
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    lower_orange = np.array([2,10,10])
    upper_orange = np.array([17,255,255])
    
    mask = cv2.inRange(hsv,lower_orange,upper_orange)
    mask = cv2.erode(mask, None, iterations=3)
    mask = cv2.dilate(mask, None, iterations=8)
    mask = cv2.erode(mask, None, iterations=10)
    mask = cv2.dilate(mask, None, iterations=5)
    
    
   
    photo = cv2.bitwise_and(frame,frame,mask= mask)
    
    

    cnts = cv2.findContours(mask.copy(),cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_NONE)[0]

    if len(cnts) > 0:
        c = max(cnts, key=cv2.contourArea)
        x,y,w,h = cv2.boundingRect(c)
        if 6>= h/w >=2:
            cv2.rectangle(photo, (x,y), (x+w,y+h), (0,255,0),2)

    ser = serial.Serial('/dev/ttyACM0',9600)
    if w < 68 :#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
         if 100 > np.abs(x+w/2) >= 0:
               dirX = "1" 
               ser.write('1')
         if 150> np.abs(x+w/2) >= 100:
               dirX = "2" 
               ser.write('2')
         if 190> np.abs(x+w/2) >= 150:
               dirX = "3" 
               ser.write('3')
         if 260> np.abs(x+w/2)>=190 :
               dirX = "4" 
               ser.write('4')
         if  np.abs(x+w/2) >= 260:
               dirX = "5" 
               ser.write('5')
    else:
        ser.write('0')
        dirX="0"
    

    #for c in cnts:
    cv2.putText(photo,str(w), (10, 30), cv2.FONT_HERSHEY_SIMPLEX,0.65, (0, 0, 255), 3)
    cv2.putText(photo,str(x+w/2), (100, 30), cv2.FONT_HERSHEY_SIMPLEX,0.65, (255, 255, 255), 3)
    cv2.putText(photo,str(h), (90, 50), cv2.FONT_HERSHEY_SIMPLEX,0.65, (100, 0, 255), 3)
    #cv2.putText(photo,str(h/w), (200, 200), cv2.FONT_HERSHEY_SIMPLEX,0.65, (100, 0, 255), 3)

    
    cv2.imshow('frame',photo)
    #cv2.imshow('frame1',mask)
    #cv2.imshow('frame2',frame)
   
    
    
    #cv2.imshow('frame',photo)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
