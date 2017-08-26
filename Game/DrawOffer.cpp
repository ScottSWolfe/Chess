#include "ChessDebug.h"
#include "GameManager.h"
#include "DrawOffer.h"

namespace chess {


bool DrawOffer::enactAction(GameManager &manager) const {
    return manager.offerDraw();
}


}
