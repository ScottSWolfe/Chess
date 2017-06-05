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

PieceType King::getType() const {
    return PieceType::KING;
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
    int dimension = state.getBoardDimension();
    int castle_column = castleColumn(delta_x, dimension);
    Position rook_position;
    if (canCastle(state, start, delta_x, rook_position)) {
        Position end(castle_column, start.y);
        // TODO add castle move effect
        Move move(start, end);
        moves.push_back(move);
    }
}

void King::addMoveEffect(const GameState &state, Move &move) const {
    if (hasMoved() == true) {
        return;
    }
    Position start = move.getStart();
    Position end = move.getEnd();
    int delta_x;
    if (start.x - end.x == 0) {
        return;
    }
    if (start.x - end.x < 0) {
        delta_x = 1;
    }
    if (start.x - end.x > 0) {
        delta_x = -1;
    }
    Position rook_position;
    if (canCastle(state, start, delta_x, rook_position)) {
        // add move effect to move
    }
}

bool King::canCastle(const GameState &state, Position start, int delta_x, Position &rook_position) const {
    int dimension = state.getBoardDimension();
    int castle_column = castleColumn(delta_x, dimension);
    Position pos = start.add(delta_x, 0);
    int distance = abs(pos.x - castle_column);
    while (distance >= 0 && rook_position.empty()) {
        if (state.isPiece(pos)) {
            if (state.getPieceType(pos) != PieceType::ROOK) {
                return false;
            }
            else if (state.hasPieceMoved(pos)) {
                return false;
            }
            else if (rook_position.empty() == false) {
                return false;
            }
            rook_position = pos;
        }
        pos = pos.add(delta_x, 0);
        distance = abs(pos.x - castle_column);
    }
    if (rook_position.empty()) {
        return false;
    }
    return true;
}

int King::castleColumn(int direction, int dimension) const {
    if (direction >= 0) {
        return dimension - 2;
    }
    else {
        return 2;
    }
}
