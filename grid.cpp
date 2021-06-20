#include "grid.h"

int grid::getSize() const {
    return size;
}

entity ***grid::getBoard() const {
    return board;
}

grid::~grid() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (board[i][j] != nullptr) delete board[i][j];
        }
        delete[] board[i];
    }
    delete[] board;
}

grid::grid(int size) : size(size) {
    for (int i = 0; i < size; ++i) {
        board[i] = new entity*[size];
        for (int j = 0; j < size; ++j) {
            board[i][j] = nullptr;
        }
    }
}
