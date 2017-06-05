#include <vector>
#include "ChessDebug.h"
#include "GameState.h"
#include "Knight.h"
#include "Move.h"
#include "Position.h"
using namespace std;


Knight::Knight(PieceColor color) : Piece(color) {}

std::unique_ptr<Piece> Knight::getCopy() const {
    return make_unique<Knight>(*this);
}

PieceType Knight::getType() const {
    return PieceType::KNIGHT;
}

const string Knight::getSymbol() const {
    return KNIGHT_SYMBOL;
}

vector<Move> Knight::getAvailableMoves(const GameState &state, Position start) const {
    vector<Move> moves;
    for (int delta_y = -2; delta_y <= 2; delta_y++) {
        for (int delta_x = -2; delta_x <= 2; delta_x++) {
            if (abs(delta_y) + abs(delta_x) == 3) {
                Position end = start.add(delta_x, delta_y);
                if (state.inBounds(end) && 
                    (state.isPiece(end) == false || state.isOppPieceColor(end, color)))
                {
                    moves.push_back(Move(start, end));
                }
            }
        }
    }
    return moves;
}

void Knight::addMoveEffect(const GameState &state, Move &move) const {
    return;
}
