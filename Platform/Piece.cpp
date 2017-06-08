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
    : color(piece_color), has_moved(false)
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

void Piece::setHasMoved(bool has_moved) {
    this->has_moved = has_moved;
}

bool Piece::hasMoved() const {
    return has_moved;
}


PieceColor Piece::getPieceColor(const Piece *piece) {
    if (piece == nullptr) {
        return PieceColor::NO_PIECE;
    }
    else {
        return piece->getColor();
    }
}

unique_ptr<Piece> Piece::copyPiece(const Piece *piece) {
    if (piece == nullptr) {
        return nullptr;
    }
    return piece->getCopy();
}

vector<Move> Piece::getAvailableMoves(const GameState &state, Position start) const {
    vector<Move> moves;
    vector<Position> positions = getSquaresAttacked(state, start);
    for (Position end : positions) {
        moves.push_back(Move(start, end));
    }
    return moves;
}

void Piece::getStraightSquaresAttacked(vector<Position> &positions, const GameState &state, Position start) const {
    getSquaresAttackedInLine(positions, state, start,  1,  0);
    getSquaresAttackedInLine(positions, state, start, -1,  0);
    getSquaresAttackedInLine(positions, state, start,  0,  1);
    getSquaresAttackedInLine(positions, state, start,  0, -1);
}

void Piece::getDiagonalSquaresAttacked(vector<Position> &positions, const GameState &state, Position start) const {
    getSquaresAttackedInLine(positions, state, start,  1,  1);
    getSquaresAttackedInLine(positions, state, start,  1, -1);
    getSquaresAttackedInLine(positions, state, start, -1,  1);
    getSquaresAttackedInLine(positions, state, start, -1, -1);
}

void Piece::getSquaresAttackedInLine(vector<Position> &positions, const GameState &state, Position start, int delta_x, int delta_y) const {
    Position end = start.add(delta_x, delta_y);
    while (state.inBounds(end) && state.isPiece(end) == false) {
        positions.push_back(end);
        end = end.add(delta_x, delta_y);
    }
    if (state.inBounds(end) && state.isOppPieceColor(end, color)) {
        positions.push_back(end);
    }
}

std::unique_ptr<Piece> Piece::createPiece(PieceType type, PieceColor color) {
    switch (type)
    {
    case PieceType::PAWN:
        return make_unique<Pawn>(color);

    case PieceType::KNIGHT:
        return make_unique<Knight>(color);

    case PieceType::BISHOP:
        return make_unique<Bishop>(color);

    case PieceType::ROOK:
        return make_unique<Rook>(color);

    case PieceType::QUEEN:
        return make_unique<Queen>(color);

    case PieceType::KING:
        return make_unique<King>(color);

    default:
        throw invalid_argument("invalid PieceType");
    }
}
