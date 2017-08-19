#include "ChessDebug.h"
#include "GameManager.h"
#include "Resignation.h"

namespace chess {


bool Resignation::enactAction(GameManager &manager) const {
    return manager.resign();
}


}
