#pragma once
#include <memory>

class Board;
enum class PieceColor;


class BoardInitializer {

public:
	static std::unique_ptr<Board> initializeStandardSetup();

private:
	static void addStandardPieces(Board *board);
	static void addRowOfPawns(Board *board, const int row, const PieceColor color);
	static void addStandardRowOfPieces(Board *board, const int row, const PieceColor color);

};
