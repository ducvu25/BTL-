'''
Ý tưởng dựa trên việc trừ tuyệt đối 2 khung ảnh rồi lấy ra điểm khác nhau
'''
import cv2

cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)

#Lay Background 
cv2.waitKey(500)
ret, frame_bg = cap.read()

frame_bg = cv2.resize(frame_bg, (640, 480))
gray = cv2.cvtColor(frame_bg, cv2.COLOR_BGR2GRAY)
# lọc
gray = cv2.GaussianBlur(gray, (25, 25), 0)
background = gray

while 1:
    ret_2, frame_picture = cap.read()

    #Xử lý frame
    gray = cv2.cvtColor(frame_picture, cv2.COLOR_BGR2GRAY)
    abs_img = cv2.absdiff(background, gray)
    background = gray
    # lọc nhiễu
    _, img_mask = cv2.threshold(abs_img, 30, 255, cv2.THRESH_BINARY)

    # Phát hiện chuyen động
    contours, _ = cv2.findContours(img_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    # Bỏ qua các chuyển động nhỏ
    for contour in contours:
        if cv2.contourArea(contour) < 100:
            continue
        x, y, w, h = cv2.boundingRect(contour)
        cv2.rectangle(frame_picture, (x, y), (x+w, y+h), (0, 255, 0), 3)
    cv2.imshow("cua so", frame_picture)
    if cv2.waitKey(1) == 27:
        break
cv2.destroyAllWindows()