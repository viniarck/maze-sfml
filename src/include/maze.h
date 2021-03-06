#ifndef MAZE_H
#define MAZE_H

#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <vector>

enum cell_type { wall, floor, floor_visited };

class Maze {
  private:
    std::vector<std::pair<int, int>>
    floor_neighbors(const std::pair<int, int> &pos);
    std::vector<std::pair<int, int>> floor_neighbors(int i, int j);
    void dfs(std::vector<std::pair<int, int>> &positions);
    bool has_floor_islands(const std::pair<int, int> &first_position);
    std::pair<int, int> find_first_floor();
    uint32_t **gen(int wall_rate_percent = 20);
    void clear();

  public:
    uint32_t height;
    uint32_t width;
    uint32_t **matrix;

    Maze(uint32_t height, uint32_t width);
    ~Maze();
    void try_to_gen(int wall_rate_percent = 2, int max_retries = 2000);
    bool is_valid();
    void print();
};

#endif
