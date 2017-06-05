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

vector<Move> Queen::getAvailableMoves(const GameState &state, Position pos) const {
    vector<Move> moves;
    getStraightMoves(moves, state, pos);
    getDiagonalMoves(moves, state, pos);
    return moves;
}

void Queen::addMoveEffect(const GameState &state, Move &move) const {
    return;
}
