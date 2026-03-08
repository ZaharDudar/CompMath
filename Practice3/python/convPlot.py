import matplotlib.pyplot as plt
import numpy as np
from math import sqrt

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
totalTime = 50
totalL = 20

hs = np.array(list(range(1,6))) * 0.1

norma = "C" # C, L1, L2
appA = []
appB = []
#норма C
if norma == "C":
    for i, data in enumerate(dataA):
        delta = 0
        for j, line in enumerate(data):
            x = np.linspace(0,20, len(line))
            delta = max(delta, np.max(np.abs(np.sin(4*np.pi / 20 * (-tB[i][j] + x)) - line)))
        appA.append(delta)

    for i, data in enumerate(dataB):
        delta = 0
        for j, line in enumerate(data):
            x = np.linspace(0,20, len(line))
            delta = max(delta, np.max(np.abs(np.sin(4*np.pi / 20 * (-tB[i][j] + x)) - line)))
        appB.append(delta)

if norma=="L1":
#норма L1
    for i, data in enumerate(dataA):
        delta = 0
        dt = totalTime / len(data)
        for j, line in enumerate(data):
            dh = totalL / len(line)
            x = np.linspace(0,20, len(line))
            delta += np.sum(np.abs(np.sin(4*np.pi / 20 * (-tB[i][j] + x)) - line)) * dh * dt
        appA.append(delta)

    for i, data in enumerate(dataB):
        delta = 0
        dt = totalTime / len(data)
        for j, line in enumerate(data):
            dh = totalL / len(line)
            x = np.linspace(0,20, len(line))
            delta += np.sum(np.abs(np.sin(4*np.pi / 20 * (-tB[i][j] + x)) - line)) * dh * dt
        appB.append(delta)
if norma=="L2":
    #норма L1
    for i, data in enumerate(dataA):
        delta = 0
        dt = totalTime / len(data)
        for j, line in enumerate(data):
            dh = totalL / len(line)
            x = np.linspace(0,20, len(line))
            delta += np.sum(np.abs(np.sin(4*np.pi / 20 * (-tB[i][j] + x)) - line)**2) * dh * dt
        appA.append(sqrt(delta))

    for i, data in enumerate(dataB):
        delta = 0
        dt = totalTime / len(data)
        for j, line in enumerate(data):
            dh = totalL / len(line)
            x = np.linspace(0,20, len(line))
            delta += np.sum(np.abs(np.sin(4*np.pi / 20 * (-tB[i][j] + x)) - line)**2) * dh * dt
        appB.append(sqrt(float(delta)))

# print(appA, np.log(appA), np.log(np.log(appA)))
# appA = np.abs(np.log(np.abs(np.log(appA))))
# appB = np.abs(np.log(np.abs(np.log(appB))))
appA = np.log(appA)
appB = np.log(appB)
ax[0].plot(hs, appA, 'o')
ax[1].plot(hs, appB, 'o')

pA = np.polyfit(hs, appA, 1)
ax[0].plot(hs, np.polyval(pA, hs))
pB = np.polyfit(hs, appB, 1)
ax[1].plot(hs, np.polyval(pB, hs))
print(f"{norma} a {pA[0]}, {norma} b {pB[0]}")


# ax[0].set_yscale('log')
# ax[1].set_yscale('log')

ax[0].grid()
ax[1].grid()

ax[0].set_title("A")
ax[1].set_title("B")


# ax[0].set_ylim((np.min([np.min(d) for d in dataA]) * 1.5, np.max([np.max(d) for d in dataA]) * 1.5))
# ax[1].set_ylim((np.min([np.min(d) for d in dataB]) * 1.5, np.max([np.max(d) for d in dataB]) * 1.5))

# fig.set_size_inches(10,8)

# ani.save("../XIV.gif")
plt.show()
