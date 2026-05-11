import matplotlib.pyplot as plt
import matplotlib.animation as anim
import numpy as np

heatSlice = []
heat = []
with open("./output/heat.csv", "r") as f:
    N = int(f.readline().strip())
    for line in f.readlines():
        line = line.strip().split(",")
        heatSlice = []
        for i in range(N):
            heatSlice.append(line[i * N:i * N +N])
        heat.append(heatSlice)
heat = np.array(heat).astype(float)

time = np.loadtxt("./output/htime.csv", delimiter=",")

fig, ax = plt.subplots()

# x = np.linspace(0, 500, len(p[0]))

heatmap = ax.imshow(heat[0])

def update(frame):
    if frame<len(heat):
        heatmap.set_array(heat[frame])

    plt.title(f"{round(time[frame], 2)} sec")


    return (heatmap)

# ax.grid()

ax.set_xlabel("Координата (м)")
ax.set_xlabel("Координата (м)")
fig.colorbar(heatmap)

# ax[0].set_ylim((np.min(p), np.max(p)*1.1))
# ax[1].set_ylim((np.min(rho), np.max(rho)*1.1))


ani = anim.FuncAnimation(fig, update, frames=range(len(time)), interval=1, repeat_delay=5000)
# ani.save("../filtering.gif")
plt.show()
