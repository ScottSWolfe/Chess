#include "GameManager.h"
#include "Resignation.h"


bool Resignation::enactAction(GameManager &manager) const {
    return manager.resign();
}
