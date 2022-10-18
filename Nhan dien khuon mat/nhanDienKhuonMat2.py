import cv2
import face_recognition
import os
import numpy as np
path = "picture"
images = []
classNames = []
list_anh = os.listdir(path) #['anh1.png', 'anh2.png', 'anh3.png', 'anh4.png', 'anh5.png']
print(list_anh)
for name in list_anh:
    anh_mau = cv2.imread(f"{path}/{name}")
    images.append(anh_mau)
    classNames.append(name[0:name.index(".")]) # tach ten
print(classNames)

def MaHoa(images):
    encodeList = []
    for img in images:
        img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        encode = face_recognition.face_encodings(img)
        if(len(encode) != 0):
            encodeList.append(encode[0])
    return encodeList

encodeListKnow = MaHoa(images)
print("Ma hoa thanh cong")
print(len(encodeListKnow))

# khởi động cam
cap = cv2.VideoCapture("videocheck.mp4")
while 1:
    ret, frame = cap.read()
    frameS = cv2.resize(frame, (0, 0), None, fx=0.5, fy=0.5)
    frameS = cv2.cvtColor(frameS, cv2.COLOR_BGR2RGB)

    # xác định vị trí khuôn mặt
    facecurFrame = face_recognition.face_locations(frameS) # lấy từng khuôn mặt và vị trí khuôn mặt hiện tại
    encodecurFrame = face_recognition.face_encodings(frameS)

    for encodeFace, facLoc in zip(encodecurFrame, facecurFrame): # lấy từng khuôn mặt và vị trí khuôn mặt tại thời điểm so sánh
        matches = face_recognition.compare_faces(encodeListKnow, encodeFace)
        faceDis = face_recognition.face_distance(encodeListKnow, encodeFace)
        print(faceDis)
        matchIndex = np.argmin(faceDis)

        if faceDis[matchIndex] < 0.5:
            name = classNames[matchIndex].upper()
        else:
            name = "Unknow"

        y1, x2, y2, x1 = facLoc
        y1, x2, y2, x1 = y1*2, x2*2, y2*2, x1*2
        cv2.rectangle(frame, (x1, y1), (x2, y2), (255, 0, 0), 2)
        cv2.putText(frame, name, (x1, y1), cv2.FONT_HERSHEY_COMPLEX, 1, (255, 255, 0), 2)
    cv2.imshow("cua so", frame)
    if cv2.waitKey(1) == 27:
        break

cv2.destroyAllWindows()
