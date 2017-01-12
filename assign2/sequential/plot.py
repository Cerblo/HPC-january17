import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D as ax
from matplotlib import cm

import numpy as np


#fig = plt.figure()
# The text file has to be structured as 'i j '

path1 = 'results_jac.txt'

f1 = open(path1,'r')
g = f1.read().split('\n')[:-1] # List of rows

x1 = np.array([float(i.split()[0]) for i in g])
y1 = np.array([float(i.split()[1]) for i in g])

plt.semilogx(x1,y1,'r',label='Jacobi method')

path2='results_gauss.txt'

f2 = open(path2,'r')
g = f2.read().split('\n')[:-1] # List of rows

y2 = np.array([float(i.split()[1]) for i in g])
x2 = range(len(y2))

plt.semilogx(x2,y2,'b',label='Gauss-Seidel method')
lim = y1[1]
plt.legend()
plt.ylim(0, lim)

plt.xlabel("Number of iterations")
plt.ylabel("Error") 
plt.title("Convergence behavior of Jacobi and Gauss Seidel methods.")
plt.show()
