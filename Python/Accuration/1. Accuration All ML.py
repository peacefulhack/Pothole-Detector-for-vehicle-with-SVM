from micromlgen import port
from sklearn.svm import SVC
from sklearn.linear_model import LinearRegression as LR
from sklearn.kernel_ridge import KernelRidge as KR
from sklearn.neighbors import KNeighborsClassifier as KNN
from sklearn.naive_bayes import GaussianNB as GNB
from sklearn.metrics import accuracy_score as acc
import pandas as pd
import numpy as np

if __name__ == '__main__':
    training = pd.read_excel("datasetFix.xlsx", index_col=None,sheet_name=0, usecols=[2,3,7,9])
    testing = pd.read_excel("datasetFix.xlsx", index_col=None,sheet_name=1, usecols=[2,3,7,9])

    train = training.to_numpy()
    test = testing.to_numpy()

    tr_x , tr_y = train[:,:-1], train[:,-1]
    ts_x, ts_y = test[:,:-1], test[:,-1]

    svm = SVC(kernel='linear', gamma=0.001).fit(tr_x, tr_y)
    lr = LR().fit(tr_x, tr_y)
    kr = KR().fit(tr_x, tr_y)
    for i in range(1,11):
        knn = KNN(n_neighbors=i).fit(tr_x, tr_y)
        knn_pred = knn.score(ts_x, ts_y)* 100
        print( "knn"+"-"+str(i)+": " + str(knn_pred) + "%")
    gnb = GNB().fit(tr_x, tr_y)
    
    svm_pred = svm.score(ts_x, ts_y)* 100
    lr_pred = lr.score(ts_x, ts_y)* 100
    kr_pred = kr.score(ts_x, ts_y)* 100
    
    gnb_pred = gnb.score(ts_x, ts_y)* 100
    
    print( "svm: "+  str(svm_pred) + "%")
    print( "lr: "+  str(lr_pred) + "%")
    print( "kr: "+  str(kr_pred) + "%")
    print( "gnb: "+  str(gnb_pred) + "%")
    


