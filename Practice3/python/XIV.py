import matplotlib.pyplot as plt
import matplotlib.animation as anim
import numpy as np

data = np.loadtxt("./output/XIV.10.2a(0.600000).csv", delimiter=',')
data1 = np.loadtxt("./output/XIV.10.2a(1.000000).csv", delimiter=',')
data2 = np.loadtxt("./output/XIV.10.2a(1.010000).csv", delimiter=',')

data3 = np.loadtxt("./output/XIV.10.2b(0.600000).csv", delimiter=',')
data4 = np.loadtxt("./output/XIV.10.2b(1.000000).csv", delimiter=',')
data5 = np.loadtxt("./output/XIV.10.2b(1.010000).csv", delimiter=',')

fig, ax = plt.subplots(2, 3)

x = np.linspace(0, 20, len(data[0]))

line1 = ax[0][0].plot(x, x * 0, "o--")
line2 = ax[0][1].plot(x, x * 0, "o--")
line3 = ax[0][2].plot(x, x * 0, "o--")

line4 = ax[1][0].plot(x, x * 0, "o--")
line5 = ax[1][1].plot(x, x * 0, "o--")
line6 = ax[1][2].plot(x, x * 0, "o--")
def update(frame):
    if frame<len(data):
        line1[0].set_ydata(data[frame])
    if frame<len(data1):
        line2[0].set_ydata(data1[frame])
    if frame<len(data2):
        line3[0].set_ydata(data2[frame])

    if frame<len(data3):
        line4[0].set_ydata(data3[frame])
    if frame<len(data4):
        line5[0].set_ydata(data4[frame])
    if frame<len(data5):
        line6[0].set_ydata(data5[frame])
    return (line1, line2, line3, line4, line5, line6)

ax[0][0].grid()
ax[0][1].grid()
ax[0][2].grid()
ax[1][0].grid()
ax[1][1].grid()
ax[1][2].grid()

ax[0][0].set_title("cft 0.6")
ax[0][1].set_title("cft 1.00")
ax[0][2].set_title("cft 1.01")

ax[0][0].set_ylim((np.min(data), np.max(data)))
ax[0][1].set_ylim((np.min(data1), np.max(data1)))
ax[0][2].set_ylim((np.min(data2), np.max(data2)))
ax[1][0].set_ylim((np.min(data3), np.max(data3)))
ax[1][1].set_ylim((np.min(data4), np.max(data4)))
ax[1][2].set_ylim((np.min(data5), np.max(data5)))
fig.set_size_inches(10,8)

ax[0][0].set_ylabel("a")
ax[1][0].set_ylabel("b")
ani = anim.FuncAnimation(fig, update, frames=max([len(d) for d in [data, data1, data2]]), interval=50, repeat_delay=2000)
ani.save("../XIV.gif")
plt.show()
