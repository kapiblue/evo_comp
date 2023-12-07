from glob import glob
import os

import numpy as np
import pandas as pd

import matplotlib.pyplot as plt

instancesPath = "../instance_data/"
solutionsPath = "../lab7/solutions/"

colors = ['red', 'green', 'blue', 'orange', 'violet']


for instancePath in glob(os.path.join(instancesPath, "*.csv")):
    # Read raw Instance
    instance = pd.read_csv(instancePath, sep=';', header=None).T.to_numpy()
    xs, ys, costs = instance
    
    instanceName = instancePath.split('/')[-1].split('.')[0]
    print(instanceName)
    edges = []
    solutionNames = []
    for edgesPath in sorted(glob(os.path.join(solutionsPath, instanceName, "*.csv"))):
        # Read generated edges
        tmp1 = pd.read_csv(edgesPath, sep=';', header=None).to_numpy().squeeze()
        tmp2 = np.roll(tmp1, 1)
        edges.append(np.stack([tmp1, tmp2]).T)

        solutionNames.append(edgesPath.split('/')[-1].split('.')[0])

    # Make plots
    fig, ax = plt.subplots(1, 1, dpi = 300)
    fig.suptitle(instanceName, fontsize=20)
    
    # Plot coords
    ax.scatter(xs, ys, s=costs/10)
    # Plot edges
    for idx1, idx2 in edges[0]:
        ax.plot([xs[idx1], xs[idx2]], [ys[idx1], ys[idx2]], 
                    color='red')
    
    # ax.set_title(solutionNames[0], fontsize=9)
    ax.set(xlabel='x', ylabel='y')
    ax.label_outer()

    # Save
    fig.savefig(f"../lab7/plots/{instanceName}.jpg")
