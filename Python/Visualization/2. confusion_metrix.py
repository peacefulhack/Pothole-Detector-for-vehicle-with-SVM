import matplotlib.pyplot as plt
from sklearn.datasets import make_classification
from sklearn.metrics import confusion_matrix, ConfusionMatrixDisplay
from sklearn.model_selection import train_test_split
from sklearn.svm import SVC
import pandas as pd

training = pd.read_excel("datasetFix.xlsx", index_col=None,sheet_name=0, usecols=[2,3,7,9])
testing = pd.read_excel("datasetFix.xlsx", index_col=None,sheet_name=1, usecols=[2,3,7,9])

train = training.to_numpy()
test = testing.to_numpy()

tr_x , tr_y = train[:,:-1], train[:,-1]
ts_x, ts_y = test[:,:-1], test[:,-1]

svm = SVC(kernel='linear', gamma=0.001).fit(tr_x, tr_y)

pred = svm.predict(ts_x)
cm = confusion_matrix(ts_y, pred, labels=svm.classes_)
disp = ConfusionMatrixDisplay(cm, display_labels=["Jalan aman","Jalan berlubang","Jalan crack"])

disp.plot()

plt.show()