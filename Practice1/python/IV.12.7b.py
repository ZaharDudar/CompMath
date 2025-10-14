import matplotlib.pyplot as plt
import numpy as np
from math import sqrt, exp

data_x = np.linspace(-5,5,500)
# print(data_x)
h = 1/sqrt(2) * exp(-1/2)
plt.plot(data_x, np.exp(-data_x**2)*data_x)
plt.plot(data_x, np.ones_like(data_x)*h/2)
plt.grid()
plt.show()