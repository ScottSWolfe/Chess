#include "ChessDebug.h"
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h> 
#endif
#include "StandardGameManager.h"
#include "ConsoleUI.h"


int main() {
    #ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    #endif

    chess::StandardGameManager manager;
    chess::ConsoleUI ui;
    manager.registerObserver(&ui);
    manager.startGame();

    system("pause");

    return 0;
}
