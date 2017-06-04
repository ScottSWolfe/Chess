#include <vector>
#include "ChessDebug.h"
#include "GameState.h"
#include "Pawn.h"
#include "Move.h"
#include "MoveEffect.h"
#include "Position.h"
#include "Queen.h"
using namespace std;


Pawn::Pawn(PieceColor color)
    : Piece(color)
{}

unique_ptr<const Piece> Pawn::getCopy() const {
    return make_unique<const Pawn>(color);
}

const string Pawn::getSymbol() const {
    return PAWN_SYMBOL;
}

vector<Move> Pawn::getAvailableMoves(const GameState &state, Position start) const {
    vector<Move> moves;
    addOneSquareMove(moves, state, start);
    addTwoSquareMove(moves, state, start);
    addDiagonalMoves(moves, state, start);
    addEnPassantMove(moves, state, start);
    return moves;
}

void Pawn::addOneSquareMove(vector<Move> &moves, const GameState &state, Position start) const {
    Position end = start.add(0, step());
    if (state.inBounds(end) == true && state.isPiece(end) == false) {
        Move move(start, end);
        addPromotionMoveEffect(state, move);
        moves.push_back(move);
    }
}

void Pawn::addTwoSquareMove(vector<Move> &moves, const GameState &state, Position start) const {
    if (start.y == startRow(state.getBoardDimension())) {
        Position step_1 = start.add(0, step());
        Position step_2 = start.add(0, 2 * step());
        if (state.inBounds(step_2) &&
            state.isPiece(step_1) == false && state.isPiece(step_2) == false)
        {
            moves.push_back(Move(start, step_2));
        }
    }
}

void Pawn::addDiagonalMoves(vector<Move> &moves, const GameState &state, Position start) const {
    addDiagonalMove(moves, state, start, -1);
    addDiagonalMove(moves, state, start,  1);
}

void Pawn::addDiagonalMove(vector<Move> &moves, const GameState &state, Position start, int delta_x) const {
    Position end = start.add(delta_x, step());
    if (state.inBounds(end) && state.isPiece(end) && state.isOppPieceColor(end, color)) {
        Move move(start, end);
        addPromotionMoveEffect(state, move);
        moves.push_back(move);
    }
}

void Pawn::addEnPassantMove(vector<Move> &moves, const GameState state, Position start) const {
    int delta_x = 0;
    if (isEnPassantAvailable(state, start, delta_x)) {
        Position end = start.add(delta_x, step());
        Position pos_piece_to_remove = start.add(delta_x, 0);
        auto effect = make_unique<const MoveEffect>(pos_piece_to_remove, MoveEffectType::EN_PASSANT);
        moves.push_back(Move(start, end, effect));
    }
}

bool Pawn::isEnPassantAvailable(const GameState &state, Position start, int &dst_delta_x) const {
    if (start.y == enPassantRow(state.getBoardDimension())) {
        const Move *last_move = state.getLastMove();
        if (last_move != nullptr) {
            Position last_move_start = last_move->getStart();
            Position last_move_end = last_move->getEnd();
            if (last_move_end == start.add(1, 0) || last_move_end == start.add(-1, 0)) {
                if (dynamic_cast<const Pawn*>(state.getPiece(last_move_end))) {
                    dst_delta_x = last_move_end.x - start.x;
                    if (last_move_start == start.add(dst_delta_x, 2 * step())) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void Pawn::addMoveEffect(const GameState &state, Move &move) const {
    addEnPassantMoveEffect(state, move);
    addPromotionMoveEffect(state, move);
}

bool Pawn::addEnPassantMoveEffect(const GameState &state, Move &move) const {
    Position start = move.getStart();
    int delta_x = 0;
    if (isEnPassantAvailable(state, start, delta_x)) {
        Position end = start.add(delta_x, step());
        Position piece_to_remove = start.add(delta_x, 0);
        auto effect = make_unique<const MoveEffect>(piece_to_remove, MoveEffectType::EN_PASSANT);
        move = Move(start, end, effect);
        return true;
    }
    return false;
}

bool Pawn::addPromotionMoveEffect(const GameState &state, Move &move) const {
    if (move.getEnd().y == promotionRow(state.getBoardDimension())) {
        if (state.inBounds(move.getEnd())) {
            // TODO add request to player for choice of piece
            unique_ptr<const Piece> queen = make_unique<const Queen>(state.getPieceColor(move.getStart()));
            unique_ptr<const MoveEffect> effect = make_unique<const MoveEffect>(move.getEnd(), queen, MoveEffectType::PROMOTION);
            move = Move(move.getStart(), move.getEnd(), effect);
            return true;
        }
    }
    return false;
}

int Pawn::step() const {
    if (color == PieceColor::BLACK) {
        return -1;
    }
    return 1;
}

int Pawn::startRow(int dimension) const {
    if (getColor() == PieceColor::BLACK) {
        return dimension - 2;
    }
    return 1;
}

int Pawn::enPassantRow(int dimension) const {
    if (getColor() == PieceColor::BLACK) {
        return 3;
    }
    return dimension - 4;
}

int Pawn::promotionRow(int dimension) const {
    if (getColor() == PieceColor::BLACK) {
        return 0;
    }
    return dimension - 1;
}
