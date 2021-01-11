import gameOfLife
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

class ConwayMap:
    def __init__ (self,dim,widths,heights,odds):
        self.dim= dim
        self.widths = widths
        self.heights = heights
        self.grid = np.zeros([dim*widths,dim*heights],np.float32)

        self.generateGrid() 


    

    def generateGrid(self):
        for i in range (0,self.dim):
            for j in range (0,self.dim):
              game = gameOfLife.GameOfLife(self.widths,self.heights,.23)
              game.run_rules()
              self.grid[i*self.heights:(i+1)*(self.heights),
                        j*self.widths:(j+1)*(self.widths)] = game.totalSum
    
    def display(self): 
        x = np.linspace(int(0-(self.widths*self.dim/2)),int(0+(self.widths*self.dim/2)),int(self.widths*self.dim))
        y = np.linspace(int(0-(self.heights*self.dim/2)),int(0+(self.heights*self.dim/2)),int(self.heights*self.dim))
        xgrid,ygrid = np.meshgrid(x,y)
    
      

        fig = plt.figure()
        ax = Axes3D(fig)

        #sea level
        ax.plot_surface(xgrid,ygrid,
                       -1*2* np.ones((int(self.widths*self.dim),int(self.heights*self.dim)))
                        )
        #land
        ax.plot_surface(xgrid,ygrid,self.grid)


        plt.show()