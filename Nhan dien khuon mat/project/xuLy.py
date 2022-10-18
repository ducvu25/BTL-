import cv2
import face_recognition
import os
import numpy as np
def taoBanCheck():
    nguon = "videonguon"
    check = "anhcheck"
    images = []
    classNames = []
    list_anh = os.listdir(nguon)
    print(list_anh)
    for video in list_anh:
        cap = cv2.VideoCapture(f"{nguon}/{video}") # videonguon/
        x = 0
        i = 0;
        while 1:
            ret, frame = cap.read()

            cv2.imshow(f"cua so {video}", frame)
            x += 10
            i += 1
            if(i % 10 == 0):
                cv2.imwrite(f"{check}/{video[0:video.index('.')]}_number{i/10}.png", frame)
            if cv2.waitKey(1) == 27 or x == 1000:
                break
        cap.release()
        cv2.destroyAllWindows()
        print(video)

