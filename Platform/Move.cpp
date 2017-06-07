#include "ChessDebug.h"
#include "Move.h"
#include "MoveEffect.h"
#include "Position.h"
using namespace std;


Move::Move(Position start_coord, Position end_coord)
    : start(start_coord), end(end_coord), effect(nullptr)
{}

Move::Move(Position start, Position end, unique_ptr<const MoveEffect> &effect)
    : start(start), end(end), effect(effect.release())
{}

Move::Move(const Move &other) 
    : start(other.start), end(other.end), effect(other.getCopyOfEffect())
{}

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

const MoveEffect *Move::getEffect() const {
    return effect.get();
}

unique_ptr<const MoveEffect> Move::getCopyOfEffect() const {
    if (effect == nullptr) {
        return nullptr;
    }
    return effect->getCopy();
}
