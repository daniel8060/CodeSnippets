import pyglet 

from gameOfLife import GameOfLife

class Window(pyglet.window.Window):
    def __init__(self, windowWidth=1280 ,windowHeight=720):
        super().__init__(windowWidth,windowHeight)
        self.gameofLife = GameOfLife(self.get_size()[0],
                                     self.get_size()[1],
                                     20,
                                     .23)
        pyglet.clock.schedule_interval(self.update,1.0/10);
        

    def on_draw(self):
        self.clear()  
        self.gameofLife.draw()
        

    def update (self,dt):
        self.gameofLife.run_rules()


if __name__ == '__main__':
    window = Window()
    pyglet.app.run()
    