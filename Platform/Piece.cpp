#include <memory>
#include <string>
#include <vector>
#include "ChessDebug.h"
#include "Bishop.h"
#include "GameState.h"
#include "Knight.h"
#include "King.h"
#include "Move.h"
#include "MoveValidator.h"
#include "Pawn.h"
#include "Position.h"
#include "Piece.h"
#include "Queen.h"
#include "Rook.h"
using namespace std;


const std::string Piece::PAWN_SYMBOL = "p";
const std::string Piece::ROOK_SYMBOL = "R";
const std::string Piece::BISHOP_SYMBOL = "B";
const std::string Piece::KNIGHT_SYMBOL = "N";
const std::string Piece::QUEEN_SYMBOL = "Q";
const std::string Piece::KING_SYMBOL = "K";

Piece::Piece(PieceColor piece_color)
    : color(piece_color)
{}

PieceColor Piece::getColor() const {
    return Piece::color;
}

const std::string Piece::getPieceSymbol(const Piece *piece) {
    if (piece == nullptr) {
        return " ";
    }
    else {
        return piece->getSymbol();
    }
}

bool Piece::canPieceMakeMove(const GameState &state, Position pos) const {
    vector<Move> moves = this->getAvailableMoves(state, pos);
    for (Move move : moves) {
        if (state.willKingBeInCheck(move) == false) {
            return true;
        }
    }
    return false;
}

PieceColor Piece::getPieceColor(const Piece *piece) {
    if (piece == nullptr) {
        return PieceColor::NO_PIECE;
    }
    else {
        return piece->getColor();
    }
}

unique_ptr<const Piece> Piece::copyPiece(const Piece *piece) {
    if (piece == nullptr) {
        return nullptr;
    }
    return piece->getCopy();
}

void Piece::getStraightMoves(vector<Move> &moves, const GameState &state, Position start) const {
    getMovesInLine(moves, state, start,  1,  0);
    getMovesInLine(moves, state, start, -1,  0);
    getMovesInLine(moves, state, start,  0,  1);
    getMovesInLine(moves, state, start,  0, -1);
}

void Piece::getDiagonalMoves(vector<Move> &moves, const GameState &state, Position start) const {
    getMovesInLine(moves, state, start,  1,  1);
    getMovesInLine(moves, state, start,  1, -1);
    getMovesInLine(moves, state, start, -1,  1);
    getMovesInLine(moves, state, start, -1, -1);
}

void Piece::getMovesInLine(vector<Move> &moves, const GameState &state, Position start, int delta_x, int delta_y) const {
    Position end = start.add(delta_x, delta_y);
    while (state.inBounds(end) && state.isPiece(end) == false) {
        moves.push_back(Move(start, end));
        end = end.add(delta_x, delta_y);
    }
    if (state.inBounds(end) && state.isOppPieceColor(end, color)) {
        moves.push_back(Move(start, end));
    }
}
