import matplotlib.pyplot as plt
import matplotlib.animation as anim
import numpy as np

rho1 = np.loadtxt("./output/RIMAN_1_rho.csv", delimiter=',')
u1 = np.loadtxt("./output/RIMAN_1_u.csv", delimiter=',')
e1 = np.loadtxt("./output/RIMAN_1_e.csv", delimiter=',') / 10**3
p1 = np.loadtxt("./output/RIMAN_1_p.csv", delimiter=',') / 10**5
t1 = np.loadtxt("./output/RIMAN_1_t.csv", delimiter=',')

rho2 = np.loadtxt("./output/RIMAN_HLLc_1_rho.csv", delimiter=',')
u2 = np.loadtxt("./output/RIMAN_HLLc_1_u.csv", delimiter=',')
e2 = np.loadtxt("./output/RIMAN_HLLc_1_e.csv", delimiter=',') / 10**3
p2 = np.loadtxt("./output/RIMAN_HLLc_1_p.csv", delimiter=',') / 10**5
t2 = np.loadtxt("./output/RIMAN_HLLc_1_t.csv", delimiter=',')

rho3 = np.loadtxt("../../Practice3/python/output/RIMAN_1_rho.csv", delimiter=',')
u3 = np.loadtxt("../../Practice3/python/output/RIMAN_1_u.csv", delimiter=',')
e3 = np.loadtxt("../../Practice3/python/output/RIMAN_1_e.csv", delimiter=',') / 10**3
p3 = np.loadtxt("../../Practice3/python/output/RIMAN_1_p.csv", delimiter=',') / 10**5
t3 = np.loadtxt("../../Practice3/python/output/RIMAN_1_t.csv", delimiter=',')


fig, ax = plt.subplots(2, 2)
# print(rho)
x = np.linspace(-10, 10, len(rho1[0]))

linestyle = "--"

line1hll = ax[0][0].plot(x, x * 0, linestyle, label="HLL")
line1hllc = ax[0][0].plot(x, x * 0, linestyle, label="HLLc")
line1kir = ax[0][0].plot(x, x * 0, linestyle, label="КИР")
line2hll = ax[0][1].plot(x, x * 0, linestyle)
line2hllc = ax[0][1].plot(x, x * 0, linestyle)
line2kir = ax[0][1].plot(x, x * 0, linestyle)

line3hll = ax[1][0].plot(x, x * 0, linestyle)
line3hllc = ax[1][0].plot(x, x * 0, linestyle)
line3kir = ax[1][0].plot(x, x * 0, linestyle)
line4hll = ax[1][1].plot(x, x * 0, linestyle)
line4hllc = ax[1][1].plot(x, x * 0, linestyle)
line4kir = ax[1][1].plot(x, x * 0, linestyle)
def update(frame):
    if frame<len(rho1):
        line1hll[0].set_ydata(rho1[frame])
    if frame<len(rho2):
        line1hllc[0].set_ydata(rho2[frame])
    if frame<len(rho3):
        line1kir[0].set_ydata(rho3[frame])

    if frame<len(u1):
        line2hll[0].set_ydata(u1[frame])
    if frame<len(u2):
        line2hllc[0].set_ydata(u2[frame])
    if frame<len(u3):
        line2kir[0].set_ydata(u3[frame])

    if frame<len(e1):
        line3hll[0].set_ydata(e1[frame])
    if frame<len(e2):
        line3hllc[0].set_ydata(e2[frame])
    if frame<len(e3):
        line3kir[0].set_ydata(e3[frame])

    if frame<len(p1):
        line4hll[0].set_ydata(p1[frame])
    if frame<len(p2):
        line4hllc[0].set_ydata(p2[frame])
    if frame<len(p3):
        line4kir[0].set_ydata(p3[frame])

    fig.suptitle(f"{round(t1[frame] * 10**3, 4)} ms")


    return (line1hll, line1hllc, line1kir,
            line2hll, line2hllc, line2kir,
            line3hll, line3hllc, line3kir,
            line4hll, line4hllc, line4kir)

ax[0][0].grid()
ax[0][1].grid()
ax[1][0].grid()
ax[1][1].grid()

ax[0][0].set_title("rho кг/м3")
ax[0][1].set_title("u м/с")
ax[1][0].set_title("e кДж/кг")
ax[1][1].set_title("P aтм")

min_t, max_t = 0, 15.5 #ms
idx_0, idx_1 = (np.abs(t1 - min_t/10**3)).argmin(), (np.abs(t1 - max_t/10**3)).argmin()
# idx_0, idx_1, di = 0, len(rho), 100

# rho = np.where(np.isnan(rho), 0, rho)
# u = np.where(np.isnan(u), 0, u)
# e= np.where(np.isnan(e), 0, e)
# p= np.where(np.isnan(p), 0, p)
ax[0][0].legend()
ax[0][0].set_ylim((np.min(rho1[idx_0:idx_1]), np.max(rho1[idx_0:idx_1])*1.1))
ax[0][1].set_ylim((np.min(u1[idx_0:idx_1]), np.max(u1[idx_0:idx_1])*1.1))
ax[1][0].set_ylim((np.min(e1[idx_0:idx_1]), np.max(e1[idx_0:idx_1])*1.1))
ax[1][1].set_ylim((np.min(p1[idx_0:idx_1]), np.max(p1[idx_0:idx_1])*1.1))
fig.set_size_inches(10,8)


ani = anim.FuncAnimation(fig, update, frames=range(idx_0, idx_1), interval=5, repeat_delay=5000)
# ani.save("../riman_1.gif")
plt.show()
