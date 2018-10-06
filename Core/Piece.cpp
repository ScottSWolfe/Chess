#include <memory>
#include <string>
#include <vector>
#include "ChessDebug.h"
#include "Bishop.h"
#include "GameState.h"
#include "Knight.h"
#include "King.h"
#include "Move.h"
#include "Pawn.h"
#include "Position.h"
#include "Piece.h"
#include "Queen.h"
#include "Rook.h"

namespace chess {


const std::string Piece::PAWN_SYMBOL = std::string(1, PAWN_CHAR);
const std::string Piece::ROOK_SYMBOL = std::string(1, ROOK_CHAR);
const std::string Piece::BISHOP_SYMBOL = std::string(1, BISHOP_CHAR);
const std::string Piece::KNIGHT_SYMBOL = std::string(1, KNIGHT_CHAR);
const std::string Piece::QUEEN_SYMBOL = std::string(1, QUEEN_CHAR);
const std::string Piece::KING_SYMBOL = std::string(1, KING_CHAR);

Piece::Piece(PieceColor piece_color)
    : color(piece_color), has_moved(false), turn_first_moved(0)
{}

PieceColor Piece::getColor() const {
    return color;
}

bool Piece::isWhiteColor() const {
    return color == PieceColor::WHITE;
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
    std::vector<Move> moves = this->getAvailableMoves(state, pos);
    for (Move move : moves) {
        if (state.willKingBeInCheck(move) == false) {
            return true;
        }
    }
    return false;
}

void Piece::moved(int turn_number) {
    if (hasMoved() == false) {
        setHasMoved(true);
        setTurnFirstMoved(turn_number);
    }
}

void Piece::undoMove(int turn_number) {
    if (turn_number == getTurnFirstMoved()) {
        setHasMoved(false);
        setTurnFirstMoved(0);
    }
}

void Piece::setHasMoved(bool has_moved) {
    this->has_moved = has_moved;
}

bool Piece::hasMoved() const {
    return has_moved;
}

void Piece::setTurnFirstMoved(int turn) {
    turn_first_moved = turn;
}

int Piece::getTurnFirstMoved() const {
    return turn_first_moved;
}

PieceColor Piece::getPieceColor(const Piece *piece) {
    if (piece == nullptr) {
        return PieceColor::NO_PIECE;
    }
    else {
        return piece->getColor();
    }
}

bool Piece::doesPieceAttackInLine(const Piece *piece) {
    if (piece->getType() == PieceType::QUEEN || piece->getType() == PieceType::ROOK) {
        return true;
    }
    return false;
}

bool Piece::doesPieceAttackInDiagonal(const Piece *piece) {
    if (piece->getType() == PieceType::QUEEN || piece->getType() == PieceType::BISHOP) {
        return true;
    }
    return false;
}

std::unique_ptr<Piece> Piece::copyPiece(const Piece *piece) {
    if (piece == nullptr) {
        return nullptr;
    }
    return piece->getCopy();
}

std::vector<Move> Piece::getAvailableMoves(const GameState &state, Position start) const {
    std::vector<Move> moves;
    std::vector<Position> positions = getSquaresAttacked(state.getBoard(), start);
    for (Position end : positions) {
        moves.push_back(Move(start, end));
    }
    return moves;
}

void Piece::getStraightSquaresAttacked(std::vector<Position> &positions, const Board &board, Position start) const {
    getSquaresAttackedInLine(positions, board, start,  1,  0);
    getSquaresAttackedInLine(positions, board, start, -1,  0);
    getSquaresAttackedInLine(positions, board, start,  0,  1);
    getSquaresAttackedInLine(positions, board, start,  0, -1);
}

void Piece::getDiagonalSquaresAttacked(std::vector<Position> &positions, const Board &board, Position start) const {
    getSquaresAttackedInLine(positions, board, start,  1,  1);
    getSquaresAttackedInLine(positions, board, start,  1, -1);
    getSquaresAttackedInLine(positions, board, start, -1,  1);
    getSquaresAttackedInLine(positions, board, start, -1, -1);
}

void Piece::getSquaresAttackedInLine(std::vector<Position> &positions, const Board &board, Position start, int delta_x, int delta_y) const {
    Position end = start.add(delta_x, delta_y);
    while (board.inBounds(end) && board.isPiece(end) == false) {
        positions.push_back(end);
        end = end.add(delta_x, delta_y);
    }
    if (board.inBounds(end) && board.isOppPieceColor(end, color)) {
        positions.push_back(end);
    }
}

bool Piece::areEqual (const Piece *left, const Piece *right) {
    if (left == nullptr && right == nullptr) {
        return true;
    }
    else if (left == nullptr || right == nullptr) {
        return false;
    }

    if (left->color != right->color) {
        return false;
    }
    if (left->has_moved != right->has_moved) {
        return false;
    }
    if (left->turn_first_moved != right->turn_first_moved) {
        return false;
    }
    if (left->getType() != right->getType()) {
        return false;
    }

    return true;
}

std::unique_ptr<Piece> Piece::createPiece(PieceType type, PieceColor color) {
    switch (type) {
        case PieceType::PAWN:
            return std::make_unique<Pawn>(color);

        case PieceType::KNIGHT:
            return std::make_unique<Knight>(color);

        case PieceType::BISHOP:
            return std::make_unique<Bishop>(color);

        case PieceType::ROOK:
            return std::make_unique<Rook>(color);

        case PieceType::QUEEN:
            return std::make_unique<Queen>(color);

        case PieceType::KING:
            return std::make_unique<King>(color);

        default:
            throw std::invalid_argument("invalid PieceType");
    }
}

std::unique_ptr<Piece> Piece::createPiece(char fen_char) {
    // validate that character is a letter
    if (!isalpha(fen_char)) {
        throw std::invalid_argument("invalid character");
    }

    // set color based on letter case
    PieceColor color = PieceColor::WHITE;
    if (islower(fen_char)) {
        color = PieceColor::BLACK;
        fen_char = toupper(fen_char);
    }

    // create piece based on character
    switch (fen_char) {
        case PAWN_CHAR:
            return createPiece(PieceType::PAWN, color);

        case ROOK_CHAR:
            return createPiece(PieceType::ROOK, color);

        case KNIGHT_CHAR:
            return createPiece(PieceType::KNIGHT, color);

        case BISHOP_CHAR:
            return createPiece(PieceType::BISHOP, color);

        case QUEEN_CHAR:
            return createPiece(PieceType::QUEEN, color);

        case KING_CHAR:
            return createPiece(PieceType::KING, color);

        default:
            throw std::invalid_argument("invalid character");
    }
}


}
