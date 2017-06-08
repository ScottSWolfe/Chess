#include <vector>
#include "ChessDebug.h"
#include "Bishop.h"
#include "GameState.h"
#include "Move.h"
#include "Position.h"
using namespace std;


Bishop::Bishop(PieceColor color) : Piece(color) {}

std::unique_ptr<Piece> Bishop::getCopy() const {
    return make_unique<Bishop>(*this);
}

PieceType Bishop::getType() const {
    return PieceType::BISHOP;
}

const string Bishop::getSymbol() const {
    return BISHOP_SYMBOL;
}

std::vector<Position> Bishop::getSquaresAttacked(const GameState &state, Position start) const {
    vector<Position> positions;
    getDiagonalSquaresAttacked(positions, state, start);
    return positions;
}

void Bishop::addMoveEffect(const GameState &state, Move &move) const {
    return;
}
