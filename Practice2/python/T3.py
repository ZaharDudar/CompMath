import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt("output/T3.csv",delimiter=',')
print(data)
plt.plot(data[:,0],data[:,1])
plt.grid()
plt.show()