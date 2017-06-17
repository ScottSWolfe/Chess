#include <iostream>
#include "ChessDebug.h"
#include "ChessEnums.h"
#include "ConsoleUI.h"
#include "GameState.h"
using namespace std;


void ConsoleUI::gameStarted(const GameState &state) {
    cout << "====  Game Started  ====" << endl << endl;
    presenter.displayBoard(state.getBoard());
    cout << endl;
}

void ConsoleUI::gameEnded(const GameState &state) {
    cout << "====  Game Over  ====" << endl;
    cout << getGameEndMessage(state.getGameOverState()) << endl << endl;
}

void ConsoleUI::turnStarted(const GameState &newState) {
    cout << currentTurnToString(newState) << "'s Turn" << endl;
}

void ConsoleUI::turnEnded(const GameState &newState) {
    presenter.displayBoard(newState.getBoard());
}

string ConsoleUI::currentTurnToString(const GameState &newState) const {
    if (newState.getCurrentPlayersTurn() == PieceColor::BLACK) {
        return "Black";
    }
    else {
        return "White";
    }
}

string ConsoleUI::getGameEndMessage(GameEndType end_type) const {
    switch (end_type)
    {
    case GameEndType::WHITE_CHECKMATE:
        return string("White wins by checkmate.");

    case GameEndType::BLACK_CHECKMATE:
        return string("Black wins by checkmate.");

    case GameEndType::WHITE_RESIGN:
        return string("Black wins by resignation.");

    case GameEndType::BLACK_RESIGN:
        return string("White wins by resignation.");

    case GameEndType::DRAW_AGREEMENT:
        return string("The players agreed to a draw.");

    case GameEndType::DRAW_50_MOVES:
        return string("Draw: 50 moves passed without a capture or pawn move.");

    case GameEndType::DRAW_3_REPITITIONS:
        return string("Draw: The same position appeared 3 times.");

    case GameEndType::STALEMATE:
        return string("Stalemate.");

    default:
        throw invalid_argument("invalid GameEndType");
    }
}
