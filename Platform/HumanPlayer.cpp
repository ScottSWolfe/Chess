#include <iostream>
#include "ChessDebug.h"
#include "Board.h"
#include "HumanPlayer.h"
#include "Move.h"
#include "MoveInputParser.h"
#include "PlayerAction.h"
#include "Position.h"
using namespace std;

namespace chess {


HumanPlayer::HumanPlayer(PieceColor color)
    : Player(color)
{}

shared_ptr<PlayerAction> HumanPlayer::getAction(const GameState &state) const {
    shared_ptr<PlayerAction> action;
    while (action == nullptr) {
        action = getUserAction();
    }
    return action;
}

shared_ptr<PlayerAction> HumanPlayer::getUserAction() const {
    cout << "Enter a move (O for other): ";
    string input;
    getline(cin, input);

    if (input == "O") {
        return getOther(input);
    }
    else {
        return getMove(input);
    }
}

shared_ptr<PlayerAction> HumanPlayer::getOther(string input) const {
    return selector.selectAction(input);
}

shared_ptr<Move> HumanPlayer::getMove(string input) const {
    auto move = parser.parseMoveInput(input);
    if (move == nullptr) {
        cout << "Move not entered correctly." << endl;
    }
    return move;
}

PieceType HumanPlayer::getPromotionPiece(const GameState &state, const Move &move) const {
    return getPromotionPiece();
}

PieceType HumanPlayer::getPromotionPiece() const {
    cout << "Choose a promotion piece (Q, R, B, N): ";
    string input;
    getline(cin, input);
    return parsePromotionPiece(input);
}

PieceType HumanPlayer::parsePromotionPiece(string input) const {
    if (input.size() != 1) {
        return getPromotionPiece();
    }
    char c = input[0];

    switch (c) {

    case 'Q':
        return PieceType::QUEEN;

    case 'R':
        return PieceType::ROOK;

    case 'B':
        return PieceType::BISHOP;

    case 'N':
        return PieceType::KNIGHT;

    default:
        return getPromotionPiece();
    }
}


}
