#include "stdafx.h"
#include "CppUnitTest.h"
#include "Piece.h"
#include "Rook.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace chess;


namespace CoreTest
{		
	TEST_CLASS(Rook_Test)
	{
	public:

		TEST_METHOD(returnsCorrectSymbol)
		{
			Rook rook(PieceColor::WHITE);
			Assert::AreEqual(std::string("R"), rook.getSymbol());
		}

	};
}
