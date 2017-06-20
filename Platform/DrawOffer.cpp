#include "ChessDebug.h"
#include "GameManager.h"
#include "DrawOffer.h"


bool DrawOffer::enactAction(GameManager &manager) const {
    return manager.offerDraw();
}
