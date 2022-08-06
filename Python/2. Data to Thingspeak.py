import serial
import datetime
import pandas as pd 
import os
from tb_device_mqtt import TBDeviceMqttClient, TBPublishInfo

arduino_port = "COM3"
serial_port = 9600

ser = serial.Serial(arduino_port,serial_port)
print("connect arduino")
lat_arr = []
lon_arr = []
prefdisttof_arr = []
disttof_arr = []
difftof_arr = []
pred_arr = []
while True:
    while True:
        getData = str(ser.readline().decode("utf-8"))
        data = getData[0:][:-2]
        print(data)
        if data != None and "b" in data:
            print("break!")
            if(len(lat_arr) > 0):
                break
            continue
        elif data == None:
            print("data is None")
            continue
        try:
            if data[0] == 0:
                continue
        except:
            pass
        data = data.split(',')
        try:
            prefdisttof = data[0]
        except:
            prefdisttof = 0
        try:
            disttof = data[1]
        except:
            disttof = 0
        try:
            difftof = data[2]
        except:
            difftof = 0
        try:
            lat= data[3]
        except:
            lat = 0
        try:
            lon= data[4]
        except:
            lon = 0
        try:
            pred = data[5]
        except:
            pred = 0

        if(lat == 0 or lon == 0 or prefdisttof == 0 or disttof == 0 or difftof == 0 or pred == 0):
            continue
        lat_arr.append(lat)
        lon_arr.append(lon)
        prefdisttof_arr.append(prefdisttof)
        disttof_arr.append(disttof)
        difftof_arr.append(difftof)
        pred_arr.append(pred)

        URL='https://api.thingspeak.com/update?api_key='
        KEY='5K23ZTWMLBDGBI2I'
        HEADER='&field1={}&field2={}&field3={}&field4={}&field5={}'.format(lat, lon, disttof, difftof, pred)
        comb_url = URL+KEY+HEADER
        req = requests.get(comb_url)
        print(req.text)
        time.sleep(1)

    tanggal = datetime.date.today().strftime('%d-%m-%Y')
    try:
        os.mkdir(tanggal)
    except FileExistsError:
        pass
    filename=tanggal+"/latlon-" + datetime.datetime.today().strftime('%d-%m-%Y--%H-%M-%S') + ".xlsx"
    dataall = pd.DataFrame([lat_arr,lon_arr,prefdisttof_arr,disttof_arr,difftof_arr,pred_arr])
    dataall = dataall.T
    dataall.columns = ["latitute", "longitute", "prefdisttof", "disttof", "difftof", "pred"]
    pd.DataFrame(dataall).to_excel(filename, index=False)

    lat_arr.clear()
    lon_arr.clear()
    prefdisttof_arr.clear()
    disttof_arr.clear()
    difftof_arr.clear()
    pred_arr.clear()