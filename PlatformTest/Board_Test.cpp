#include <memory>
#include "stdafx.h"
#include "CppUnitTest.h"
#include "Board.h"
#include "Piece.h"
#include "Rook.h"
#include "ChessEnums.h"
#include "Position.h"
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace PlatformTest
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

			Board board(2);
			unique_ptr<Piece> rook = make_unique<Rook>(PieceColor::BLACK);
			board.addPieceToSquare(Position(0, 1), rook);
			Board copy_of_board(board);

			// squares are same colors
			Assert::IsTrue(board.getSquare(pos00).getColor() ==  copy_of_board.getSquare(pos00).getColor());
			Assert::IsTrue(board.getSquare(pos01).getColor() == copy_of_board.getSquare(pos01).getColor());
			Assert::IsTrue(board.getSquare(pos10).getColor() == copy_of_board.getSquare(pos10).getColor());
			Assert::IsTrue(board.getSquare(pos11).getColor() == copy_of_board.getSquare(pos11).getColor());

			// square with a piece
			Assert::IsNotNull(copy_of_board.getSquare(pos01).getPiece());

			// square without a piece
			Assert::IsNull(copy_of_board.getSquare(pos00).getPiece());
		}

		TEST_METHOD(copyConstructorMakesCopyAndNotReference)
		{
			Position pos00(0, 0);
			Position pos11(1, 1);

			Board board(4);
			unique_ptr<Piece> black_rook = make_unique<Rook>(PieceColor::BLACK);
			board.addPieceToSquare(pos00, black_rook);
			Board copy_of_board(board);

			unique_ptr<Piece> white_rook = make_unique<Rook>(PieceColor::WHITE);
			copy_of_board.addPieceToSquare(pos11, white_rook);

			// square without white rook
			Assert::IsNull(board.getSquare(pos11).getPiece());

			// square with white rook
			Assert::IsNotNull(copy_of_board.getSquare(pos11).getPiece());
		}

	};
}
