#include <vector>
#include "Board.h"
#include "ChessDebug.h"
#include "GameState.h"
#include "Move.h"
#include "Position.h"
#include "Queen.h"
using namespace std;

namespace chess {


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

vector<Position> Queen::getSquaresAttacked(const Board &board, Position start) const {
    vector<Position> positions;
    getStraightSquaresAttacked(positions, board, start);
    getDiagonalSquaresAttacked(positions, board, start);
    return positions;
}

void Queen::addMoveEffect(const GameState &state, Move &move) const {
    return;
}


}
