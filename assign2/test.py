import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D as ax
from matplotlib import cm

import numpy as np

fig = plt.figure()
#ax = fig.add_subplot(111, projection='3d')

# Read the file and outputs 3 list X, Y, Z.
# The text file has to be structured as 'i j value'
path='results.txt'
f=open(path,'r')
g=f.read().split('\n') # List of rows


Z = [[float(j) for j in i.split()] for i in g]
#Z = np.array([[float(j) for j in i.split()] for i in g])
print(Z)

N=len(Z[0])
X_col=np.array(range(N))
X=X_col

for i in range(1,N):
    X=np.vstack((X,X_col))
Y=np.transpose(X)

Z=np.random.rand(N,N)

print(X,X.shape)
print(Y,Y.shape)
print(Z,Z.shape)
# Printing code

plt.imshow(Z)

#ax.plot_surface(X,Y,Z, rstride=1, cstride=1, cmap=cm.coolwarm,
#                       linewidth=0, antialiased=False)
plt.show()
