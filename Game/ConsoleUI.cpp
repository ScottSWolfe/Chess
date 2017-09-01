#include <iostream>
#include "ChessDebug.h"
#include "ConsoleUI.h"
#include "GameState.h"
#include "Piece.h"

namespace chess {


void ConsoleUI::gameStarted(const GameState &state) {
    std::cout << "====  Game Started  ====" << std::endl << std::endl;
    presenter.displayBoard(state.getBoard());
    std::cout << std::endl;
}

void ConsoleUI::gameEnded(const GameState &state) {
    std::cout << "====  Game Over  ====" << std::endl;
    std::cout << getGameEndMessage(state.getGameOverState()) << std::endl << std::endl;
}

void ConsoleUI::turnStarted(const GameState &newState) {
    std::cout << currentTurnToString(newState) << "'s Turn" << std::endl;
}

void ConsoleUI::turnEnded(const GameState &newState) {
    presenter.displayBoard(newState.getBoard());
}

std::string ConsoleUI::currentTurnToString(const GameState &newState) const {
    if (newState.getCurrentPlayersTurn() == PieceColor::BLACK) {
        return "Black";
    }
    else {
        return "White";
    }
}

std::string ConsoleUI::getGameEndMessage(GameEndType end_type) const {
    switch (end_type)
    {
    case GameEndType::WHITE_CHECKMATE:
        return std::string("White wins by checkmate.");

    case GameEndType::BLACK_CHECKMATE:
        return std::string("Black wins by checkmate.");

    case GameEndType::WHITE_RESIGN:
        return std::string("Black wins by resignation.");

    case GameEndType::BLACK_RESIGN:
        return std::string("White wins by resignation.");

    case GameEndType::DRAW_AGREEMENT:
        return std::string("The players agreed to a draw.");

    case GameEndType::DRAW_50_MOVES:
        return std::string("Draw: 50 moves passed without a capture or pawn move.");

    case GameEndType::DRAW_3_REPITITIONS:
        return std::string("Draw: The same position appeared 3 times.");

    case GameEndType::STALEMATE:
        return std::string("Stalemate.");

    default:
        throw std::invalid_argument("invalid GameEndType");
    }
}


}
