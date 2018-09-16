#pragma once

#include <memory>
#include "Piece.h"

namespace chess {

class Board;


class BoardInitializer {

public:
    static Board initializeStandardSetup();

private:
    static void addStandardPieces(Board &board);
    static void addRowOfPawns(Board &board, int row, PieceColor color);
    static void addStandardRowOfPieces(Board &board, int row, PieceColor color);

};


}
