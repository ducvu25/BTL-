import cv2
import face_recognition

imgGirl = face_recognition.load_image_file("D:\\Nam 1 - He\\python\\opencv\\Nhan dien khuon mat\\anh4.png")
imgGirl = cv2.cvtColor(imgGirl, cv2.COLOR_BGR2RGB)
imgGirl = cv2.resize(imgGirl, (0, 0), fx=0.5, fy=0.5)

# Xác định vị trí khuôn mặt
faceLoc = face_recognition.face_locations(imgGirl)[0]
print(faceLoc) # y1, x2, y2, x1
# mã hóa hình ảnh
encodeGirl = face_recognition.face_encodings(imgGirl)[0]
cv2.rectangle(imgGirl, (faceLoc[3], faceLoc[0]), (faceLoc[1], faceLoc[2]), (255, 0, 0), 2)

imgGirlCheck = face_recognition.load_image_file("D:\\Nam 1 - He\\python\\opencv\\Nhan dien khuon mat\\Girl.png")
imgGirlCheck = cv2.cvtColor(imgGirlCheck, cv2.COLOR_BGR2RGB)
imgGirlCheck = cv2.resize(imgGirlCheck, (0, 0), fx=0.5, fy=0.5)
faceCheck = face_recognition.face_locations(imgGirlCheck)[0]
print(faceCheck) # y1, x2, y2, x1
# mã hóa hình ảnh
encodeCheck = face_recognition.face_encodings(imgGirlCheck)[0]
cv2.rectangle(imgGirlCheck, (faceCheck[3], faceCheck[0]), (faceCheck[1], faceCheck[2]), (255, 0, 255), 2)
# kiểm tra
# sai số
# khoảng cách sai số
faceDis = face_recognition.face_distance([encodeGirl], encodeCheck)
results = face_recognition.compare_faces([encodeGirl], encodeCheck)
imgGirl = cv2.putText(imgGirl, f"{results[0]} - {int((1 - faceDis[0])*100)}%", (100, 200), cv2.FONT_HERSHEY_COMPLEX, 1, (255, 0, 0))


cv2.imshow("cua so 1", imgGirl)
#cv2.imshow("cua so 2", imgGirlCheck)
cv2.waitKey()