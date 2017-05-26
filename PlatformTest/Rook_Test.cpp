#include "stdafx.h"
#include "CppUnitTest.h"
#include "Piece.h"
#include "Rook.h"
#include "ChessEnums.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PlatformTest
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
