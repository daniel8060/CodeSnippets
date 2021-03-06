import gameOfLife
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

if __name__ == '__main__':
    length = 400
    width = 400
    size = 20
    thing = gameOfLife.GameOfLife(width,length,size,.23) 
    thing.run_rules() 
    x = np.linspace(int(0-(width/(2*size))),int(0+(width/(2*size))),int(width/size))
    y = np.linspace(int(0-(length/(2*size))),int(0+(length/(2*size))),int(length/size))
    xgrid,ygrid = np.meshgrid(x,y)
    
    print(xgrid)
    print(thing.totalSum)

    fig = plt.figure()
    ax = Axes3D(fig)

    ax.plot_surface(xgrid,ygrid,thing.totalSum)
    plt.show()