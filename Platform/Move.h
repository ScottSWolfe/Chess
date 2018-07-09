#pragma once

#include <memory>
#include "PlayerAction.h"
#include "Position.h"
#include "MoveEffect.h"

namespace chess {

class GameManager;
enum class PieceType;


class Move : public PlayerAction {

public:
    Move(Position start, Position end);
    Move(Position start, Position end, std::unique_ptr<MoveEffect> &effect);
    Move(const Move &other_move);
    bool enactAction(GameManager &manager) const override;
    Move &operator=(const Move &other);
    bool operator==(const Move &other) const;
    Position getStart() const;
    Position getEnd() const;
    bool hasEffect() const;
    const MoveEffect *getEffect() const;
    bool isPromotionType() const;
    bool isEnPassantType() const;
    void setPromotionPiece(PieceType type);
    PieceType getPromotionPieceType() const;
    std::unique_ptr<MoveEffect> getCopyOfEffect() const;

private:
    Position start;
    Position end;
    std::unique_ptr<MoveEffect> effect;

    MoveEffectType getEffectType() const;

};


}
