from email import header
from posixpath import split
import serial
import datetime
import pandas as pd 
import os
class Dataset:
    ultraLast = []
    ultra = []
    TofLast = []
    Tof = []
    ampLast = []
    amp = []
    diffUltra = []
    difftof = []
    diffAmp = []

arduino_port = "COM3"
serial_port = 115200


ser = serial.Serial(arduino_port,serial_port)
print("connect arduino")
dataset = Dataset()
while True:
    while True:
        getData=str(ser.readline().decode("utf-8"))
        data = getData[0:][:-2]
        print(data)
        if data != None and "b" in data:
            print("break!")
            if len(dataset.amp) > 0:
                break
            continue
        data = data.split(',')
        
        try:
            data_0 = data[0]
        except:
            data_0 = "-"
        try:
            data_1 = data[1]
        except:
            data_1 = "-"
        try:
            data_2 = data[2]
        except:
            data_2 = "-"

        ################==============#####################
        if not dataset.ultra:
            lastUltra = data_0
            diffUltra = 0
        else:
            lastUltra = dataset.ultra[-1]
            try:
                diffUltra = int(data_0) - int(lastUltra)
            except:
                diffUltra = "-"
        ###################################################
        
        dataset.ultraLast.append(lastUltra)
        dataset.diffUltra.append(diffUltra)

        try:
            dataset.ultra.append(data_0)
        except IndexError:
            dataset.ultra.append("-")

        
        ################==============#####################

        ################==============#####################
        if not dataset.Tof:
            lastTof = data_1
            diffTof = 0
        else:
            lastTof = dataset.Tof[-1]
            try:
                diffTof = int(data_1) - int(lastTof)
            except:
                diffTof = "-"
        ###################################################
        
        dataset.TofLast.append(lastTof)
        dataset.difftof.append(diffTof)

        try:
            dataset.Tof.append(data_1)
        except IndexError:
            dataset.Tof.append("-")
        ################==============#####################
        
        ################==============#####################

        if not dataset.amp:
            lastAmp = data_2
            diffAmp = 0
        else:
            lastAmp = dataset.amp[-1]
            try:
                diffAmp = int(data_2) - int(lastAmp)
            except:
                diffAmp = "-"
        ###################################################

        dataset.diffAmp.append(diffAmp)
        dataset.ampLast.append(lastAmp)
        
        try:
            dataset.amp.append(data_2)
        except IndexError:
            dataset.amp.append("-")
        ################==============#####################
    
    tanggal = datetime.date.today().strftime('%d-%m-%Y')
    try:
        os.mkdir(tanggal)
    except FileExistsError:
        pass
    filename=tanggal+"/logData-" + datetime.datetime.today().strftime('%d-%m-%Y--%H-%M-%S') + ".xlsx"
    dataall = pd.DataFrame([dataset.ultraLast,dataset.ultra,dataset.TofLast,dataset.Tof,dataset.ampLast,dataset.amp,dataset.diffUltra,dataset.difftof,dataset.diffAmp])
    dataall = dataall.T
    dataall.columns = ["ultras last dist","ultras dist", "ToF Last Dist", "ToF Dist", "amp last dist", "amp dist", "diff ultra", "diff ToF", "diff amp"]
    pd.DataFrame(dataall).to_excel(filename, index=False)
    
    dataset.ultraLast.clear()
    dataset.ultra.clear()
    dataset.TofLast.clear()
    dataset.Tof.clear()
    dataset.ampLast.clear()
    dataset.amp.clear()
    dataset.diffUltra.clear()
    dataset.difftof.clear()
    dataset.diffAmp.clear()