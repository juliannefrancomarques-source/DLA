# Diffusion_Limited_Aggragation

A numerical simulation of **dendritic crystal growth** and thin-film deposition using the **DLA (Diffusion-Limited Aggregation)** model. This project uses **C** for the calculations and **Python** for visualization and analysis.

## My approach

To simulate atom deposition, the C program handles the complex physics by causing particles to move randomly until they attach to a central seed to form a branched structure (dendrite). The result of this simulation is then saved to a text file as a matrix of 0s and 1s. Finally, Python retrieves this file to visually map the nanomaterial and analyze its porosity graphically

###Step 1
A random particle moves until it comes into contact with the aggregate and becomes attached to it. (2D-->3D)

###Step 2
-add a probability of attachment 

-In more probable directions (such as gravitational fields), we go down more than we go up
Identify the various factors affecting travel 
