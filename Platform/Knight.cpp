#include <vector>
#include "Board.h"
#include "ChessDebug.h"
#include "GameState.h"
#include "Knight.h"
#include "Move.h"
#include "Position.h"

namespace chess {


Knight::Knight(PieceColor color) : Piece(color) {}

std::unique_ptr<Piece> Knight::getCopy() const {
    return std::make_unique<Knight>(*this);
}

PieceType Knight::getType() const {
    return PieceType::KNIGHT;
}

const std::string Knight::getSymbol() const {
    return KNIGHT_SYMBOL;
}

std::vector<Position> Knight::getSquaresAttacked(const Board &board, Position start) const {
    std::vector<Position> positions;
    for (int delta_y = -2; delta_y <= 2; delta_y++) {
        for (int delta_x = -2; delta_x <= 2; delta_x++) {
            if (abs(delta_y) + abs(delta_x) == 3) {
                Position end = start.add(delta_x, delta_y);
                if (board.inBounds(end) &&
                   (board.isPiece(end) == false || board.isOppPieceColor(end, color)))
                {
                    positions.push_back(end);
                }
            }
        }
    }
    return positions;
}

void Knight::addMoveEffect(const GameState &state, Move &move) const {
    return;
}


}
