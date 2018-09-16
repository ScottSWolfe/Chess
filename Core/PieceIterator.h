#pragma once

#include "Board.h"
#include "Piece.h"
#include "Position.h"

namespace chess {


class PieceIterator {

public:
    PieceIterator(const Board &board, PieceColor color);
    const Piece *next();
    bool hasNext();
    
private:
    const Board &board;
    const PieceColor color;
    Position current_pos;

    void incrementCurrentPosition();

};


}
