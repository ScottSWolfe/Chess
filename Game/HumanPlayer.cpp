#include <iostream>
#include "ChessDebug.h"
#include "Board.h"
#include "HumanPlayer.h"
#include "Move.h"
#include "MoveInputParser.h"
#include "PlayerAction.h"
#include "Position.h"

namespace chess {


HumanPlayer::HumanPlayer(PieceColor color)
    : Player(color)
{}

std::shared_ptr<PlayerAction> HumanPlayer::getAction(const GameState &state) const {
    std::shared_ptr<PlayerAction> action;
    while (action == nullptr) {
        action = getUserAction();
    }
    return action;
}

std::shared_ptr<PlayerAction> HumanPlayer::getUserAction() const {
    std::cout << "Enter a move (O for other): ";
    std::string input;
    std::getline(std::cin, input);

    if (input == "O") {
        return getOther(input);
    }
    else {
        return getMove(input);
    }
}

std::shared_ptr<PlayerAction> HumanPlayer::getOther(std::string input) const {
    return selector.selectAction(input);
}

std::shared_ptr<Move> HumanPlayer::getMove(std::string input) const {
    auto move = parser.parseMoveInput(input);
    if (move == nullptr) {
        std::cout << "Move not entered correctly." << std::endl;
    }
    return move;
}

PieceType HumanPlayer::getPromotionPiece(const GameState &state, const Move &move) const {
    return getPromotionPiece();
}

PieceType HumanPlayer::getPromotionPiece() const {
    std::cout << "Choose a promotion piece (Q, R, B, N): ";
    std::string input;
    std::getline(std::cin, input);
    return parsePromotionPiece(input);
}

PieceType HumanPlayer::parsePromotionPiece(std::string input) const {
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
