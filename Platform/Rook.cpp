#include <vector>
#include "ChessDebug.h"
#include "GameState.h"
#include "Move.h"
#include "Piece.h"
#include "Position.h"
#include "Rook.h"
using namespace std;


Rook::Rook(PieceColor color) : Piece(color) {}

std::unique_ptr<Piece> Rook::getCopy() const {
    return make_unique<Rook>(*this);
}

PieceType Rook::getType() const {
    return PieceType::ROOK;
}

const string Rook::getSymbol() const {
    return ROOK_SYMBOL;
}

vector<Position> Rook::getSquaresAttacked(const GameState &state, Position start) const {
    vector<Position> positions;
    getStraightSquaresAttacked(positions, state, start);
    return positions;
}

void Rook::addMoveEffect(const GameState &state, Move &move) const {
    return;
}
