#include <memory>
#include <string>
#include "stdafx.h"
#include "CppUnitTest.h"
#include "Move.h"
#include "MoveInputParser.h"
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace PlatformTest
{
	TEST_CLASS(MoveInputParser_Test)
	{
	public:
		MoveInputParser parser;

		TEST_METHOD(goodInputReturnsGoodOutput)
		{
			// returns correct move
			Move move(SquareCoordinates(0, 0), SquareCoordinates(1, 1));
			Assert::IsTrue(move == *parser.parseMoveInput("A1 B2"));

			// does not return incorrect moves
			move = Move(SquareCoordinates(0, 0), SquareCoordinates(1, 1));
			Assert::IsFalse(move == *parser.parseMoveInput("A1 B1"));

			move = Move(SquareCoordinates(0, 0), SquareCoordinates(1, 1));
			Assert::IsFalse(move == *parser.parseMoveInput("A1 C1"));

			move = Move(SquareCoordinates(0, 0), SquareCoordinates(1, 1));
			Assert::IsFalse(move == *parser.parseMoveInput("A5 B2"));

			move = Move(SquareCoordinates(0, 0), SquareCoordinates(1, 1));
			Assert::IsFalse(move == *parser.parseMoveInput("B1 B2"));
		}

		TEST_METHOD(canParseAtoZand1to9)
		{
			// can parse from A to Z and 1 to 9
			Move move(SquareCoordinates(25, 8), SquareCoordinates(0, 0));
			Assert::IsTrue(move == *parser.parseMoveInput("Z9 A1"));

			// cannot parse 0
			Assert::IsNull(parser.parseMoveInput("A0 B1").get());

			// cannot parse greater than 9
			Assert::IsNull(parser.parseMoveInput("A10 B1").get());
		}

		TEST_METHOD(badInputReturnsNull)
		{
			// when only one square is given
			Assert::IsNull(parser.parseMoveInput("A1").get());
		}

		TEST_METHOD(canHandleSpuriousSpaces)
		{
			// when only one square is given
			Assert::IsNotNull(parser.parseMoveInput(" A1  B2  ").get());
			Move move(SquareCoordinates(0, 0), SquareCoordinates(1, 1));
			Assert::IsTrue(move == *parser.parseMoveInput(" A1  B2  "));
		}

		TEST_METHOD(ignoresExtraSquares)
		{
			// when a third square is given
			Assert::IsNotNull(parser.parseMoveInput("A1 B2 C3").get());
			Move move(SquareCoordinates(0, 0), SquareCoordinates(1, 1));
			Assert::IsTrue(move == *parser.parseMoveInput("A1 B2 C3"));
		}

		TEST_METHOD(isCaseInsensitive)
		{
			// accepts lower and upper case letters
			Move move(SquareCoordinates(0, 0), SquareCoordinates(1, 1));
			Assert::IsTrue(move == *parser.parseMoveInput("a1 B2"));
		}

	};
}
