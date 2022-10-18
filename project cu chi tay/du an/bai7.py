import cv2
import time
import numpy as np
import hand as htm
import math 
from cTYPEs import cast, POINTER
from comTYPEs import CLSCTX_ALL
from pycaw.pycaw import AudioUtilities, IAudioEndpointVolume

pTime = 0
cap = cv2.VideoCapture(0)
detector = htm.handDetector(detectionCon = 1)# độ chính xác tín hiệu

devices = AudioUtilities.GetSpeakers()
interface = devices.Activate(IAudioEndpointVolume._iid_, CLSCTX_ALL, None)
volume = cast(interface, POINTER(IAudioEndpointVolume))
volRange = volume.GetVolumeRange()
volumeMin = volRange[0]
volumeMax = volRange[1]
#-96 -> 0

viTridau = [4, 8, 12, 16, 20]
while True:
    ret, frame = cap.read()
    frame = detector.findHands(frame)
    lmList = detector.findPosition(frame, draw=False)
    soluong = []
    cv2.rectangle(frame, (50, 150), (80, 150 + 200), (200, 150, 100), 5)

    if len(lmList) != 0:
        x1, y1 = lmList[4][1], lmList[4][2] # toa do ngon cai
        x2, y2 = lmList[8][1], lmList[8][2] # toa do ngon tro
        x3, y3 = (x1+x2) // 2, (y1 + y2) // 2
        # độ dài
        lenght = math.sqrt((x1-x2)**2 + (y1-y2)**2)
        #30 ->250
        vol = np.interp(lenght, [30, 230], [volumeMin, volumeMax])
        volRect = np.interp(lenght, [30, 230], [350, 150])
        cv2.rectangle(frame, (50, int(volRect)), (80, 350), (200, 150, 100), -1)
        cv2.putText(frame, f"{ (lenght + 10) // 3}%", (0, 400), cv2.FONT_HERSHEY_TRIPLEX, 2, (200, 150, 100), 3)
        volume.SetMasterVolumeLevel(vol, None)
        if lenght < 30:
            cv2.circle(frame, (x3, y3), 10, (0, 250, 127), -1)
        elif lenght > 260:
            cv2.circle(frame, (x1, y1), 10, (0, 250, 127), -1)
            cv2.circle(frame, (x2, y2), 10, (0, 250, 127), -1)
            cv2.circle(frame, (x3, y3), 10, (0, 250, 127), -1)
            cv2.line(frame, (x1, y1), (x2, y2), (0, 250, 127), 5)
        else:
            cv2.circle(frame, (x1, y1), 10, (100, 250, 0), -1)
            cv2.circle(frame, (x2, y2), 10, (100, 250, 0), -1)
            cv2.circle(frame, (x3, y3), 10, (100, 250, 0), -1)
            cv2.line(frame, (x1, y1), (x2, y2), (100, 250, 0), 5)
        
        for vitri in range(1, 5):
            if lmList[viTridau[vitri]][2] < lmList[viTridau[vitri] - 2][2]:
                soluong.append(1)
            else:
                soluong.append(0)

        if lmList[2][1] < lmList[4][1]:
            soluong.append(1)
        else:
            soluong.append(0)

    #Viet FPS
    cTime = time.time()
    fps = 1/(cTime - pTime)
    pTime = cTime
    cv2.putText(frame, f"FPS: {int(fps)}", (0, 50), cv2.FONT_HERSHEY_TRIPLEX, 1, (255, 55, 100), 3)
    cv2.imshow("cua so", frame)


    if cv2.waitKey(1) == ord("s") or soluong.count(1) == 5:
        break

cap.release()  # giải phóng camera
cv2.destroyAllWindows()  # thoát tất cả các cửa sổ
