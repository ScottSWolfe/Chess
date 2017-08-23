#include "Board.h"
#include "BoardInitializer.h"
#include "ChessDebug.h"
#include "Piece.h"
#include "Position.h"
using namespace std;

namespace chess {


Board BoardInitializer::initializeStandardSetup() {
    Board board(8);
    addStandardPieces(board);
    return board;
}

void BoardInitializer::addStandardPieces(Board &board) {
    addRowOfPawns(board, 1, PieceColor::WHITE);
    addRowOfPawns(board, 6, PieceColor::BLACK);
    addStandardRowOfPieces(board, 0, PieceColor::WHITE);
    addStandardRowOfPieces(board, 7, PieceColor::BLACK);
}

void BoardInitializer::addRowOfPawns(Board &board, int row, PieceColor color) {
    int dimension = board.getDimension();
    for (int i = 0; i < dimension; ++i) {
        auto pawn = Piece::createPiece(PieceType::PAWN, color);
        Position pos(i, row);
        board.addPieceToSquare(pos, pawn);
    }
}

void BoardInitializer::addStandardRowOfPieces(Board &board, int row, PieceColor color) {
    auto rook_a = Piece::createPiece(PieceType::ROOK, color);
    auto rook_b = Piece::createPiece(PieceType::ROOK, color);
    auto knight_a = Piece::createPiece(PieceType::KNIGHT, color);
    auto knight_b = Piece::createPiece(PieceType::KNIGHT, color);
    auto bishop_a = Piece::createPiece(PieceType::BISHOP, color);
    auto bishop_b = Piece::createPiece(PieceType::BISHOP, color);
    auto queen = Piece::createPiece(PieceType::QUEEN, color);
    auto king = Piece::createPiece(PieceType::KING, color);

    board.addPieceToSquare(Position(0, row), rook_a);
    board.addPieceToSquare(Position(7, row), rook_b);
    board.addPieceToSquare(Position(1, row), knight_a);
    board.addPieceToSquare(Position(6, row), knight_b);
    board.addPieceToSquare(Position(2, row), bishop_a);
    board.addPieceToSquare(Position(5, row), bishop_b);
    board.addPieceToSquare(Position(3, row), queen);
    board.addPieceToSquare(Position(4, row), king);
}


}
