import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt("output/T4Shooting.csv",delimiter=',')
print(data)
plt.plot(data[:,0],data[:,1], label="Shooting")
data = np.loadtxt("output/T4Lin.csv",delimiter=',')
plt.plot(data[:,0],data[:,1], label="Linearize")

plt.grid()
plt.legend()
plt.show()