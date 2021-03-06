#ifndef MAZERENDERER_H
#define MAZERENDERER_H

#include "maze.h"
#include <SFML/Graphics.hpp>

class MazeRenderer {
  private:
    sf::RenderWindow *window;
    Maze *maze;
    float square_size;

  public:
    void draw();

    MazeRenderer(sf::RenderWindow *window_, Maze *maze_, float square_size_ = 50.0);
    ~MazeRenderer();
};

#endif
