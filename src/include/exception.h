#ifndef MAZE_EXCEPTION_H
#define MAZE_EXCEPTION_H

#include <exception>
#include <string>

struct MazeException : public std::exception {

    std::string content{""};
    const char *what() const throw() { return content.c_str(); }
};

#endif
