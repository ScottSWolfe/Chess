#include <random>
#include "ChessEnums.h"
#include "GameState.h"
#include "Move.h"
#include "MoveValidator.h"
#include "RandomPlayer.h"
using namespace std;


RandomPlayer::RandomPlayer(PieceColor color)
    : Player(color)
{}

shared_ptr<Move> RandomPlayer::makeMove(const GameState &state) const {
    vector<Move> moves = state.getAvailableMoves();
    eliminateIllegalMoves(state, moves);
    if (moves.size() <= 0) {
        return nullptr;
    }
    int rand_num = randomInteger(moves.size() - 1);
    return make_shared<Move>(moves[rand_num]);
}

PieceType RandomPlayer::getPromotionPiece(const GameState &state, const Move &move) const {
    const int num_piece_types = 6;
    int piece_type_num = randomInteger(num_piece_types - 1);
    PieceType piece_type = static_cast<PieceType>(piece_type_num);
    if (piece_type == PieceType::PAWN || piece_type == PieceType::KING) {
        piece_type = getPromotionPiece(state, move);
    }
    return piece_type;
}

void RandomPlayer::eliminateIllegalMoves(const GameState &state, vector<Move> &moves) const {
    for (size_t i = 0; i < moves.size(); i++) {
        Move move = moves[i];
        MoveValidator validator(state, move);
        if (validator.validateMoveIsSafe() == false) {
            moves.erase(moves.begin() + i);
            i--;
        }
        else if (validator.validateMoveIsLegal() == false) {
            moves.erase(moves.begin() + i);
            i--;
        }
    }
}

int RandomPlayer::randomInteger(int max_int) const {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, max_int);
    return distribution(generator);
}
