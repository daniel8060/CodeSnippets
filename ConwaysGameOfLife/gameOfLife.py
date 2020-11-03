import random as rand
import pyglet

class GameOfLife: 
    def __init__ (self,windowWidth,windowHeight,cellSize,odds):
        self.odds = odds
        self.gridWidth= int(windowWidth/cellSize)
        self.gridHeight= int(windowWidth/cellSize)
        self.cellSize = cellSize
        self.cells = [[0 for row in range(0,self.gridHeight)]for y in range (0,self.gridWidth)]
        self.generate_cells()

    """
    Fills in random cells with 1 ie populates grid with living cells
    """
    def generate_cells (self):
        for row in range (0,self.gridHeight):
            for col in range(0,self.gridWidth): 
                if rand.random() < self.odds: 
                    self.cells[row][col]=1

    """
    Returns value of cell at a given [row][col]
    @param row: Row in which we're interested
    @param col: column in which we're interested
    @return: Either 1 or 0 value of the desired cell
    """
    def getCellVal(self,row,col):
        if row >=0 and row < self.gridHeight and  col>=0 and col < self.gridWidth: 
            return self.cells[row][col]
        return 0
    """
    Returns value of sum of 8 adjacent grid cells. Wraps on boundaries. 
    @param row: Row in which we're interested
    @param col: column in which we're interested
    @return: sum of all adjacent cells 
    """
    def getNeighborhoodVal(self,row,col):
        if row >=0 and row < self.gridHeight and  col>=0 and col < self.gridWidth:
           return     sum([self.getCellVal(row-1,col),   
                       self.getCellVal(row-1,col-1), 
                       self.getCellVal(row,  col-1), 
                       self.getCellVal(row+1,col-1), 
                       self.getCellVal(row+1,  col), 
                       self.getCellVal(row+1,col+1), 
                       self.getCellVal(row,  col+1), 
                       self.getCellVal(row-1,col+1)])
           
        else:
           return 0

    """
     Ruleset for this cellular automaton. 
     We use classical Conway's Game of Life https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
     """
    def run_rules(self):
        newCells = []
        for row in range (0,self.gridHeight):
            newCells.append([])
            for col in range (0,self.gridWidth):
                cell_sum = self.getNeighborhoodVal(row,col)

                if cell_sum==3 and self.cells[row][col] ==0:
                    newCells[row].append(1)
                elif self.cells[row][col]==1 and (cell_sum==2 or cell_sum==3):
                    newCells[row].append(1)
                else:
                    newCells[row].append(0)
        self.cells = newCells 

    def draw(self):
        for row in range (0,self.gridHeight):
            for col in range(0,self.gridWidth):
                if self.cells[row][col]==1: #alive
                    squareCoords = (row*self.cellSize, col*self.cellSize,
                                    row*self.cellSize,col*self.cellSize + self.cellSize,
                                    row*self.cellSize + self.cellSize,col*self.cellSize,
                                    row*self.cellSize + self.cellSize,col*self.cellSize+self.cellSize)
                    pyglet.graphics.draw_indexed(4,pyglet.gl.GL_TRIANGLES,
                                         [0,1,2,1,2,3],
                                         ('v2i',squareCoords))