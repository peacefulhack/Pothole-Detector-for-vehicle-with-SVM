from cProfile import label
from sys import platlibdir
import seaborn as sns
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.svm import SVC

def plot_svc_decision_function(model, ax=None, plot_support=True):
    """Plot the decision function for a 2D SVC"""
    if ax is None:
        ax = plt.gca()
    xlim = ax.get_xlim()
    ylim = ax.get_ylim()
    
    # create grid to evaluate model
    x = np.linspace(xlim[0], xlim[1], 30)
    y = np.linspace(ylim[0], ylim[1], 30)
    Y, X = np.meshgrid(y, x)
    xy = np.vstack([X.ravel(), Y.ravel()]).T
    P = model.decision_function(xy).reshape(X.shape)
    
    # plot decision boundary and margins
    ax.contour(X, Y, P, colors='k',
               levels=[-1, 0, 1], alpha=0.5,
               linestyles=['--', '-', '--'])
    
    # plot support vectors
    if plot_support:
        ax.scatter(model.support_vectors_[:, 0],
                   model.support_vectors_[:, 1],
                   s=300, linewidth=1, facecolors='none');
    ax.set_xlim(xlim)
    ax.set_ylim(ylim)

excel = pd.read_excel("datasetFix.xlsx", index_col=None,sheet_name=0, usecols=[2,3,7,9])
# print(excel['diffToF'])
# excel = excel[(excel['Target']!=1)]
excel = excel.drop('ToFLastDist', axis=1)
x = excel.iloc[:,0:2]
y = excel['Target']


plt.scatter(x.iloc[:, 0], x.iloc[:, 1],color="white")

clf = SVC(kernel='linear', gamma=0.001).fit(x, y)
support_vectors = clf.support_vectors_

plt.scatter(support_vectors[:,0], support_vectors[:, 1], color='black', label="support_vectors")
plt.title('SVM Linear(Hijau: Jalan berlubang; Merah: Jalan normal; Kuning: Jalan pecah)')
plt.xlabel('Jarak')
plt.ylabel('Differensial')
plt.show()
# plt.scatter(x.iloc[:, 0], x.iloc[:, 1], c=y, s=50, cmap='autumn')
# clf = SVC(kernel='linear', gamma=0.001, C=1E10).fit(x, y)
# plot_svc_decision_function(clf)