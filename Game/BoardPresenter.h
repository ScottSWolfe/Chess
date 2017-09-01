#pragma once

namespace chess {

class Board;


enum class SquareColor { LIGHT, DARK };

class BoardPresenter {

public:
    virtual void displayBoard(const Board &board) const = 0;

};


}
