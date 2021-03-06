#include "maze.h"
#include "maze_renderer.h"

int main() {
    auto maze = Maze(20, 20);
    sf::RenderWindow window(sf::VideoMode(500, 500), "Main window");
    auto renderer = MazeRenderer(&window, &maze);
    int wall_rate_percent = 2;
    maze.try_to_gen(wall_rate_percent);
    renderer.draw();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::N) {
                    maze.try_to_gen(wall_rate_percent);
                    renderer.draw();
                }
                if (event.key.code == sf::Keyboard::Q) {
                    window.clear();
                    window.close();
                    return 0;
                    break;
                }
                break;
            default:
                break;
            }
        }
    }
    return 0;
}
