#include "BTRGameState.h"
#include "PositionRanker.h"
#include "Piece.h"
#include "PieceIterator.h"
#include "Promotion.h"

namespace chess {


std::map<PieceType, int> PositionRanker::pieceValues = { std::make_pair(PieceType::PAWN, 1),
                                                         std::make_pair(PieceType::BISHOP, 3),
                                                         std::make_pair(PieceType::KNIGHT, 3),
                                                         std::make_pair(PieceType::ROOK, 5),
                                                         std::make_pair(PieceType::QUEEN, 9), 
                                                         std::make_pair(PieceType::KING, 100) };

int PositionRanker::scorePosition(const BTRGameState &state) {
    int position_ranking = state.getRelativePieceValue();
    if (state.getCurrentPlayersTurn() == PieceColor::WHITE) {
        return -position_ranking;
    }
    else {
        return position_ranking;
    }
}

int PositionRanker::rankPosition(const GameState &state) {
    int white_val = sumPieceValues(state, PieceColor::WHITE);
    int black_val = sumPieceValues(state, PieceColor::BLACK);
    return white_val - black_val;
}

int PositionRanker::getRelativePieceValueChange(const GameState &state, const Move &move) {
    int change = 0;

    auto piece = state.getPiece(move.getEnd());
    if (piece) {
        if (piece->isWhiteColor()) {
            change -= pieceValues[piece->getType()];
        }
        else {
            change += pieceValues[piece->getType()];
        }
    }

    if (move.isPromotionType()) {
        if (piece->isWhiteColor()) {
            change += pieceValues[move.getPromotionPieceType()] - pieceValues[piece->getType()];
        }
        else {
            change -= pieceValues[move.getPromotionPieceType()] - pieceValues[piece->getType()];
        }
    }
    else if (move.isEnPassantType()) {
        if (state.getCurrentPlayersTurn() == PieceColor::WHITE) {
            change += 1;
        }
        else {
            change -= 1;
        }
    }

    return change;
}

int PositionRanker::sumPieceValues(const GameState &state, PieceColor color) {
    int sum = 0;
    PieceIterator pieces = state.getPieceIterator(color);
    while (pieces.hasNext()) {
        sum += pieceValues[pieces.next()->getType()];
    }
    return sum;
}


}
