#pragma once

#include <memory>
#include <string>
#include "Piece.h"

namespace chess {

class Board;


class BoardInitializer {

public:
    static Board initializeStandardSetup();
    static Board initializeFromFEN(const std::string &fen);

private:
    static void addStandardPieces(Board &board);
    static void addRowOfPawns(Board &board, int row, PieceColor color);
    static void addStandardRowOfPieces(Board &board, int row, PieceColor color);
    static int getBoardSizeFromFEN(const std::string &fen);
    static void addPiecesToBoardFromFEN(Board &board, const std::string &fen);
    static std::vector<std::string> BoardInitializer::tokenize(const std::string &str, const char delimiter);
    static int getFullIntegerAtIndex(const std::string &str, int index, int &num_digits);
    static void updateCastlingAbility(Board &board, const std::string &fen_castle);

    static const std::string FEN_MALFORMED_MESSAGE;

};


}
