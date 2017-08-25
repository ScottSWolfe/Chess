#include <vector>
#include "ChessDebug.h"
#include "Board.h"
#include "GameState.h"
#include "Move.h"
#include "Piece.h"
#include "Position.h"
#include "Rook.h"

namespace chess {


Rook::Rook(PieceColor color) : Piece(color) {}

std::unique_ptr<Piece> Rook::getCopy() const {
    return std::make_unique<Rook>(*this);
}

PieceType Rook::getType() const {
    return PieceType::ROOK;
}

const std::string Rook::getSymbol() const {
    return ROOK_SYMBOL;
}

std::vector<Position> Rook::getSquaresAttacked(const Board &board, Position start) const {
    std::vector<Position> positions;
    getStraightSquaresAttacked(positions, board, start);
    return positions;
}

void Rook::addMoveEffect(const GameState &state, Move &move) const {
    return;
}


}
