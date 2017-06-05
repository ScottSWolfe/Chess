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

const string Rook::getSymbol() const {
    return ROOK_SYMBOL;
}

vector<Move> Rook::getAvailableMoves(const GameState &state, Position pos) const {
    vector<Move> moves;
    getStraightMoves(moves, state, pos);
    return moves;
}

void Rook::addMoveEffect(const GameState &state, Move &move) const {
    return;
}
