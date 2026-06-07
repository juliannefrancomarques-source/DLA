import numpy as np
import matplotlib.pyplot as plt

space=np.loadtxt('space.txt')
plt.figure(figsize=(10,10))
plt.imshow(space, cmap='gray_r', origin='lower')
plt.title('Visualization ')
plt.xlabel('colonnes')
plt.ylabel('lignes')
plt.show()  