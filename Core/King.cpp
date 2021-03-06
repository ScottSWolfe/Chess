#include <vector>
#include "Castle.h"
#include "ChessDebug.h"
#include "GameState.h"
#include "King.h"
#include "Move.h"
#include "Position.h"

namespace chess {


King::King(PieceColor color)
    : Piece(color)
{}

std::unique_ptr<Piece> King::getCopy() const {
    return std::make_unique<King>(*this);
}

PieceType King::getType() const {
    return PieceType::KING;
}

const std::string King::getSymbol() const {
    return KING_SYMBOL;
}

std::vector<Move> King::getAvailableMoves(const GameState &state, Position start) const {
    std::vector<Move> moves;
    addAdjacentMoves(moves, state, start);
    addCastleMoves(moves, state, start);
    return moves;
}

std::vector<Position> King::getSquaresAttacked(const Board &board, Position start) const {
    return getAdjacentSquaresAttacked(board, start);
}

std::vector<Position> King::getAdjacentSquaresAttacked(const Board &board, Position start) const {
    std::vector<Position> positions;
    for (int delta_y = -1; delta_y <= 1; delta_y++) {
        for (int delta_x = -1; delta_x <= 1; delta_x++) {
            Position end = start.add(delta_x, delta_y);
            if (board.inBounds(end) &&
                (board.isPiece(end) == false || board.isOppPieceColor(end, color)))
            {
                positions.push_back(end);
            }
        }
    }
    return positions;
}

void King::addAdjacentMoves(std::vector<Move> &moves, const GameState &state, Position start) const {
    std::vector<Position> positions = getAdjacentSquaresAttacked(state.getBoard(), start);
    for (Position end : positions) {
        moves.push_back(Move(start, end));
    }
}

void King::addCastleMoves(std::vector<Move> &moves, const GameState &state, Position start) const {
    addCastleMove(moves, state, start, -1);
    addCastleMove(moves, state, start, 1);
    return;
}

void King::addCastleMove(std::vector<Move> &moves, const GameState &state, Position start, int delta_x) const {
    int dimension = state.getBoardDimension();
    int castle_column = castleColumn(delta_x, dimension);
    Position rook_position;
    if (canCastle(state, start, delta_x, rook_position)) {
        Position end(castle_column, start.y);
        Move move = createMoveWithCastleEffect(start, end, rook_position, delta_x);
        moves.push_back(move);
    }
}

void King::addMoveEffect(const GameState &state, Move &move) const {
    Position start = move.getStart();
    Position end = move.getEnd();
    int delta_x = castleDirection(start.x, end.x);
    Position rook_position;
    if (canCastle(state, start, delta_x, rook_position)) {
        move = createMoveWithCastleEffect(start, end, rook_position, delta_x);
    }
}

Move King::createMoveWithCastleEffect(Position king_start, Position king_end, Position rook_start, int delta_x) const {
    Position rook_end = king_end.add(-delta_x, 0);
    std::unique_ptr<MoveEffect> effect = std::make_unique<Castle>(rook_start, rook_end);
    return Move(king_start, king_end, effect);
}

bool King::canCastle(const GameState &state, Position start, int delta_x, Position &rook_position) const {
    if (delta_x == 0) {
        return false;
    }
    if (delta_x < 0 && !state.isCastlingAvailableKingside()) {
        return false;
    }
    if (delta_x > 0 && !state.isCastlingAvailableQueenside()) {
        return false;
    }

    const int castle_column = castleColumn(delta_x, state.getBoardDimension());
    Position pos = start.add(delta_x, 0);
    int dist = (castle_column - pos.x) * delta_x;
    while ((dist >= 0 || rook_position.empty()) && state.inBounds(pos)) {
        if (state.isPiece(pos)) {
            if (state.getPieceType(pos) != PieceType::ROOK) {
                return false;
            }
            else if (rook_position.empty() == false) {
                return false;
            }
            rook_position = pos;
        }
        if (dist >= 0 && state.isSquareAttacked(pos, color)) {
            return false;
        }
        pos = pos.add(delta_x, 0);
        dist = (castle_column - pos.x) * delta_x;
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

int King::castleDirection(int start, int end) const {
    if (start - end < 0) {
        return 1;
    }
    if (start - end > 0) {
        return -1;
    }
    return 0;
}


}
