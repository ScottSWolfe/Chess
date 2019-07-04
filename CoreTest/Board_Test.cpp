#include <memory>
#include "stdafx.h"
#include "CppUnitTest.h"
#include "Board.h"
#include "Piece.h"
#include "Rook.h"
#include "Position.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace chess;


namespace CoreTest
{
	TEST_CLASS(Board_Test)
	{
	public:
		
		TEST_METHOD(copyConstructorMakesAccurateCopy)
		{
			Position pos00(0, 0);
			Position pos01(0, 1);
			Position pos10(1, 0);
			Position pos11(1, 1);

			Board board(6);
            std::unique_ptr<Piece> rook = std::make_unique<Rook>(PieceColor::BLACK);
			board.addPieceToSquare(Position(0, 1), rook);
			Board copy_of_board(board);

			// square with a piece
			Assert::IsNotNull(copy_of_board.getPiece(pos01), L"message", LINE_INFO());

			// squares without a piece
			Assert::IsNull(copy_of_board.getPiece(pos00));
            Assert::IsNull(copy_of_board.getPiece(pos10));
            Assert::IsNull(copy_of_board.getPiece(pos11));
		}

		TEST_METHOD(copyConstructorMakesCopyAndNotReference)
		{
			Position pos00(0, 0);
			Position pos11(1, 1);

			Board board(6);
			std::unique_ptr<Piece> black_rook = std::make_unique<Rook>(PieceColor::BLACK);
			board.addPieceToSquare(pos00, black_rook);
			Board copy_of_board(board);

			std::unique_ptr<Piece> white_rook = std::make_unique<Rook>(PieceColor::WHITE);
			copy_of_board.addPieceToSquare(pos11, white_rook);

			// square without white rook
			Assert::IsNull(board.getPiece(pos11));

			// square with white rook
			Assert::IsNotNull(copy_of_board.getPiece(pos11));
		}

	};
}
