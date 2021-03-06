#include "maze.h"
#include <iostream>
#include <stdexcept>

Maze::Maze(uint32_t height_, uint32_t width_) {
    height = height_;
    width = width_;
    matrix = new uint32_t *[height];
    for (size_t i = 0; i < height; i++) {
        matrix[i] = new uint32_t[width];
    }
}

Maze::~Maze() {
    for (size_t i = 0; i < height; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void Maze::clear() {

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            matrix[i][j] = floor;
        }
    }
};

uint32_t **Maze::gen(int wall_rate_percent) {

    srand(time(NULL));
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            if (std::rand() % 100 <= wall_rate_percent) {
                matrix[i][j] = wall;
            } else {
                matrix[i][j] = floor;
            }
        }
    }
    return matrix;
}

void Maze::try_to_gen(int wall_rate_percent, int max_retries) {
    int retry = 0;
    while (retry < max_retries) {
        Maze::clear();
        Maze::gen(wall_rate_percent);
        if (Maze::is_valid()) {
            return;
        }
        retry += 1;
    }
    throw std::invalid_argument(
        "It couldn't generate a valid maze with wall_rate_percent: " +
        std::string(std::to_string(wall_rate_percent)) +
        " max_retries: " + std::string(std::to_string(max_retries)));
}

std::pair<int, int> Maze::find_first_floor() {
    std::pair<int, int> first_pair;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (matrix[i][j] != wall) {
                return std::pair<int, int>{i, j};
            }
        }
    }
    throw std::invalid_argument("It couldn't find any floor cell");
}

bool Maze::has_floor_islands(const std::pair<int, int> &first_position) {
    auto positions = std::vector<std::pair<int, int>>{first_position};
    Maze::dfs(positions);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (matrix[i][j] == floor) {
                return true;
            }
        }
    }
    return false;
}

bool Maze::is_valid() {
    return !Maze::has_floor_islands(Maze::find_first_floor());
}

void Maze::dfs(std::vector<std::pair<int, int>> &positions) {
    if (positions.size() == 0) {
        return;
    }

    auto pos = positions.back();
    if (matrix[pos.first][pos.second] == wall) {
        throw std::invalid_argument(
            "The vector positions can't be a wall type. i: " +
            std::string(std::to_string(pos.first)) +
            " j: " + std::string(std::to_string(pos.second)));
    }

    matrix[pos.first][pos.second] = floor_visited;
    positions.pop_back();
    for (auto &i : Maze::floor_neighbors(pos)) {
        if (matrix[i.first][i.second] == wall) {
            continue;
        }
        if (matrix[i.first][i.second] == floor) {
            matrix[i.first][i.second] = floor_visited;
            positions.push_back(std::pair<int, int>(i.first, i.second));
        }
    }
    Maze::dfs(positions);
}

std::vector<std::pair<int, int>>
Maze::floor_neighbors(const std::pair<int, int> &pos) {
    return Maze::floor_neighbors(pos.first, pos.second);
}

std::vector<std::pair<int, int>> Maze::floor_neighbors(int i, int j) {

    auto pairs = std::vector<std::pair<int, int>>{};

    if ((i + 1) < height) {
        pairs.push_back(std::pair<int, int>{i + 1, j});
    }
    if ((i - 1) > -1) {
        pairs.push_back(std::pair<int, int>{i - 1, j});
    }
    if ((j + 1) < width) {
        pairs.push_back(std::pair<int, int>{i, j + 1});
    }
    if ((j - 1) > -1) {
        pairs.push_back(std::pair<int, int>{i, j - 1});
    }

    return pairs;
}

void Maze::print() {

    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            std::cout << matrix[i][j];
        }
        std::cout << std::endl;
    }
}
