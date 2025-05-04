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

SINGLE_BATTLE_TEST("Panic has a 25% chance of skipping the turn")
{
    PASSES_RANDOMLY(25, 100, RNG_PANIC);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Status1(STATUS1_PANIC); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } SCENE {
        MESSAGE("Wobbuffet is too panicked to move!");
    }
}

AI_SINGLE_BATTLE_TEST("AI avoids Scary Face when it can not panic target")
{
    u32 species, ability;

    PARAMETRIZE { species = SPECIES_KOMALA; ability = ABILITY_COMATOSE; }
    PARAMETRIZE { species = SPECIES_NACLI; ability = ABILITY_PURIFYING_SALT; }

    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT | AI_FLAG_OMNISCIENT);
        PLAYER(species) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_CELEBRATE, MOVE_SCARY_FACE); }
    } WHEN {
        TURN { SCORE_EQ(opponent, MOVE_CELEBRATE, MOVE_SCARY_FACE); } // Both get -10
    }
}