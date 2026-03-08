import matplotlib.pyplot as plt
import matplotlib.animation as anim
import numpy as np
from matplotlib.pyplot import legend

dataA = []
dataB = []
tA = []
tB = []

for i in range(1,6):
    dataA.append(np.loadtxt(f"./output/aConv({round(i * 0.1,1)}00000).csv", delimiter=','))
    tA.append(np.loadtxt(f"./output/aConv({round(i * 0.1,1)}00000)t.csv", delimiter=','))
    dataB.append(np.loadtxt(f"./output/bConv({round(i * 0.1,1)}00000).csv", delimiter=','))
    tB.append(np.loadtxt(f"./output/bConv({round(i * 0.1,1)}00000)t.csv", delimiter=','))

fig, ax = plt.subplots(1, 2)

linesA = []
linesB = []
for i,data in enumerate(dataA):
    x = np.linspace(0, 20, len(data[0]))
    linesA.append(ax[0].plot(x, x, '1--', label=round((i+1)*0.1,1)))
    linesB.append(ax[1].plot(x, x, '1--', label=round((i+1)*0.1,1)))

frames = 500
T = 50 #Из кода с расчётом
dt = T / frames

xR = np.linspace(0,20,200)
realA = ax[0].plot(xR, xR, '-')
realB = ax[1].plot(xR, xR, '-')


def update(frame):
    for i,data in enumerate(dataA):
        ind = np.abs(tA[i] - dt*frame).argmin()
        if frame < len(data):
            linesA[i][0].set_ydata(data[ind])

    for i,data in enumerate(dataB):
        ind = np.abs(tB[i] - dt*frame).argmin()
        if frame < len(data):
            linesB[i][0].set_ydata(data[ind])

    realA[0].set_ydata(np.sin(4*np.pi / 20 * (-dt * frame + xR)))
    realB[0].set_ydata(np.sin(4*np.pi / 20 * (-dt * frame + xR)))

    ret = []
    for line in linesA:
        ret.append(line)
    for line in linesB:
        ret.append(line)
    ret.append(realA)
    ret.append(realB)
    return ret

ax[0].grid()
ax[1].grid()

ax[0].legend()
ax[1].legend()

ax[0].set_title("A")
ax[1].set_title("B")
ax[0].set_ylim((np.min([np.min(d) for d in dataA]) * 1.5, np.max([np.max(d) for d in dataA]) * 1.5))
ax[1].set_ylim((np.min([np.min(d) for d in dataB]) * 1.5, np.max([np.max(d) for d in dataB]) * 1.5))

fig.set_size_inches(10,8)

ani = anim.FuncAnimation(fig, update, frames=frames, interval=5, repeat_delay=1000)
# ani.save("../XIV.gif")
plt.show()
