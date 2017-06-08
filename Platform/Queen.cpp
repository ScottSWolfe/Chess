#include <vector>
#include "ChessDebug.h"
#include "GameState.h"
#include "Move.h"
#include "Position.h"
#include "Queen.h"
using namespace std;


Queen::Queen(PieceColor color) : Piece(color) {}

std::unique_ptr<Piece> Queen::getCopy() const {
    return make_unique<Queen>(*this);
}

PieceType Queen::getType() const {
    return PieceType::QUEEN;
}

const string Queen::getSymbol() const {
    return QUEEN_SYMBOL;
}

vector<Position> Queen::getSquaresAttacked(const GameState &state, Position start) const {
    vector<Position> positions;
    getStraightSquaresAttacked(positions, state, start);
    getDiagonalSquaresAttacked(positions, state, start);
    return positions;
}

void Queen::addMoveEffect(const GameState &state, Move &move) const {
    return;
}
