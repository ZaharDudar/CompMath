import matplotlib.pyplot as plt
import matplotlib.animation as anim
import numpy as np

rho = np.loadtxt("./output/RIMAN_1_rho.csv", delimiter=',')
u = np.loadtxt("./output/RIMAN_1_u.csv", delimiter=',')
e = np.loadtxt("./output/RIMAN_1_e.csv", delimiter=',') / 10**3
p = np.loadtxt("./output/RIMAN_1_p.csv", delimiter=',') / 10**5
t = np.loadtxt("./output/RIMAN_1_t.csv", delimiter=',')

fig, ax = plt.subplots(2, 2)
# print(rho)
x = np.linspace(-10, 10, len(rho[0]))

line1 = ax[0][0].plot(x, x * 0, "o--")
line2 = ax[0][1].plot(x, x * 0, "o--")

line3 = ax[1][0].plot(x, x * 0, "o--")
line4 = ax[1][1].plot(x, x * 0, "o--")
def update(frame):
    if frame<len(rho):
        line1[0].set_ydata(rho[frame])
    if frame<len(u):
        line2[0].set_ydata(u[frame])
    if frame<len(e):
        line3[0].set_ydata(e[frame])
    if frame<len(p):
        line4[0].set_ydata(p[frame])

    fig.suptitle(f"{round(t[frame] * 10**3, 4)} ms")


    return (line1, line2, line3, line4)

ax[0][0].grid()
ax[0][1].grid()
ax[1][0].grid()
ax[1][1].grid()

ax[0][0].set_title("rho кг/м3")
ax[0][1].set_title("u м/с")
ax[1][0].set_title("e кДж/кг")
ax[1][1].set_title("P aтм")

min_t, max_t = 0, 15.5 #ms
idx_0, idx_1, di = (np.abs(t - min_t/10**3)).argmin(), (np.abs(t - max_t/10**3)).argmin(), 1
# idx_0, idx_1, di = 0, len(rho), 100

# rho = np.where(np.isnan(rho), 0, rho)
# u = np.where(np.isnan(u), 0, u)
# e= np.where(np.isnan(e), 0, e)
# p= np.where(np.isnan(p), 0, p)
ax[0][0].set_ylim((np.min(rho[idx_0:idx_1:di]), np.max(rho[idx_0:idx_1:di])*1.1))
ax[0][1].set_ylim((np.min(u[idx_0:idx_1:di]), np.max(u[idx_0:idx_1:di])*1.1))
ax[1][0].set_ylim((np.min(e[idx_0:idx_1:di]), np.max(e[idx_0:idx_1:di])*1.1))
ax[1][1].set_ylim((np.min(p[idx_0:idx_1:di]), np.max(p[idx_0:idx_1:di])*1.1))
fig.set_size_inches(10,8)


ani = anim.FuncAnimation(fig, update, frames=range(idx_0, idx_1, di), interval=1, repeat_delay=5000)
ani.save("../riman_1.gif")
plt.show()
