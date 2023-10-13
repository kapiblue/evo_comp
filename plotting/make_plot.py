import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

instancePath = "../lab1/TSPA.csv"
edgesPath = "./edges.csv"

# Read raw Instance
instance = pd.read_csv(instancePath, sep=';', header=None).T.to_numpy()
xs, ys, costs = instance
# Read generated edges
edges = pd.read_csv(edgesPath, sep=';', header=None).to_numpy()

colors = ['red', 'green', 'blue', 'black']
fig, axs = plt.subplots(2, 2, figsize=(20, 10), dpi = 200)
fig.suptitle('Alg 1', fontsize=20)

for i, ax in enumerate(axs.flat):
    # Plot coords
    ax.scatter(xs, ys, s=costs/10)
    # Plot edges
    for idx1, idx2 in edges:
        ax.plot([xs[idx1], xs[idx2]], [ys[idx1], ys[idx2]], 
                 color=colors[i])
    
    ax.set_title(f"Instance {i}")
    ax.set(xlabel='x', ylabel='y')
    ax.label_outer()
# Save
fig.savefig('plot.jpg')