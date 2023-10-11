import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

nodes = pd.read_csv('lab1/TSPA.csv', sep=';', header=None).to_numpy()
xs = nodes[:,0]
ys = nodes[:,1]
costs = nodes[:,2]

tmp1 = pd.read_csv('plotting/file.csv', sep=';', header=None).to_numpy().squeeze()
tmp2 = np.roll(tmp1, 1)
edges = np.stack([tmp1, tmp2]).T

plt.scatter(xs, ys, s=costs/20)

for idx1, idx2 in edges:
    plt.plot([xs[idx1], xs[idx2]], [ys[idx1], ys[idx2]], color='red')


plt.savefig('plotting/plot.jpg')