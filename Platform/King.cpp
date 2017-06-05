#include <vector>
#include "ChessDebug.h"
#include "GameState.h"
#include "King.h"
#include "Move.h"
#include "Position.h"
using namespace std;


King::King(PieceColor color)
    : Piece(color)
{}

std::unique_ptr<Piece> King::getCopy() const {
    return make_unique<King>(*this);
}

const string King::getSymbol() const {
    return KING_SYMBOL;
}

vector<Move> King::getAvailableMoves(const GameState &state, Position start) const {
    vector<Move> moves;
    addAdjacentMoves(moves, state, start);
    addCastleMoves(moves, state, start);
    return moves;
}

void King::addAdjacentMoves(vector<Move> &moves, const GameState &state, Position start) const {
    for (int delta_y = -1; delta_y <= 1; delta_y++) {
        for (int delta_x = -1; delta_x <= 1; delta_x++) {
            Position end = start.add(delta_x, delta_y);
            if (state.inBounds(end) &&
                (state.isPiece(end) == false || state.isOppPieceColor(end, color)))
            {
                moves.push_back(Move(start, end));
            }
        }
    }
}

void King::addCastleMoves(vector<Move> &moves, const GameState &state, Position start) const {
    if (hasMoved() == true) {
        return;
    }
    addCastleMove(moves, state, start, -1);
    addCastleMove(moves, state, start, 1);
    return;
}

void King::addCastleMove(vector<Move> &moves, const GameState &state, Position start, int delta_x) const {
    return;
    /*
    int dimension = state.getBoardDimension();
    int castle_column = castleColumn(delta_x, dimension);
    Position rook_pos;
    Position pos = start.add(delta_x, 0);
    int distance = abs(pos.x - castle_column);
    while (distance >= 0) {
        if (state.isPiece(pos)) {
            if (state.getPieceType(pos) != PieceType::ROOK) {
                return;
            }
            else if (state.hasPieceMoved(pos)) {
                return;
            }
            else if (rook_pos.empty() == false) {
                return;
            }
            rook_pos = pos;
        }
        pos = pos.add(delta_x, 0);
    }
    // continue checking squares until out of bounds or rook_pos is not empty
    Position end(castle_column, start.y);
    MoveEffect effect(rook_pos, MoveEffectType::CASTLE);
    Move move(start, end, effect);
    */
}

void King::addMoveEffect(const GameState &state, Move &move) const {
    // TODO check for castle
    return;
}

int King::castleColumn(int direction, int dimension) const {
    if (direction >= 0) {
        return dimension - 2;
    }
    else {
        return 2;
    }
}
