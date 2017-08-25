#include "ChessDebug.h"
#include "ChessEnums.h"
#include "GameManager.h"
#include "Move.h"
#include "MoveEffect.h"
#include "Position.h"
#include "Promotion.h"

namespace chess {


Move::Move(Position start_coord, Position end_coord)
    : start(start_coord), end(end_coord), effect(nullptr)
{}

Move::Move(Position start, Position end, std::unique_ptr<MoveEffect> &effect)
    : start(start), end(end), effect(effect.release())
{}

Move::Move(const Move &other) 
    : start(other.start), end(other.end), effect(other.getCopyOfEffect())
{}

bool Move::enactAction(GameManager &manager) const {
    return manager.makeMove(*this);
}

Move &Move::operator=(const Move &other) {
    start = other.start;
    end = other.end;
    effect = other.getCopyOfEffect();
    return *this;
}

bool Move::operator==(const Move &other) const {
    if (start != other.start || end != other.end) {
        return false;
    }

    if (effect == nullptr) {
        if (other.effect == nullptr) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        if (other.effect == nullptr) {
            return false;
        }
    }

    if (*effect == *other.effect) {
        return true;
    }
    return false;
}

Position Move::getStart() const {
    return start;
}

Position Move::getEnd() const {
    return end;
}

bool Move::hasEffect() const {
    return effect != nullptr;
}

const MoveEffect *Move::getEffect() const {
    return effect.get();
}

MoveEffectType Move::getEffectType() const {
    return effect->getType();
}

void Move::setPromotionPiece(PieceType type) {
    if (effect == nullptr) {
        return;
    }
    if (effect->getType() == MoveEffectType::PROMOTION) {
        dynamic_cast<Promotion*>(effect.get())->setPromotionPiece(type);
    }
}

std::unique_ptr<MoveEffect> Move::getCopyOfEffect() const {
    if (effect == nullptr) {
        return nullptr;
    }
    return effect->getCopy();
}


}
