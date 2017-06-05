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

const string Bishop::getSymbol() const {
    return BISHOP_SYMBOL;
}

vector<Move> Bishop::getAvailableMoves(const GameState &state, Position pos) const {
    vector<Move> moves;
    getDiagonalMoves(moves, state, pos);
    return moves;
}

void Bishop::addMoveEffect(const GameState &state, Move &move) const {
    return;
}
