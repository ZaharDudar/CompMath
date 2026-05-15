import matplotlib.pyplot as plt
import matplotlib.animation as anim
import numpy as np

p = np.loadtxt("./output/p.csv", delimiter=',')
time = np.loadtxt("./output/time.csv", delimiter=',')
# rho = 1000 * (np.ones_like(p) + 1e-4 * (p - 120 * 1e5))
rho = ((p * 1e-5 - 120) * 1e-4 + 1) * 1000
fig, ax = plt.subplots(1, 2)

x = np.linspace(0, 500, len(p[0]))

line1 = ax[0].plot(x, x * 0, "o--")
line2 = ax[1].plot(x, x * 0, "o--")

def update(frame):
    if frame<len(p):
        line1[0].set_ydata(p[frame])
    if frame<len(rho):
        line2[0].set_ydata(rho[frame])

    fig.suptitle(f"{round(time[frame], 2)} days")


    return (line1, line2)

ax[0].grid()
ax[1].grid()

ax[0].set_title("p Па")
ax[1].set_title("rho кг/м3")

ax[0].set_xlabel("Координата (м)")
ax[1].set_xlabel("Координата (м)")


ax[0].set_ylim((np.min(p), np.max(p)*1.1))
ax[1].set_ylim((np.min(rho), np.max(rho)*1.1))


ani = anim.FuncAnimation(fig, update, frames=range(len(time)), interval=1, repeat_delay=5000)
# ani.save("../filtering.gif")
plt.show()
