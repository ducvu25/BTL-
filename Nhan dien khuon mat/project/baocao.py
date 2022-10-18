from datetime import datetime

def thamdu(name):
    with open("baocao.txt", "r+") as f:
        myDatalist = f.readline() # đọc dữ liệu
        DSten = []
        if(len(myDatalist) > 0):
            for line in myDatalist:
                ten = line.split(",") # tách tên theo ,
                DSten.append(ten[0])
            if name not in DSten:
                now = datetime.now() #2022-09-13 00:18:05.310875
                timestring = now.strftime("%H:%M:%S")
                f.writelines(f"\n{name}, {timestring}")


