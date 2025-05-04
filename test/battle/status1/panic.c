#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Panic reduces the power of special attacks by 50%", s16 damage)
{
    bool32 panicked;
    PARAMETRIZE { panicked = FALSE; }
    PARAMETRIZE { panicked = TRUE; }
    GIVEN {
        ASSUME(GetMoveCategory(MOVE_SWIFT) == DAMAGE_CATEGORY_SPECIAL);
        PLAYER(SPECIES_WOBBUFFET) { if (panicked) Status1(STATUS1_PANIC); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SWIFT); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(0.5), results[1].damage);
    }
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

    PARAMETRIZE { species = SPECIES_WOBBUFFET; ability = ABILITY_COMATOSE; }

    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT | AI_FLAG_OMNISCIENT);
        PLAYER(species) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_CELEBRATE, MOVE_SCARY_FACE); }
    } WHEN {
        TURN { SCORE_EQ(opponent, MOVE_CELEBRATE, MOVE_SCARY_FACE); } // Both get -10
    }
}