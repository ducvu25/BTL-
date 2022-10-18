from email.mime import image
import imp
import cv2
import time
import os
import hand as htm


cap = cv2.VideoCapture(0)
pTime = 0
FolderPath = "D:\\Nam 1 - He\\python\\opencv\\project cu chi tay\\Fingers"
lst = os.listdir(FolderPath)
lst_2 = []
for i in lst:
    imgae = cv2.imread(f"{FolderPath}/{i}")
    lst_2.append(imgae)
    

detector = htm.handDetector(detectionCon = 1)
viTridau = [4, 8, 12, 16, 20]

while True:
    ret, frame = cap.read()
    frame = detector.findHands(frame)
    lmList = detector.findPosition(frame, draw=False)
    print(lmList)
    # kiem tra ngon dai
    soluong = []
    if len(lmList) != 0:
        for vitri in range(1, 5):
            if lmList[viTridau[vitri]][2] < lmList[viTridau[vitri] - 2][2]:
                soluong.append(1)
            else:
                soluong.append(0)

        if lmList[2][1] < lmList[4][1]:
            soluong.append(1)
        else:
            soluong.append(0)
    h, w, c = lst_2[soluong.count(1)].shape
    frame[0:h, 0:w] = lst_2[soluong.count(1)]

    # viết fs
    cTime = time.time() # trả về số giây
    fps = 1/(cTime - pTime)
    pTime = cTime

    #show trên màn hình
    cv2.putText(frame, f"FPS: {int(fps)}", (0, 150), cv2.FONT_HERSHEY_TRIPLEX, 1, (255, 0, 100), 3)
    cv2.putText(frame, f"Number: {soluong.count(1)}", (0, 200), cv2.FONT_HERSHEY_TRIPLEX, 1, (255, 0, 100), 3)
    cv2.imshow("cam", frame)
    if cv2.waitKey(1) == ord("s"):
        break

cap.release()
cv2.destroyAllWindows() 