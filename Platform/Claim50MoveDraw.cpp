#include "ChessDebug.h"
#include "Claim50MoveDraw.h"
#include "GameManager.h"


bool Claim50MoveDraw::enactAction(GameManager &manager) const {
    return manager.claim50MoveDraw();
}
