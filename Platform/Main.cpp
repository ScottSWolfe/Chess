#include <iostream>
#include "ChessDebug.h"
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h> 
#endif
#include "windows.h"
#include "Move.h"
#include "MoveInputParser.h"
#include "ChessEnums.h"
#include "Piece.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"
#include "Square.h"
#include "Board.h"
#include "ConsoleBoardPresenter.h"
#include "BoardInitializer.h"
#include "GameManager.h"
#include "ConsoleUI.h"
using namespace std;


int main() {
    #ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    #endif

    GameManager manager;
    ConsoleUI ui;
    manager.registerObserver(&ui);
    manager.startGame();

    system("pause");

    return 0;
}
