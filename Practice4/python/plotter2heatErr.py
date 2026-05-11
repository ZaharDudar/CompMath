import matplotlib.pyplot as plt
import matplotlib.animation as anim
import numpy as np

data = np.loadtxt("./output/herror.csv", delimiter=',')
data = np.log(data)
plt.plot(data[:,0], data[:,1], "o--")
p = np.polyfit(data[3:,0], data[3:,1], 1)
print(p)
plt.plot(data[:,0], np.polyval(p, data[:,0]), "--")
plt.grid()
plt.show()
