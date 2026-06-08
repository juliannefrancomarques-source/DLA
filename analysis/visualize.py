import numpy as np
import matplotlib.pyplot as plt

space=np.loadtxt('space.txt')
size_x,size_y,size_z=100,100,100
space=space.reshape((size_x,size_y,size_z))

fig=plt.figure(figsize=(10,10))
ax = fig.add_subplot(111, projection='3d')
x, y, z = np.where(space == 1)

scat=ax.scatter(x, y, z, c=z, cmap='viridis', s=20, marker='o')

cbar = plt.colorbar(scat, ax=ax, shrink=0.6, pad=0.1)
cbar.set_label('Hauteur de la particule (Axe Z)', fontsize=12)

plt.title('Visualization ')

ax.set_xlabel('Axe Y (Devant / Derrière)') 
ax.set_zlabel('Axe Z (Haut / Bas)') 
ax.set_ylabel('Axe X (Gauche / Droite)')
plt.show()        