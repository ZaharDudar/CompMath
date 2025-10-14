import matplotlib.pyplot as plt
import numpy as np
from math import sqrt, exp

dataSpline = np.loadtxt("/home/zahar/Edu/CompMath/CompMath/Practice1/tasks/output/outSpline.csv", delimiter=',')
dataIntrap = np.loadtxt("/home/zahar/Edu/CompMath/CompMath/Practice1/tasks/output/out.csv", delimiter=',')
baseData = np.loadtxt("/home/zahar/Edu/CompMath/CompMath/Practice1/python/baseData.csv", delimiter=',')
plt.plot(baseData[:,0], baseData[:,1], 'o')
# plt.plot([0,1,2,3], np.array([0,1,2,3])**2+1,'o')
plt.plot(dataIntrap[:,0], dataIntrap[:,1],'--')
plt.plot(dataSpline[:,0], dataSpline[:,1],'--')
plt.grid()
plt.show()