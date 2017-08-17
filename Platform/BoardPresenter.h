#pragma once

class Board;

namespace chess {


class BoardPresenter {

public:
    virtual void displayBoard(const Board &board) const = 0;

};


}
