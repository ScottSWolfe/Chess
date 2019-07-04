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
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace chess;


namespace CoreTest
{
	TEST_CLASS(Piece_Test)
	{
	public:

		TEST_METHOD(isCorrectColor)
		{
			auto white_rook = std::make_unique<const Rook>(PieceColor::WHITE);
			Assert::AreEqual(static_cast<int>(PieceColor::WHITE), static_cast<int>(white_rook->getColor()));

			auto black_rook = std::make_unique<const Rook>(PieceColor::BLACK);
			Assert::AreEqual(static_cast<int>(PieceColor::BLACK), static_cast<int>(black_rook->getColor()));
		}

		TEST_METHOD(piecesReturnCorrectSymbols)
		{
			auto pawn = std::make_unique<const Pawn>(PieceColor::WHITE);
			Assert::AreEqual(std::string("P"), pawn->getSymbol());

            auto rook = std::make_unique<const Rook>(PieceColor::WHITE);
			Assert::AreEqual(std::string("R"), rook->getSymbol());

            auto knight = std::make_unique<const Knight>(PieceColor::WHITE);
			Assert::AreEqual(std::string("N"), knight->getSymbol());

            auto bishop = std::make_unique<const Bishop>(PieceColor::WHITE);
			Assert::AreEqual(std::string("B"), bishop->getSymbol());

            auto queen = std::make_unique<const Queen>(PieceColor::WHITE);
			Assert::AreEqual(std::string("Q"), queen->getSymbol());

            auto king = std::make_unique<const King>(PieceColor::WHITE);
			Assert::AreEqual(std::string("K"), king->getSymbol());
		}

	};
}
