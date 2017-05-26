#include "stdafx.h"
#include "CppUnitTest.h"
#include "Piece.h"
#include "Bishop.h"
#include "Pawn.h"
#include "King.h"
#include "Knight.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include "ChessEnums.h"
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PlatformTest
{
	TEST_CLASS(Piece_Test)
	{
	public:

		TEST_METHOD(isCorrectColor)
		{
			unique_ptr<const Piece> white_rook = make_unique<const Rook>(PieceColor::WHITE);
			Assert::AreEqual(static_cast<int>(PieceColor::WHITE), static_cast<int>(white_rook->getColor()));

			unique_ptr<const Piece> black_rook = make_unique<const Rook>(PieceColor::BLACK);
			Assert::AreEqual(static_cast<int>(PieceColor::BLACK), static_cast<int>(black_rook->getColor()));
		}

		TEST_METHOD(piecesReturnCorrectSymbols)
		{
			unique_ptr<const Piece> pawn = make_unique<const Pawn>(PieceColor::WHITE);
			Assert::AreEqual(string("p"), pawn->getSymbol());

			unique_ptr<const Piece> rook = make_unique<const Rook>(PieceColor::WHITE);
			Assert::AreEqual(string("R"), rook->getSymbol());

			unique_ptr<const Piece> knight = make_unique<const Knight>(PieceColor::WHITE);
			Assert::AreEqual(string("N"), knight->getSymbol());

			unique_ptr<const Piece> bishop = make_unique<const Bishop>(PieceColor::WHITE);
			Assert::AreEqual(string("B"), bishop->getSymbol());

			unique_ptr<const Piece> queen = make_unique<const Queen>(PieceColor::WHITE);
			Assert::AreEqual(string("Q"), queen->getSymbol());

			unique_ptr<const Piece> king = make_unique<const King>(PieceColor::WHITE);
			Assert::AreEqual(string("K"), king->getSymbol());
		}

	};
}
