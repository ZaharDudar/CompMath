import matplotlib.pyplot as plt
import numpy as np
from matplotlib.animation import FuncAnimation


L = 1
h = 0.001
tau = 0.01
N = int(L/h) + 1
print(N)
u0 = []
x = np.linspace(0, L, N)
kappa=1*10**-5

for i in range(N//2):
    u0.append(1000)
for i in range(N//2, N):
    u0.append(300)
def calc(uInp):
    u = np.zeros_like(uInp)
    # for i in range(1, N-1):
    #     u[i] = (uInp[i+1] - 2*uInp[i] + uInp[i-1]) * kappa / h**2 * tau + uInp[i]
        # print(i, uInp[i], u[i],"f",(uInp[i+1] - 2*uInp[i] + uInp[i-1]))

    u[1:-1] = (uInp[2:] - 2*uInp[1:-1] + uInp[:-2]) * kappa / h**2 * tau + uInp[1:-1]
    u[0] = u[1]
    u[N-1]= u[N-2]
    return u

fig, ax = plt.subplots()

lin = ax.plot(x, u0, 'o--')

u = np.array(u0, dtype=float)
def update(frame):
    global u
    if frame == 0:
        u = np.array(u0, dtype=float)
    u1 = calc(u)
    lin[0].set_ydata(u1)
    plt.title(f"{round(frame * tau, 2)} сек")
    u = u1
    return (lin)

plt.grid()
anim = FuncAnimation(fig, update, frames=range(5000), interval=0.01)
plt.show()