from math import  exp

def factorial(n):
    if n == 0: return 1
    return factorial(n-1) * n

for i in range(100):
    if 1/factorial(2*i+1) <= 10**-3:
        print(i, " < Номер последнего члена для удовлетворительной точности sin t [0,1]")
        break
for i in range(100):
    if 11**(2*i+1)/factorial(2*i+1) <= 10**-3:
        print(i, " < Номер последнего члена для удовлетворительной точности sin t [10,11]")
        break

for i in range(100):
    if exp(1)/factorial(i) <= 10**-3:
        print(i, " < Номер последнего члена для удовлетворительной точности e t [0,1]")
        break

for i in range(100):
    if exp(11)*11**(i)/factorial(i) <= 10**-3:
        print(i, " < Номер последнего члена для удовлетворительной точности e t [10,11]")
        break