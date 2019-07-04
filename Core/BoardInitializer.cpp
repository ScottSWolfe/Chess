#include <sstream>
#include "Board.h"
#include "BoardInitializer.h"
#include "ChessDebug.h"
#include "Piece.h"
#include "Position.h"

namespace chess {


const std::string BoardInitializer::FEN_MALFORMED_MESSAGE = "given FEN is malformed";

Board BoardInitializer::initializeStandardSetup() {
    Board board(8);
    addStandardPieces(board);
    return board;
}

Board BoardInitializer::initializeFromFEN(const std::string &fen) {
    const int board_size = getBoardSizeFromFEN(fen);
    Board board(board_size);
    addPiecesToBoardFromFEN(board, fen);
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

int BoardInitializer::getBoardSizeFromFEN(const std::string &fen) {
    int fen_size = static_cast<int>(fen.size());
    
    int counter = 0;
    for (int i = 0; i < fen_size; i++) {
        char c = fen[i];
        if (c == '/') {
            return counter;
        }
        else if (isdigit(c)) {
            int num_digits;
            int num_empty_squares = getFullIntegerAtIndex(fen, i, num_digits);
            counter += num_empty_squares;
            i += num_digits - 1;
        }
        else {
            counter += 1;
        }
    }
    
    throw std::invalid_argument(FEN_MALFORMED_MESSAGE);
}

void BoardInitializer::addPiecesToBoardFromFEN(Board &board, const std::string &fen) {
    // get the rows from the fen string
    std::vector<std::string> fen_tokens = tokenize(fen, ' ');
    std::vector<std::string> rows = tokenize(fen_tokens[0], '/');
    if (rows.size() != board.getDimension()) {
        throw std::invalid_argument(FEN_MALFORMED_MESSAGE);
    }

    // iterate through the rows, last to first, adding pieces to the board
    for (int board_row = static_cast<int>(rows.size()) - 1; board_row >= 0; board_row--) {
        int board_column = 0;
        for (int fen_index = 0; fen_index < rows[board_row].size(); fen_index++) {
            char c = rows[board_row][fen_index];
            if (isdigit(c)) {
                int num_digits;
                int num_empty_squares = getFullIntegerAtIndex(rows[board_row], fen_index, num_digits);
                board_column += num_empty_squares;
                fen_index += num_digits - 1;
            }
            else if (isalpha(c)) {
                Position pos(board_row, board_column);
                auto piece = Piece::createPiece(c);
                board.addPieceToSquare(pos, piece);
                board_column++;
            }
            else {
                throw std::invalid_argument(FEN_MALFORMED_MESSAGE);
            }
        }
    }
}

std::vector<std::string> BoardInitializer::tokenize(const std::string &str, const char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream stream(str);
    std::string token;
    while (std::getline(stream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int BoardInitializer::getFullIntegerAtIndex(const std::string &str, int index, int &num_digits) {
    char c = str[index];
    num_digits = 0;
    while (isdigit(c)) {
        num_digits++;
        c = str[index + num_digits];
    }
    if (num_digits == 0) {
        throw std::invalid_argument("no digit at given index");
    }
    std::string full_number = str.substr(index, num_digits);
    return stoi(full_number);
}

void BoardInitializer::updateCastlingAbility(Board &board, const std::string &fen_castle) {
    // TODO: implement this
}


}
