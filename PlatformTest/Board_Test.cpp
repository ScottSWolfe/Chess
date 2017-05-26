#include <memory>
#include "stdafx.h"
#include "CppUnitTest.h"
#include "Board.h"
#include "Piece.h"
#include "Rook.h"
#include "ChessEnums.h"
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace PlatformTest
{
	TEST_CLASS(Board_Test)
	{
	public:
		
		TEST_METHOD(copyConstructorMakesAccurateCopy)
		{
			Board board(2);
			unique_ptr<const Piece> rook = make_unique<const Rook>(PieceColor::BLACK);
			board.addPieceToSquare(0, 1, rook);
			Board copy_of_board(board);

			// squares are same colors
			Assert::AreEqual(static_cast<int>(board.getSquare(0, 0).getColor()),
				static_cast<int>(copy_of_board.getSquare(0, 0).getColor()));
			Assert::AreEqual(static_cast<int>(board.getSquare(0, 1).getColor()),
				static_cast<int>(copy_of_board.getSquare(0, 1).getColor()));
			Assert::AreEqual(static_cast<int>(board.getSquare(1, 0).getColor()),
				static_cast<int>(copy_of_board.getSquare(1, 0).getColor()));
			Assert::AreEqual(static_cast<int>(board.getSquare(1, 1).getColor()),
				static_cast<int>(copy_of_board.getSquare(1, 1).getColor()));

			// square with a piece
			Assert::IsNotNull(copy_of_board.getSquare(0, 1).getPiece());

			// square without a piece
			Assert::IsNull(copy_of_board.getSquare(0, 0).getPiece());
		}

		TEST_METHOD(copyConstructorMakesCopyAndNotReference)
		{
			Board board(4);
			unique_ptr<const Piece> black_rook = make_unique<const Rook>(PieceColor::BLACK);
			board.addPieceToSquare(0, 0, black_rook);
			Board copy_of_board(board);

			unique_ptr<const Piece> white_rook = make_unique<const Rook>(PieceColor::WHITE);
			copy_of_board.addPieceToSquare(1, 1, white_rook);

			// square without white rook
			Assert::IsNull(board.getSquare(1, 1).getPiece());

			// square with white rook
			Assert::IsNotNull(copy_of_board.getSquare(1, 1).getPiece());
		}

	};
}
