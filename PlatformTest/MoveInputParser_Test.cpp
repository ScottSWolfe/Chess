#include <memory>
#include <string>
#include "stdafx.h"
#include "CppUnitTest.h"
#include "Move.h"
#include "MoveInputParser.h"
#include "Position.h"
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
			Move move(Position(0, 0), Position(1, 1));
			Assert::IsTrue(move == *parser.parseMoveInput("A1 B2"));

			// does not return incorrect moves
			move = Move(Position(0, 0), Position(1, 1));
			Assert::IsFalse(move == *parser.parseMoveInput("A1 B1"));

			move = Move(Position(0, 0), Position(1, 1));
			Assert::IsFalse(move == *parser.parseMoveInput("A1 C1"));

			move = Move(Position(0, 0), Position(1, 1));
			Assert::IsFalse(move == *parser.parseMoveInput("A5 B2"));

			move = Move(Position(0, 0), Position(1, 1));
			Assert::IsFalse(move == *parser.parseMoveInput("B1 B2"));
		}

		TEST_METHOD(canParseMultipleNumbersAndLetters)
		{
			// can parse from A to Z and 1 to 9
			Move move(Position(25, 8), Position(0, 0));
			Assert::IsTrue(move == *parser.parseMoveInput("Z9 A1"));

			// cannot parse 0
			Assert::IsNull(parser.parseMoveInput("A0 B1").get());

			// can parse greater than 9
			move = Move(Position(0, 15), Position(0, 0));
			Assert::IsTrue(move == *parser.parseMoveInput("A16 A1").get());

			// can parse multiple letters
			move = Move(Position(29, 0), Position(59, 0));
			Assert::IsTrue(move == *parser.parseMoveInput("AD1 BH1").get());
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
			Move move(Position(0, 0), Position(1, 1));
			Assert::IsTrue(move == *parser.parseMoveInput(" A1  B2  "));
		}

		TEST_METHOD(ignoresExtraSquares)
		{
			// when a third square is given
			Assert::IsNotNull(parser.parseMoveInput("A1 B2 C3").get());
			Move move(Position(0, 0), Position(1, 1));
			Assert::IsTrue(move == *parser.parseMoveInput("A1 B2 C3"));
		}

		TEST_METHOD(isCaseInsensitive)
		{
			// accepts lower and upper case letters
			Move move(Position(0, 0), Position(1, 1));
			Assert::IsTrue(move == *parser.parseMoveInput("a1 B2"));
		}

	};
}
