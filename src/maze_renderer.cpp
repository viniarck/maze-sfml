#include "maze_renderer.h"

MazeRenderer::MazeRenderer(sf::RenderWindow *window_, Maze *maze_, float square_size_) {
    window = window_;
    maze = maze_;
    square_size = square_size_;
}

void MazeRenderer::draw() {
    window->clear();
    for (size_t i = 0; i < maze->height; i++) {
        for (size_t j = 0; j < maze->width; j++) {
            sf::RectangleShape shape({square_size, square_size});
            if (maze->matrix[i][j] == wall) {
                shape.setFillColor(sf::Color::Black);
            } else {
                shape.setFillColor(sf::Color::Cyan);
            }
            shape.setOutlineThickness(2);
            shape.setPosition(i * square_size, j * square_size);
            window->draw(shape);
        }
    }
    window->display();
}

MazeRenderer::~MazeRenderer() {
    window = nullptr;
    maze = nullptr;
}
