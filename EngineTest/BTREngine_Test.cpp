#include <memory>
#include "stdafx.h"
#include "CppUnitTest.h"
#include "BoardInitializer.h"
#include "BTREngine.h"
#include "GameState.h"
#include "Move.h"
#include "Piece.h"
#include "Position.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace chess;


namespace EngineTest
{
    TEST_CLASS(BTREngine_Test)
    {
    private:
        BTREngine engine;

    public:

        TEST_METHOD(BTREngine_getAction_returnsFirstMove)
        {
            auto state = getStartGameState();
            auto action = engine.getAction(state);
            auto actual = dynamic_cast<Move*>(action.get());
            auto expected = &getFirstMove();
            Assert::IsTrue(*actual == *expected, L"Did not return first move.", LINE_INFO());
        }

        TEST_METHOD(BTREngine_getPromotionPiece_returnsQueen)
        {
            auto state = getStartGameState();
            auto move = getFirstMove();
            auto piece = engine.getPromotionPiece(state, move);
            Assert::IsTrue(piece == PieceType::QUEEN, L"Did not return queen.", LINE_INFO());
        }

    private:
        GameState getStartGameState() {
            Board board = BoardInitializer::initializeStandardSetup();
            GameState state(board, PieceColor::WHITE);
            return state;
        }

        Move getFirstMove() {
            Position start(1, 0);
            Position end(0, 2);
            Move move(start, end);
            return move;
        }
};


}
