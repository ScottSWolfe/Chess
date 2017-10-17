#include "GameState.h"
#include "PositionRanker.h"
#include "PieceIterator.h"

namespace chess {


std::map<PieceType, int> PositionRanker::pieceValues = { std::make_pair(PieceType::PAWN, 1),
                                                         std::make_pair(PieceType::BISHOP, 3),
                                                         std::make_pair(PieceType::KNIGHT, 3),
                                                         std::make_pair(PieceType::ROOK, 5),
                                                         std::make_pair(PieceType::QUEEN, 9), 
                                                         std::make_pair(PieceType::KING, 100) };
 
int PositionRanker::rankPosition(const GameState &state) {
    int white_val = sumPieceValues(state, PieceColor::WHITE);
    int black_val = sumPieceValues(state, PieceColor::BLACK);
    return white_val - black_val;
}

int PositionRanker::sumPieceValues(const GameState &state, PieceColor color) {
    int sum = 0;
    PieceIterator pieces = state.getBoard().getPieceIterator(color);
    while (pieces.hasNext()) {
        sum += pieceValues[pieces.next()->getType()];
    }
    return sum;
}


}
