#include <memory>
#include "stdafx.h"
#include "CppUnitTest.h"
#include "ChessEnums.h"
#include "Piece.h"
#include "Rook.h"
#include "Square.h"
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace PlatformTest
{
    TEST_CLASS(Square_Test)
    {
    public:

        TEST_METHOD(Square_isPiece_returnsTrueIfPiece)
        {
            Square square = createSquareWithPiece();
            Assert::IsTrue(square.isPiece(), L"isPiece() should return true when square contains piece", LINE_INFO());
        }

        TEST_METHOD(Square_isPiece_returnsFalseIfNoPiece)
        {
            Square square = createSquareWithoutPiece();
            Assert::IsFalse(square.isPiece(), L"isPiece() should return false when square does not contain piece", LINE_INFO());
        }

        TEST_METHOD(Square_getPiece_returnsNullptrIfNoPiece)
        {
            Square square = createSquareWithoutPiece();
            Assert::IsNull(square.getPiece(), L"getPiece() should return nullptr when square does not contain piece", LINE_INFO());
        }
        
        TEST_METHOD(Square_getPiece_returnsPointerToPieceIfPiece)
        {
            auto piece = createPiece();
            void *piece_address = (void*)piece.get();
            Square square(piece);
            Assert::IsTrue(piece_address == square.getPiece(), L"getPiece() should return pointer to piece when square contains piece", LINE_INFO());
        }
        
    private:

        Square createSquareWithPiece() {
            auto piece = createPiece();
            return Square(piece);
        }

        Square createSquareWithoutPiece() {
            return Square();
        }
        
        std::unique_ptr<Piece> createPiece() {
            return Piece::createPiece(PieceType::ROOK, PieceColor::WHITE);
        }
        
    };
}
