import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt("output/T5.csv",delimiter=',')
fig, ax = plt.subplots(2,1)

ax[0].plot(data[:,0],data[:,1], ',')
# ax[0].plot(data[:,0],data[:,1], '4')
ax[0].grid()
ax[1].plot(data[:-1,0], np.abs(data[:-1,0]-data[1:,0]))

# ax[0].set_xlim((0,80))
# ax[1].set_xlim((0,80))
ax[0].set_xlim((34.1,34.15))
ax[1].set_xlim((34.1,34.15))
ax[0].set_ylim((-1.5,1.5))
ax[0].set_ylim((0.97,1))
ax[1].set_ylim((0,1e-4))
plt.show()