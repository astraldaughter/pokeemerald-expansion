#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Panic reduces the power of special attacks by 50 percent")
{
    s16 reducedDamage;
    s16 normaleDamage;

    GIVEN {
        ASSUME(gMovesInfo[MOVE_SWIFT].category == DAMAGE_CATEGORY_SPECIAL);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Status1(STATUS1_PANIC); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_SWIFT); MOVE(player, MOVE_FLAME_WHEEL); }
        TURN { MOVE(opponent, MOVE_SWIFT); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SWIFT, opponent);
        HP_BAR(player, captureDamage: &reducedDamage);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FLAME_WHEEL, player);
        HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SWIFT, opponent);
        HP_BAR(player, captureDamage: &normaleDamage);
   } THEN { EXPECT_EQ(reducedDamage * 2, normaleDamage); }
}