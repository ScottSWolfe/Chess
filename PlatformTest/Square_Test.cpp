#include <memory>
#include "stdafx.h"
#include "CppUnitTest.h"
#include "ChessEnums.h"
#include "Piece.h"
#include "Square.h"
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace PlatformTest
{
    TEST_CLASS(Square_Test)
    {
    public:

        TEST_METHOD(Square_constructor_noParamCreatesSquareWithoutPiece)
        {
            Square square;
            Assert::IsFalse(square.isPiece(), L"square constructed with no param should not contain piece", LINE_INFO());
        }

        TEST_METHOD(Square_constructor_withPieceParamCreatesSquareWithPiece)
        {
            auto piece = createPiece();
            Square square(piece);
            Assert::IsTrue(square.isPiece(), L"square constructed with piece param should contain piece", LINE_INFO());
        }

        TEST_METHOD(Square_constructor_withPieceParamTransfersOwnershipToSquare)
        {
            auto piece = createPiece();
            Square square(piece);
            Assert::IsNull(piece.get(), L"ownership should be transferred to square constructed with piece param", LINE_INFO());
        }

        TEST_METHOD(Square_constructor_withPieceParamSquareHasPointerToPiece)
        {
            auto piece = createPiece();
            auto piece_address = piece.get();
            Square square(piece);
            Assert::IsTrue(piece_address == square.getPiece(), L"square should contain piece that was passed to it", LINE_INFO());
        }

        TEST_METHOD(Square_copyConstructor_newSquareContainsCopyOfPiece)
        {
            Square original_square = createSquareWithPiece();
            auto original_piece = original_square.getPiece();

            Square copied_square(original_square);
            auto copied_piece = copied_square.getPiece();

            Assert::IsTrue(original_piece->getColor() == copied_piece->getColor(), L"original and copied pieces should be same color", LINE_INFO());
            Assert::IsTrue(original_piece->getType() == copied_piece->getType(), L"original and copied pieces should be same type", LINE_INFO());
        }

        TEST_METHOD(Square_copyConstructor_newSquareIsDeepCopy)
        {
            Square original_square = createSquareWithPiece();
            auto original_piece = original_square.getPiece();

            Square copied_square(original_square);
            auto copied_piece = copied_square.getPiece();

            Assert::IsTrue(&original_square != &copied_square, L"original and copied squares should not have same address", LINE_INFO());
            Assert::IsTrue(original_piece != copied_piece, L"original and copied pieces should not have same address", LINE_INFO());
        }

        TEST_METHOD(Square_copyConstructor_ifNoPieceNewSquareHasNoPiece)
        {
            Square original_square = createSquareWithoutPiece();
            Square copied_square(original_square);
            Assert::IsFalse(copied_square.isPiece(), L"copied square should not have piece if original did not have piece", LINE_INFO());
        }

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

        TEST_METHOD(Square_setPiece_hasPieceWhenPieceIsSet)
        {
            Square square = createSquareWithoutPiece();
            auto piece = createPiece();
            square.setPiece(piece);
            Assert::IsTrue(square.isPiece(), L"setPiece() should make square contain a piece", LINE_INFO());
        }

        TEST_METHOD(Square_setPiece_hasPieceThatWasSet)
        {
            Square square = createSquareWithoutPiece();
            auto piece = createPiece();
            Piece *piece_address = piece.get();
            square.setPiece(piece);
            Assert::IsTrue(piece_address == square.getPiece(), L"square should contain piece set using setPiece()", LINE_INFO());
        }

        TEST_METHOD(Square_setPiece_pieceOwnershipIsTransferredToSquare)
        {
            Square square = createSquareWithoutPiece();
            auto piece = createPiece();
            square.setPiece(piece);
            Assert::IsNull(piece.get(), L"setPiece() should transfer ownership of piece to the square", LINE_INFO());
        }

        TEST_METHOD(Square_removePiece_squareHasNoPieceAfterRemoval)
        {
            Square square = createSquareWithPiece();
            square.removePiece();
            Assert::IsFalse(square.isPiece(), L"square should have no piece after removePiece()", LINE_INFO());
        }

        TEST_METHOD(Square_removePiece_returnsThePieceRemoved)
        {
            Square square = createSquareWithPiece();
            const Piece *piece = square.getPiece();
            auto removed_piece = square.removePiece();
            Assert::IsTrue(piece == removed_piece.get(), L"removePiece() should return the piece", LINE_INFO());
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
