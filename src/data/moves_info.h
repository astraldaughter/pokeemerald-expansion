#include "battle_dynamax.h"
#include "battle_anim_scripts.h"
#include "constants/battle.h"
#include "constants/battle_move_effects.h"
#include "constants/battle_script_commands.h"
#include "constants/battle_string_ids.h"
#include "constants/battle_z_move_effects.h"
#include "constants/hold_effects.h"
#include "constants/moves.h"
#include "constants/contest.h"

// The Gen. 4+ contest data comes from urpg's contest movedex.

#if B_BINDING_TURNS >= GEN_5
#define BINDING_TURNS "4 or 5"
#else
#define BINDING_TURNS "2 to 5"
#endif

// Shared Move Description entries

const u8 gNotDoneYetDescription[] = _(
    "This move can't be used. Its\n"
    "effect is in development.");

static const u8 sNullDescription[] = _("");

static const u8 sMegaDrainDescription[] = _(
    "A nutrient-draining attack. The\n"
    "user's HP is restored by half\n"
    "the damage taken by the target.");

static const u8 sHyperBeamDescription[] = _(
    "Powerful, but leaves the\n"
    "user immobile the next turn.");

static const u8 sRevengeDescription[] = _(
    "An attack that gains power\n"
    "if injured by the foe.");

static const u8 sPluckDescription[] = _(
    "Eats the foe's held Berry\n"
    "gaining its effect.");

static const u8 sHealingWishDescription[] = _(
    "The user faints to heal up\n"
    "the recipient.");

static const u8 sWringOutDescription[] = _(
    "The higher the foe's HP\n"
    "the more damage caused.");

static const u8 sUTurnDescription[] = _(
    "Does damage then switches\n"
    "out the user.");

static const u8 sStormThrowDescription[] = _(
    "This attack always results\n"
    "in a critical hit.");

static const u8 sCircleThrowDescription[] = _(
    "Knocks the foe away to end\n"
    "the battle.");

static const u8 sChipAwayDescription[] = _(
    "Strikes through the foe's\n"
    "stat changes.");

static const u8 sHeavySlamDescription[] = _(
    "Does more damage if the\n"
    "user outweighs the foe.");

static const u8 sPsyshockDescription[] = _(
    "Attacks with a psychic wave\n"
    "that does physical damage.");

static const u8 sLavaPlumeDescription[] = _(
    "Scarlet flames torch\n"
    "everything around the user.");

static const u8 sShadowForceDescription[] = _(
    "Vanishes on the first turn\n"
    "then strikes the next turn.");

static const u8 sFalseSwipeDescription[] = _(
    "An attack that leaves the\n"
    "foe with at least 1 HP.");

static const u8 sDrainingKissDescription[] = _(
    "An attack that absorbs over\n"
    "half the damage inflicted.");

static const u8 sCloseCombatDescription[] = _(
    "A strong attack but lowers\n"
    "the defensive stats.");

static const u8 sHyperspaceHoleDescription[] = _(
    "Uses a warp hole to attack.\n"
    "Can't be evaded.");

static const u8 sSuckerPunchDescription[] = _(
    "Strikes first if the foe\n"
    "is preparing an attack.");

static const u8 sFeintDescription[] = _(
    "An attack that hits foes\n"
    "using moves like Protect.");

const struct MoveInfo gMovesInfo[MOVES_COUNT_ALL] =
{
    [MOVE_NONE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("-"),
        .description = COMPOUND_STRING(""),
        .effect = EFFECT_HIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .metronomeBanned = TRUE,
        .mirrorMoveBanned = TRUE,
        .sketchBanned = TRUE,
        .assistBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_None,
    },

    [MOVE_POUND] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("POUND"),
        .description = COMPOUND_STRING(
			"The target is physically pounded\n"
			"with a long tail, a foreleg,\n"
			"or the like."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = B_UPDATED_MOVE_FLAGS == GEN_4,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_POUND,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Pound,
    },

    [MOVE_KARATE_CHOP] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("KARATE CHOP"),
        .description = COMPOUND_STRING(
            "The target is attacked with a\n"
			"sharp chop. Critical hits land\n"
			"more easily."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .criticalHitStage = 1,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .battleAnimScript = gBattleAnimMove_KarateChop,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DOUBLE_SLAP] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("DOUBLE SLAP"),
        .description = COMPOUND_STRING(
            "The target is slapped repeatedly back and forth, two to five times in a row."),
        .effect = EFFECT_MULTI_HIT,
        .power = 15,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_POUND},
        .battleAnimScript = gBattleAnimMove_DoubleSlap,
        .validApprenticeMove = TRUE,
    },

    [MOVE_COMET_PUNCH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("COMET PUNCH"),
        .description = COMPOUND_STRING(
            "Repeatedly punches the foe 2 to 5 times."),
        .effect = EFFECT_MULTI_HIT,
        .power = 18,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_CometPunch,
    },

    [MOVE_MEGA_PUNCH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("MEGA PUNCH"),
        .description = COMPOUND_STRING(
            "The target is slugged by a punch thrown with muscle-packed power. "),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_MIND_READER},
        .battleAnimScript = gBattleAnimMove_MegaPunch,
        .validApprenticeMove = TRUE,
    },

    [MOVE_PAY_DAY] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("PAY DAY"),
        .description = COMPOUND_STRING(
            "Numerous coins are hurled at the target to inflict damage. Money is earned after the battle."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PAYDAY,
        }),
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PayDay,
    },

    [MOVE_FIRE_PUNCH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FIRE PUNCH"),
        .description = COMPOUND_STRING(
            "The target is punched with a fiery fist. This may also leave the target with a burn."),
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_FIRE_PUNCH,
        .contestComboMoves = {COMBO_STARTER_ICE_PUNCH, COMBO_STARTER_SUNNY_DAY, COMBO_STARTER_THUNDER_PUNCH},
        .battleAnimScript = gBattleAnimMove_FirePunch,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ICE_PUNCH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ICE PUNCH"),
        .description = COMPOUND_STRING(
            "The target is punched with an icy fist. This may also leave the target frozen."),
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FREEZE_OR_FROSTBITE,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_ICE_PUNCH,
        .contestComboMoves = {COMBO_STARTER_FIRE_PUNCH, COMBO_STARTER_THUNDER_PUNCH},
        .battleAnimScript = gBattleAnimMove_IcePunch,
        .validApprenticeMove = TRUE,
    },

    [MOVE_THUNDER_PUNCH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("THUNDER PUNCH"),
        .description = COMPOUND_STRING(
            "The target is punched with an electrified fist. This may also leave the target with paralysis."),
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_THUNDER_PUNCH,
        .contestComboMoves = {COMBO_STARTER_CHARGE, COMBO_STARTER_FIRE_PUNCH, COMBO_STARTER_ICE_PUNCH},
        .battleAnimScript = gBattleAnimMove_ThunderPunch,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SCRATCH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SCRATCH"),
        .description = COMPOUND_STRING(
            "Hard, pointed, and sharp claws rake the target to inflict damage."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_SCRATCH,
        .contestComboMoves = {COMBO_STARTER_LEER},
        .battleAnimScript = gBattleAnimMove_Scratch,
    },

    [MOVE_VISE_GRIP] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("VICE GRIP"),
        .description = COMPOUND_STRING(
            "The target is gripped and squeezed with pincers to inflict damage."),
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_VICE_GRIP,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ViseGrip,
    },

    [MOVE_GUILLOTINE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("GUILLOTINE"),
        .description = COMPOUND_STRING(
            "A vicious, tearing attack with huge pincers. The target faints instantly if this attack hits."),
        .effect = EFFECT_OHKO,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 30,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_VICE_GRIP},
        .battleAnimScript = gBattleAnimMove_Guillotine,
        .validApprenticeMove = TRUE,
    },

    [MOVE_RAZOR_WIND] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("RAZOR WIND"),
        .description = COMPOUND_STRING(
            "The user attacks the target with powerful, slicing winds. Critical hits land more easily."),
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_FLYING,
        .accuracy = 90,
        .criticalHitStage = 1,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .windMove = B_EXTRAPOLATED_MOVE_FLAGS,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RazorWind,
    },

    [MOVE_SWORDS_DANCE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SWORDS DANCE"),
        .description = COMPOUND_STRING(
            "A frenetic dance to uplift the fighting spirit. This sharply raises the user's ATTACK stat."),
        .effect = EFFECT_ATTACK_UP_2,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 20 : 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .danceMove = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_SWORDS_DANCE,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SwordsDance,
        .validApprenticeMove = TRUE,
    },

    [MOVE_CUT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("CUT"),
        .description = COMPOUND_STRING(
            "The target is cut with a scythe or claw. This move is super effective on Grass types."),
        .effect = EFFECT_CUT,
        .power = 55,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SWORDS_DANCE},
        .battleAnimScript = gBattleAnimMove_Cut,
    },

    [MOVE_GUST] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("GUST"),
        .description = COMPOUND_STRING(
            "A gust of wind is whipped up by wings and launched at the target to inflict damage."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = (B_UPDATED_MOVE_FLAGS == GEN_4) || (B_UPDATED_MOVE_FLAGS < GEN_3),
        .damagesAirborneDoubleDamage = TRUE,
        .windMove = TRUE,
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Gust,
    },

    [MOVE_WING_ATTACK] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("WING ATTACK"),
        .description = COMPOUND_STRING(
            "The target is struck with large, imposing wings spread wide to inflict damage."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_WingAttack,
    },

    [MOVE_WHIRLWIND] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("WHIRLWIND"),
        .description = COMPOUND_STRING(
            "The target is blown away, and a different Pokémon is dragged out. In the wild, ends a battle."),
        .effect = EFFECT_ROAR,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_6 ? 0 : 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = -6,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .windMove = TRUE,
        .ignoresProtect = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Whirlwind,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FLY] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FLY"),
        .description = COMPOUND_STRING(
            "The user flies up into the sky on the first turn, then attacks on the following turn."),
        .effect = EFFECT_SEMI_INVULNERABLE,
        .power = B_UPDATED_MOVE_DATA >= GEN_4 ? 90 : 70,
        .type = TYPE_FLYING,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .gravityBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        .argument.twoTurnAttack = { .stringId =  STRINGID_PKMNFLEWHIGH, .status = COMPRESS_BITS(STATUS3_ON_AIR) },
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Fly,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BIND] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("BIND"),
        .description = COMPOUND_STRING(
            "Things such as long bodies or tentacles are used to bind the target for 4-5 turns."),
        .effect = EFFECT_HIT,
        .power = 15,
        .type = TYPE_NORMAL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 85 : 75,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = B_UPDATED_MOVE_FLAGS < GEN_3,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
        }),
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_VICE_GRIP},
        .battleAnimScript = gBattleAnimMove_Bind,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SLAM] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SLAM"),
        .description = COMPOUND_STRING(
            "The target is slammed with a long tail, vines, or the like to inflict damage."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 75,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_POUND},
        .battleAnimScript = gBattleAnimMove_Slam,
        .validApprenticeMove = TRUE,
    },

    [MOVE_VINE_WHIP] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("VINE WHIP"),
        .description = COMPOUND_STRING(
            "The target is struck with slender, whiplike vines to inflict damage."),
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .pp = 25,
        #elif B_UPDATED_MOVE_DATA >= GEN_4
            .pp = 15,
        #else
            .pp = 10,
        #endif
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 45 : 35,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .battleAnimScript = gBattleAnimMove_VineWhip,
    },

    [MOVE_STOMP] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("STOMP"),
        .description = COMPOUND_STRING(
            "The target is stomped with a big foot. This may also make the target flinch."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .minimizeDoubleDamage = TRUE,
        .skyBattleBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_LEER},
        .battleAnimScript = gBattleAnimMove_Stomp,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DOUBLE_KICK] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("DOUBLE KICK"),
        .description = COMPOUND_STRING(
            "The target is quickly kicked twice in succession using both feet."),
        .effect = EFFECT_HIT,
        .power = 30,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .strikeCount = 2,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DoubleKick,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MEGA_KICK] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("MEGA KICK"),
        .description = COMPOUND_STRING(
            "The target is attacked by a kick launched with muscle-packed power."),
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_NORMAL,
        .accuracy = 75,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_MIND_READER},
        .battleAnimScript = gBattleAnimMove_MegaKick,
        .validApprenticeMove = TRUE,
    },

    [MOVE_JUMP_KICK] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("JUMP KICK"),
        .description = COMPOUND_STRING(
            "The user jumps up high, then strikes with a kick. If the kick misses, the user hurts itself."),
        .power = 85,
        .effect = EFFECT_RECOIL_IF_MISS,
        .type = TYPE_FIGHTING,
        .accuracy = 95,
        .pp = B_UPDATED_MOVE_DATA >= GEN_5 ? 10 : 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .gravityBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_MIND_READER},
        .battleAnimScript = gBattleAnimMove_JumpKick,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ROLLING_KICK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ROLLING KICK"),
        .description = COMPOUND_STRING(
            "A fast kick delivered from a rapid spin."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FIGHTING,
        .accuracy = 85,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = B_UPDATED_MOVE_FLAGS < GEN_3,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RollingKick,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SAND_ATTACK] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SAND ATTACK"),
        .description = COMPOUND_STRING(
            "Sand is hurled in the target's face, reducing its accuracy. "),
        .effect = EFFECT_ACCURACY_DOWN,
        .power = 0,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_EVSN_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_SAND_ATTACK,
        .contestComboMoves = {COMBO_STARTER_MUD_SLAP, COMBO_STARTER_SANDSTORM},
        .battleAnimScript = gBattleAnimMove_SandAttack,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HEADBUTT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("HEADBUTT"),
        .description = COMPOUND_STRING(
            "The user attacks by charging headfirst into the target. This may also make the target flinch."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .battleAnimScript = gBattleAnimMove_Headbutt,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HORN_ATTACK] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("HORN ATTACK"),
        .description = COMPOUND_STRING(
            "The target is jabbed with a sharply pointed horn to inflict damage."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_HORN_ATTACK,
        .contestComboMoves = {COMBO_STARTER_LEER},
        .battleAnimScript = gBattleAnimMove_HornAttack,
    },

    [MOVE_FURY_ATTACK] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FURY ATTACK"),
        .description = COMPOUND_STRING(
            "The target is jabbed repeatedly with a horn or beak 2-5 times in a row."),
        .effect = EFFECT_MULTI_HIT,
        .power = 15,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HORN_ATTACK, COMBO_STARTER_PECK},
        .battleAnimScript = gBattleAnimMove_FuryAttack,
    },

    [MOVE_HORN_DRILL] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("HORN DRILL"),
        .description = COMPOUND_STRING(
            "The user stabs the target with a spinning horn. The target faints instantly if this attack hits."),
        .effect = EFFECT_OHKO,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 30,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HORN_ATTACK},
        .battleAnimScript = gBattleAnimMove_HornDrill,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TACKLE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("TACKLE"),
        .description = COMPOUND_STRING(
            "A physical attack in which the user charges and slams into the target with its whole body."),
        .power = 40,
        .effect = EFFECT_HIT,
        .type = TYPE_NORMAL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 100 : 95,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_DEFENSE_CURL, COMBO_STARTER_HARDEN, COMBO_STARTER_LEER},
        .battleAnimScript = gBattleAnimMove_Tackle,
    },

    [MOVE_BODY_SLAM] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("BODY SLAM"),
        .description = COMPOUND_STRING(
            "The user drops onto the target with its full body weight. This may also paralyze the target."),
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .minimizeDoubleDamage = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .skyBattleBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_BodySlam,
        .validApprenticeMove = TRUE,
    },

    [MOVE_WRAP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("WRAP"),
        .description = COMPOUND_STRING(
            "Wraps and squeezes the foe\n"
            BINDING_TURNS" times with vines, etc."),
        .effect = EFFECT_HIT,
        .power = 15,
        .type = TYPE_NORMAL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 90 : 85,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
        }),
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Wrap,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TAKE_DOWN] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("TAKE DOWN"),
        .description = COMPOUND_STRING(
            "A reckless, charging attack that slams into the target. This also damages the user a little."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .recoil = 25,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_HARDEN},
        .battleAnimScript = gBattleAnimMove_TakeDown,
        .validApprenticeMove = TRUE,
    },

    [MOVE_THRASH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("THRASH"),
        .description = COMPOUND_STRING(
            "The user rampages and attacks for 2-3 turns. The user then becomes confused."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 120 : 90,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_5 ? 10 : 20,
        .target = MOVE_TARGET_RANDOM,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .instructBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_THRASH,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAGE},
        .battleAnimScript = gBattleAnimMove_Thrash,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DOUBLE_EDGE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("DOUBLE-EDGE"),
        .description = COMPOUND_STRING(
            "A life-risking tackle where the user rushes the target and also damages the user quite a lot."),
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .recoil = 33,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_HARDEN},
        .battleAnimScript = gBattleAnimMove_DoubleEdge,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TAIL_WHIP] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("TAIL WHIP"),
        .description = COMPOUND_STRING(
            "The user wags its tail cutely to make opposing Pokémon less wary and lower their DEFENSE stats."),
        .effect = EFFECT_DEFENSE_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARM},
        .battleAnimScript = gBattleAnimMove_TailWhip,
    },

    [MOVE_POISON_STING] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("POISON STING"),
        .description = COMPOUND_STRING(
            "The user stabs the target with a poisonous stinger. This may also poison the target."),
        .effect = EFFECT_HIT,
        .power = 15,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PoisonSting,
    },

    [MOVE_TWINEEDLE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TWINEEDLE"),
        .description = COMPOUND_STRING(
            "Stingers on the forelegs jab the foe twice."),
        .effect = EFFECT_HIT,
        .power = 25,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresKingsRock = (B_UPDATED_MOVE_FLAGS == GEN_3 || B_UPDATED_MOVE_FLAGS == GEN_4),
        .strikeCount = 2,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 20,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Twineedle,
        .validApprenticeMove = TRUE,
    },

    [MOVE_PIN_MISSILE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("PIN MISSILE"),
        .description = COMPOUND_STRING(
            "Sharp spikes are shot at the target in rapid succession. They hit 2-5 times in a row."),
        .effect = EFFECT_MULTI_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 25 : 14,
        .type = TYPE_BUG,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_6 ? 95 : 85,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PinMissile,
    },

    [MOVE_LEER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("LEER"),
        .description = COMPOUND_STRING(
            "The user gives opposing Pokémon an intimidating leer that lowers the DEFENSE stat."),
        .effect = EFFECT_DEFENSE_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_LEER,
        .contestComboMoves = {COMBO_STARTER_RAGE, COMBO_STARTER_SCARY_FACE},
        .battleAnimScript = gBattleAnimMove_Leer,
    },

    [MOVE_BITE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("BITE"),
        .description = COMPOUND_STRING(
            "The target is bitten with sharp fangs. This may also make the target flinch."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_LEER, COMBO_STARTER_SCARY_FACE},
        .battleAnimScript = gBattleAnimMove_Bite,
        .validApprenticeMove = TRUE,
    },

    [MOVE_GROWL] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("GROWL"),
        .description = COMPOUND_STRING(
            "The user growls endearingly to make opposing Pokémon less wary, lowering their ATTACK stats."),
        .effect = EFFECT_ATTACK_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .magicCoatAffected = TRUE,
        .soundMove = TRUE,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARM},
        .battleAnimScript = gBattleAnimMove_Growl,
    },

    [MOVE_ROAR] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ROAR"),
        .description = COMPOUND_STRING(
            "The target is scared away, and a different Pokémon is dragged out. In the wild, ends a battle."),
        .effect = EFFECT_ROAR,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_6 ? 0 : 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = -6,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .ignoresProtect = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .soundMove = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Roar,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SING] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SING"),
        .description = COMPOUND_STRING(
            "A soothing lullaby is sung in a a calming voice that puts the target into a deep slumber."),
        .effect = EFFECT_SLEEP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 55,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .magicCoatAffected = TRUE,
        .soundMove = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_SING,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Sing,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SUPERSONIC] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SUPERSONIC"),
        .description = COMPOUND_STRING(
            "The user generates odd sound waves from its body that confuse the target."),
        .effect = EFFECT_CONFUSE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 55,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .magicCoatAffected = TRUE,
        .soundMove = TRUE,
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Supersonic,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SONIC_BOOM] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SONIC BOOM"),
        .description = COMPOUND_STRING(
            "The user makes a sonic boom that hits opposing Pokémon. This move always goes first."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 1,
        .soundMove = TRUE,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SonicBoom,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DISABLE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("DISABLE"),
        .description = COMPOUND_STRING(
            "For four turns, this move prevents the target from using the last move it used."),
        .accuracy = 100,
        .effect = EFFECT_DISABLE,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Disable,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ACID] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ACID"),
        .description = COMPOUND_STRING(
            "Opposing Pokémon are attacked with a spray of harsh acid. This may lower their DEFENSE stats."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
            .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 50,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Acid,
    },

    [MOVE_EMBER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("EMBER"),
        .description = COMPOUND_STRING(
            "The target is attacked with small flames. This may also leave the target with a burn."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_Ember,
    },

    [MOVE_FLAMETHROWER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FLAMETHROWER"),
        .description = COMPOUND_STRING(
            "The target is scorched with an intense blast of fire. This may also burn the target."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 90 : 95,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_Flamethrower,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MIST] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("MIST"),
        .description = COMPOUND_STRING(
            "The user cloaks itself and its allies in a mist that stops their stats being lowered for 5 turns."),
        .effect = EFFECT_MIST,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RECOVER_HP },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Mist,
        .validApprenticeMove = TRUE,
    },

    [MOVE_WATER_GUN] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("WATER GUN"),
        .description = COMPOUND_STRING(
            "The target is blasted with a forceful shot of water. "),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_MUD_SPORT, COMBO_STARTER_RAIN_DANCE, COMBO_STARTER_WATER_SPORT},
        .battleAnimScript = gBattleAnimMove_WaterGun,
    },

    [MOVE_HYDRO_PUMP] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("HYDRO PUMP"),
        .description = COMPOUND_STRING(
            "The target is blasted by a huge volume of water launched under great pressure."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 110 : 120,
        .type = TYPE_WATER,
        .accuracy = 80,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_HydroPump,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SURF] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SURF"),
        .description = COMPOUND_STRING(
            "Attacks foes by creating a giant wave and crashing it down on them."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .damagesUnderwater = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_SURF,
        .contestComboMoves = {COMBO_STARTER_DIVE, COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_Surf,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ICE_BEAM] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ICE BEAM"),
        .description = COMPOUND_STRING(
            "The target is struck with an ice cold beam of energy. This may also leave the target frozen."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 90 : 95,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            // The following effect is also relevant in battle_Pike.c
            // If you cherry-pick this to use something other than the config, make sure to update it there too
            .moveEffect = MOVE_EFFECT_FREEZE_OR_FROSTBITE,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HAIL},
        .battleAnimScript = gBattleAnimMove_IceBeam,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BLIZZARD] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("BLIZZARD"),
        .description = COMPOUND_STRING(
            "A howling blizzard is summoned to strike opposing Pokémon. This may freeze the opposing Pokémon."),
        .effect = B_BLIZZARD_HAIL >= GEN_4 ? EFFECT_BLIZZARD : EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 110 : 120,
        .type = TYPE_ICE,
        .accuracy = 85,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .windMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FREEZE_OR_FROSTBITE,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HAIL, COMBO_STARTER_POWDER_SNOW},
        .battleAnimScript = gBattleAnimMove_Blizzard,
        .validApprenticeMove = TRUE,
    },

    [MOVE_PSYBEAM] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("PSYBEAM"),
        .description = COMPOUND_STRING(
            "The target is attacked with a peculiar ray. This may also leave the target confused."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND},
        .battleAnimScript = gBattleAnimMove_Psybeam,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BUBBLE_BEAM] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("BUBBLE BEAM"),
        .description = COMPOUND_STRING(
            "A spray of bubbles is forcefully ejected at the target. This may also lower the target's SPEED."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_BubbleBeam,
    },

    [MOVE_AURORA_BEAM] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("AURORA BEAM"),
        .description = COMPOUND_STRING(
            "The target is hit with a rainbow colored beam. This may also lower the target's ATTACK stat."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_MINUS_1,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HAIL},
        .battleAnimScript = gBattleAnimMove_AuroraBeam,
    },

    [MOVE_HYPER_BEAM] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("HYPER BEAM"),
        .description = COMPOUND_STRING(
            "The target is attacked with a powerful beam. The user can't move on the next turn."),
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = B_UPDATED_MOVE_FLAGS < GEN_3,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HyperBeam,
        .validApprenticeMove = TRUE,
    },

    [MOVE_PECK] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("PECK"),
        .description = COMPOUND_STRING(
            "The target is jabbed with a sharply pointed beak. "),
        .effect = EFFECT_HIT,
        .power = 35,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_PECK,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Peck,
    },

    [MOVE_DRILL_PECK] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("DRILL PECK"),
        .description = COMPOUND_STRING(
            "A corkscrewing attack that strikes the target with a sharp beak acting as a drill."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_PECK},
        .battleAnimScript = gBattleAnimMove_DrillPeck,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SUBMISSION] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SUBMISSION"),
        .description = COMPOUND_STRING(
            "A reckless body slam that also hurts the user."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FIGHTING,
        .accuracy = 80,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 20 : 25,
        .recoil = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_MIND_READER},
        .battleAnimScript = gBattleAnimMove_Submission,
        .validApprenticeMove = TRUE,
    },

    [MOVE_LOW_KICK] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("LOW KICK"),
        .description = COMPOUND_STRING(
            "A powerful low kick that makes the target fall over. Heavier targets take more damage."),
        .effect = EFFECT_LOW_KICK,
        .power = 1,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_LowKick,
        .validApprenticeMove = TRUE,
    },

    [MOVE_COUNTER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("COUNTER"),
        .description = COMPOUND_STRING(
            "A retaliation move that counters any physical attack, inflicting double the damage taken."),
        .effect = EFFECT_COUNTER,
        .power = 1,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_DEPENDS,
        .priority = -5,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = (B_UPDATED_MOVE_FLAGS == GEN_3 || B_UPDATED_MOVE_FLAGS == GEN_4),
        .meFirstBanned = TRUE,
        //.metronomeBanned = B_UPDATED_MOVE_FLAGS >= GEN_2,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_TAUNT},
        .battleAnimScript = gBattleAnimMove_Counter,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SEISMIC_TOSS] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SEISMIC TOSS"),
        .description = COMPOUND_STRING(
            "The target is powerfully thrown to the ground, inflicting damage equal to the user's level."),
        .effect = EFFECT_LEVEL_DAMAGE,
        .power = 1,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FAKE_OUT},
        .battleAnimScript = gBattleAnimMove_SeismicToss,
        .validApprenticeMove = TRUE,
    },

    [MOVE_STRENGTH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("STRENGTH"),
        .description = COMPOUND_STRING(
            "The target is struck with a tackle thrown at maximum power. "),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Strength,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ABSORB] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ABSORB"),
        .description = sMegaDrainDescription,
        .effect = EFFECT_ABSORB,
        .power = 20,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_4 ? 25 : 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .argument = { .absorbPercentage = 50 },
        .ignoresKingsRock = (B_UPDATED_MOVE_FLAGS == GEN_3 || B_UPDATED_MOVE_FLAGS == GEN_4),
        .healingMove = B_HEAL_BLOCKING >= GEN_6,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .battleAnimScript = gBattleAnimMove_Absorb,
    },

    [MOVE_MEGA_DRAIN] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("MEGA DRAIN"),
        .description = sMegaDrainDescription,
        .effect = EFFECT_ABSORB,
        .power = 40,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_4 ? 15 : 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .argument = { .absorbPercentage = 50 },
        .zMove = { .powerOverride = 120 },
        .ignoresKingsRock = (B_UPDATED_MOVE_FLAGS == GEN_3 || B_UPDATED_MOVE_FLAGS == GEN_4),
        .healingMove = B_HEAL_BLOCKING >= GEN_6,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .battleAnimScript = gBattleAnimMove_MegaDrain,
    },

    [MOVE_LEECH_SEED] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("LEECH SEED"),
        .description = COMPOUND_STRING(
            "A seed is planted on the target. It steals some HP from the target every turn."),
        .effect = EFFECT_LEECH_SEED,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_LEECH_SEED,
        .contestComboMoves = {COMBO_STARTER_GROWTH, COMBO_STARTER_WORRY_SEED},
        .battleAnimScript = gBattleAnimMove_LeechSeed,
        .validApprenticeMove = TRUE,
    },

    [MOVE_GROWTH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("GROWTH"),
        .description = COMPOUND_STRING(
            "The user's body grows all at once, raising the ATTACK and SP. ATK stats."),
        .effect = B_GROWTH_STAT_RAISE >= GEN_5 ? EFFECT_GROWTH : EFFECT_SPECIAL_ATTACK_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 20 : 40,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_GROWTH,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Growth,
        .validApprenticeMove = TRUE,
    },

    [MOVE_RAZOR_LEAF] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("RAZOR LEAF"),
        .description = COMPOUND_STRING(
            "Sharp-edged leaves are launched to slash at opposing Pokémon. Critical hits land more easily."),
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_GRASS,
        .accuracy = 95,
        .criticalHitStage = 1,
        .pp = 25,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .slicingMove = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .battleAnimScript = gBattleAnimMove_RazorLeaf,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SOLAR_BEAM] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SOLAR BEAM"),
        .description = COMPOUND_STRING(
            "The user gathers light, then with a beam on the next turn. This only takes one turn in sun."),
        .effect = EFFECT_SOLAR_BEAM,
        .power = 120,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .argument.twoTurnAttack = { .stringId =  STRINGID_PKMNTOOKSUNLIGHT, .status = B_WEATHER_SUN },
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH, COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_SolarBeam,
        .validApprenticeMove = TRUE,
    },

    [MOVE_POISON_POWDER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("POISON POWDER"),
        .description = COMPOUND_STRING(
            "The user scatters a cloud of toxic dust that poisons the target."),
        .effect = EFFECT_POISON,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 75,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .magicCoatAffected = TRUE,
        .powderMove = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SWEET_SCENT},
        .battleAnimScript = gBattleAnimMove_PoisonPowder,
        .validApprenticeMove = TRUE,
    },

    [MOVE_STUN_SPORE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("STUN SPORE"),
        .description = COMPOUND_STRING(
            "The user scatters a cloud of numbing powder that paralyzes the target."),
        .effect = EFFECT_PARALYZE,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 75,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .magicCoatAffected = TRUE,
        .powderMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SWEET_SCENT},
        .battleAnimScript = gBattleAnimMove_StunSpore,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SLEEP_POWDER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SLEEP POWDER"),
        .description = COMPOUND_STRING(
            "The user scatters a big cloud of sleep-inducing dust around the target."),
        .effect = EFFECT_SLEEP,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 75,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .magicCoatAffected = TRUE,
        .powderMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SWEET_SCENT},
        .battleAnimScript = gBattleAnimMove_SleepPowder,
        .validApprenticeMove = TRUE,
    },

    [MOVE_PETAL_DANCE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("PETAL DANCE"),
        .description = COMPOUND_STRING(
            "The user attacks the target by scattering petals for 2-3 turns. The user then becomes confused."),
        .power = 120,
        .effect = EFFECT_HIT,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_5 ? 10 : 20,
        .target = MOVE_TARGET_RANDOM,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .danceMove = TRUE,
        .instructBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_THRASH,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .battleAnimScript = gBattleAnimMove_PetalDance,
        .validApprenticeMove = TRUE,
    },

    [MOVE_STRING_SHOT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("STRING SHOT"),
        .description = COMPOUND_STRING(
            "Opposing Pokémon are bound with silk blown from the user's mouth that harshly lowers SPEED."),
        .effect = B_UPDATED_MOVE_DATA >= GEN_6 ? EFFECT_SPEED_DOWN_2 : EFFECT_SPEED_DOWN,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 95,
        .pp = 40,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_STRING_SHOT,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_StringShot,
    },

    [MOVE_DRAGON_RAGE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("DRAGON RAGE"),
        .description = COMPOUND_STRING(
            "This attack hits the target with a shock wave of pure rage that always inflicts 40 HP damage."),
        .effect = EFFECT_FIXED_DAMAGE_ARG,
        .power = 1,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = (B_UPDATED_MOVE_FLAGS == GEN_4) || (B_UPDATED_MOVE_FLAGS < GEN_3),
        .argument = { .fixedDamage = 40 },
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_DRAGON_RAGE,
        .contestComboMoves = {COMBO_STARTER_DRAGON_BREATH, COMBO_STARTER_DRAGON_DANCE, COMBO_STARTER_TYRANT_CRUSH, COMBO_STARTER_DRAGON_TAIL},
        .battleAnimScript = gBattleAnimMove_DragonRage,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FIRE_SPIN] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FIRE SPIN"),
        .description = COMPOUND_STRING(
            "The target becomes trapped in a fierce vortex of fire that rages for 4-5 turns."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 35 : 15,
        .type = TYPE_FIRE,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 85 : 70,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = B_UPDATED_MOVE_FLAGS < GEN_3,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
        }),
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_FireSpin,
        .validApprenticeMove = TRUE,
    },

    [MOVE_THUNDER_SHOCK] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("THUNDER SHOCK"),
        .description = COMPOUND_STRING(
            "A jolt of electricity strikes the target to inflict damage. This may also paralyze the target."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARGE},
        .battleAnimScript = gBattleAnimMove_ThunderShock,
    },

    [MOVE_THUNDERBOLT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("THUNDERBOLT"),
        .description = COMPOUND_STRING(
            "A strong electric blast strikes the target. This may also paralyze the target."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 90 : 95,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARGE},
        .battleAnimScript = gBattleAnimMove_Thunderbolt,
        .validApprenticeMove = TRUE,
    },

    [MOVE_THUNDER_WAVE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("THUNDER WAVE"),
        .description = COMPOUND_STRING(
            "The user launches a weak jolt of electricity that paralyzes the target."),
        .effect = EFFECT_PARALYZE,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_7 ? 90 : 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARGE},
        .battleAnimScript = gBattleAnimMove_ThunderWave,
        .validApprenticeMove = TRUE,
    },

    [MOVE_THUNDER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("THUNDER"),
        .description = COMPOUND_STRING(
            "A wicked thunderbolt strikes the target to inflict damage. This may also paralyze the target."),
        .effect = EFFECT_THUNDER,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 110 : 120,
        .type = TYPE_ELECTRIC,
        .accuracy = 70,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .damagesAirborne = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARGE, COMBO_STARTER_LOCK_ON, COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_Thunder,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ROCK_THROW] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ROCK THROW"),
        .description = COMPOUND_STRING(
            "The user picks up and throws a small rock at the target to attack."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_ROCK,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_ROCK_THROW,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RockThrow,
    },

    [MOVE_EARTHQUAKE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("EARTHQUAKE"),
        .description = COMPOUND_STRING(
            "The user causes an earthquake that strikes every Pokémon around it."),
        .effect = EFFECT_EARTHQUAKE,
        .power = 100,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresKingsRock = B_UPDATED_MOVE_FLAGS < GEN_3,
        .damagesUnderground = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_EARTHQUAKE,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Earthquake,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FISSURE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FISSURE"),
        .description = COMPOUND_STRING(
            "The user drops the target into a fissure. The target faints instantly if this attack hits."),
        .effect = EFFECT_OHKO,
        .power = 1,
        .type = TYPE_GROUND,
        .accuracy = 30,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .damagesUnderground = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_EARTHQUAKE},
        .battleAnimScript = gBattleAnimMove_Fissure,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DIG] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("DIG"),
        .description = COMPOUND_STRING(
            "The user burrows into the ground, then attacks on the next turn."),
        .effect = EFFECT_SEMI_INVULNERABLE,
        .power = B_UPDATED_MOVE_DATA >= GEN_4 ? 80 : 60,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        .skyBattleBanned = TRUE,
        .argument.twoTurnAttack = { .stringId = STRINGID_PKMNDUGHOLE, .status = COMPRESS_BITS(STATUS3_UNDERGROUND) },
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Dig,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TOXIC] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("TOXIC"),
        .description = COMPOUND_STRING(
            "A move that leaves the target badly poisoned. Its poison damage worsens every turn."),
        .effect = EFFECT_TOXIC,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 90 : 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_TOXIC,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Toxic,
        .validApprenticeMove = TRUE,
    },

    [MOVE_CONFUSION] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("CONFUSION"),
        .description = COMPOUND_STRING(
            "The target is hit by a weak telekinetic force. This may also confuse the target."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 20,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_CONFUSION,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND, COMBO_STARTER_KINESIS, COMBO_STARTER_PSYCHIC},
        .battleAnimScript = gBattleAnimMove_Confusion,
    },

    [MOVE_PSYCHIC] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("PSYCHIC"),
        .description = COMPOUND_STRING(
            "The target is hit by a strong telekinetic force. This may also lower the target's SP. DEF."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_PSYCHIC,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND, COMBO_STARTER_CONFUSION, COMBO_STARTER_KINESIS},
        .battleAnimScript = gBattleAnimMove_Psychic,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HYPNOSIS] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("HYPNOSIS"),
        .description = COMPOUND_STRING(
            "The user employs hypnotic suggestion to make the target fall into a deep sleep."),
        .effect = EFFECT_SLEEP,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 60,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_HYPNOSIS,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Hypnosis,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MEDITATE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("MEDITATE"),
        .description = COMPOUND_STRING(
            "The user meditates to awaken the power deep within its body and raise its ATTACK stat."),
        .effect = EFFECT_ATTACK_UP,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND},
        .battleAnimScript = gBattleAnimMove_Meditate,
        .validApprenticeMove = TRUE,
    },

    [MOVE_AGILITY] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("AGILITY"),
        .description = COMPOUND_STRING(
            "The user relaxes and lightens its body to move faster. This sharply raises the SPEED stat."),
        .effect = EFFECT_SPEED_UP_2,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_DOUBLE_TEAM},
        .battleAnimScript = gBattleAnimMove_Agility,
        .validApprenticeMove = TRUE,
    },

    [MOVE_QUICK_ATTACK] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("QUICK ATTACK"),
        .description = COMPOUND_STRING(
            "The user lunges at the target at blinding speed. This move always goes first."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_DOUBLE_TEAM},
        .battleAnimScript = gBattleAnimMove_QuickAttack,
        .validApprenticeMove = TRUE,
    },

    [MOVE_RAGE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("RAGE"),
        .description = COMPOUND_STRING(
            "As long as this move is in use, the power of rage raises the user's ATTACK when it's hit."),
        .effect = EFFECT_RAGE,
        .power = 45,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_RAGE,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Rage,
    },

    [MOVE_TELEPORT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("TELEPORT"),
        .description = COMPOUND_STRING(
            "The user switches places with a party Pokémon. If used by a wild Pokémon, it flees instead."),
        .effect = EFFECT_TELEPORT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = -6,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RECOVER_HP },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CONFUSION, COMBO_STARTER_DOUBLE_TEAM, COMBO_STARTER_KINESIS, COMBO_STARTER_PSYCHIC},
        .battleAnimScript = gBattleAnimMove_Teleport,
    },

    [MOVE_NIGHT_SHADE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("NIGHT SHADE"),
        .description = COMPOUND_STRING(
            "The target is shown a horrific mirage, inflicting damage equal to the user's level."),
        .effect = EFFECT_LEVEL_DAMAGE,
        .power = 1,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_NightShade,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MIMIC] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("MIMIC"),
        .description = COMPOUND_STRING(
            "The user copies the target's last move. It can be used until the Pokémon is switched out."),
        .effect = EFFECT_MIMIC,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ACC_UP_1 },
        .ignoresSubstitute = TRUE,
        .mimicBanned = TRUE,
        //.metronomeBanned = B_UPDATED_MOVE_FLAGS >= GEN_2,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Mimic,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SCREECH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SCREECH"),
        .description = COMPOUND_STRING(
            "An earsplitting screech harshly lowers the target's DEFENSE. "),
        .effect = EFFECT_DEFENSE_DOWN_2,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .magicCoatAffected = TRUE,
        .soundMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Screech,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DOUBLE_TEAM] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("DOUBLE TEAM"),
        .description = COMPOUND_STRING(
            "By moving rapidly, the user makes illusory copies of itself to raise its evasiveness."),
        .effect = EFFECT_EVASION_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_DOUBLE_TEAM,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DoubleTeam,
        .validApprenticeMove = TRUE,
    },

    [MOVE_RECOVER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("RECOVER"),
        .description = COMPOUND_STRING(
            "Restoring its own cells, the user restores its own HP by half its max HP."),
        .pp = 10,
        .effect = EFFECT_RESTORE_HP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Recover,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HARDEN] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("HARDEN"),
        .description = COMPOUND_STRING(
            "The user stiffens all the muscles in its body to raise its DEFENSE stat."),
        .effect = EFFECT_DEFENSE_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_HARDEN,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Harden,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MINIMIZE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("MINIMIZE"),
        .description = COMPOUND_STRING(
            "The user compresses its body to make itself look smaller, which sharply raises its evasiveness."),
        .effect = EFFECT_MINIMIZE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 10 : 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Minimize,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SMOKESCREEN] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SMOKESCREEN"),
        .description = COMPOUND_STRING(
            "The user releases an obscuring cloud of smoke or ink. This lowers the target's accuracy."),
        .effect = EFFECT_ACCURACY_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_EVSN_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SMOG},
        .battleAnimScript = gBattleAnimMove_Smokescreen,
        .validApprenticeMove = TRUE,
    },

    [MOVE_CONFUSE_RAY] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("CONFUSE RAY"),
        .description = COMPOUND_STRING(
            "The target is exposed to a sinister ray that triggers confusion."),
        .effect = EFFECT_CONFUSE,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ConfuseRay,
        .validApprenticeMove = TRUE,
    },

    [MOVE_WITHDRAW] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("WITHDRAW"),
        .description = COMPOUND_STRING(
            "The user withdraws its body into its hard shell, raising its DEFENSE stat."),
        .effect = EFFECT_DEFENSE_UP,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_Withdraw,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DEFENSE_CURL] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("DEFENSE CURL"),
        .description = COMPOUND_STRING(
            "The user curls up to conceal weak spots and raise its DEFENSE stat."),
        .effect = EFFECT_DEFENSE_CURL,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ACC_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_DEFENSE_CURL,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DefenseCurl,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BARRIER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("BARRIER"),
        .description = COMPOUND_STRING(
            "The user throws up a sturdy wall that sharply raises its DEFENSE stat."),
        .effect = EFFECT_DEFENSE_UP_2,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 20 : 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Barrier,
        .validApprenticeMove = TRUE,
    },

    [MOVE_LIGHT_SCREEN] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("LIGHT SCREEN"),
        .description = COMPOUND_STRING(
            "A wondrous wall of light is put up to reduce damage from special attacks for 5 turns."),
        .effect = EFFECT_LIGHT_SCREEN,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND},
        .battleAnimScript = gBattleAnimMove_LightScreen,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HAZE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("HAZE"),
        .description = COMPOUND_STRING(
            "The user creates a haze that eliminates all stat changes of all active Pokémon."),
        .effect = EFFECT_HAZE,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RECOVER_HP },
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HAIL},
        .battleAnimScript = gBattleAnimMove_Haze,
        .validApprenticeMove = TRUE,
    },

    [MOVE_REFLECT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("REFLECT"),
        .description = COMPOUND_STRING(
            "A wondrous wall of light is put up to reduce damage from physical attacks for 5 turns."),
        .effect = EFFECT_REFLECT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND},
        .battleAnimScript = gBattleAnimMove_Reflect,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FOCUS_ENERGY] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FOCUS ENERGY"),
        .description = COMPOUND_STRING(
            "The user takes a deep breath and focuses so that critical hits land more easily."),
        .effect = EFFECT_FOCUS_ENERGY,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ACC_UP_1 },
        .argument = { .status = STATUS2_FOCUS_ENERGY },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_FOCUS_ENERGY,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FocusEnergy,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BIDE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("BIDE"),
        .description = COMPOUND_STRING(
            "The user endures attacks for 2 turns, then strikes back to cause double the damage taken."),
        .effect = EFFECT_BIDE,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_4 ? 0 : 100,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = B_UPDATED_MOVE_DATA >= GEN_4 ? 1 : 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Bide,
    },

    [MOVE_METRONOME] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("METRONOME"),
        .description = COMPOUND_STRING(
            "The user waggles a finger and stimulates its brain into randomly using nearly any move."),
        .effect = EFFECT_METRONOME,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .mimicBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = B_UPDATED_MOVE_FLAGS >= GEN_3,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Metronome,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MIRROR_MOVE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MIRROR MOVE"),
        .description = COMPOUND_STRING(
            "Counters the foe's attack with the same move."),
        .effect = EFFECT_MIRROR_MOVE,
        .power = 0,
        .type = TYPE_FLYING,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_2 },
        .mimicBanned = TRUE,
        //.metronomeBanned = B_UPDATED_MOVE_FLAGS >= GEN_4,
        .copycatBanned = TRUE,
        .sleepTalkBanned = B_UPDATED_MOVE_FLAGS >= GEN_3,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MirrorMove,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SELF_DESTRUCT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SELF-DESTRUCT"),
        .description = COMPOUND_STRING(
            "The user blows up to inflict damage on all Pokémon in battle, and then faints afterwards."),
        .effect = EFFECT_EXPLOSION,
        .power = 200,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .parentalBondBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_GREAT_APPEAL_BUT_NO_MORE_MOVES,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SelfDestruct,
        .validApprenticeMove = TRUE,
    },

    [MOVE_EGG_BOMB] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("EGG BOMB"),
        .description = COMPOUND_STRING(
            "An egg is forcibly hurled at the foe."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_NORMAL,
        .accuracy = 75,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ballisticMove = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SOFT_BOILED},
        .battleAnimScript = gBattleAnimMove_EggBomb,
        .validApprenticeMove = TRUE,
    },

    [MOVE_LICK] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("LICK"),
        .description = COMPOUND_STRING(
            "The target is licked with a long tongue, causing damage. This may also paralyze the target."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 30 : 20,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Lick,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SMOG] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SMOG"),
        .description = COMPOUND_STRING(
            "The target is attacked with a discharge of filthy gases. This may also poison the target."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 30 : 20,
        .type = TYPE_POISON,
        .accuracy = 85,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 40,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_SMOG,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Smog,
    },

    [MOVE_SLUDGE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SLUDGE"),
        .description = COMPOUND_STRING(
            "Unsanitary sludge is hurled at the target. This may also poison the target."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_SLUDGE,
        .contestComboMoves = {COMBO_STARTER_SLUDGE_BOMB},
        .battleAnimScript = gBattleAnimMove_Sludge,
    },

    [MOVE_BONE_CLUB] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("BONE CLUB"),
        .description = COMPOUND_STRING(
            "The user clubs the target with a bone. This may also make the target flinch."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_GROUND,
        .accuracy = 85,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_BONE_CLUB,
        .contestComboMoves = {COMBO_STARTER_BONEMERANG, COMBO_STARTER_BONE_RUSH, COMBO_STARTER_SHADOW_BONE},
        .battleAnimScript = gBattleAnimMove_BoneClub,
    },

    [MOVE_FIRE_BLAST] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FIRE BLAST"),
        .description = COMPOUND_STRING(
            "The target is blasted with an all-consuming fire. This may also burn the target."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 110 : 120,
        .type = TYPE_FIRE,
        .accuracy = 85,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_FireBlast,
        .validApprenticeMove = TRUE,
    },

    [MOVE_WATERFALL] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("WATERFALL"),
        .description = COMPOUND_STRING(
            "The user charges at the target and may make it flinch. "),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        #if B_UPDATED_MOVE_DATA >= GEN_4
            .additionalEffects = ADDITIONAL_EFFECTS({
                .moveEffect = MOVE_EFFECT_FLINCH,
                .chance = 20,
            }),
        #endif
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_Waterfall,
        .validApprenticeMove = TRUE,
    },

    [MOVE_CLAMP] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("CLAMP"),
        .description = COMPOUND_STRING(
            "The target is clamped and squeezed by the user's shell for 4-5 turns."),
        .effect = EFFECT_HIT,
        .power = 35,
        .type = TYPE_WATER,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 85 : 75,
        .pp = B_UPDATED_MOVE_DATA >= GEN_5 ? 15 : 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = B_UPDATED_MOVE_FLAGS < GEN_3,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
        }),
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_Clamp,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SWIFT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SWIFT"),
        .description = COMPOUND_STRING(
            "Star-shaped rays are shot at opposing Pokémon. This attack never misses."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Swift,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SKULL_BASH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SKULL BASH"),
        .description = COMPOUND_STRING(
            "The user tucks in its head to raise its DEFENSE, then rams the target on the next turn."),
        .effect = EFFECT_TWO_TURNS_ATTACK,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 130 : 100,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 10 : 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .argument.twoTurnAttack = { .stringId = STRINGID_PKMNLOWEREDHEAD },
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_PLUS_1,
            .self = TRUE,
            .onChargeTurnOnly = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SkullBash,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SPIKE_CANNON] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SPIKE CANNON"),
        .description = COMPOUND_STRING(
            "Sharp spikes are shot at the target in rapid succession. They hit 2-5 times in a row."),
        .effect = EFFECT_MULTI_HIT,
        .power = 20,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SpikeCannon,
    },

    [MOVE_CONSTRICT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("CONSTRICT"),
        .description = COMPOUND_STRING(
            "The target is constricted to inflict pain. This may also lower the target's SPEED."),
        .effect = EFFECT_HIT,
        .power = 10,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Constrict,
    },

    [MOVE_AMNESIA] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("AMNESIA"),
        .description = COMPOUND_STRING(
            "The user temporarily empties its mind to forget its concerns and sharply raise its SP. DEF stat."),
        .effect = EFFECT_SPECIAL_DEFENSE_UP_2,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Amnesia,
        .validApprenticeMove = TRUE,
    },

    [MOVE_KINESIS] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("KINESIS"),
        .description = COMPOUND_STRING(
            "Distracts the foe. May lower accuracy."),
        .effect = EFFECT_ACCURACY_DOWN,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 80,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_EVSN_UP_1 },
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_KINESIS,
        .contestComboMoves = {COMBO_STARTER_CONFUSION, COMBO_STARTER_PSYCHIC},
        .battleAnimScript = gBattleAnimMove_Kinesis,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SOFT_BOILED] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SOFT-BOILED"),
        .description = COMPOUND_STRING(
            "By consuming an egg, the user restores its own HP by up to half of its max HP."),
        .effect = EFFECT_SOFTBOILED,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .healingMove = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_SOFT_BOILED,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SoftBoiled,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HIGH_JUMP_KICK] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("HIGH JUMP KICK"),
        .description = COMPOUND_STRING(
            "The target is attacked with a jumping knee kick. If it misses, the user is hurt instead."),
        .power = 100,
        .effect = EFFECT_RECOIL_IF_MISS,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = B_UPDATED_MOVE_DATA >= GEN_5 ? 10 : 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .gravityBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_MIND_READER},
        .battleAnimScript = gBattleAnimMove_HighJumpKick,
        .validApprenticeMove = TRUE,
    },

    [MOVE_GLARE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("GLARE"),
        .description = COMPOUND_STRING(
            "The user transfixes the target with terrifying sharp eyes, frightening it into paralysis."),
        .accuracy = 100,
        .effect = EFFECT_PARALYZE,
        .power = 0,
        .type = TYPE_NORMAL,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_LEER},
        .battleAnimScript = gBattleAnimMove_Glare,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DREAM_EATER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("DREAM EATER"),
        .description = COMPOUND_STRING(
            "The user eats the dreams of a sleeping target, restoring its HP by half the damage dealt."),
        .effect = EFFECT_DREAM_EATER,
        .power = 100,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .healingMove = B_HEAL_BLOCKING >= GEN_6,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND, COMBO_STARTER_HYPNOSIS},
        .battleAnimScript = gBattleAnimMove_DreamEater,
        .validApprenticeMove = TRUE,
    },

    [MOVE_POISON_GAS] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("POISON GAS"),
        .description = COMPOUND_STRING(
            "A cloud of poison gas is sprayed in the face of opposing Pokémon, poisoning those it hits."),
        .accuracy = 90,
        .effect = EFFECT_POISON,
        .power = 0,
        .type = TYPE_POISON,
        .pp = 40,
        .target = B_UPDATED_MOVE_DATA >= GEN_5 ? MOVE_TARGET_BOTH : MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PoisonGas,
    },

    [MOVE_BARRAGE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BARRAGE"),
        .description = COMPOUND_STRING(
            "Hurls round objects at the foe 2 to 5 times."),
        .effect = EFFECT_MULTI_HIT,
        .power = 15,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ballisticMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Barrage,
    },

    [MOVE_LEECH_LIFE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("LEECH LIFE"),
        .description = COMPOUND_STRING(
            "The user drains the target's blood, restoring its HP by half the damage taken by the target."),
        .effect = EFFECT_ABSORB,
        .power = 35,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .argument = { .absorbPercentage = 50 },
        .makesContact = TRUE,
        .ignoresKingsRock = (B_UPDATED_MOVE_FLAGS == GEN_3 || B_UPDATED_MOVE_FLAGS == GEN_4),
        .healingMove = B_HEAL_BLOCKING >= GEN_6,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_LeechLife,
    },

    [MOVE_LOVELY_KISS] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("LOVELY KISS"),
        .description = COMPOUND_STRING(
            "With a scary face, the user tries to force a kiss on the target that induces sleep."),
        .effect = EFFECT_SLEEP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 75,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_LovelyKiss,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SKY_ATTACK] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SKY ATTACK"),
        .description = COMPOUND_STRING(
            "A two-turn attack move that may also make the target flinch. Critical hits land more easily."),
        .effect = EFFECT_TWO_TURNS_ATTACK,
        .power = 140,
        .type = TYPE_FLYING,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .criticalHitStage = B_UPDATED_MOVE_DATA >= GEN_3,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .argument.twoTurnAttack = { .stringId = B_UPDATED_MOVE_DATA >= GEN_4 ? STRINGID_CLOAKEDINAHARSHLIGHT : STRINGID_PKMNISGLOWING },
    #if B_UPDATED_MOVE_DATA >= GEN_3
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
    #endif
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SkyAttack,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TRANSFORM] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("TRANSFORM"),
        .description = COMPOUND_STRING(
            "The user transforms into a copy of the target right down to having the same move set."),
        .effect = EFFECT_TRANSFORM,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RECOVER_HP },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .mimicBanned = TRUE,
        //.metronomeBanned = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .copycatBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Transform,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BUBBLE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("BUBBLE"),
        .description = COMPOUND_STRING(
            "A spray of countless bubbles is jetted at the opposing Pokémon. This may also lower their SPEED."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 40 : 20,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_Bubble,
    },

    [MOVE_DIZZY_PUNCH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("DIZZY PUNCH"),
        .description = COMPOUND_STRING(
            "The target is hit with rhythmic punches. This may also leave the target confused."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 20,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DizzyPunch,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SPORE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SPORE"),
        .description = COMPOUND_STRING(
            "The user scatters bursts of spores that induce sleep. "),
        .effect = EFFECT_SLEEP,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .magicCoatAffected = TRUE,
        .powderMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Spore,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FLASH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FLASH"),
        .description = COMPOUND_STRING(
            "The user flashes a bright light that cuts the target's accuracy."),
        .effect = EFFECT_ACCURACY_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_4 ? 100 : 70,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_EVSN_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Flash,
        .validApprenticeMove = TRUE,
    },

    [MOVE_PSYWAVE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("PSYWAVE"),
        .description = COMPOUND_STRING(
            "The target is attacked with an odd psychic wave. The attack varies in intensity."),
        .effect = EFFECT_PSYWAVE,
        .power = 1,
        .type = TYPE_PSYCHIC,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_6 ? 100 : 80,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND},
        .battleAnimScript = gBattleAnimMove_Psywave,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SPLASH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SPLASH"),
        .description = COMPOUND_STRING(
            "The user just flops and splashes around to no effect at all... "),
        .effect = EFFECT_DO_NOTHING,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_3 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .gravityBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Splash,
    },

    [MOVE_ACID_ARMOR] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ACID ARMOR"),
        .description = COMPOUND_STRING(
            "The user alters its cellular structure to liquefy itself, sharply raising its DEFENSE."),
        .effect = EFFECT_DEFENSE_UP_2,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 0,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 20 : 40,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_AcidArmor,
        .validApprenticeMove = TRUE,
    },

    [MOVE_CRABHAMMER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("CRABHAMMER"),
        .description = COMPOUND_STRING(
            "The target is hammered with a large pincer. Critical hits land more easily."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 100 : 90,
        .type = TYPE_WATER,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 90 : 85,
        .criticalHitStage = 1,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE, COMBO_STARTER_SWORDS_DANCE},
        .battleAnimScript = gBattleAnimMove_Crabhammer,
        .validApprenticeMove = TRUE,
    },

    [MOVE_EXPLOSION] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("EXPLOSION"),
        .description = COMPOUND_STRING(
            "The user blows up to inflict damage on all Pokémon in battle, and then faints afterwards."),
        .effect = EFFECT_EXPLOSION,
        .power = 250,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .parentalBondBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_GREAT_APPEAL_BUT_NO_MORE_MOVES,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Explosion,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FURY_SWIPES] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FURY SWIPES"),
        .description = COMPOUND_STRING(
            "The target is raked with sharp claws or scythes quickly 2-5 times in a row."),
        .effect = EFFECT_MULTI_HIT,
        .power = 18,
        .type = TYPE_NORMAL,
        .accuracy = 80,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SCRATCH},
        .battleAnimScript = gBattleAnimMove_FurySwipes,
    },

    [MOVE_BONEMERANG] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("BONEMERANG"),
        .description = COMPOUND_STRING(
            "The user throws a bone that loops around to hit the target twice - coming and going."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_GROUND,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .strikeCount = 2,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_BONEMERANG,
        .contestComboMoves = {COMBO_STARTER_BONE_CLUB, COMBO_STARTER_BONE_RUSH, COMBO_STARTER_SHADOW_BONE},
        .battleAnimScript = gBattleAnimMove_Bonemerang,
        .validApprenticeMove = TRUE,
    },

    [MOVE_REST] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("REST"),
        .description = COMPOUND_STRING(
            "The user sleeps for 2 turns, fully restoring its HP and healing any status conditions."),
        .effect = EFFECT_REST,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = B_UPDATED_MOVE_DATA >= GEN_9 ? 5 : 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .healingMove = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_REST,
        .contestComboMoves = {COMBO_STARTER_BELLY_DRUM, COMBO_STARTER_CHARM, COMBO_STARTER_YAWN},
        .battleAnimScript = gBattleAnimMove_Rest,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ROCK_SLIDE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ROCK SLIDE"),
        .description = COMPOUND_STRING(
            "Large boulders are hurled at opposing Pokémon. This may also cause them to flinch."),
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_ROCK,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_ROCK_THROW},
        .battleAnimScript = gBattleAnimMove_RockSlide,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HYPER_FANG] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("HYPER FANG"),
        .description = COMPOUND_STRING(
            "The user bites the target with its sharp front fangs. This may also make the target flinch."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HyperFang,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SHARPEN] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SHARPEN"),
        .description = COMPOUND_STRING(
            "The user makes its edges more jagged, which raises its ATTACK stat."),
        .effect = EFFECT_ATTACK_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Sharpen,
        .validApprenticeMove = TRUE,
    },

    [MOVE_CONVERSION] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("CONVERSION"),
        .description = COMPOUND_STRING(
            "The user changes its type to become the same type as its first move."),
        .effect = EFFECT_CONVERSION,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ALL_STATS_UP_1 },
        .snatchAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Conversion,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TRI_ATTACK] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("TRI ATTACK"),
        .description = COMPOUND_STRING(
            "The user attacks with three simultaneous beams that may burn, freeze, or paralyze."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_TRI_ATTACK,
            .chance = 20,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_LOCK_ON},
        .battleAnimScript = gBattleAnimMove_TriAttack,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SUPER_FANG] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SUPER FANG"),
        .description = COMPOUND_STRING(
            "The user chomps hard on the target with its sharp fangs. This cuts the target's HP in half."),
        .effect = EFFECT_SUPER_FANG,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = (B_UPDATED_MOVE_FLAGS == GEN_3 || B_UPDATED_MOVE_FLAGS == GEN_4),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SCARY_FACE},
        .battleAnimScript = gBattleAnimMove_SuperFang,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SLASH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SLASH"),
        .description = COMPOUND_STRING(
            "The target is attacked with slashing claws. Critical hits land more easily."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .criticalHitStage = 1,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SCRATCH, COMBO_STARTER_SWORDS_DANCE},
        .battleAnimScript = gBattleAnimMove_Slash,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SUBSTITUTE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SUBSTITUTE"),
        .description = COMPOUND_STRING(
            "The user creates a substitute for itself using some of its HP to serve as a decoy."),
        .effect = EFFECT_SUBSTITUTE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Substitute,
        .validApprenticeMove = TRUE,
    },

    [MOVE_STRUGGLE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("STRUGGLE"),
        .description = COMPOUND_STRING(
            "This attack is only used in desperation if the user has no PP. It hurts the user a little."),
        .effect = EFFECT_RECOIL_HP_25,
        .accuracy = 0,
        .mirrorMoveBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECOIL_HP_25,
            .self = TRUE,
        }),
        .power = 50,
        .type = TYPE_NORMAL,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .meFirstBanned = TRUE,
        .mimicBanned = TRUE,
        .metronomeBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .copycatBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .sketchBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_Struggle,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SKETCH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SKETCH"),
        .description = COMPOUND_STRING(
            "Copies the foe's last move permanently."),
        .effect = EFFECT_SKETCH,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ALL_STATS_UP_1 },
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .mimicBanned = TRUE,
        // .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .sketchBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Sketch,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TRIPLE_KICK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TRIPLE KICK"),
        .description = COMPOUND_STRING(
            "Kicks the foe 3 times in a row with rising intensity."),
        .effect = EFFECT_TRIPLE_KICK,
        .power = 10,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .strikeCount = 3,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .battleAnimScript = gBattleAnimMove_TripleKick,
        .validApprenticeMove = TRUE,
    },

    [MOVE_THIEF] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("THIEF"),
        .description = COMPOUND_STRING(
            "The user attacks and steals the target's held item if it isn't holding one."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 60 : 40,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 25 : 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = (B_UPDATED_MOVE_FLAGS == GEN_3 || B_UPDATED_MOVE_FLAGS == GEN_4),
        .meFirstBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_STEAL_ITEM,
        }),
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Thief,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SPIDER_WEB] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SPIDER WEB"),
        .description = COMPOUND_STRING(
            "The user ensnares the target in gooey webs, so it can't flee or switch out of battle."),
        .effect = EFFECT_MEAN_LOOK,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .ignoresProtect = (B_UPDATED_MOVE_FLAGS >= GEN_6) || (B_UPDATED_MOVE_FLAGS <= GEN_3),
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_STRING_SHOT},
        .battleAnimScript = gBattleAnimMove_SpiderWeb,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MIND_READER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("MIND READER"),
        .description = COMPOUND_STRING(
            "The user senses the target's movements with its mind to ensure its next attack hits."),
        .effect = EFFECT_LOCK_ON,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_4 ? 0 : 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_MIND_READER,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MindReader,
        .validApprenticeMove = TRUE,
    },

    [MOVE_NIGHTMARE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("NIGHTMARE"),
        .description = COMPOUND_STRING(
            "A sleeping target sees a nightmare that inflicts 1/4 damage every turn."),
        .effect = EFFECT_NIGHTMARE,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_4 ? 100 : 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .ignoresProtect = B_UPDATED_MOVE_FLAGS <= GEN_3,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Nightmare,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FLAME_WHEEL] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FLAME WHEEL"),
        .description = COMPOUND_STRING(
            "A fiery charge attack that may burn. Boosted for each SPEED boost the user has."),
        .effect = EFFECT_FLAME_WHEEL,
        .power = 60,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .thawsUser = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_FlameWheel,
    },

    [MOVE_SNORE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SNORE"),
        .description = COMPOUND_STRING(
            "This attack can only be used if the user is asleep. The noise may make the target flinch."),
        .effect = EFFECT_SNORE,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 50 : 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .soundMove = TRUE,
        //.metronomeBanned = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_REST},
        .battleAnimScript = gBattleAnimMove_Snore,
        .validApprenticeMove = TRUE,
    },

    [MOVE_CURSE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("CURSE"),
        .description = COMPOUND_STRING(
            "A move that works differently if the user is a Ghost type. "),
        .effect = EFFECT_CURSE,
        .power = 0,
        .type = B_UPDATED_MOVE_TYPES >= GEN_5 ? TYPE_GHOST : TYPE_MYSTERY,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_CURSE },
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_LATER,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_CURSE,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Curse,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FLAIL] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FLAIL"),
        .description = COMPOUND_STRING(
            "The user flails about aimlessly to attack. Does more damage the lower the user's HP."),
        .effect = EFFECT_FLAIL,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_ENDURE},
        .battleAnimScript = gBattleAnimMove_Flail,
        .validApprenticeMove = TRUE,
    },

    [MOVE_CONVERSION_2] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("CONVERSION 2"),
        .description = COMPOUND_STRING(
            "The user changes its type to make itself resistant to the move the target used last."),
        .effect = EFFECT_CONVERSION_2,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = B_UPDATED_MOVE_DATA >= GEN_5 ? MOVE_TARGET_SELECTED : MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RECOVER_HP },
        .ignoresProtect = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Conversion2,
        .validApprenticeMove = TRUE,
    },

    [MOVE_AEROBLAST] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("AEROBLAST"),
        .description = COMPOUND_STRING(
            "Launches a vacuumed blast. High critical-hit ratio."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FLYING,
        .accuracy = 95,
        .criticalHitStage = 1,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .windMove = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Aeroblast,
        .validApprenticeMove = TRUE,
    },

    [MOVE_COTTON_SPORE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("COTTON SPORE"),
        .description = COMPOUND_STRING(
            "Sheds cottony spores that cling to the foe, lowering its evasion and harshly lowering its SPEED."),
        .effect = EFFECT_COTTON_SPORE,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .magicCoatAffected = TRUE,
        .powderMove = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_CottonSpore,
        .validApprenticeMove = TRUE,
    },

    [MOVE_REVERSAL] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("REVERSAL"),
        .description = COMPOUND_STRING(
            "An all-out attack that becomes more powerful the less HP the user has."),
        .effect = EFFECT_FLAIL,
        .power = 1,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_ENDURE},
        .battleAnimScript = gBattleAnimMove_Reversal,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SPITE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SPITE"),
        .description = COMPOUND_STRING(
            "The user unleashes its grudge on on the move last used by the target by cutting 4 PP from it."),
        .effect = EFFECT_SPITE,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RECOVER_HP },
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .ignoresSubstitute = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CURSE},
        .battleAnimScript = gBattleAnimMove_Spite,
        .validApprenticeMove = TRUE,
    },

    [MOVE_POWDER_SNOW] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("POWDER SNOW"),
        .description = COMPOUND_STRING(
            "The user attacks with a chilling gust of powdery snow. This may also freeze opposing Pokémon."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FREEZE_OR_FROSTBITE,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_POWDER_SNOW,
        .contestComboMoves = {COMBO_STARTER_HAIL},
        .battleAnimScript = gBattleAnimMove_PowderSnow,
    },

    [MOVE_PROTECT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("PROTECT"),
        .description = COMPOUND_STRING(
            "The user protects itself from all attacks. May fail if it is used in succession."),
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = B_UPDATED_MOVE_DATA >= GEN_5 ? 4 : 3,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HARDEN},
        .battleAnimScript = gBattleAnimMove_Protect,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MACH_PUNCH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("MACH PUNCH"),
        .description = COMPOUND_STRING(
            "The user throws a punch at blinding speed. This move always goes first."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MachPunch,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SCARY_FACE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SCARY FACE"),
        .description = COMPOUND_STRING(
            "Makes a frightening face to scare the foe, causing panic."),
        .effect = EFFECT_PANIC,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_SCARY_FACE,
        .contestComboMoves = {COMBO_STARTER_LEER, COMBO_STARTER_RAGE},
        .battleAnimScript = gBattleAnimMove_ScaryFace,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FEINT_ATTACK] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FEINT ATTACK"),
        .description = COMPOUND_STRING(
            "The user approaches the target disarmingly, then attacks it. This attack never misses."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = B_UPDATED_MOVE_DATA >= GEN_4,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FAKE_OUT, COMBO_STARTER_LEER, COMBO_STARTER_POUND},
        .battleAnimScript = gBattleAnimMove_FeintAttack,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SWEET_KISS] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SWEET KISS"),
        .description = COMPOUND_STRING(
            "The user kisses the target with a sweet, angelic cuteness that causes confusion."),
        .effect = EFFECT_CONFUSE,
        .power = 0,
        .type = B_UPDATED_MOVE_TYPES >= GEN_6 ? TYPE_FAIRY : TYPE_NORMAL,
        .accuracy = 75,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARM},
        .battleAnimScript = gBattleAnimMove_SweetKiss,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BELLY_DRUM] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("BELLY DRUM"),
        .description = COMPOUND_STRING(
            "The user maximizes its ATTACK stat in exchange for HP equal to half its max HP."),
        .effect = EFFECT_BELLY_DRUM,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RECOVER_HP },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_BELLY_DRUM,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_BellyDrum,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SLUDGE_BOMB] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SLUDGE BOMB"),
        .description = COMPOUND_STRING(
            "Unsanitary sludge is hurled at the target. This may also poison the target."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ballisticMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_SLUDGE_BOMB,
        .contestComboMoves = {COMBO_STARTER_SLUDGE},
        .battleAnimScript = gBattleAnimMove_SludgeBomb,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MUD_SLAP] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("MUD-SLAP"),
        .description = COMPOUND_STRING(
            "The user hurls mud in the target's face to inflict damage and lower its accuracy."),
        .effect = EFFECT_HIT,
        .power = 20,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ACC_MINUS_1,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_MUD_SLAP,
        .contestComboMoves = {COMBO_STARTER_MUD_SPORT, COMBO_STARTER_SAND_ATTACK, COMBO_STARTER_SANDSTORM},
        .battleAnimScript = gBattleAnimMove_MudSlap,
        .validApprenticeMove = TRUE,
    },

    [MOVE_OCTAZOOKA] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("OCTAZOOKA"),
        .description = COMPOUND_STRING(
            "The user attacks by spraying ink in the target's eyes. This may lower the target's accuracy."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_WATER,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ballisticMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ACC_MINUS_1,
            .chance = 50,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_LOCK_ON, COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_Octazooka,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SPIKES] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SPIKES"),
        .description = COMPOUND_STRING(
            "The user lays spikes at the opposing team's feet, hurting Pokémon that switch into battle."),
        .effect = EFFECT_SPIKES,
        .power = 0,
        .type = TYPE_GROUND,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_OPPONENTS_FIELD,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .forcePressure = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Spikes,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ZAP_CANNON] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ZAP CANNON"),
        .description = COMPOUND_STRING(
            "The user fires an electric blast like a cannon to inflict damage and cause paralysis."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_4 ? 120 : 100,
        .type = TYPE_ELECTRIC,
        .accuracy = 50,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ballisticMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARGE, COMBO_STARTER_LOCK_ON},
        .battleAnimScript = gBattleAnimMove_ZapCannon,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FORESIGHT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FORESIGHT"),
        .description = COMPOUND_STRING(
            "Enables the user to hit a Ghost type with any type of move, and to hit evasive foes."),
        .effect = EFFECT_FORESIGHT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 0 : 100,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_BOOST_CRITS },
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .ignoresSubstitute = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Foresight,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DESTINY_BOND] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("DESTINY BOND"),
        .description = COMPOUND_STRING(
            "If the user faints after using this move, the attacker faints. May fail if used repeatedly."),
        .effect = EFFECT_DESTINY_BOND,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_FOLLOW_ME },
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_GREAT_APPEAL_BUT_NO_MORE_MOVES,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CURSE, COMBO_STARTER_ENDURE, COMBO_STARTER_MEAN_LOOK},
        .battleAnimScript = gBattleAnimMove_DestinyBond,
        .validApprenticeMove = TRUE,
    },

    [MOVE_PERISH_SONG] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("PERISH SONG"),
        .description = COMPOUND_STRING(
            "Any Pokémon that hears this song faints in 3 turns, unless it switches out of battle."),
        .effect = EFFECT_PERISH_SONG,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .mirrorMoveBanned = TRUE,
        .soundMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_MEAN_LOOK, COMBO_STARTER_SING},
        .battleAnimScript = gBattleAnimMove_PerishSong,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ICY_WIND] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ICY WIND"),
        .description = COMPOUND_STRING(
            "The user attacks with a gust of chilled air. This also lowers opposing Pokémon's SPEED."),
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_ICE,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .windMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HAIL},
        .battleAnimScript = gBattleAnimMove_IcyWind,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DETECT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("DETECT"),
        .description = COMPOUND_STRING(
            "The user protects itself from all attacks. May fail if it is used in succession."),
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = B_UPDATED_MOVE_DATA >= GEN_5 ? 4 : 3,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_EVSN_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_TAUNT},
        .battleAnimScript = gBattleAnimMove_Detect,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BONE_RUSH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("BONE RUSH"),
        .description = COMPOUND_STRING(
            "The user strikes the target with a hard bone 2-5 times in a row. "),
        .effect = EFFECT_MULTI_HIT,
        .power = 25,
        .type = TYPE_GROUND,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 90 : 80,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_BONE_RUSH,
        .contestComboMoves = {COMBO_STARTER_BONE_CLUB, COMBO_STARTER_BONEMERANG, COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_SHADOW_BONE},
        .battleAnimScript = gBattleAnimMove_BoneRush,
    },

    [MOVE_LOCK_ON] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("LOCK-ON"),
        .description = COMPOUND_STRING(
            "The user takes aim at the target to ensure the next attack does not miss."),
        .effect = EFFECT_LOCK_ON,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_4 ? 0 : 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_LOCK_ON,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_LockOn,
        .validApprenticeMove = TRUE,
    },

    [MOVE_OUTRAGE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("OUTRAGE"),
        .description = COMPOUND_STRING(
            "The user rampages with righteous fury for 2-3 turns. The user then becomes confused."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_4 ? 120 : 90,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_5 ? 10 : 15,
        .target = MOVE_TARGET_RANDOM,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .instructBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_THRASH,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Outrage,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SANDSTORM] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SANDSTORM"),
        .description = COMPOUND_STRING(
            "A 5-turn sandstorm is summoned to hurt all combatants except Rock, Ground, and Steel types."),
        .effect = EFFECT_SANDSTORM,
        .power = 0,
        .type = TYPE_ROCK,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .windMove = TRUE,
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_SANDSTORM,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Sandstorm,
        .validApprenticeMove = TRUE,
    },

    [MOVE_GIGA_DRAIN] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("GIGA DRAIN"),
        .description = sMegaDrainDescription,
        .effect = EFFECT_ABSORB,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 75 : 60,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_4 ? 10 : 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .argument = { .absorbPercentage = 50 },
        .ignoresKingsRock = (B_UPDATED_MOVE_FLAGS == GEN_3 || B_UPDATED_MOVE_FLAGS == GEN_4),
        .healingMove = B_HEAL_BLOCKING >= GEN_6,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .battleAnimScript = gBattleAnimMove_GigaDrain,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ENDURE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ENDURE"),
        .description = COMPOUND_STRING(
            "The user endures any attack with at least 1 HP. May fail if it is used in succession."),
        .effect = EFFECT_ENDURE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = B_UPDATED_MOVE_DATA >= GEN_5 ? 4 : 3,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_ENDURE,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Endure,
        .validApprenticeMove = TRUE,
    },

    [MOVE_CHARM] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("CHARM"),
        .description = COMPOUND_STRING(
            "The user gazes at the target charmingly, making it less wary, harshly lowering its ATTACK."),
        .effect = EFFECT_ATTACK_DOWN_2,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_CHARM,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Charm,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ROLLOUT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ROLLOUT"),
        .description = COMPOUND_STRING(
            "The user continually rolls into the target over 5 turns. It gets more powerful each time it hits."),
        .effect = EFFECT_ROLLOUT,
        .power = 30,
        .type = TYPE_ROCK,
        .accuracy = 90,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .instructBanned = TRUE,
        .parentalBondBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_DEFENSE_CURL, COMBO_STARTER_HARDEN},
        .battleAnimScript = gBattleAnimMove_Rollout,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FALSE_SWIPE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FALSE SWIPE"),
        .description = COMPOUND_STRING(
            "A restrained attack that always leaves the target with at least 1 HP."),
        .effect = EFFECT_FALSE_SWIPE,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SWORDS_DANCE},
        .battleAnimScript = gBattleAnimMove_FalseSwipe,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SWAGGER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SWAGGER"),
        .description = COMPOUND_STRING(
            "The user enrages and confuses the target, but also sharply raising its ATTACK."),
        .effect = EFFECT_SWAGGER,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_7 ? 85 : 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Swagger,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MILK_DRINK] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("MILK DRINK"),
        .description = COMPOUND_STRING(
            "By drinking its own milk, the user restores its own HP by up to half of its max HP."),
        .effect = EFFECT_SOFTBOILED,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MilkDrink,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SPARK] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SPARK"),
        .description = COMPOUND_STRING(
            "The user throws an electrically charged tackle at the target. This may paralyze the target."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARGE},
        .battleAnimScript = gBattleAnimMove_Spark,
    },

    [MOVE_FURY_CUTTER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FURY CUTTER"),
        .description = COMPOUND_STRING(
            "The target is slashed with claws or scythes. This attack becomes stronger if used consecutively."),
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .power = 40,
        #elif B_UPDATED_MOVE_DATA >= GEN_5
            .power = 20,
        #else
            .power = 10,
        #endif
        .effect = EFFECT_FURY_CUTTER,
        .type = TYPE_BUG,
        .accuracy = 95,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SWORDS_DANCE},
        .battleAnimScript = gBattleAnimMove_FuryCutter,
        .validApprenticeMove = TRUE,
    },

    [MOVE_STEEL_WING] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("STEEL WING"),
        .description = COMPOUND_STRING(
            "Strikes the foe with hard wings spread wide."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_STEEL,
        .accuracy = 90,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_PLUS_1,
            .self = TRUE,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SteelWing,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MEAN_LOOK] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("MEAN LOOK"),
        .description = COMPOUND_STRING(
            "The user pins the target with a dark, arresting look. The target becomes unable to flee."),
        .effect = EFFECT_MEAN_LOOK,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .ignoresProtect = (B_UPDATED_MOVE_FLAGS >= GEN_6) || (B_UPDATED_MOVE_FLAGS <= GEN_3),
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_MEAN_LOOK,
        .contestComboMoves = {COMBO_STARTER_CURSE},
        .battleAnimScript = gBattleAnimMove_MeanLook,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ATTRACT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ATTRACT"),
        .description = COMPOUND_STRING(
            "The target becomes infatuated and unlikely to attack if it is the opposite gender of the user."),
        .effect = EFFECT_ATTRACT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .magicCoatAffected = TRUE,
        .ignoresSubstitute = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Attract,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SLEEP_TALK] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SLEEP TALK"),
        .description = COMPOUND_STRING(
            "While it is asleep, the user randomly uses one of the moves it knows."),
        .effect = EFFECT_SLEEP_TALK,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_BOOST_CRITS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .mimicBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_REST},
        .battleAnimScript = gBattleAnimMove_SleepTalk,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HEAL_BELL] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("HEAL BELL"),
        .description = COMPOUND_STRING(
            "The user chimes a soothing bell to heal the status conditions of all the party Pokémon."),
        .effect = EFFECT_HEAL_BELL,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RECOVER_HP },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .soundMove = B_UPDATED_MOVE_FLAGS != GEN_5,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_HEAL_BELL,
        .contestComboMoves = {COMBO_STARTER_LUCKY_CHANT},
        .battleAnimScript = gBattleAnimMove_HealBell,
        .validApprenticeMove = TRUE,
    },

    [MOVE_RETURN] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("RETURN"),
        .description = COMPOUND_STRING(
            "This full-power attack grows more powerful the more the user likes its Trainer."),
        .effect = EFFECT_RETURN,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_EXCITE_AUDIENCE_IN_ANY_CONTEST,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Return,
        .validApprenticeMove = TRUE,
    },

    [MOVE_PRESENT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("PRESENT"),
        .description = COMPOUND_STRING(
            "The user attacks by giving the target a gift with a hidden trap. It may restore HP instead."),
        .effect = EFFECT_PRESENT,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresKingsRock = (B_UPDATED_MOVE_FLAGS == GEN_3 || B_UPDATED_MOVE_FLAGS == GEN_4),
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Present,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FRUSTRATION] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FRUSTRATION"),
        .description = COMPOUND_STRING(
            "An attack that is stronger if the Trainer is disliked."),
        .effect = EFFECT_FRUSTRATION,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_EXCITE_AUDIENCE_IN_ANY_CONTEST,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Frustration,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SAFEGUARD] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SAFEGUARD"),
        .description = COMPOUND_STRING(
            "The user creates a protective field that prevents status conditions for 5 turns."),
        .effect = EFFECT_SAFEGUARD,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 25,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Safeguard,
        .validApprenticeMove = TRUE,
    },

    [MOVE_PAIN_SPLIT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("PAIN SPLIT"),
        .description = COMPOUND_STRING(
            "A move that adds the HPs of the user and the target, then divides the total between them."),
        .effect = EFFECT_PAIN_SPLIT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_ENDURE},
        .battleAnimScript = gBattleAnimMove_PainSplit,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SACRED_FIRE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SACRED FIRE"),
        .description = COMPOUND_STRING(
            "A mystical fire attack that may inflict a burn."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIRE,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .thawsUser = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 50,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_SacredFire,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MAGNITUDE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("MAGNITUDE"),
        .description = COMPOUND_STRING(
            "The user attacks everything around it with a ground-shaking quake. Its power varies."),
        .effect = EFFECT_MAGNITUDE,
        .power = 1,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .damagesUnderground = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Magnitude,
    },

    [MOVE_DYNAMIC_PUNCH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("DYNAMIC PUNCH"),
        .description = COMPOUND_STRING(
            "The user punches the target with full, concentrated power. This confuses the target if it hits."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIGHTING,
        .accuracy = 50,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_MIND_READER},
        .battleAnimScript = gBattleAnimMove_DynamicPunch,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MEGAHORN] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("MEGAHORN"),
        .description = COMPOUND_STRING(
            "Using its tough and impressive horn, the user rams into the target with no letup."),
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_BUG,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Megahorn,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DRAGON_BREATH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("DRAGON BREATH"),
        .description = COMPOUND_STRING(
            "The user exhales a mighty blast that inflicts damage. This may also paralyze the target."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresKingsRock = B_UPDATED_MOVE_FLAGS < GEN_3,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_DRAGON_BREATH,
        .contestComboMoves = {COMBO_STARTER_DRAGON_DANCE, COMBO_STARTER_DRAGON_RAGE, COMBO_STARTER_TYRANT_CRUSH, COMBO_STARTER_DRAGON_TAIL},
        .battleAnimScript = gBattleAnimMove_DragonBreath,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BATON_PASS] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("BATON PASS"),
        .description = COMPOUND_STRING(
            "The user switches places with a party Pokémon in waiting and passes along any stat changes."),
        .effect = EFFECT_BATON_PASS,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_BatonPass,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ENCORE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ENCORE"),
        .description = COMPOUND_STRING(
            "The user compels the target to keep using the move it just used for 3 turns."),
        .effect = EFFECT_ENCORE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .encoreBanned = TRUE,
        .ignoresSubstitute = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Encore,
        .validApprenticeMove = TRUE,
    },

    [MOVE_PURSUIT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("PURSUIT"),
        .description = COMPOUND_STRING(
            "The power of this move is doubled if it's used on a target that's switching out of battle."),
        .effect = EFFECT_PURSUIT,
        .power = 40,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresKingsRock = (B_UPDATED_MOVE_FLAGS == GEN_3 || B_UPDATED_MOVE_FLAGS == GEN_4),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Pursuit,
        .validApprenticeMove = TRUE,
    },

    [MOVE_RAPID_SPIN] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("RAPID SPIN"),
        .description = COMPOUND_STRING(
            "The user spins to attack, raising its SPEED, and clearing any trapping effects or hazards."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_8 ? 50 : 20,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS(
        #if B_SPEED_BUFFING_RAPID_SPIN >= GEN_8
            {
                .moveEffect = MOVE_EFFECT_SPD_PLUS_1,
                .self = TRUE,
                .chance = 100,
            }
        #endif
        ),
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RapidSpin,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SWEET_SCENT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SWEET SCENT"),
        .description = COMPOUND_STRING(
            "A sweet scent that harshly lowers opposing Pokémon's evasiveness."),
        .effect = B_UPDATED_MOVE_DATA >= GEN_6 ? EFFECT_EVASION_DOWN_2 : EFFECT_EVASION_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ACC_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_SWEET_SCENT,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SweetScent,
        .validApprenticeMove = TRUE,
    },

    [MOVE_IRON_TAIL] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("IRON TAIL"),
        .description = COMPOUND_STRING(
            "The target is slammed with a steel-hard tail. This may also lower the target's DEFENSE."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_STEEL,
        .accuracy = 75,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_IronTail,
        .validApprenticeMove = TRUE,
    },

    [MOVE_METAL_CLAW] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("METAL CLAW"),
        .description = COMPOUND_STRING(
            "The target is raked with steel claws. This may also raise the user's ATTACK stat."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_STEEL,
        .accuracy = 95,
        .pp = 35,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_PLUS_1,
            .self = TRUE,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_METAL_SOUND},
        .battleAnimScript = gBattleAnimMove_MetalClaw,
        .validApprenticeMove = TRUE,
    },

    [MOVE_VITAL_THROW] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("VITAL THROW"),
        .description = COMPOUND_STRING(
            "The user attacks last. In return, this throw move never misses."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = -1,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_LATER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FAKE_OUT},
        .battleAnimScript = gBattleAnimMove_VitalThrow,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MORNING_SUN] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("MORNING SUN"),
        .description = COMPOUND_STRING(
            "The user restores its own HP. The amount of HP regained varies with the weather."),
        .effect = EFFECT_MORNING_SUN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_MorningSun,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SYNTHESIS] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SYNTHESIS"),
        .description = COMPOUND_STRING(
            "The user restores its own HP. The amount of HP regained varies with the weather."),
        .effect = EFFECT_SYNTHESIS,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_Synthesis,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MOONLIGHT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("MOONLIGHT"),
        .description = COMPOUND_STRING(
            "The user restores its own HP. The amount of HP regained varies with the weather."),
        .effect = EFFECT_MOONLIGHT,
        .power = 0,
        .type = B_UPDATED_MOVE_TYPES >= GEN_6 ? TYPE_FAIRY : TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_Moonlight,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HIDDEN_POWER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("HIDDEN POWER"),
        .description = COMPOUND_STRING(
            "A unique attack that varies in type depending on the Pokémon using it."),
        .power = B_HIDDEN_POWER_DMG >= GEN_6 ? 60 : 1,
        .effect = EFFECT_HIDDEN_POWER,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HiddenPower,
        .validApprenticeMove = TRUE,
    },

    [MOVE_CROSS_CHOP] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("CROSS CHOP"),
        .description = COMPOUND_STRING(
            "The user delivers a double chop with its forearms crossed. Critical hits land more easily."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIGHTING,
        .accuracy = 80,
        .criticalHitStage = 1,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .battleAnimScript = gBattleAnimMove_CrossChop,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TWISTER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TWISTER"),
        .description = COMPOUND_STRING(
            "Whips up a vicious twister to tear at the foe."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .damagesAirborneDoubleDamage = TRUE,
        .windMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 20,
        }),
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Twister,
    },

    [MOVE_RAIN_DANCE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("RAIN DANCE"),
        .description = COMPOUND_STRING(
            "The user summons a downpour that lasts 5 turns, boosting Water moves and weakening Fire moves."),
        .effect = EFFECT_RAIN_DANCE,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_RAIN_DANCE,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RainDance,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SUNNY_DAY] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SUNNY DAY"),
        .description = COMPOUND_STRING(
            "The user summons sunny weather lasting 5 turns, boosting Fire moves and weakening Water moves."),
        .effect = EFFECT_SUNNY_DAY,
        .power = 0,
        .type = TYPE_FIRE,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_SUNNY_DAY,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SunnyDay,
        .validApprenticeMove = TRUE,
    },

    [MOVE_CRUNCH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("CRUNCH"),
        .description = COMPOUND_STRING(
            "The user crunches up the target with sharp fangs. This may also lower the target's SP. DEF."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .bitingMove = TRUE,
            .additionalEffects = ADDITIONAL_EFFECTS({
                .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
                .chance = 20,
            }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SCARY_FACE},
        .battleAnimScript = gBattleAnimMove_Crunch,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MIRROR_COAT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("MIRROR COAT"),
        .description = COMPOUND_STRING(
            "A retaliation move that counters any special attack, inflicting double the damage taken."),
        .effect = EFFECT_MIRROR_COAT,
        .power = 1,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_DEPENDS,
        .priority = -5,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .mirrorMoveBanned = B_UPDATED_MOVE_FLAGS >= GEN_4,
        .meFirstBanned = TRUE,
        .metronomeBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_TAUNT},
        .battleAnimScript = gBattleAnimMove_MirrorCoat,
        .validApprenticeMove = TRUE,
    },

    [MOVE_PSYCH_UP] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("PSYCH UP"),
        .description = COMPOUND_STRING(
            "The user hypnotizes itself into copying any stat change made by the target."),
        .effect = EFFECT_PSYCH_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RECOVER_HP },
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = B_UPDATED_MOVE_FLAGS < GEN_5,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PsychUp,
        .validApprenticeMove = TRUE,
    },

    [MOVE_EXTREME_SPEED] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("EXTREME SPEED"),
        .description = COMPOUND_STRING(
            "The user charges the target at blinding speed. This move always goes first."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = B_UPDATED_MOVE_DATA >= GEN_5 ? 2 : 1,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ExtremeSpeed,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ANCIENT_POWER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ANCIENT POWER"),
        .description = COMPOUND_STRING(
            "The user attacks with a prehistoric power. This may also raise all the user's stats."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = B_UPDATED_MOVE_DATA < GEN_4,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ALL_STATS_UP,
            .self = TRUE,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_AncientPower,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SHADOW_BALL] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SHADOW BALL"),
        .description = COMPOUND_STRING(
            "The user hurls a shadowy blob at the target. This may also lower the target's SP. DEF."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ballisticMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 20,
        }),
        .contestEffect = CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ShadowBall,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FUTURE_SIGHT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FUTURE SIGHT"),
        .description = COMPOUND_STRING(
            "Two turns after this move is used, the target is attacked psychically."),
        .power = 120,
        .effect = EFFECT_FUTURE_SIGHT,
        .type = TYPE_PSYCHIC,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 100 : 90,
        .pp = B_UPDATED_MOVE_DATA >= GEN_5 ? 10 : 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND, COMBO_STARTER_CONFUSION, COMBO_STARTER_KINESIS, COMBO_STARTER_PSYCHIC},
        .battleAnimScript = gBattleAnimMove_FutureSight,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ROCK_SMASH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ROCK SMASH"),
        .description = COMPOUND_STRING(
            "Strikes foe with a crushing attack that lowers its DEFENSE. "),
        .effect = EFFECT_HIT,
        .power = 20,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_BETTER_WITH_GOOD_CONDITION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RockSmash,
        .validApprenticeMove = TRUE,
    },

    [MOVE_WHIRLPOOL] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("WHIRLPOOL"),
        .description = COMPOUND_STRING(
            "The user traps the target in a violent swirling whirlpool for 4-5 turns."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 35 : 15,
        .type = TYPE_WATER,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 85 : 70,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .damagesUnderwater = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
        }),
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_Whirlpool,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BEAT_UP] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("BEAT UP"),
        .description = COMPOUND_STRING(
            "The user gets all party Pokémon to attack the target. This move hits once for each party member."),
        .effect = EFFECT_BEAT_UP,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 1 : 10,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_BeatUp,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FAKE_OUT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FAKE OUT"),
        .description = COMPOUND_STRING(
            "This attack hits first and makes the target flinch. It only works on the user's first turn."),
        .priority = B_UPDATED_MOVE_DATA >= GEN_5 ? 3 : 1,
        .makesContact = B_UPDATED_MOVE_DATA >= GEN_4,
        .effect = EFFECT_FIRST_TURN_ONLY,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_FAKE_OUT,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FakeOut,
        .validApprenticeMove = TRUE,
    },

    [MOVE_UPROAR] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("UPROAR"),
        .description = COMPOUND_STRING(
            "The user attacks in an uproar for 3 turns. During that time, no Pokémon can fall asleep."),
        .effect = EFFECT_UPROAR,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 90 : 50,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_RANDOM,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .soundMove = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_UPROAR,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Uproar,
        .validApprenticeMove = TRUE,
    },

    [MOVE_STOCKPILE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("STOCKPILE"),
        .description = COMPOUND_STRING(
            "The user charges up power up to 3 times. This raises its DEFENSE and SP. DEF for each stack."),
        .effect = EFFECT_STOCKPILE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = B_UPDATED_MOVE_DATA >= GEN_4 ? 20 : 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RECOVER_HP },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_STOCKPILE,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Stockpile,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SPIT_UP] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SPIT UP"),
        .description = COMPOUND_STRING(
            "The user releases its stockpiled power to attack. This move is stronger with more Stockpiles."),
        .effect = EFFECT_SPIT_UP,
        .power = B_UPDATED_MOVE_DATA >= GEN_4 ? 1 : 100,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_STOCKPILE},
        .battleAnimScript = gBattleAnimMove_SpitUp,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SWALLOW] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SWALLOW"),
        .description = COMPOUND_STRING(
            "The user absorbs its stockpiled power to heal. This restores more HP with more Stockpiles."),
        .effect = EFFECT_SWALLOW,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_STOCKPILE},
        .battleAnimScript = gBattleAnimMove_Swallow,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HEAT_WAVE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("HEAT WAVE"),
        .description = COMPOUND_STRING(
            "The user attacks by blasting opposing Pokémon with hot air. This may also inflict burns."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 95 : 100,
        .type = TYPE_FIRE,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .windMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_HeatWave,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HAIL] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("HAIL"),
        .description = COMPOUND_STRING(
            "A 5-turn hailstorm is summoned to hurt all combatants except Ice types."),
        .effect = EFFECT_HAIL,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_HAIL,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Hail,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TORMENT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("TORMENT"),
        .description = COMPOUND_STRING(
            "The user torments and enrages the target, preventing it from using the same move repeatedly."),
        .effect = EFFECT_TORMENT,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Torment,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FLATTER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FLATTER"),
        .description = COMPOUND_STRING(
            "Flattery is used to confuse the target. However, this also raise the target's SP. ATK."),
        .effect = EFFECT_FLATTER,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARM},
        .battleAnimScript = gBattleAnimMove_Flatter,
        .validApprenticeMove = TRUE,
    },

    [MOVE_WILL_O_WISP] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("WILL-O-WISP"),
        .description = COMPOUND_STRING(
            "The user shoots a sinister flame at the target to inflict a burn. "),
        .effect = EFFECT_WILL_O_WISP,
        .power = 0,
        .type = TYPE_FIRE,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_6 ? 85 : 75,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_WillOWisp,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MEMENTO] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("MEMENTO"),
        .description = COMPOUND_STRING(
            "The user faints. In return, the target's ATTACK and SP. ATK is harshly lowered."),
        .effect = EFFECT_MEMENTO,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESTORE_REPLACEMENT_HP },
        .contestEffect = CONTEST_EFFECT_GREAT_APPEAL_BUT_NO_MORE_MOVES,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Memento,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FACADE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FACADE"),
        .description = COMPOUND_STRING(
            "This attack move doubles its power if the user is poisoned, burned, or paralyzed."),
        .effect = EFFECT_FACADE,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Facade,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FOCUS_PUNCH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FOCUS PUNCH"),
        .description = COMPOUND_STRING(
            "The user focuses its mind before launching a punch. This move fails if the user is hit first."),
        .effect = EFFECT_FOCUS_PUNCH,
        .power = 150,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = -3,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .mirrorMoveBanned = TRUE,
        .punchingMove = TRUE,
        .meFirstBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_LATER,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .battleAnimScript = gBattleAnimMove_FocusPunch,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SMELLING_SALTS] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SMELLING SALTS"),
        .description = COMPOUND_STRING(
            "Powerful against paralyzed foes, but also heals them."),
        .effect = EFFECT_DOUBLE_POWER_ON_ARG_STATUS,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 70 : 60,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .argument = { .status = STATUS1_PARALYSIS },
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_REMOVE_STATUS,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SmellingSalts,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FOLLOW_ME] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FOLLOW ME"),
        .description = COMPOUND_STRING(
            "The user draws attention to itself, making all targets take aim only at the user."),
        .effect = EFFECT_FOLLOW_ME,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = B_UPDATED_MOVE_DATA >= GEN_6 ? 2 : 3,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FollowMe,
        .validApprenticeMove = TRUE,
    },

    [MOVE_NATURE_POWER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("NATURE POWER"),
        .description = COMPOUND_STRING(
            "This attack makes use of natural power. Its effects vary based on the user's environment."),
        .effect = EFFECT_NATURE_POWER,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        //.metronomeBanned = B_UPDATED_MOVE_FLAGS >= GEN_4,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .mimicBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_NaturePower,
        .validApprenticeMove = TRUE,
    },

    [MOVE_CHARGE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("CHARGE"),
        .description = COMPOUND_STRING(
            "The user boosts the power of the next Electric move it uses. This also raises the user's SP. DEF."),
        .effect = EFFECT_CHARGE,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_CHARGE,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Charge,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TAUNT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("TAUNT"),
        .description = COMPOUND_STRING(
            "The target is taunted into a rage that allows it to use only attack moves for three turns."),
        .effect = EFFECT_TAUNT,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_TAUNT,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Taunt,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HELPING_HAND] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("HELPING HAND"),
        .description = COMPOUND_STRING(
            "The user assists an ally by boosting the power of its attack."),
        .effect = EFFECT_HELPING_HAND,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = B_UPDATED_MOVE_DATA >= GEN_4 ? MOVE_TARGET_ALLY : MOVE_TARGET_USER,
        .priority = 5,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HelpingHand,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TRICK] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("TRICK"),
        .description = COMPOUND_STRING(
            "The user catches the target off guard and swaps its held item with its own."),
        .effect = EFFECT_TRICK,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_2 },
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Trick,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ROLE_PLAY] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ROLE PLAY"),
        .description = COMPOUND_STRING(
            "The user mimics the target completely, copying its Ability. "),
        .effect = EFFECT_ROLE_PLAY,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RolePlay,
        .validApprenticeMove = TRUE,
    },

    [MOVE_WISH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("WISH"),
        .description = COMPOUND_STRING(
            "At the end of the next turn, the user or its replacement's HP is restored by half the user's max."),
        .effect = EFFECT_WISH,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .healingMove = TRUE,
        .snatchAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Wish,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ASSIST] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ASSIST"),
        .description = COMPOUND_STRING(
            "The user hurriedly and randomly uses a move among those known by ally Pokémon."),
        .effect = EFFECT_ASSIST,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.metronomeBanned = B_UPDATED_MOVE_FLAGS >= GEN_4,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .mimicBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Assist,
        .validApprenticeMove = TRUE,
    },

    [MOVE_INGRAIN] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("INGRAIN"),
        .description = COMPOUND_STRING(
            "The user lays roots that restore its HP on every turn, but that prevent it from switching out."),
        .effect = EFFECT_INGRAIN,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Ingrain,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SUPERPOWER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SUPERPOWER"),
        .description = COMPOUND_STRING(
            "The user attacks the target with great power. This also lowers the user's ATTACK and DEFENSE."),
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_DEF_DOWN,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_LOCK_ON, COMBO_STARTER_MIND_READER},
        .battleAnimScript = gBattleAnimMove_Superpower,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MAGIC_COAT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("MAGIC COAT"),
        .description = COMPOUND_STRING(
            "The user puts up a barrier that reflects status moves back at the attacker."),
        .effect = EFFECT_MAGIC_COAT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 4,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_2 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MagicCoat,
        .validApprenticeMove = TRUE,
    },

    [MOVE_RECYCLE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("RECYCLE"),
        .description = COMPOUND_STRING(
            "The user recycles a held item that has been used in battle so it can be used again."),
        .effect = EFFECT_RECYCLE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_2 },
        .snatchAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Recycle,
        .validApprenticeMove = TRUE,
    },

    [MOVE_REVENGE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("REVENGE"),
        .description = COMPOUND_STRING(
            "The user strikes with vengeance. This move is boosted if the target attacked it this turn."),
        .effect = EFFECT_REVENGE,
        .power = 60,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = -4,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_LATER,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_REVENGE,
        .contestComboMoves = {COMBO_STARTER_PAYBACK},
        .battleAnimScript = gBattleAnimMove_Revenge,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BRICK_BREAK] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("BRICK BREAK"),
        .description = COMPOUND_STRING(
            "The user attacks with a swift chop that also breaks barriers, such as Light Screen and Reflect."),
        .effect = EFFECT_BRICK_BREAK,
        .power = 75,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .battleAnimScript = gBattleAnimMove_BrickBreak,
        .validApprenticeMove = TRUE,
    },

    [MOVE_YAWN] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("YAWN"),
        .description = COMPOUND_STRING(
            "The user yawns, lulling the target into falling asleep on the next turn."),
        .effect = EFFECT_YAWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_YAWN,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Yawn,
        .validApprenticeMove = TRUE,
    },

    [MOVE_KNOCK_OFF] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("KNOCK OFF"),
        .description = COMPOUND_STRING(
            "The user slaps away the target's held item, preventing it from being used."),
        .effect = EFFECT_KNOCK_OFF,
        .power = 40,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_KNOCK_OFF,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FAKE_OUT},
        .battleAnimScript = gBattleAnimMove_KnockOff,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ENDEAVOR] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ENDEAVOR"),
        .description = COMPOUND_STRING(
            "This attack move cuts down the target's HP to equal the user's HP."),
        .effect = EFFECT_ENDEAVOR,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .parentalBondBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_ENDURE},
        .battleAnimScript = gBattleAnimMove_Endeavor,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ERUPTION] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ERUPTION"),
        .description = COMPOUND_STRING(
            "The user attacks opposing Pokémon with explosive fury. This move is stronger at high HP."),
        .effect = EFFECT_POWER_BASED_ON_USER_HP,
        .power = 150,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_EARTHQUAKE, COMBO_STARTER_ENDURE, COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_Eruption,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SKILL_SWAP] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SKILL SWAP"),
        .description = COMPOUND_STRING(
            "The user employs its psychic power to exchange Abilities with the target."),
        .effect = EFFECT_SKILL_SWAP,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresSubstitute = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SkillSwap,
        .validApprenticeMove = TRUE,
    },

    [MOVE_IMPRISON] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("IMPRISON"),
        .description = COMPOUND_STRING(
            "Prevents opposing Pokémon from using any moves known by the user."),
        .effect = EFFECT_IMPRISON,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_2 },
        .snatchAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .forcePressure = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Imprison,
        .validApprenticeMove = TRUE,
    },

    [MOVE_REFRESH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("REFRESH"),
        .description = COMPOUND_STRING(
            "The user rests to cure itself of poisoning, a burn, or paralysis. "),
        .effect = EFFECT_REFRESH,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RECOVER_HP },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SING, COMBO_STARTER_WATER_SPORT},
        .battleAnimScript = gBattleAnimMove_Refresh,
        .validApprenticeMove = TRUE,
    },

    [MOVE_GRUDGE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("GRUDGE"),
        .description = COMPOUND_STRING(
            "If the user faints, its grudge fully depletes the PP of the move that knocked it out."),
        .effect = EFFECT_GRUDGE,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_FOLLOW_ME },
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CURSE},
        .battleAnimScript = gBattleAnimMove_Grudge,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SNATCH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SNATCH"),
        .description = COMPOUND_STRING(
            "The user steals the effects of any healing or stat-changing move used this turn."),
        .effect = EFFECT_SNATCH,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 4,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_2 },
        .ignoresSubstitute = TRUE,
        .forcePressure = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Snatch,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SECRET_POWER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SECRET POWER"),
        .description = COMPOUND_STRING(
            "An attack with effects that vary by location."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SECRET_POWER,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_BETTER_WITH_GOOD_CONDITION,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SecretPower,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DIVE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("DIVE"),
        .description = COMPOUND_STRING(
            "Diving on the first turn, the user floats up and attacks on the next turn."),
        .effect = EFFECT_SEMI_INVULNERABLE,
        .power = B_UPDATED_MOVE_DATA >= GEN_4 ? 80 : 60,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        .skyBattleBanned = TRUE,
        .argument.twoTurnAttack = { .stringId =  STRINGID_PKMNHIDUNDERWATER, .status = COMPRESS_BITS(STATUS3_UNDERWATER) },
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_DIVE,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE, COMBO_STARTER_SURF},
        .battleAnimScript = gBattleAnimMove_Dive,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ARM_THRUST] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ARM THRUST"),
        .description = COMPOUND_STRING(
            "Straight-arm punches that strike the foe 2 to 5 times."),
        .effect = EFFECT_MULTI_HIT,
        .power = 15,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FAKE_OUT, COMBO_STARTER_FOCUS_ENERGY},
        .battleAnimScript = gBattleAnimMove_ArmThrust,
    },

    [MOVE_CAMOUFLAGE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("CAMOUFLAGE"),
        .description = COMPOUND_STRING(
            "The user's type is changed depending on its environment. "),
        .effect = EFFECT_CAMOUFLAGE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_EVSN_UP_1 },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Camouflage,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TAIL_GLOW] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TAIL GLOW"),
        .description = COMPOUND_STRING(
            "Flashes a light that sharply raises SP. ATK."),
        .effect = B_UPDATED_MOVE_DATA >= GEN_5 ? EFFECT_SPECIAL_ATTACK_UP_3 : EFFECT_SPECIAL_ATTACK_UP_2,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_TailGlow,
        .validApprenticeMove = TRUE,
    },

    [MOVE_LUSTER_PURGE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("LUSTER PURGE"),
        .description = COMPOUND_STRING(
            "Attacks with a burst of light. May lower SP. DEF."),
        .effect = EFFECT_HIT,
        .power = (B_UPDATED_MOVE_DATA >= GEN_9) ? 95 : 70,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 50,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND},
        .battleAnimScript = gBattleAnimMove_LusterPurge,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MIST_BALL] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MIST BALL"),
        .description = COMPOUND_STRING(
            "Attacks with a flurry of down. May lower SP. ATK."),
        .effect = EFFECT_HIT,
        .power = (B_UPDATED_MOVE_DATA >= GEN_9) ? 95 : 70,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ballisticMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_1,
            .chance = 50,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND},
        .battleAnimScript = gBattleAnimMove_MistBall,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FEATHER_DANCE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FEATHER DANCE"),
        .description = COMPOUND_STRING(
            "The user covers the target's body with a mass of down that harshly lowers its ATTACK stat."),
        .effect = EFFECT_ATTACK_DOWN_2,
        .power = 0,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .magicCoatAffected = TRUE,
        .danceMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FeatherDance,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TEETER_DANCE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("TEETER DANCE"),
        .description = COMPOUND_STRING(
            "The user performs a wobbly dance that confuses the Pokémon around it."),
        .effect = EFFECT_CONFUSE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .danceMove = TRUE,
        .mirrorMoveBanned = B_UPDATED_MOVE_FLAGS < GEN_4,
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_TeeterDance,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BLAZE_KICK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BLAZE KICK"),
        .description = COMPOUND_STRING(
            "A kick with a high critical- hit ratio. May cause a burn."),
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_FIRE,
        .accuracy = 90,
        .criticalHitStage = 1,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_BlazeKick,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MUD_SPORT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("MUD SPORT"),
        .description = COMPOUND_STRING(
            "The user kicks up mud on the battlefield. This weakens Electric-type moves for 5 turns."),
        .effect = EFFECT_MUD_SPORT,
        .power = 0,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_MUD_SPORT,
        .contestComboMoves = {COMBO_STARTER_MUD_SLAP, COMBO_STARTER_SANDSTORM, COMBO_STARTER_WATER_SPORT},
        .battleAnimScript = gBattleAnimMove_MudSport,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ICE_BALL] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ICE BALL"),
        .description = COMPOUND_STRING(
            "A 5-turn attack that gains power on successive hits."),
        .effect = EFFECT_ROLLOUT,
        .power = 30,
        .type = TYPE_ICE,
        .accuracy = 90,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ballisticMove = TRUE,
        .instructBanned = TRUE,
        .parentalBondBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HAIL},
        .battleAnimScript = gBattleAnimMove_IceBall,
    },

    [MOVE_NEEDLE_ARM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("NEEDLE ARM"),
        .description = COMPOUND_STRING(
            "Attacks with thorny arms. May cause flinching."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .minimizeDoubleDamage = B_UPDATED_MOVE_FLAGS < GEN_4,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_NeedleArm,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SLACK_OFF] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SLACK OFF"),
        .description = COMPOUND_STRING(
            "The user slacks off, restoring its own HP by up to half of its max HP."),
        .effect = EFFECT_RESTORE_HP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SlackOff,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HYPER_VOICE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("HYPER VOICE"),
        .description = COMPOUND_STRING(
            "The user lets loose a horribly echoing shout with the power to inflict damage."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .soundMove = TRUE,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HyperVoice,
        .validApprenticeMove = TRUE,
    },

    [MOVE_POISON_FANG] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("POISON FANG"),
        .description = COMPOUND_STRING(
            "The user bites the target with toxic fangs that may also leave the target badly poisoned."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_TOXIC,
            .chance = B_UPDATED_MOVE_DATA >= GEN_6 ? 50 : 30,
        }),
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PoisonFang,
    },

    [MOVE_CRUSH_CLAW] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("CRUSH CLAW"),
        .description = COMPOUND_STRING(
            "The user slashes the target with hard and sharp claws. This may also lower the target's DEFENSE."),
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_NORMAL,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 50,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SWORDS_DANCE},
        .battleAnimScript = gBattleAnimMove_CrushClaw,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BLAST_BURN] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("BLAST BURN"),
        .description = COMPOUND_STRING(
            "The target is razed with a fiery explosion. The user can't move on the next turn."),
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_FIRE,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_BlastBurn,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HYDRO_CANNON] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("HYDRO CANNON"),
        .description = COMPOUND_STRING(
            "The target is doused with a watery blast. The user can't move on the next turn."),
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_WATER,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_HydroCannon,
        .validApprenticeMove = TRUE,
    },

    [MOVE_METEOR_MASH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("METEOR MASH"),
        .description = COMPOUND_STRING(
            "Fires a meteor-like punch. May raise ATTACK."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 90 : 100,
        .type = TYPE_STEEL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_6 ? 90 : 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_PLUS_1,
            .self = TRUE,
            .chance = 20,
        }),
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MeteorMash,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ASTONISH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ASTONISH"),
        .description = COMPOUND_STRING(
            "The user attacks the target while shouting startlingly. This may also make the target flinch."),
        .effect = EFFECT_HIT,
        .power = 30,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .minimizeDoubleDamage = B_UPDATED_MOVE_FLAGS < GEN_4,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Astonish,
        .validApprenticeMove = TRUE,
    },

    [MOVE_WEATHER_BALL] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("WEATHER BALL"),
        .description = COMPOUND_STRING(
            "This attack move varies in power and type depending on the weather."),
        .effect = EFFECT_WEATHER_BALL,
        .power = 50,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .zMove = { .powerOverride = 160 },
        .ballisticMove = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HAIL, COMBO_STARTER_RAIN_DANCE, COMBO_STARTER_SANDSTORM, COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_WeatherBall,
        .validApprenticeMove = TRUE,
    },

    [MOVE_AROMATHERAPY] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("AROMATHERAPY"),
        .description = COMPOUND_STRING(
            "The user releases a soothing scent that heals all status conditions affecting its party."),
        .effect = EFFECT_HEAL_BELL,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RECOVER_HP },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Aromatherapy,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FAKE_TEARS] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FAKE TEARS"),
        .description = COMPOUND_STRING(
            "The user feigns crying to fluster the target, harshly lowering its SP. DEF stat."),
        .effect = EFFECT_SPECIAL_DEFENSE_DOWN_2,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FakeTears,
        .validApprenticeMove = TRUE,
    },

    [MOVE_AIR_CUTTER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("AIR CUTTER"),
        .description = COMPOUND_STRING(
            "Hacks with razorlike wind. High critical-hit ratio."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 60 : 55,
        .type = TYPE_FLYING,
        .accuracy = 95,
        .criticalHitStage = 1,
        .pp = 25,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .windMove = TRUE,
        .slicingMove = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_AirCutter,
        .validApprenticeMove = TRUE,
    },

    [MOVE_OVERHEAT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("OVERHEAT"),
        .description = COMPOUND_STRING(
            "The user releases intense heat to attack. This also harshly lowers the user's SP. ATK stat."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 130 : 140,
        .type = TYPE_FIRE,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = B_UPDATED_MOVE_DATA < GEN_4,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_2,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_Overheat,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ODOR_SLEUTH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ODOR SLEUTH"),
        .description = COMPOUND_STRING(
            "Enables the user to hit a Ghost type with any type of move, and to hit evasive foes."),
        .effect = EFFECT_FORESIGHT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_4 ? 0 : 100,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_OdorSleuth,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ROCK_TOMB] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ROCK TOMB"),
        .description = COMPOUND_STRING(
            "Hurls boulders to prevent the foe from moving, lowering its SPEED and evasiveness."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_ROCK,
        .accuracy = 85,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 15 : 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        },
        {
            .moveEffect = MOVE_EFFECT_EVS_MINUS_1,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_ROCK_THROW},
        .battleAnimScript = gBattleAnimMove_RockTomb,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SILVER_WIND] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SILVER WIND"),
        .description = COMPOUND_STRING(
            "The target is attacked with silvery scales blown by the wind. This may raise the user's stats."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .windMove = B_EXTRAPOLATED_MOVE_FLAGS,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ALL_STATS_UP,
            .self = TRUE,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SilverWind,
        .validApprenticeMove = TRUE,
    },

    [MOVE_METAL_SOUND] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("METAL SOUND"),
        .description = COMPOUND_STRING(
            "A horrible sound like scraping metal harshly lowers the target's SP. DEF stat."),
        .effect = EFFECT_SPECIAL_DEFENSE_DOWN_2,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .magicCoatAffected = TRUE,
        .soundMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_METAL_SOUND,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MetalSound,
        .validApprenticeMove = TRUE,
    },

    [MOVE_GRASS_WHISTLE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("GRASS WHISTLE"),
        .description = COMPOUND_STRING(
            "The user plays a pleasant melody that lulls the target into a deep sleep."),
        .effect = EFFECT_SLEEP,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 55,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .magicCoatAffected = TRUE,
        .soundMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_GrassWhistle,
        .validApprenticeMove = TRUE,
    },

    [MOVE_TICKLE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("TICKLE"),
        .description = COMPOUND_STRING(
            "The user tickles the target, making it laugh and reducing its ATTACK and DEFENSE."),
        .effect = EFFECT_TICKLE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Tickle,
        .validApprenticeMove = TRUE,
    },

    [MOVE_COSMIC_POWER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("COSMIC POWER"),
        .description = COMPOUND_STRING(
            "The user absorbs a mystical power from space to raise its DEFENSE and SP. DEF."),
        .effect = EFFECT_COSMIC_POWER,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_CosmicPower,
        .validApprenticeMove = TRUE,
    },

    [MOVE_WATER_SPOUT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("WATER SPOUT"),
        .description = COMPOUND_STRING(
            "The user spouts water to damage opposing Pokémon. This move is stronger at high HP."),
        .effect = EFFECT_POWER_BASED_ON_USER_HP,
        .power = 150,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_WaterSpout,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SIGNAL_BEAM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SIGNAL BEAM"),
        .description = COMPOUND_STRING(
            "The user attacks with a strange beam of light. This may also confuse the target."),
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SignalBeam,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SHADOW_PUNCH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SHADOW PUNCH"),
        .description = COMPOUND_STRING(
            "The user throws a punch from the shadows. This attack never misses."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_GHOST,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ShadowPunch,
        .validApprenticeMove = TRUE,
    },

    [MOVE_EXTRASENSORY] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("EXTRASENSORY"),
        .description = COMPOUND_STRING(
            "The user attacks with an odd power. This may also make the target flinch."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 20 : 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .minimizeDoubleDamage = B_UPDATED_MOVE_FLAGS < GEN_4,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Extrasensory,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SKY_UPPERCUT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SKY UPPERCUT"),
        .description = COMPOUND_STRING(
            "The user attacks the target with with an uppercut thrown skyward with force."),
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .damagesAirborne = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .battleAnimScript = gBattleAnimMove_SkyUppercut,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SAND_TOMB] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SAND TOMB"),
        .description = COMPOUND_STRING(
            "The user traps the target inside a harshly raging sandstorm for 4-5 turns."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 35 : 15,
        .type = TYPE_GROUND,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 85 : 70,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
        }),
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SANDSTORM},
        .battleAnimScript = gBattleAnimMove_SandTomb,
        .validApprenticeMove = TRUE,
    },

    [MOVE_SHEER_COLD] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SHEER COLD"),
        .description = COMPOUND_STRING(
            "The target is subjected to absolute-zero cold. The target faints instantly if this hits."),
        .effect = EFFECT_OHKO,
        .power = 1,
        .type = TYPE_ICE,
        .accuracy = 30,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HAIL, COMBO_STARTER_MIND_READER},
        .battleAnimScript = gBattleAnimMove_SheerCold,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MUDDY_WATER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MUDDY WATER"),
        .description = COMPOUND_STRING(
            "The user attacks by shooting muddy water at opposing Pokémon. This may lower their accuracy."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 90 : 95,
        .type = TYPE_WATER,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .skyBattleBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ACC_MINUS_1,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_MuddyWater,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BULLET_SEED] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("BULLET SEED"),
        .description = COMPOUND_STRING(
            "The user forcefully shoots seeds at the target 2-5 times in a row. "),
        .effect = EFFECT_MULTI_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 25 : 10,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ballisticMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .battleAnimScript = gBattleAnimMove_BulletSeed,
    },

    [MOVE_AERIAL_ACE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("AERIAL ACE"),
        .description = COMPOUND_STRING(
            "The user confounds the target with speed, then slashes. This attack never misses."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FLYING,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_AerialAce,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ICICLE_SPEAR] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ICICLE SPEAR"),
        .description = COMPOUND_STRING(
            "The user launches sharp icicles at the target 2-5 times in a row. "),
        .effect = EFFECT_MULTI_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 25 : 10,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_IcicleSpear,
    },

    [MOVE_IRON_DEFENSE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("IRON DEFENSE"),
        .description = COMPOUND_STRING(
            "The user hardens its body's surface like iron, sharply raising its DEFENSE."),
        .effect = EFFECT_DEFENSE_UP_2,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_IronDefense,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BLOCK] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("BLOCK"),
        .description = COMPOUND_STRING(
            "The user blocks the target's way with arms spread wide to prevent escape."),
        .effect = EFFECT_MEAN_LOOK,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .ignoresProtect = (B_UPDATED_MOVE_FLAGS >= GEN_6) || (B_UPDATED_MOVE_FLAGS <= GEN_3),
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Block,
        .validApprenticeMove = TRUE,
    },

    [MOVE_HOWL] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("HOWL"),
        .description = COMPOUND_STRING(
            "The user howls loudly to raise the spirit of itself and allies. This raises their ATTACK."),
        .power = 0,
        .effect = B_UPDATED_MOVE_DATA >= GEN_8 ? EFFECT_ATTACK_UP_USER_ALLY : EFFECT_ATTACK_UP,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_USER, // Targeting is handled through the script
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .soundMove = B_UPDATED_MOVE_FLAGS >= GEN_8,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Howl,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DRAGON_CLAW] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("DRAGON CLAW"),
        .description = COMPOUND_STRING(
            "The user slashes the target with huge sharp claws. "),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_DRAGON_BREATH, COMBO_STARTER_DRAGON_DANCE, COMBO_STARTER_DRAGON_RAGE, COMBO_STARTER_TYRANT_CRUSH, COMBO_STARTER_DRAGON_TAIL},
        .battleAnimScript = gBattleAnimMove_DragonClaw,
        .validApprenticeMove = TRUE,
    },

    [MOVE_FRENZY_PLANT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FRENZY PLANT"),
        .description = COMPOUND_STRING(
            "The target is slammed with enormous roots. The user can't move on the next turn."),
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_GRASS,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .skyBattleBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .battleAnimScript = gBattleAnimMove_FrenzyPlant,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BULK_UP] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("BULK UP"),
        .description = COMPOUND_STRING(
            "The user tenses its muscles to bulk up its body, raising both its ATTACK and DEFENSE."),
        .effect = EFFECT_BULK_UP,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_BulkUp,
        .validApprenticeMove = TRUE,
    },

    [MOVE_BOUNCE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("BOUNCE"),
        .description = COMPOUND_STRING(
            "The user bounces up high and drops on the target on the next turn. This may paralyze it."),
        .effect = EFFECT_SEMI_INVULNERABLE,
        .power = 85,
        .type = TYPE_FLYING,
        .accuracy = 85,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .gravityBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        .argument.twoTurnAttack = { .stringId =  STRINGID_PKMNSPRANGUP, .status = COMPRESS_BITS(STATUS3_ON_AIR) },
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Bounce,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MUD_SHOT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("MUD SHOT"),
        .description = COMPOUND_STRING(
            "The user attacks by hurling mud at the target. This also lowers the target's SPEED."),
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_GROUND,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SANDSTORM},
        .battleAnimScript = gBattleAnimMove_MudShot,
    },

    [MOVE_POISON_TAIL] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("POISON TAIL"),
        .description = COMPOUND_STRING(
            "The user hits the target with its tail. This may poison the target. Critical hits land more easily."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_POISON,
        .accuracy = 100,
        .criticalHitStage = 1,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PoisonTail,
        .validApprenticeMove = TRUE,
    },

    [MOVE_COVET] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("COVET"),
        .description = COMPOUND_STRING(
            "The user endearingly approaches the target, then steals the target's held item."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 60 : 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 25 : 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = B_UPDATED_MOVE_DATA >= GEN_4,
        .meFirstBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_STEAL_ITEM,
        }),
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Covet,
        .validApprenticeMove = TRUE,
    },

    [MOVE_VOLT_TACKLE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("VOLT TACKLE"),
        .description = COMPOUND_STRING(
            "A life-risking tackle that slightly hurts the user."),
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .recoil = 33,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        #if B_UPDATED_MOVE_DATA >= GEN_4
            .additionalEffects = ADDITIONAL_EFFECTS({
                .moveEffect = MOVE_EFFECT_PARALYSIS,
                .chance = 10,
            }),
        #endif
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_VoltTackle,
        .validApprenticeMove = TRUE,
    },

    [MOVE_MAGICAL_LEAF] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("MAGICAL LEAF"),
        .description = COMPOUND_STRING(
            "The user scatters curious leaves that chase the target. This attack never misses."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .battleAnimScript = gBattleAnimMove_MagicalLeaf,
        .validApprenticeMove = TRUE,
    },

    [MOVE_WATER_SPORT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("WATER SPORT"),
        .description = COMPOUND_STRING(
            "The user soaks the battlefield with water. This weakens Fire-type moves for 5 turns."),
        .effect = EFFECT_WATER_SPORT,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_WATER_SPORT,
        .contestComboMoves = {COMBO_STARTER_MUD_SPORT, COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_WaterSport,
        .validApprenticeMove = TRUE,
    },

    [MOVE_CALM_MIND] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("CALM MIND"),
        .description = COMPOUND_STRING(
            "The user quietly focuses its mind and calms its spirit to raise its SP. ATK and SP. DEF."),
        .effect = EFFECT_CALM_MIND,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_CALM_MIND,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_CalmMind,
        .validApprenticeMove = TRUE,
    },

    [MOVE_LEAF_BLADE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("LEAF BLADE"),
        .description = COMPOUND_STRING(
            "The user attacks with sharp, blade-like leaves. Critical hits land more easily."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_4 ? 90 : 70,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .criticalHitStage = 1,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_LeafBlade,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DRAGON_DANCE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("DRAGON DANCE"),
        .description = COMPOUND_STRING(
            "A mystic, powerful dance that raises the user's ATTACK and SPEED."),
        .effect = EFFECT_DRAGON_DANCE,
        .power = 0,
        .type = TYPE_DRAGON,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .danceMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_DRAGON_DANCE,
        .contestComboMoves = {COMBO_STARTER_DRAGON_BREATH, COMBO_STARTER_DRAGON_RAGE, COMBO_STARTER_TYRANT_CRUSH, COMBO_STARTER_DRAGON_TAIL},
        .battleAnimScript = gBattleAnimMove_DragonDance,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ROCK_BLAST] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ROCK BLAST"),
        .description = COMPOUND_STRING(
            "The user hurls 2-5 hard rocks at the target. "),
        .effect = EFFECT_MULTI_HIT,
        .power = 25,
        .type = TYPE_ROCK,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 90 : 80,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ballisticMove = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RockBlast,
    },

    [MOVE_SHOCK_WAVE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SHOCK WAVE"),
        .description = COMPOUND_STRING(
            "The user strikes the target with a quick jolt of electricity. This attack never misses."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARGE},
        .battleAnimScript = gBattleAnimMove_ShockWave,
        .validApprenticeMove = TRUE,
    },

    [MOVE_WATER_PULSE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("WATER PULSE"),
        .description = COMPOUND_STRING(
            "The user attacks with a pulsing blast of water. This may also confuse the target."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .pulseMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 20,
        }),
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_WaterPulse,
        .validApprenticeMove = TRUE,
    },

    [MOVE_DOOM_DESIRE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DOOM DESIRE"),
        .description = COMPOUND_STRING(
            "Summons strong sunlight to attack 2 turns later."),
        .effect = EFFECT_FUTURE_SIGHT,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 140 : 120,
        .type = TYPE_STEEL,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 100 : 85,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DoomDesire,
        .validApprenticeMove = TRUE,
    },

    [MOVE_PSYCHO_BOOST] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("PSYCHO BOOST"),
        .description = COMPOUND_STRING(
            "Allows a full-power attack, but sharply lowers SP. ATK."),
        .effect = EFFECT_HIT,
        .power = 140,
        .type = TYPE_PSYCHIC,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_2,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CALM_MIND},
        .battleAnimScript = gBattleAnimMove_PsychoBoost,
        .validApprenticeMove = TRUE,
    },

    [MOVE_ROOST] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ROOST"),
        .description = COMPOUND_STRING(
            "Landing to rest, the user restores its own HP by half its max HP."),
        .effect = EFFECT_ROOST,
        .power = 0,
        .type = TYPE_FLYING,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_BRAVE_BIRD},
        .battleAnimScript = gBattleAnimMove_Roost,
    },

    [MOVE_GRAVITY] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("GRAVITY"),
        .description = COMPOUND_STRING(
            "Intensifies gravity for 5 turns, grounding airborne Pokémon and raising the accuracy of moves."),
        .effect = EFFECT_GRAVITY,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Gravity,
    },

    [MOVE_MIRACLE_EYE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MIRACLE EYE"),
        .description = COMPOUND_STRING(
            "Negate evasiveness and Dark-type's immunities."),
        .effect = EFFECT_MIRACLE_EYE,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MiracleEye,
    },

    [MOVE_WAKE_UP_SLAP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("WAKE-UP SLAP"),
        .description = COMPOUND_STRING(
            "Powerful against sleeping foes, but also heals them."),
        .effect = EFFECT_DOUBLE_POWER_ON_ARG_STATUS,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 70 : 60,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .argument = { .status = STATUS1_SLEEP },
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_REMOVE_STATUS,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_WakeUpSlap,
    },

    [MOVE_HAMMER_ARM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("HAMMER ARM"),
        .description = COMPOUND_STRING(
            "A swinging fist attack that also lowers SPEED."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .battleAnimScript = gBattleAnimMove_HammerArm,
    },

    [MOVE_GYRO_BALL] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("GYRO BALL"),
        .description = COMPOUND_STRING(
            "A high-speed spin that does more damage to faster foes."),
        .effect = EFFECT_GYRO_BALL,
        .power = 1,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ballisticMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_GyroBall,
    },

    [MOVE_HEALING_WISH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("HEALING WISH"),
        .description = sHealingWishDescription,
        .effect = EFFECT_HEALING_WISH,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .healingMove = TRUE,
        .snatchAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_GREAT_APPEAL_BUT_NO_MORE_MOVES,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HealingWish,
    },

    [MOVE_BRINE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BRINE"),
        .description = COMPOUND_STRING(
            "Sprays the target with salty water, dealing double damage if it has half HP or less."),
        .effect = EFFECT_BRINE,
        .power = 65,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_Brine,
    },

    [MOVE_NATURAL_GIFT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("NATURAL GIFT"),
        .description = COMPOUND_STRING(
            "The effectiveness varies with the held Berry."),
        .effect = EFFECT_NATURAL_GIFT,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_NaturalGift,
    },

    [MOVE_FEINT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FEINT"),
        .description = sFeintDescription,
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 30 : 50,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 2,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = B_UPDATED_MOVE_FLAGS < GEN_6,
        //.metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FEINT,
        }),
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Feint,
    },

    [MOVE_PLUCK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("PLUCK"),
        .description = COMPOUND_STRING(
            "The user pecks the target, stealing and eating its Berry if it is holding one."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BUG_BITE,
        }),
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Pluck,
    },

    [MOVE_TAILWIND] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TAILWIND"),
        .description = COMPOUND_STRING(
            "Whips up a turbulent breeze that raises SPEED."),
        .effect = EFFECT_TAILWIND,
        .power = 0,
        .type = TYPE_FLYING,
        .accuracy = 0,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 15 : 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_BOOST_CRITS },
        .snatchAffected = TRUE,
        .windMove = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Tailwind,
    },

    [MOVE_ACUPRESSURE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ACUPRESSURE"),
        .description = COMPOUND_STRING(
            "The user sharply raises one of its stats."),
        .effect = EFFECT_ACUPRESSURE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER | MOVE_TARGET_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_BOOST_CRITS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .snatchAffected = B_UPDATED_MOVE_FLAGS < GEN_5,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Acupressure,
    },

    [MOVE_METAL_BURST] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("METAL BURST"),
        .description = COMPOUND_STRING(
            "Retaliates any hit with greater power."),
        .effect = EFFECT_METAL_BURST,
        .power = 1,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .meFirstBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_METAL_SOUND},
        .battleAnimScript = gBattleAnimMove_MetalBurst,
    },

    [MOVE_U_TURN] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("U-TURN"),
        .description = sUTurnDescription,
        .effect = EFFECT_HIT_ESCAPE,
        .power = 70,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_UTurn,
    },

    [MOVE_CLOSE_COMBAT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("CLOSE COMBAT"),
        .description = sCloseCombatDescription,
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_SPDEF_DOWN,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY, COMBO_STARTER_MIND_READER},
        .battleAnimScript = gBattleAnimMove_CloseCombat,
    },

    [MOVE_PAYBACK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("PAYBACK"),
        .description = COMPOUND_STRING(
            "An attack that gains power if the user moves last."),
        .effect = EFFECT_PAYBACK,
        .power = 50,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_PAYBACK,
        .contestComboMoves = {COMBO_STARTER_REVENGE},
        .battleAnimScript = gBattleAnimMove_Payback,
    },

    [MOVE_ASSURANCE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ASSURANCE"),
        .description = COMPOUND_STRING(
            "An attack that gains power if the foe has been hurt."),
        .effect = EFFECT_ASSURANCE,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 60 : 50,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_PAYBACK, COMBO_STARTER_REVENGE},
        .battleAnimScript = gBattleAnimMove_Assurance,
    },

    [MOVE_EMBARGO] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("EMBARGO"),
        .description = COMPOUND_STRING(
            "Prevents the foe from using any items."),
        .effect = EFFECT_EMBARGO,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Embargo,
    },

    [MOVE_FLING] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FLING"),
        .description = COMPOUND_STRING(
            "The user flings its held item at the target. This move's power and effects depend on the item."),
        .effect = EFFECT_FLING,
        .power = 1,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .parentalBondBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Fling,
    },

    [MOVE_PSYCHO_SHIFT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("PSYCHO SHIFT"),
        .description = COMPOUND_STRING(
            "Transfers status problems to the foe."),
        .effect = EFFECT_PSYCHO_SHIFT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_6 ? 100 : 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_2 },
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PsychoShift,
    },

    [MOVE_TRUMP_CARD] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TRUMP CARD"),
        .description = COMPOUND_STRING(
            "The less PP the move has the more damage it does."),
        .effect = EFFECT_TRUMP_CARD,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_TrumpCard,
    },

    [MOVE_HEAL_BLOCK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("HEAL BLOCK"),
        .description = COMPOUND_STRING(
            "Prevents the foe from recovering any HP."),
        .effect = EFFECT_HEAL_BLOCK,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_2 },
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HealBlock,
    },

    [MOVE_WRING_OUT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("WRING OUT"),
        .description = sWringOutDescription,
        .effect = EFFECT_POWER_BASED_ON_TARGET_HP,
        .power = 120,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_WringOut,
    },

    [MOVE_POWER_TRICK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("POWER TRICK"),
        .description = COMPOUND_STRING(
            "The user swaps its ATTACK and DEFENSE stats."),
        .effect = EFFECT_POWER_TRICK,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .snatchAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PowerTrick,
    },

    [MOVE_GASTRO_ACID] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("GASTRO ACID"),
        .description = COMPOUND_STRING(
            "The user hurls up its stomach acids on the target, eliminating the effect of its Ability."),
        .effect = EFFECT_GASTRO_ACID,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_GastroAcid,
    },

    [MOVE_LUCKY_CHANT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("LUCKY CHANT"),
        .description = COMPOUND_STRING(
            "The user chants an incantation to protect itself and its allies from critical hits for 5 turns."),
        .effect = EFFECT_LUCKY_CHANT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_EVSN_UP_1 },
        .snatchAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_LUCKY_CHANT,
        .contestComboMoves = {COMBO_STARTER_HEAL_BELL},
        .battleAnimScript = gBattleAnimMove_LuckyChant,
    },

    [MOVE_ME_FIRST] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ME FIRST"),
        .description = COMPOUND_STRING(
            "Executes the foe's attack with greater power."),
        .effect = EFFECT_ME_FIRST,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_OPPONENT,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_2 },
        .ignoresSubstitute = TRUE,
        //.metronomeBanned = TRUE,
        .mirrorMoveBanned = TRUE,
        .meFirstBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .mimicBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MeFirst,
    },

    [MOVE_COPYCAT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("COPYCAT"),
        .description = COMPOUND_STRING(
            "The user mimics the move used before it. This fails if no other move has been used yet."),
        .effect = EFFECT_COPYCAT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ACC_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .mimicBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Copycat,
    },

    [MOVE_POWER_SWAP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("POWER SWAP"),
        .description = COMPOUND_STRING(
            "Swaps changes to ATTACK and SP. ATK with the foe."),
        .effect = EFFECT_POWER_SWAP,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresSubstitute = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PowerSwap,
    },

    [MOVE_GUARD_SWAP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("GUARD SWAP"),
        .description = COMPOUND_STRING(
            "Swaps changes to DEFENSE and SP. DEF with the foe."),
        .effect = EFFECT_GUARD_SWAP,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresSubstitute = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_GuardSwap,
    },

    [MOVE_PUNISHMENT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("PUNISHMENT"),
        .description = COMPOUND_STRING(
            "Does more damage if the foe has powered up."),
        .effect = EFFECT_PUNISHMENT,
        .power = 60,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Punishment,
    },

    [MOVE_LAST_RESORT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("LAST RESORT"),
        .description = COMPOUND_STRING(
            "Can only be used if every other move has been used."),
        .effect = EFFECT_LAST_RESORT,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 140 : 130,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_LastResort,
    },

    [MOVE_WORRY_SEED] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("WORRY SEED"),
        .description = COMPOUND_STRING(
            "Plants a seed on the foe giving it Insomnia."),
        .effect = EFFECT_WORRY_SEED,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_WORRY_SEED,
        .contestComboMoves = {COMBO_STARTER_LEECH_SEED},
        .battleAnimScript = gBattleAnimMove_WorrySeed,
    },

    [MOVE_SUCKER_PUNCH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SUCKER PUNCH"),
        .description = COMPOUND_STRING(
            "The user attacks first against an incoming foe. This move fails if the target isn't attacking."),
        .effect = EFFECT_SUCKER_PUNCH,
        .power = 70,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SuckerPunch,
    },

    [MOVE_TOXIC_SPIKES] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("TOXIC SPIKES"),
        .description = COMPOUND_STRING(
            "The user lays spikes at the opposing team's feet, poisoning Pokémon that switch into battle."),
        .effect = EFFECT_TOXIC_SPIKES,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_OPPONENTS_FIELD,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .forcePressure = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ToxicSpikes,
    },

    [MOVE_HEART_SWAP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("HEART SWAP"),
        .description = COMPOUND_STRING(
            "Swaps any stat changes with the foe."),
        .effect = EFFECT_HEART_SWAP,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_BOOST_CRITS },
        .ignoresSubstitute = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HeartSwap,
    },

    [MOVE_AQUA_RING] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("AQUA RING"),
        .description = COMPOUND_STRING(
            "Forms a veil of water that restores HP."),
        .effect = EFFECT_AQUA_RING,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .snatchAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_AquaRing,
    },

    [MOVE_MAGNET_RISE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAGNET RISE"),
        .description = COMPOUND_STRING(
            "The user levitates using electromagnetic force for 5 turns."),
        .effect = EFFECT_MAGNET_RISE,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_EVSN_UP_1 },
        .snatchAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .gravityBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MagnetRise,
    },

    [MOVE_FLARE_BLITZ] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FLARE BLITZ"),
        .description = COMPOUND_STRING(
            "A charge that may burn the foe. Also hurts the user."),
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .recoil = 33,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .thawsUser = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_FlareBlitz,
    },

    [MOVE_FORCE_PALM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FORCE PALM"),
        .description = COMPOUND_STRING(
            "A shock wave attack that may paralyze the foe."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ForcePalm,
    },

    [MOVE_AURA_SPHERE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("AURA SPHERE"),
        .description = COMPOUND_STRING(
            "Attacks with an aura blast that cannot be evaded."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 80 : 90,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .pulseMove = TRUE,
        .ballisticMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_AuraSphere,
    },

    [MOVE_ROCK_POLISH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ROCK POLISH"),
        .description = COMPOUND_STRING(
            "The user polishes its body to reduce drag. This sharply raises the SPEED stat."),
        .effect = EFFECT_SPEED_UP_2,
        .power = 0,
        .type = TYPE_ROCK,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RockPolish,
    },

    [MOVE_POISON_JAB] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("POISON JAB"),
        .description = COMPOUND_STRING(
            "The user stabs the target with a limb steeped in poison. This may poison the target."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PoisonJab,
    },

    [MOVE_DARK_PULSE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DARK PULSE"),
        .description = COMPOUND_STRING(
            "Attacks with a horrible aura. May cause flinching."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .pulseMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 20,
        }),
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DarkPulse,
    },

    [MOVE_NIGHT_SLASH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("NIGHT SLASH"),
        .description = COMPOUND_STRING(
            "The user slashes the target the instant it drops its guard. Critical hits land more easily."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_DARK,
        .accuracy = 100,
        .criticalHitStage = 1,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_NightSlash,
    },

    [MOVE_AQUA_TAIL] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("AQUA TAIL"),
        .description = COMPOUND_STRING(
            "The user swings its tail like a wave to attack."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_WATER,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_AquaTail,
    },

    [MOVE_SEED_BOMB] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SEED BOMB"),
        .description = COMPOUND_STRING(
            "A barrage of hard seeds is fired at the foe."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ballisticMove = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SeedBomb,
    },

    [MOVE_AIR_SLASH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("AIR SLASH"),
        .description = COMPOUND_STRING(
            "Attacks with a blade of air. May cause flinching."),
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_FLYING,
        .accuracy = 95,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 15 : 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .slicingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_AirSlash,
    },

    [MOVE_X_SCISSOR] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("X-SCISSOR"),
        .description = COMPOUND_STRING(
            "Slashes the foe with crossed scythes, claws, etc."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SWORDS_DANCE},
        .battleAnimScript = gBattleAnimMove_XScissor,
    },

    [MOVE_BUG_BUZZ] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("BUG BUZZ"),
        .description = COMPOUND_STRING(
            "The user generates a harsh sound wave by flapping its wings. It may lower the target's SP. DEF."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .soundMove = TRUE,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_BugBuzz,
    },

    [MOVE_DRAGON_PULSE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DRAGON PULSE"),
        .description = COMPOUND_STRING(
            "Generates a shock wave to damage the foe."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 85 : 90,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .pulseMove = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DragonPulse,
    },

    [MOVE_TYRANT_CRUSH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("TYRANT CRUSH"),
        .description = COMPOUND_STRING(
            "A menacingly powerful crushing attack that may make the foe flinch."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_DRAGON,
        .accuracy = 75,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .minimizeDoubleDamage = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 20,
        }),
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_TYRANT_CRUSH,
        .contestComboMoves = {COMBO_STARTER_DRAGON_BREATH, COMBO_STARTER_DRAGON_DANCE, COMBO_STARTER_DRAGON_RAGE, COMBO_STARTER_DRAGON_TAIL},
        .battleAnimScript = gBattleAnimMove_TyrantCrush,
    },

    [MOVE_POWER_GEM] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("POWER GEM"),
        .description = COMPOUND_STRING(
            "The user attacks with a ray of light that sparkles as if it were itself made of gemstones."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 80 : 70,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PowerGem,
    },

    [MOVE_DRAIN_PUNCH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DRAIN PUNCH"),
        .description = sMegaDrainDescription,
        .effect = EFFECT_ABSORB,
        .power = B_UPDATED_MOVE_DATA >= GEN_5 ? 75 : 60,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_5 ? 10 : 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .argument = { .absorbPercentage = 50 },
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .healingMove = B_HEAL_BLOCKING >= GEN_6,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .battleAnimScript = gBattleAnimMove_DrainPunch,
    },

    [MOVE_VACUUM_WAVE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("VACUUM WAVE"),
        .description = COMPOUND_STRING(
            "Whirls its fists to send a wave that strikes first."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_VacuumWave,
    },

    [MOVE_FOCUS_BLAST] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FOCUS BLAST"),
        .description = COMPOUND_STRING(
            "The user heightens its focus and unleashes its power. This may lower the target's SP. DEF."),
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_FIGHTING,
        .accuracy = 70,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ballisticMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_FOCUS_ENERGY},
        .battleAnimScript = gBattleAnimMove_FocusBlast,
    },

    [MOVE_ENERGY_BALL] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ENERGY BALL"),
        .description = COMPOUND_STRING(
            "Draws power from nature to attack. May lower SP. DEF."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 90 : 80,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ballisticMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .battleAnimScript = gBattleAnimMove_EnergyBall,
    },

    [MOVE_BRAVE_BIRD] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BRAVE BIRD"),
        .description = COMPOUND_STRING(
            "A low altitude charge that also hurts the user."),
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .recoil = 33,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_BRAVE_BIRD,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_BraveBird,
    },

    [MOVE_EARTH_POWER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("EARTH POWER"),
        .description = COMPOUND_STRING(
            "The user makes the ground under the target erupt violently. This may lower the target's SP. DEF."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .skyBattleBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_EarthPower,
    },

    [MOVE_SWITCHEROO] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SWITCHEROO"),
        .description = COMPOUND_STRING(
            "Swaps items with the foe faster than the eye can see."),
        .effect = EFFECT_TRICK,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_2 },
        //.metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Switcheroo,
    },

    [MOVE_GIGA_IMPACT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("GIGA IMPACT"),
        .description = sHyperBeamDescription,
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_GigaImpact,
    },

    [MOVE_NASTY_PLOT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("NASTY PLOT"),
        .description = COMPOUND_STRING(
            "The user stimulates its brain by thinking bad thoughts, sharply raising its SP. ATK."),
        .effect = EFFECT_SPECIAL_ATTACK_UP_2,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_NastyPlot,
    },

    [MOVE_BULLET_PUNCH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BULLET PUNCH"),
        .description = COMPOUND_STRING(
            "Punches as fast as a bul- let. It always hits first."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_BulletPunch,
    },

    [MOVE_AVALANCHE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("AVALANCHE"),
        .description = COMPOUND_STRING(
            "The user triggers an avalanche. This move is boosted if the target attacked it this turn."),
        .effect = EFFECT_REVENGE,
        .power = 60,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = -4,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_LATER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Avalanche,
    },

    [MOVE_ICE_SHARD] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ICE SHARD"),
        .description = COMPOUND_STRING(
            "The user flash-freezes chunks of ice and hurls them at the target. This move always goes first."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_IceShard,
    },

    [MOVE_SHADOW_CLAW] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SHADOW CLAW"),
        .description = COMPOUND_STRING(
            "The user slashes with a sharp claw made from shadows. Critical hits land more easily."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .criticalHitStage = 1,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ShadowClaw,
    },

    [MOVE_THUNDER_FANG] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("THUNDER FANG"),
        .description = COMPOUND_STRING(
            "The user bites with electrified fangs. This may make the target flinch or paralyze it."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_ELECTRIC,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 10,
        },
        {
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_THUNDER_FANG,
        .contestComboMoves = {COMBO_STARTER_CHARGE, COMBO_STARTER_FIRE_FANG, COMBO_STARTER_ICE_FANG},
        .battleAnimScript = gBattleAnimMove_ThunderFang,
    },

    [MOVE_ICE_FANG] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ICE FANG"),
        .description = COMPOUND_STRING(
            "The user bites with freezing cold fangs. This may make the target flinch or freeze it."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_ICE,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FREEZE_OR_FROSTBITE,
            .chance = 10,
        },
        {
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_ICE_FANG,
        .contestComboMoves = {COMBO_STARTER_FIRE_FANG, COMBO_STARTER_THUNDER_FANG},
        .battleAnimScript = gBattleAnimMove_IceFang,
    },

    [MOVE_FIRE_FANG] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FIRE FANG"),
        .description = COMPOUND_STRING(
            "The user bites with flame cloaked fangs. This may make the target flinch or burn it."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_FIRE,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        },
        {
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_FIRE_FANG,
        .contestComboMoves = {COMBO_STARTER_ICE_FANG, COMBO_STARTER_THUNDER_FANG},
        .battleAnimScript = gBattleAnimMove_FireFang,
    },

    [MOVE_SHADOW_SNEAK] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SHADOW SNEAK"),
        .description = COMPOUND_STRING(
            "The user extends its shadow and attacks the target from behind. This move always goes first."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ShadowSneak,
    },

    [MOVE_MUD_BOMB] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MUD BOMB"),
        .description = COMPOUND_STRING(
            "Throws a blob of mud to damage and cut accuracy."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_GROUND,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ballisticMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ACC_MINUS_1,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MudBomb,
    },

    [MOVE_PSYCHO_CUT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("PSYCHO CUT"),
        .description = COMPOUND_STRING(
            "Tears with psychic blades. High critical-hit ratio."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .criticalHitStage = 1,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .slicingMove = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PsychoCut,
    },

    [MOVE_ZEN_HEADBUTT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ZEN HEADBUTT"),
        .description = COMPOUND_STRING(
            "The user clears its mind, then headbutts the target. This may make the target flinch."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 20,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ZenHeadbutt,
    },

    [MOVE_MIRROR_SHOT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MIRROR SHOT"),
        .description = COMPOUND_STRING(
            "Emits a flash of energy to damage and cut accuracy."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_STEEL,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ACC_MINUS_1,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MirrorShot,
    },

    [MOVE_FLASH_CANNON] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FLASH CANNON"),
        .description = COMPOUND_STRING(
            "Releases a blast of light that may lower SP. DEF."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FlashCannon,
    },

    [MOVE_ROCK_CLIMB] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ROCK CLIMB"),
        .description = COMPOUND_STRING(
            "A charging attack that may confuse the foe."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 20,
        }),
        .contestEffect = CONTEST_EFFECT_BETTER_WITH_GOOD_CONDITION,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RockClimb,
    },

    [MOVE_DEFOG] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DEFOG"),
        .description = COMPOUND_STRING(
            "Removes obstacles and lowers evasion."),
        .effect = EFFECT_DEFOG,
        .power = 0,
        .type = TYPE_FLYING,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ACC_UP_1 },
        //.ignoresSubstitute = TRUE, In Gen5+, the evasion drop will no longer bypass Substitute. However, this is tricky to code
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Defog,
    },

    [MOVE_TRICK_ROOM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TRICK ROOM"),
        .description = COMPOUND_STRING(
            "Slower Pokémon get to move first for 5 turns."),
        .effect = EFFECT_TRICK_ROOM,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = -7,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ACC_UP_1 },
        .ignoresProtect = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_LATER,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_TrickRoom,
    },

    [MOVE_DRACO_METEOR] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DRACO METEOR"),
        .description = COMPOUND_STRING(
            "Casts comets onto the foe. Harshly lowers the SP. ATK."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 130 : 140,
        .type = TYPE_DRAGON,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_2,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DracoMeteor,
    },

    [MOVE_DISCHARGE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("DISCHARGE"),
        .description = COMPOUND_STRING(
            "The user releases a wild burst of electricity that hits all around it, and may paralyze."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARGE},
        .battleAnimScript = gBattleAnimMove_Discharge,
    },

    [MOVE_LAVA_PLUME] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("LAVA PLUME"),
        .description = sLavaPlumeDescription,
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_LavaPlume,
    },

    [MOVE_LEAF_STORM] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("LEAF STORM"),
        .description = COMPOUND_STRING(
            "The user unleashes all its leaves to attack. This also harshly lowers the user's SP. ATK."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 130 : 140,
        .type = TYPE_GRASS,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_2,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_LeafStorm,
    },

    [MOVE_POWER_WHIP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("POWER WHIP"),
        .description = COMPOUND_STRING(
            "Violently lashes the foe with vines or tentacles."),
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_GRASS,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .battleAnimScript = gBattleAnimMove_PowerWhip,
    },

    [MOVE_ROCK_WRECKER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ROCK WRECKER"),
        .description = sHyperBeamDescription,
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_ROCK,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ballisticMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RockWrecker,
    },

    [MOVE_CROSS_POISON] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("CROSS POISON"),
        .description = COMPOUND_STRING(
            "A slash that may poison a foe and do critical damage."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_POISON,
        .accuracy = 100,
        .criticalHitStage = 1,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_CrossPoison,
    },

    [MOVE_GUNK_SHOT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("GUNK SHOT"),
        .description = COMPOUND_STRING(
            "The user shoots heaps of filthy garbage at the target. This may also poison the target."),
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_POISON,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_6 ? 80 : 70,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_GunkShot,
    },

    [MOVE_IRON_HEAD] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("IRON HEAD"),
        .description = COMPOUND_STRING(
            "The user slams the target with its steel-hard head. This may make the target flinch."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_STEEL,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_IronHead,
    },

    [MOVE_MAGNET_BOMB] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAGNET BOMB"),
        .description = COMPOUND_STRING(
            "Launches a magnet that strikes without fail."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ballisticMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MagnetBomb,
    },

    [MOVE_STONE_EDGE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("STONE EDGE"),
        .description = COMPOUND_STRING(
            "Stabs the foe with stones. High critical-hit ratio."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_ROCK,
        .accuracy = 80,
        .criticalHitStage = 1,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_StoneEdge,
    },

    [MOVE_CAPTIVATE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("CAPTIVATE"),
        .description = COMPOUND_STRING(
            "Makes the opposite gender sharply reduce its SP. ATK."),
        .effect = EFFECT_CAPTIVATE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_2 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARM},
        .battleAnimScript = gBattleAnimMove_Captivate,
    },

    [MOVE_STEALTH_ROCK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("STEALTH ROCK"),
        .description = COMPOUND_STRING(
            "Sets floating stones that hurt a foe switching in."),
        .effect = EFFECT_STEALTH_ROCK,
        .power = 0,
        .type = TYPE_ROCK,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_OPPONENTS_FIELD,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .magicCoatAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .forcePressure = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_StealthRock,
    },

    [MOVE_GRASS_KNOT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("GRASS KNOT"),
        .description = COMPOUND_STRING(
            "The user snares the target with grass and trips it. Heavier targets take more damage."),
        .effect = EFFECT_LOW_KICK,
        .power = 1,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_GrassKnot,
    },

    [MOVE_CHATTER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("CHATTER"),
        .description = COMPOUND_STRING(
            "Attacks with a sound wave that causes confusion."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 65 : 60,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .soundMove = TRUE,
        .mirrorMoveBanned = B_UPDATED_MOVE_FLAGS < GEN_6,
        .mimicBanned = TRUE,
        //.metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
        #if B_UPDATED_MOVE_DATA >= GEN_6
            .chance = 100,
        #elif B_UPDATED_MOVE_DATA >= GEN_5
            .chance = 10,
        #else
            .chance = 31,
        #endif
        }),
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Chatter,
    },

    [MOVE_JUDGMENT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("JUDGMENT"),
        .description = COMPOUND_STRING(
            "The type varies with the kind of Plate held."),
        .effect = EFFECT_CHANGE_TYPE_ON_ITEM,
        .power = 100,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .argument = { .holdEffect = HOLD_EFFECT_PLATE },
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Judgment,
    },

    [MOVE_BUG_BITE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BUG BITE"),
        .description = sPluckDescription,
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BUG_BITE,
        }),
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_BugBite,
    },

    [MOVE_CHARGE_BEAM] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("CHARGE BEAM"),
        .description = COMPOUND_STRING(
            "The user fires a beam of charged particles at the target. The remaining charge raises SP. ATK."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_ELECTRIC,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARGE},
        .battleAnimScript = gBattleAnimMove_ChargeBeam,
    },

    [MOVE_WOOD_HAMMER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("WOOD HAMMER"),
        .description = COMPOUND_STRING(
            "Slams into the foe like a falling tree. This also hurts the user a little."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .recoil = 33,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_WoodHammer,
    },

    [MOVE_AQUA_JET] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("AQUA JET"),
        .description = COMPOUND_STRING(
            "The user surges at the target at blinding speed. This move always goes first."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_AquaJet,
    },

    [MOVE_ATTACK_ORDER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ATTACK ORDER"),
        .description = COMPOUND_STRING(
            "Underlings pummel the foe. High critical-hit ratio."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_BUG,
        .accuracy = 100,
        .criticalHitStage = 1,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_ATTACK_ORDER,
        .contestComboMoves = {COMBO_STARTER_DEFEND_ORDER, COMBO_STARTER_HEAL_ORDER},
        .battleAnimScript = gBattleAnimMove_AttackOrder,
    },

    [MOVE_DEFEND_ORDER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DEFEND ORDER"),
        .description = COMPOUND_STRING(
            "Raises DEFENSE and SP. DEF with a living shield."),
        .effect = EFFECT_COSMIC_POWER,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_DEFEND_ORDER,
        .contestComboMoves = {COMBO_STARTER_ATTACK_ORDER, COMBO_STARTER_HEAL_ORDER},
        .battleAnimScript = gBattleAnimMove_DefendOrder,
    },

    [MOVE_HEAL_ORDER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("HEAL ORDER"),
        .description = COMPOUND_STRING(
            "The user's underlings show up to heal half its max HP."),
        .effect = EFFECT_RESTORE_HP,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_HEAL_ORDER,
        .contestComboMoves = {COMBO_STARTER_ATTACK_ORDER, COMBO_STARTER_DEFEND_ORDER},
        .battleAnimScript = gBattleAnimMove_HealOrder,
    },

    [MOVE_HEAD_SMASH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("HEAD SMASH"),
        .description = COMPOUND_STRING(
            "A life-risking headbutt that seriously hurts the user."),
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_ROCK,
        .accuracy = 80,
        .recoil = 50,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HeadSmash,
    },

    [MOVE_DOUBLE_HIT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DOUBLE HIT"),
        .description = COMPOUND_STRING(
            "Slams the foe with a tail etc. Strikes twice."),
        .effect = EFFECT_HIT,
        .power = 35,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .strikeCount = 2,
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DoubleHit,
    },

    [MOVE_ROAR_OF_TIME] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ROAR OF TIME"),
        .description = COMPOUND_STRING(
            "Powerful, but leaves the user immobile the next turn."),
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_DRAGON,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RoarOfTime,
    },

    [MOVE_SPACIAL_REND] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SPACIAL REND"),
        .description = COMPOUND_STRING(
            "Tears the foe, and space. High critical-hit ratio."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_DRAGON,
        .accuracy = 95,
        .criticalHitStage = 1,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SpacialRend,
    },

    [MOVE_LUNAR_DANCE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("LUNAR DANCE"),
        .description = sHealingWishDescription,
        .effect = EFFECT_HEALING_WISH,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .snatchAffected = B_UPDATED_MOVE_FLAGS >= GEN_5,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .healingMove = TRUE,
        .danceMove = TRUE,
        .contestEffect = CONTEST_EFFECT_GREAT_APPEAL_BUT_NO_MORE_MOVES,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_LunarDance,
    },

    [MOVE_CRUSH_GRIP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("CRUSH GRIP"),
        .description = sWringOutDescription,
        .effect = EFFECT_POWER_BASED_ON_TARGET_HP,
        .power = 120,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_CrushGrip,
    },

    [MOVE_MAGMA_STORM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAGMA STORM"),
        .description = COMPOUND_STRING(
            "Traps the foe in a vortex of fire for "BINDING_TURNS" turns."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 100 : 120,
        .type = TYPE_FIRE,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_5 ? 75 : 70,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
        }),
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_MagmaStorm,
    },

    [MOVE_DARK_VOID] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DARK VOID"),
        .description = COMPOUND_STRING(
            "Drags the foe into total darkness, inducing Sleep."),
        .effect = EFFECT_DARK_VOID,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_7 ? 50 : 80,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .magicCoatAffected = TRUE,
        .sketchBanned = (B_SKETCH_BANS >= GEN_9),
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DarkVoid,
    },

    [MOVE_SEED_FLARE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SEED FLARE"),
        .description = COMPOUND_STRING(
            "Generates a shock wave that sharply reduces SP. DEF."),
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_GRASS,
        .accuracy = 85,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_2,
            .chance = 40,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SeedFlare,
    },

    [MOVE_OMINOUS_WIND] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("OMINOUS WIND"),
        .description = COMPOUND_STRING(
            "A repulsive attack that may raise all stats."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .windMove = B_EXTRAPOLATED_MOVE_FLAGS,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ALL_STATS_UP,
            .self = TRUE,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_OminousWind,
    },

    [MOVE_SHADOW_FORCE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SHADOW FORCE"),
        .description = sShadowForceDescription,
        .effect = EFFECT_SEMI_INVULNERABLE,
        .power = 120,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresProtect = TRUE,
        .minimizeDoubleDamage = B_UPDATED_MOVE_FLAGS == GEN_6,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        .argument.twoTurnAttack = { .stringId = STRINGID_VANISHEDINSTANTLY, .status = COMPRESS_BITS(STATUS3_PHANTOM_FORCE) },
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FEINT,
        }),
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ShadowForce,
    },

    [MOVE_HONE_CLAWS] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("HONE CLAWS"),
        .description = COMPOUND_STRING(
            "Sharpens its claws to raise ATTACK and Accuracy."),
        .effect = EFFECT_ATTACK_ACCURACY_UP,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HoneClaws,
    },

    [MOVE_WIDE_GUARD] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("WIDE GUARD"),
        .description = COMPOUND_STRING(
            "The user and its allies are protected from wide-ranging attacks for one turn."),
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_ROCK,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 3,
        .category = DAMAGE_CATEGORY_STATUS,
        .argument = { .protect.side = TRUE, },
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        // .metronomeBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_WideGuard,
    },

    [MOVE_GUARD_SPLIT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("GUARD SPLIT"),
        .description = COMPOUND_STRING(
            "Averages changes to DEFENSE and SP. DEF with the foe."),
        .effect = EFFECT_GUARD_SPLIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_GuardSplit,
    },

    [MOVE_POWER_SPLIT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("POWER SPLIT"),
        .description = COMPOUND_STRING(
            "Averages changes to ATTACK and SP. ATK with the foe."),
        .effect = EFFECT_POWER_SPLIT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PowerSplit,
    },

    [MOVE_WONDER_ROOM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("WONDER ROOM"),
        .description = COMPOUND_STRING(
            "DEFENSE and SP. DEF stats are swapped for 5 turns."),
        .effect = EFFECT_WONDER_ROOM,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = B_UPDATED_MOVE_DATA >= GEN_6 ? 0 : -7,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .ignoresProtect = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_WonderRoom,
    },

    [MOVE_PSYSHOCK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("PSYSHOCK"),
        .description = sPsyshockDescription,
        .effect = EFFECT_PSYSHOCK,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Psyshock,
    },

    [MOVE_VENOSHOCK] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("VENOSHOCK"),
        .description = COMPOUND_STRING(
            "Drenches the foe in a special poisonous liquid. Its power is doubled if the foe is poisoned."),
        .effect = EFFECT_DOUBLE_POWER_ON_ARG_STATUS,
        .power = 65,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .argument = { .status = STATUS1_PSN_ANY },
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_TOXIC},
        .battleAnimScript = gBattleAnimMove_Venoshock,
    },

    [MOVE_AUTOTOMIZE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("AUTOTOMIZE"),
        .description = COMPOUND_STRING(
            "Sheds additional weight to sharply boost SPEED."),
        .effect = EFFECT_AUTOTOMIZE,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Autotomize,
    },

    [MOVE_RAGE_POWDER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("RAGE POWDER"),
        .description = COMPOUND_STRING(
            "Scatters a cloud of irritating powder to draw attention. Foes aim only at the user."),
        .effect = EFFECT_FOLLOW_ME,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = B_UPDATED_MOVE_DATA >= GEN_6 ? 2 : 3,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .powderMove = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RagePowder,
    },

    [MOVE_TELEKINESIS] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TELEKINESIS"),
        .description = COMPOUND_STRING(
            "Makes the foe float. It is easier to hit for 3 turns."),
        .effect = EFFECT_TELEKINESIS,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .magicCoatAffected = TRUE,
        .gravityBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Telekinesis,
    },

    [MOVE_MAGIC_ROOM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAGIC ROOM"),
        .description = COMPOUND_STRING(
            "Hold items lose their effects for 5 turns."),
        .effect = EFFECT_MAGIC_ROOM,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = B_UPDATED_MOVE_DATA >= GEN_6 ? 0 : -7,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .ignoresProtect = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MagicRoom,
    },

    [MOVE_SMACK_DOWN] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SMACK DOWN"),
        .description = COMPOUND_STRING(
            "Throws a rock to knock the foe down to the ground."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .damagesAirborne = TRUE,
        .skyBattleBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SMACK_DOWN,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SmackDown,
    },

    [MOVE_STORM_THROW] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("STORM THROW"),
        .description = sStormThrowDescription,
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 60 : 40,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .alwaysCriticalHit = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_StormThrow,
    },

    [MOVE_FLAME_BURST] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FLAME BURST"),
        .description = COMPOUND_STRING(
            "A bursting flame that does damage to all foes."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLAME_BURST,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FlameBurst,
    },

    [MOVE_SLUDGE_WAVE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SLUDGE WAVE"),
        .description = COMPOUND_STRING(
            "Swamps the foe with a wave of sludge. May also poison."),
        .effect = EFFECT_HIT,
        .power = 95,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SludgeWave,
    },

    [MOVE_QUIVER_DANCE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("QUIVER DANCE"),
        .description = COMPOUND_STRING(
            "Dances to raise SP. ATK SP. DEF and SPEED."),
        .effect = EFFECT_QUIVER_DANCE,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .danceMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_QuiverDance,
    },

    [MOVE_HEAVY_SLAM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("HEAVY SLAM"),
        .description = COMPOUND_STRING(
            "Slams into the foe with its heavy body. Deals more damage the more the user outweighs the foe."),
        .effect = EFFECT_HEAT_CRASH,
        .power = 1,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .minimizeDoubleDamage = B_UPDATED_MOVE_FLAGS >= GEN_7,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HeavySlam,
    },

    [MOVE_SYNCHRONOISE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SYNCHRONOISE"),
        .description = COMPOUND_STRING(
            "An odd shock wave that only damages same-type foes."),
        .effect = EFFECT_SYNCHRONOISE,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 120 : 70,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 10 : 15,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Synchronoise,
    },

    [MOVE_ELECTRO_BALL] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ELECTRO BALL"),
        .description = COMPOUND_STRING(
            "Hurls an orb that does more damage to slower foes."),
        .effect = EFFECT_ELECTRO_BALL,
        .power = 1,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ballisticMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ElectroBall,
    },

    [MOVE_SOAK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SOAK"),
        .description = COMPOUND_STRING(
            "Sprays water at the foe making it Water-type."),
        .effect = EFFECT_SOAK,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Soak,
    },

    [MOVE_FLAME_CHARGE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FLAME CHARGE"),
        .description = COMPOUND_STRING(
            "Attacks in a cloak of flames. Raises SPEED."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FlameCharge,
    },

    [MOVE_COIL] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("COIL"),
        .description = COMPOUND_STRING(
            "Coils up and concentrates to raises its ATTACK and DEFENSE as well as its accuracy."),
        .effect = EFFECT_COIL,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Coil,
    },

    [MOVE_LOW_SWEEP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("LOW SWEEP"),
        .description = COMPOUND_STRING(
            "Attacks the foe's legs lowering its SPEED."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 65 : 60,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_LowSweep,
    },

    [MOVE_ACID_SPRAY] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ACID SPRAY"),
        .description = COMPOUND_STRING(
            "Sprays a hide-melting acid. Sharply reduces SP. DEF."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ballisticMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_2,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_AcidSpray,
    },

    [MOVE_FOUL_PLAY] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FOUL PLAY"),
        .description = COMPOUND_STRING(
            "The higher the foe's ATTACK the more damage caused."),
        .effect = EFFECT_FOUL_PLAY,
        .power = 95,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FoulPlay,
    },

    [MOVE_SIMPLE_BEAM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SIMPLE BEAM"),
        .description = COMPOUND_STRING(
            "A beam that changes the foe's ability to Simple."),
        .effect = EFFECT_SIMPLE_BEAM,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SimpleBeam,
    },

    [MOVE_ENTRAINMENT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ENTRAINMENT"),
        .description = COMPOUND_STRING(
            "Dances with an odd rhythm that compels the foe to copy it and the user's ability."),
        .effect = EFFECT_ENTRAINMENT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Entrainment,
    },

    [MOVE_AFTER_YOU] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("AFTER YOU"),
        .description = COMPOUND_STRING(
            "Helps the target and makes it use its move right after the user."),
        .effect = EFFECT_AFTER_YOU,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_LATER,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_AfterYou,
    },

    [MOVE_ROUND] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ROUND"),
        .description = COMPOUND_STRING(
            "A song that inflicts damage. Others can join in too."),
        .effect = EFFECT_ROUND,
        .power = 60,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .soundMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ROUND,
        }),
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Round,
    },

    [MOVE_ECHOED_VOICE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ECHOED VOICE"),
        .description = COMPOUND_STRING(
            "Attacks with an echoing voice. If this move is used every turn, its power increases."),
        .effect = EFFECT_ECHOED_VOICE,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .soundMove = TRUE,
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_EchoedVoice,
    },

    [MOVE_CHIP_AWAY] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("CHIP AWAY"),
        .description = sChipAwayDescription,
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresTargetDefenseEvasionStages = TRUE,
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ChipAway,
    },

    [MOVE_CLEAR_SMOG] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("CLEAR SMOG"),
        .description = COMPOUND_STRING(
            "Attacks with white haze that eliminates all stat changes."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_POISON,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CLEAR_SMOG,
        }),
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ClearSmog,
    },

    [MOVE_STORED_POWER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("STORED POWER"),
        .description = COMPOUND_STRING(
            "The higher the user's stats the more damage caused."),
        .effect = EFFECT_STORED_POWER,
        .power = 20,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_StoredPower,
    },

    [MOVE_QUICK_GUARD] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("QUICK GUARD"),
        .description = COMPOUND_STRING(
            "Evades priority attacks for one turn."),
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 3,
        .category = DAMAGE_CATEGORY_STATUS,
        .argument = { .protect.side = TRUE, },
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.metronomeBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_QuickGuard,
    },

    [MOVE_ALLY_SWITCH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ALLY SWITCH"),
        .description = COMPOUND_STRING(
            "Teleports using a strange power and switches places with its ally."),
        .effect = EFFECT_ALLY_SWITCH,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = B_UPDATED_MOVE_DATA >= GEN_7 ? 2 : 1,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_2 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_AllySwitch,
    },

    [MOVE_SCALD] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SCALD"),
        .description = COMPOUND_STRING(
            "Shoots boiling water at the foe. May inflict a burn."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .thawsUser = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_SCALD,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Scald,
    },

    [MOVE_SHELL_SMASH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SHELL SMASH"),
        .description = COMPOUND_STRING(
            "Raises offensive stats, but lowers defensive stats."),
        .effect = EFFECT_SHELL_SMASH,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ShellSmash,
    },

    [MOVE_HEAL_PULSE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("HEAL PULSE"),
        .description = COMPOUND_STRING(
            "Emits a healing pulse that restores the target's HP by up to half of its max HP."),
        .effect = EFFECT_HEAL_PULSE,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .magicCoatAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        .healingMove = TRUE,
        .pulseMove = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HealPulse,
    },

    [MOVE_HEX] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("HEX"),
        .description = COMPOUND_STRING(
            "Casts a malicious spell that does double damage to a target affected by status conditions."),
        .effect = EFFECT_DOUBLE_POWER_ON_ARG_STATUS,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 65 : 50,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .zMove = { .powerOverride = 160 },
        .argument = { .status = STATUS1_ANY },
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_TOXIC},
        .battleAnimScript = gBattleAnimMove_Hex,
    },

    [MOVE_SKY_DROP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SKY DROP"),
        .description = COMPOUND_STRING(
            "Takes the foe into the sky then drops it the next turn."),
        .effect = EFFECT_SKY_DROP,
        .power = 60,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .gravityBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        .argument.twoTurnAttack = { .stringId = STRINGID_PKMNTOOKTARGETHIGH, .status = COMPRESS_BITS(STATUS3_ON_AIR) },
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SkyDrop,
    },

    [MOVE_SHIFT_GEAR] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SHIFT GEAR"),
        .description = COMPOUND_STRING(
            "Rotates its gears to raise ATTACK and SPEED."),
        .effect = EFFECT_SHIFT_GEAR,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ShiftGear,
    },

    [MOVE_CIRCLE_THROW] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("CIRCLE THROW"),
        .description = sCircleThrowDescription,
        .effect = EFFECT_HIT_SWITCH_TARGET,
        .power = 60,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = -6,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_CircleThrow,
    },

    [MOVE_INCINERATE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("INCINERATE"),
        .description = COMPOUND_STRING(
            "Burns up Berries and Gems preventing their use."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 60 : 30,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_INCINERATE,
        }),
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Incinerate,
    },

    [MOVE_QUASH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("QUASH"),
        .description = COMPOUND_STRING(
            "Suppresses the foe, making it move last."),
        .effect = EFFECT_QUASH,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        //.metronomeBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_LATER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Quash,
    },

    [MOVE_ACROBATICS] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ACROBATICS"),
        .description = COMPOUND_STRING(
            "Does double damage if the user has no item."),
        .effect = EFFECT_ACROBATICS,
        .power = 55,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Acrobatics,
    },

    [MOVE_REFLECT_TYPE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("REFLECT TYPE"),
        .description = COMPOUND_STRING(
            "Reflects the target's type, copying it. "),
        .effect = EFFECT_REFLECT_TYPE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ReflectType,
    },

    [MOVE_RETALIATE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("RETALIATE"),
        .description = COMPOUND_STRING(
            "An attack that does more damage if an ally fainted."),
        .effect = EFFECT_RETALIATE,
        .power = 70,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_LATER,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Retaliate,
    },

    [MOVE_FINAL_GAMBIT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FINAL GAMBIT"),
        .description = COMPOUND_STRING(
            "The user faints to damage the foe equal to its HP."),
        .effect = EFFECT_FINAL_GAMBIT,
        .power = 1,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .mirrorMoveBanned = TRUE,
        .parentalBondBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_GREAT_APPEAL_BUT_NO_MORE_MOVES,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FinalGambit,
    },

    [MOVE_BESTOW] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BESTOW"),
        .description = COMPOUND_STRING(
            "The user gives its held item to the foe."),
        .effect = EFFECT_BESTOW,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_2 },
        .ignoresProtect = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .ignoresSubstitute = TRUE,
        //.metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Bestow,
    },

    [MOVE_INFERNO] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("INFERNO"),
        .description = COMPOUND_STRING(
            "Powerful and sure to inflict a burn, but inaccurate."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIRE,
        .accuracy = 50,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Inferno,
    },

    [MOVE_WATER_PLEDGE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("WATER PLEDGE"),
        .description = COMPOUND_STRING(
            "Attacks with a column of water. May make a rainbow."),
        .effect = EFFECT_PLEDGE,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 80 : 50,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_WaterPledge,
    },

    [MOVE_FIRE_PLEDGE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FIRE PLEDGE"),
        .description = COMPOUND_STRING(
            "Attacks with a column of fire. May burn the grass."),
        .effect = EFFECT_PLEDGE,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 80 : 50,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FirePledge,
    },

    [MOVE_GRASS_PLEDGE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("GRASS PLEDGE"),
        .description = COMPOUND_STRING(
            "Attacks with a column of grass. May create a swamp."),
        .effect = EFFECT_PLEDGE,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 80 : 50,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_GrassPledge,
    },

    [MOVE_VOLT_SWITCH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("VOLT SWITCH"),
        .description = sUTurnDescription,
        .effect = EFFECT_HIT_ESCAPE,
        .power = 70,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_VoltSwitch,
    },

    [MOVE_STRUGGLE_BUG] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("STRUGGLE BUG"),
        .description = COMPOUND_STRING(
            "Resisting, the user attacks the foe. Lowers SP. ATK."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 50 : 30,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_1,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_StruggleBug,
    },

    [MOVE_BULLDOZE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BULLDOZE"),
        .description = COMPOUND_STRING(
            "Stomps down on the ground. Lowers SPEED."),
        .effect = EFFECT_EARTHQUAKE,
        .power = 60,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .skyBattleBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Bulldoze,
    },

    [MOVE_FROST_BREATH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FROST BREATH"),
        .description = sStormThrowDescription,
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 60 : 40,
        .type = TYPE_ICE,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .alwaysCriticalHit = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FrostBreath,
    },

    [MOVE_DRAGON_TAIL] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("DRAGON TAIL"),
        .description = COMPOUND_STRING(
            "Knocks away the target and forces it to switch out. In the wild, ends battle."),
        .effect = EFFECT_HIT_SWITCH_TARGET,
        .power = 60,
        .type = TYPE_DRAGON,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = -6,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = COMBO_STARTER_DRAGON_TAIL,
        .contestComboMoves = {COMBO_STARTER_DRAGON_BREATH, COMBO_STARTER_DRAGON_DANCE, COMBO_STARTER_DRAGON_RAGE, COMBO_STARTER_TYRANT_CRUSH},
        .battleAnimScript = gBattleAnimMove_DragonTail,
    },

    [MOVE_WORK_UP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("WORK UP"),
        .description = COMPOUND_STRING(
            "The user is roused. Ups ATTACK and SP. ATK."),
        .effect = EFFECT_ATTACK_SPATK_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_WorkUp,
    },

    [MOVE_ELECTROWEB] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ELECTROWEB"),
        .description = COMPOUND_STRING(
            "Snares the foe with an electric net. Lowers SPEED."),
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_ELECTRIC,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Electroweb,
    },

    [MOVE_WILD_CHARGE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("WILD CHARGE"),
        .description = COMPOUND_STRING(
            "An electrical tackle that also hurts the user."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .recoil = 25,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_WildCharge,
    },

    [MOVE_DRILL_RUN] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DRILL RUN"),
        .description = COMPOUND_STRING(
            "Spins its body like a drill. High critical-hit ratio."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_GROUND,
        .accuracy = 95,
        .criticalHitStage = 1,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DrillRun,
    },

    [MOVE_DUAL_CHOP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DUAL CHOP"),
        .description = COMPOUND_STRING(
            "Attacks with brutal hits that strike twice."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_DRAGON,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .strikeCount = 2,
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DualChop,
    },

    [MOVE_HEART_STAMP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("HEART STAMP"),
        .description = COMPOUND_STRING(
            "A sudden blow after a cute act. May cause flinching."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HeartStamp,
    },

    [MOVE_HORN_LEECH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("HORN LEECH"),
        .description = sMegaDrainDescription,
        .effect = EFFECT_ABSORB,
        .power = 75,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .argument = { .absorbPercentage = 50 },
        .makesContact = TRUE,
        .healingMove = B_HEAL_BLOCKING >= GEN_6,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HornLeech,
    },

    [MOVE_SACRED_SWORD] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SACRED SWORD"),
        .description = sChipAwayDescription,
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_6 ? 15 : 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresTargetDefenseEvasionStages = TRUE,
        .slicingMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SacredSword,
    },

    [MOVE_RAZOR_SHELL] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("RAZOR SHELL"),
        .description = COMPOUND_STRING(
            "Cuts the foe with sharp shells. May lower the foe's DEFENSE. "),
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_WATER,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 50,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RazorShell,
    },

    [MOVE_HEAT_CRASH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("HEAT CRASH"),
        .description = sHeavySlamDescription,
        .effect = EFFECT_HEAT_CRASH,
        .power = 1,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .minimizeDoubleDamage = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HeatCrash,
    },

    [MOVE_LEAF_TORNADO] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("LEAF TORNADO"),
        .description = COMPOUND_STRING(
            "Circles the foe with leaves to damage and cut accuracy."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_GRASS,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ACC_MINUS_1,
            .chance = 50,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_LeafTornado,
    },

    [MOVE_STEAMROLLER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("STEAMROLLER"),
        .description = COMPOUND_STRING(
            "Crushes the foe with its body. May cause flinching."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .minimizeDoubleDamage = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Steamroller,
    },

    [MOVE_COTTON_GUARD] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("COTTON GUARD"),
        .description = COMPOUND_STRING(
            "Wraps its body in cotton. Drastically raises DEFENSE."),
        .effect = EFFECT_DEFENSE_UP_3,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_CottonGuard,
    },

    [MOVE_NIGHT_DAZE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("NIGHT DAZE"),
        .description = COMPOUND_STRING(
            "Looses a pitch-black shock wave. May lower accuracy."),
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_DARK,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ACC_MINUS_1,
            .chance = 40,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_NightDaze,
    },

    [MOVE_PSYSTRIKE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("PSYSTRIKE"),
        .description = sPsyshockDescription,
        .effect = EFFECT_PSYSHOCK,
        .power = 100,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Psystrike,
    },

    [MOVE_TAIL_SLAP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TAIL SLAP"),
        .description = COMPOUND_STRING(
            "Strikes the foe with its tail 2 to 5 times."),
        .effect = EFFECT_MULTI_HIT,
        .power = 25,
        .type = TYPE_NORMAL,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_TailSlap,
    },

    [MOVE_HURRICANE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("HURRICANE"),
        .description = COMPOUND_STRING(
            "Traps the foe in a fierce wind. May cause confusion."),
        .effect = EFFECT_THUNDER,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 110 : 120,
        .type = TYPE_FLYING,
        .accuracy = 70,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .windMove = TRUE,
        .damagesAirborne = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Hurricane,
    },

    [MOVE_HEAD_CHARGE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("HEAD CHARGE"),
        .description = COMPOUND_STRING(
            "A charge using guard hair. It hurts the user a little."),
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .recoil = 25,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HeadCharge,
    },

    [MOVE_GEAR_GRIND] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("GEAR GRIND"),
        .description = COMPOUND_STRING(
            "Throws two steel gears that strike twice."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_STEEL,
        .accuracy = 85,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .zMove = { .powerOverride = 180 },
        .makesContact = TRUE,
        .strikeCount = 2,
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_GearGrind,
    },

    [MOVE_SEARING_SHOT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SEARING SHOT"),
        .description = sLavaPlumeDescription,
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ballisticMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SearingShot,
    },

    [MOVE_TECHNO_BLAST] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TECHNO BLAST"),
        .description = COMPOUND_STRING(
            "The type varies with the kind of Drive held."),
        .effect = EFFECT_CHANGE_TYPE_ON_ITEM,
        .power = B_UPDATED_MOVE_DATA >= GEN_6 ? 120 : 85,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .argument = { .holdEffect = HOLD_EFFECT_DRIVE },
        //.metronomeBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_EXCITE_AUDIENCE_IN_ANY_CONTEST,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_TechnoBlast,
    },

    [MOVE_RELIC_SONG] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("RELIC SONG"),
        .description = COMPOUND_STRING(
            "Attacks with an ancient song. May induce sleep."),
        .effect = EFFECT_RELIC_SONG,
        .power = 75,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .argument = { .status = STATUS1_SLEEP },
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .soundMove = TRUE,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SLEEP,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RelicSong,
    },

    [MOVE_SECRET_SWORD] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SECRET SWORD"),
        .description = COMPOUND_STRING(
            "Cuts with a long horn that does physical damage."),
        .effect = EFFECT_PSYSHOCK,
        .power = 85,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .slicingMove = TRUE,
        //.metronomeBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SecretSword,
    },

    [MOVE_GLACIATE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("GLACIATE"),
        .description = COMPOUND_STRING(
            "Blows very cold air at the foe. It lowers their SPEED."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_ICE,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Glaciate,
    },

    [MOVE_BOLT_STRIKE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BOLT STRIKE"),
        .description = COMPOUND_STRING(
            "Strikes with a great amount of lightning. May paralyze."),
        .effect = EFFECT_HIT,
        .power = 130,
        .type = TYPE_ELECTRIC,
        .accuracy = 85,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 20,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_BoltStrike,
    },

    [MOVE_BLUE_FLARE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BLUE FLARE"),
        .description = COMPOUND_STRING(
            "Engulfs the foe in a blue flame. May inflict a burn."),
        .effect = EFFECT_HIT,
        .power = 130,
        .type = TYPE_FIRE,
        .accuracy = 85,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 20,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_BlueFlare,
    },

    [MOVE_FIERY_DANCE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FIERY DANCE"),
        .description = COMPOUND_STRING(
            "Dances cloaked in flames. May raise SP. ATK."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .danceMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_PLUS_1,
            .self = TRUE,
            .chance = 50,
        }),
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FieryDance,
    },

    [MOVE_FREEZE_SHOCK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FREEZE SHOCK"),
        .description = COMPOUND_STRING(
            "A powerful 2-turn move that may paralyze the foe."),
        .effect = EFFECT_TWO_TURNS_ATTACK,
        .power = 140,
        .type = TYPE_ICE,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        //.metronomeBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .argument.twoTurnAttack = { .stringId = STRINGID_CLOAKEDINAFREEZINGLIGHT },
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FreezeShock,
    },

    [MOVE_ICE_BURN] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ICE BURN"),
        .description = COMPOUND_STRING(
            "A powerful 2-turn move that may inflict a burn."),
        .effect = EFFECT_TWO_TURNS_ATTACK,
        .power = 140,
        .type = TYPE_ICE,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        //.metronomeBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .argument.twoTurnAttack = { .stringId = STRINGID_CLOAKEDINAFREEZINGLIGHT },
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_IceBurn,
    },

    [MOVE_SNARL] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SNARL"),
        .description = COMPOUND_STRING(
            "Yells and rants at the foes, which lowers their SP. ATK. "),
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_DARK,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .soundMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_1,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Snarl,
    },

    [MOVE_ICICLE_CRASH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("ICICLE CRASH"),
        .description = COMPOUND_STRING(
            "Drops large icicles onto the foe. May make the target flinch. "),
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_ICE,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_IcicleCrash,
    },

    [MOVE_V_CREATE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("V-CREATE"),
        .description = COMPOUND_STRING(
            "Very powerful, but lowers DEFENSE, SP. DEF and SPEED."),
        .effect = EFFECT_HIT,
        .power = 180,
        .type = TYPE_FIRE,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .zMove = { .powerOverride = 220 },
        .makesContact = TRUE,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_V_CREATE,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_VCreate,
    },

    [MOVE_FUSION_FLARE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FUSION FLARE"),
        .description = COMPOUND_STRING(
            "Summons a fireball. Works well with a thunderbolt."),
        .effect = EFFECT_FUSION_COMBO,
        .power = 100,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .thawsUser = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FusionFlare,
    },

    [MOVE_FUSION_BOLT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FUSION BOLT"),
        .description = COMPOUND_STRING(
            "Summons a thunderbolt. Works well with a fireball."),
        .effect = EFFECT_FUSION_COMBO,
        .power = 100,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FusionBolt,
    },

    [MOVE_FLYING_PRESS] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FLYING PRESS"),
        .description = COMPOUND_STRING(
            "This attack does Fighting and Flying-type damage."),
        .effect = EFFECT_TWO_TYPED_MOVE,
        .power = B_UPDATED_MOVE_DATA >= GEN_7 ? 100 : 80,
        .type = TYPE_FIGHTING,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .zMove = { .powerOverride = 170 },
        .argument = { .type = TYPE_FLYING },
        .makesContact = TRUE,
        .minimizeDoubleDamage = TRUE,
        .gravityBanned = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FlyingPress,
    },

    [MOVE_MAT_BLOCK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAT BLOCK"),
        .description = COMPOUND_STRING(
            "Evades damaging moves for one turn."),
        .effect = EFFECT_MAT_BLOCK,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .argument = { .protect.side = TRUE },
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MatBlock,
    },

    [MOVE_BELCH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BELCH"),
        .description = COMPOUND_STRING(
            "Lets out a loud belch. Must eat a Berry to use it."),
        .effect = EFFECT_BELCH,
        .power = 120,
        .type = TYPE_POISON,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .mirrorMoveBanned = TRUE,
        .meFirstBanned = TRUE,
        //.metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Belch,
    },

    [MOVE_ROTOTILLER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ROTOTILLER"),
        .description = COMPOUND_STRING(
            "Ups the ATTACK and SP. ATK of Grass-type Pokémon."),
        .effect = EFFECT_ROTOTILLER,
        .power = 0,
        .type = TYPE_GROUND,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Rototiller,
    },

    [MOVE_STICKY_WEB] =
    {
        .name = COMPOUND_STRING("STICKY WEB"),
        .description = COMPOUND_STRING(
            "Weaves a sticky net that slows foes switching in."),
        .effect = EFFECT_STICKY_WEB,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_OPPONENTS_FIELD,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .magicCoatAffected = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_StickyWeb,
    },

    [MOVE_FELL_STINGER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FELL STINGER"),
        .description = COMPOUND_STRING(
            "Attacks with a stinger to land a finishing blow. Drastically raises user's ATTACK if it does."),
        .effect = EFFECT_FELL_STINGER,
        .power = B_UPDATED_MOVE_DATA >= GEN_7 ? 50 : 30,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 25,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FellStinger,
    },

    [MOVE_PHANTOM_FORCE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("PHANTOM FORCE"),
        .description = COMPOUND_STRING(
            "Vanishes, then strikes the foe on the next turn. Hits even if the foe protects itself."),
        .effect = EFFECT_SEMI_INVULNERABLE,
        .power = 90,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .makesContact = TRUE,
        .minimizeDoubleDamage = B_UPDATED_MOVE_FLAGS == GEN_6,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        .argument.twoTurnAttack = { .stringId = STRINGID_VANISHEDINSTANTLY, .status = COMPRESS_BITS(STATUS3_PHANTOM_FORCE) },
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FEINT,
        }),
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PhantomForce,
    },

    [MOVE_TRICK_OR_TREAT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TRICK-OR-TREAT"),
        .description = COMPOUND_STRING(
            "Goes trick-or-treating making the foe Ghost-type."),
        .effect = EFFECT_THIRD_TYPE,
        .power = 0,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .argument = { .type = TYPE_GHOST },
        .zMove = { .effect = Z_EFFECT_ALL_STATS_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_TrickOrTreat,
    },

    [MOVE_NOBLE_ROAR] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("NOBLE ROAR"),
        .description = COMPOUND_STRING(
            "Intimidates the foe, to cut ATTACK and SP. ATK."),
        .effect = EFFECT_NOBLE_ROAR,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .magicCoatAffected = TRUE,
        .soundMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_NobleRoar,
    },

    [MOVE_ION_DELUGE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ION DELUGE"),
        .description = COMPOUND_STRING(
            "Electrifies Normal-type moves with charged atoms."),
        .effect = EFFECT_ION_DELUGE,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 25,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 1,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_IonDeluge,
    },

    [MOVE_PARABOLIC_CHARGE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("PARABOLIC CHARGE"),
        .description = COMPOUND_STRING(
            "Damages adjacent Pokémon and heals up by half of it."),
        .effect = EFFECT_ABSORB,
        .power = B_UPDATED_MOVE_DATA >= GEN_7 ? 65 : 50,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .argument = { .absorbPercentage = 50 },
        .healingMove = B_HEAL_BLOCKING >= GEN_6,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ParabolicCharge,
    },

    [MOVE_FORESTS_CURSE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FOREST's Curse"),
        .description = COMPOUND_STRING(
            "Puts a curse on the foe making the foe Grass-type."),
        .effect = EFFECT_THIRD_TYPE,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .argument = { .type = TYPE_GRASS },
        .zMove = { .effect = Z_EFFECT_ALL_STATS_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ForestsCurse,
    },

    [MOVE_PETAL_BLIZZARD] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("PETAL BLIZZARD"),
        .description = COMPOUND_STRING(
            "Stirs up a violent storm of petals to attack."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .windMove = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PetalBlizzard,
    },

    [MOVE_FREEZE_DRY] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FREEZE-DRY"),
        .description = COMPOUND_STRING(
            "Super effective on Water-\n"
        #if B_USE_FROSTBITE == TRUE
            "types. May cause frostbite."),
        #else
            "types. May cause freezing."),
        #endif
        .effect = EFFECT_SUPER_EFFECTIVE_ON_ARG,
        .power = 70,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .argument = { .type = TYPE_WATER },
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FREEZE_OR_FROSTBITE,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FreezeDry,
    },

    [MOVE_DISARMING_VOICE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DISARMING VOICE"),
        .description = COMPOUND_STRING(
            "Lets out a charming cry that cannot be evaded."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .soundMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DisarmingVoice,
    },

    [MOVE_PARTING_SHOT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("PARTING SHOT"),
        .description = COMPOUND_STRING(
            "Lowers the foe's ATTACK and SP. ATK, then switches out."),
        .effect = EFFECT_PARTING_SHOT,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESTORE_REPLACEMENT_HP },
        .magicCoatAffected = TRUE,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .soundMove = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PartingShot,
    },

    [MOVE_TOPSY_TURVY] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TOPSY-TURVY"),
        .description = COMPOUND_STRING(
            "Swaps all stat changes that affect the target."),
        .effect = EFFECT_TOPSY_TURVY,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_7 ? 0 : 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_TopsyTurvy,
    },

    [MOVE_DRAINING_KISS] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("DRAINING KISS"),
        .description = COMPOUND_STRING(
            "Steals the foe's HP with a kiss. Restores HP by 3/4 damage dealt. "),
        .effect = EFFECT_ABSORB,
        .power = 50,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .argument = { .absorbPercentage = 75 },
        .makesContact = TRUE,
        .healingMove = B_HEAL_BLOCKING >= GEN_6,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DrainingKiss,
    },

    [MOVE_CRAFTY_SHIELD] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("CRAFTY SHIELD"),
        .description = COMPOUND_STRING(
            "Evades status moves for one turn."),
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 3,
        .category = DAMAGE_CATEGORY_STATUS,
        .argument = { .protect.side = TRUE, },
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.metronomeBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE_ONCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_CraftyShield,
    },

    [MOVE_FLOWER_SHIELD] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FLOWER SHIELD"),
        .description = COMPOUND_STRING(
            "Raises the DEFENSE of Grass-type Pokémon."),
        .effect = EFFECT_FLOWER_SHIELD,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER, // The targeting of Flower Shield is handled through a script
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FlowerShield,
    },

    [MOVE_GRASSY_TERRAIN] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("GRASSY TERRAIN"),
        .description = COMPOUND_STRING(
            "The ground turns to grass for 5 turns. Restores HP."),
        .effect = EFFECT_GRASSY_TERRAIN,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_GRASSY_TERRAIN,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_GrassyTerrain,
    },

    [MOVE_MISTY_TERRAIN] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MISTY TERRAIN"),
        .description = COMPOUND_STRING(
            "Covers the ground with mist for 5 turns. Blocks status."),
        .effect = EFFECT_MISTY_TERRAIN,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = COMBO_STARTER_MISTY_TERRAIN,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MistyTerrain,
    },

    [MOVE_ELECTRIFY] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ELECTRIFY"),
        .description = COMPOUND_STRING(
            "Electrifies the foe, making its next move Electric-type."),
        .effect = EFFECT_ELECTRIFY,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Electrify,
    },

    [MOVE_PLAY_ROUGH] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("PLAY ROUGH"),
        .description = COMPOUND_STRING(
            "Plays rough with the foe to attack. May lower the foe's ATTACK."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_FAIRY,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_MINUS_1,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PlayRough,
    },

    [MOVE_FAIRY_WIND] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FAIRY WIND"),
        .description = COMPOUND_STRING(
            "Stirs up a fairy wind to strike the foe."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .windMove = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FairyWind,
    },

    [MOVE_MOONBLAST] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("MOONBLAST"),
        .description = COMPOUND_STRING(
            "Borrows the power of the moon to attack. May lower the target's SP. ATK."),
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_1,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Moonblast,
    },

    [MOVE_BOOMBURST] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BOOMBURST"),
        .description = COMPOUND_STRING(
            "Attacks everything with a destructive sound wave."),
        .effect = EFFECT_HIT,
        .power = 140,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .soundMove = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Boomburst,
    },

    [MOVE_FAIRY_LOCK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FAIRY LOCK"),
        .description = COMPOUND_STRING(
            "Locks down the battlefield preventing escape next turn."),
        .effect = EFFECT_FAIRY_LOCK,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FairyLock,
    },

    [MOVE_KINGS_SHIELD] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("KING's Shield"),
        .description = COMPOUND_STRING(
            "Evades damage, and sharply reduces ATTACK if struck."),
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 4,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_KingsShield,
    },

    [MOVE_PLAY_NICE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("PLAY NICE"),
        .description = COMPOUND_STRING(
            "Befriend the foe, lowering its ATTACK without fail."),
        .effect = EFFECT_ATTACK_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PlayNice,
    },

    [MOVE_CONFIDE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("CONFIDE"),
        .description = COMPOUND_STRING(
            "Shares a secret with the foe, lowering SP. ATK."),
        .effect = EFFECT_SPECIAL_ATTACK_DOWN,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .ignoresProtect = TRUE,
        .magicCoatAffected = TRUE,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .soundMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Confide,
    },

    [MOVE_DIAMOND_STORM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DIAMOND STORM"),
        .description = COMPOUND_STRING(
            "Whips up a storm of diamonds. May up DEFENSE."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_ROCK,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = B_UPDATED_MOVE_DATA >= GEN_7 ? MOVE_EFFECT_DEF_PLUS_2:  MOVE_EFFECT_DEF_PLUS_1,
            .self = TRUE,
            .chance = 50,
        }),
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DiamondStorm,
    },

    [MOVE_STEAM_ERUPTION] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("STEAM ERUPTION"),
        .description = COMPOUND_STRING(
            "Immerses the foe in heated steam. May inflict a burn."),
        .effect = EFFECT_HIT,
        .power = 110,
        .type = TYPE_WATER,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .thawsUser = TRUE,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SCALD},
        .battleAnimScript = gBattleAnimMove_SteamEruption,
    },

    [MOVE_HYPERSPACE_HOLE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("HYPRSPACE HOLE"),
        .description = sHyperspaceHoleDescription,
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FEINT,
        }),
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_HYPERSPACE_HOLE,
        .contestComboMoves = {COMBO_STARTER_HYPERSPACE_FURY},
        .battleAnimScript = gBattleAnimMove_HyperspaceHole,
    },

    [MOVE_WATER_SHURIKEN] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("WATER SHURIKEN"),
        .description = COMPOUND_STRING(
            "Throws 2 to 5 stars that are sure to strike first."),
        .effect = EFFECT_MULTI_HIT,
        .power = 15,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = B_UPDATED_MOVE_DATA >= GEN_7 ? DAMAGE_CATEGORY_SPECIAL : DAMAGE_CATEGORY_PHYSICAL,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_WaterShuriken,
    },

    [MOVE_MYSTICAL_FIRE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MYSTICAL FIRE"),
        .description = COMPOUND_STRING(
            "Breathes a special, hot fire. Lowers SP. ATK."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_7 ? 75 : 65,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_1,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MysticalFire,
    },

    [MOVE_SPIKY_SHIELD] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SPIKY SHIELD"),
        .description = COMPOUND_STRING(
            "Evades attack, and damages the foe if struck."),
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 4,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SpikyShield,
    },

    [MOVE_AROMATIC_MIST] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("AROMATIC MIST"),
        .description = COMPOUND_STRING(
            "Raises the SP. DEF of a partner Pokémon."),
        .effect = EFFECT_AROMATIC_MIST,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_2 },
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_AromaticMist,
    },

    [MOVE_EERIE_IMPULSE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("EERIE IMPULSE"),
        .description = COMPOUND_STRING(
            "Exposes the foe to a pulse that sharply cuts SP. ATK."),
        .effect = EFFECT_SPECIAL_ATTACK_DOWN_2,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_EerieImpulse,
    },

    [MOVE_VENOM_DRENCH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("VENOM DRENCH"),
        .description = COMPOUND_STRING(
            "Lowers the ATTACK, SP. ATK and SPEED of a poisoned foe."),
        .effect = EFFECT_VENOM_DRENCH,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_TOXIC},
        .battleAnimScript = gBattleAnimMove_VenomDrench,
    },

    [MOVE_POWDER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("POWDER"),
        .description = COMPOUND_STRING(
            "Damages the foe if it uses a Fire-type move."),
        .effect = EFFECT_POWDER,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_2 },
        .powderMove = TRUE,
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Powder,
    },

    [MOVE_GEOMANCY] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("GEOMANCY"),
        .description = COMPOUND_STRING(
            "Raises SP. ATK, SP. DEF and SPEED on the 2nd turn."),
        .effect = EFFECT_GEOMANCY,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ALL_STATS_UP_1 },
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .skyBattleBanned = TRUE,
        .argument.twoTurnAttack = { .stringId = STRINGID_PKNMABSORBINGPOWER },
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Geomancy,
    },

    [MOVE_MAGNETIC_FLUX] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAGNETIC FLUX"),
        .description = COMPOUND_STRING(
            "Boosts the defenses of those with Plus or Minus."),
        .effect = EFFECT_MAGNETIC_FLUX,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MagneticFlux,
    },

    [MOVE_HAPPY_HOUR] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("HAPPY HOUR"),
        .description = COMPOUND_STRING(
            "Doubles the amount of Prize Money received."),
        .effect = EFFECT_HAPPY_HOUR,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ALL_STATS_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HappyHour,
    },

    [MOVE_ELECTRIC_TERRAIN] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ELECTRIC TERRAIN"),
        .description = COMPOUND_STRING(
            "Electrifies the ground for 5 turns. Prevents sleep."),
        .effect = EFFECT_ELECTRIC_TERRAIN,
        .power = 0,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = COMBO_STARTER_ELECTRIC_TERRAIN,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ElectricTerrain,
    },

    [MOVE_DAZZLING_GLEAM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DAZZLING GLEAM"),
        .description = COMPOUND_STRING(
            "Damages foes by emitting a bright flash."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DazzlingGleam,
    },

    [MOVE_CELEBRATE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("CELEBRATE"),
        .description = COMPOUND_STRING(
            "Congratulates you on your special day."),
        .effect = EFFECT_CELEBRATE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ALL_STATS_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Celebrate,
    },

    [MOVE_HOLD_HANDS] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("HOLD HANDS"),
        .description = COMPOUND_STRING(
            "The user and ally hold hands making them happy."),
        .effect = EFFECT_HOLD_HANDS,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 40,
        .target = MOVE_TARGET_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ALL_STATS_UP_1 },
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        //.metronomeBanned = TRUE,
        .mimicBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HoldHands,
    },

    [MOVE_BABY_DOLL_EYES] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BABY-DOLL EYES"),
        .description = COMPOUND_STRING(
            "Stares at the foe with baby-doll eyes, lowering the its ATTACK. This move always goes first."),
        .effect = EFFECT_ATTACK_DOWN,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_BabyDollEyes,
    },

    [MOVE_NUZZLE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("NUZZLE"),
        .description = COMPOUND_STRING(
            "Rubs its cheeks against the foe, paralyzing it."),
        .effect = EFFECT_HIT,
        .power = 20,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Nuzzle,
    },

    [MOVE_HOLD_BACK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("HOLD BACK"),
        .description = sFalseSwipeDescription,
        .effect = EFFECT_FALSE_SWIPE,
        .power = 40,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HoldBack,
    },

    [MOVE_INFESTATION] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("INFESTATION"),
        .description = COMPOUND_STRING(
            "Infests and attacks the foe 4-5 turns. The foe can't flee during this time."),
        .effect = EFFECT_HIT,
        .power = 20,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
        }),
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Infestation,
    },

    [MOVE_POWER_UP_PUNCH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("POWER-UP PUNCH"),
        .description = COMPOUND_STRING(
            "A hard punch that raises the user's ATTACK."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PowerUpPunch,
    },

    [MOVE_OBLIVION_WING] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("OBLIVION WING"),
        .description = sDrainingKissDescription,
        .effect = EFFECT_ABSORB,
        .power = 80,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .argument = { .absorbPercentage = 75 },
        .healingMove = B_HEAL_BLOCKING >= GEN_6,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_OblivionWing,
    },

    [MOVE_THOUSAND_ARROWS] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("THOUSAND ARROWS"),
        .description = COMPOUND_STRING(
            "Can hit Flying foes, then knocks them to the ground."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .damagesAirborne = TRUE,
        .ignoreTypeIfFlyingAndUngrounded = TRUE,
        //.metronomeBanned = TRUE,
        .skyBattleBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SMACK_DOWN,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_THOUSAND_ARROWS,
        .contestComboMoves = {COMBO_STARTER_THOUSAND_WAVES},
        .battleAnimScript = gBattleAnimMove_ThousandArrows,
    },

    [MOVE_THOUSAND_WAVES] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("THOUSAND WAVES"),
        .description = COMPOUND_STRING(
            "Those hit by the wave can no longer escape."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        //.metronomeBanned = TRUE,
        .skyBattleBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PREVENT_ESCAPE,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_THOUSAND_WAVES,
        .contestComboMoves = {COMBO_STARTER_THOUSAND_ARROWS},
        .battleAnimScript = gBattleAnimMove_ThousandWaves,
    },

    [MOVE_LANDS_WRATH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("LAND's Wrath"),
        .description = COMPOUND_STRING(
            "Gathers the energy of the land to attack every foe."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_LandsWrath,
    },

    [MOVE_LIGHT_OF_RUIN] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("LIGHT OF RUIN"),
        .description = COMPOUND_STRING(
            "Fires a great beam of light that also hurts the user."),
        .effect = EFFECT_HIT,
        .power = 140,
        .type = TYPE_FAIRY,
        .accuracy = 90,
        .recoil = 50,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .battleAnimScript = gBattleAnimMove_LightOfRuin,
    },

    [MOVE_ORIGIN_PULSE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ORIGIN PULSE"),
        .description = COMPOUND_STRING(
            "Beams of glowing blue light blast both foes."),
        .effect = EFFECT_HIT,
        .power = 110,
        .type = TYPE_WATER,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .pulseMove = TRUE,
        //.metronomeBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_OriginPulse,
    },

    [MOVE_PRECIPICE_BLADES] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("PRECIPICE BLADES"),
        .description = COMPOUND_STRING(
            "Fearsome blades of stone attack both foes."),
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_GROUND,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        //.metronomeBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PrecipiceBlades,
    },

    [MOVE_DRAGON_ASCENT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DRAGON ASCENT"),
        .description = sCloseCombatDescription,
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_SPDEF_DOWN,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DragonAscent,
    },

    [MOVE_HYPERSPACE_FURY] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("HYPERSPACE FURY"),
        .description = sHyperspaceHoleDescription,
        .effect = EFFECT_HYPERSPACE_FURY,
        .power = 100,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        //.metronomeBanned = TRUE,
        .sketchBanned = (B_SKETCH_BANS >= GEN_9),
        .additionalEffects = ADDITIONAL_EFFECTS({
            // Feint move effect handled in script as it goes before animation
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_HYPERSPACE_FURY,
        .contestComboMoves = {COMBO_STARTER_HYPERSPACE_HOLE},
        .battleAnimScript = gBattleAnimMove_HyperspaceFury,
    },

    [MOVE_SHORE_UP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SHORE UP"),
        .description = COMPOUND_STRING(
            "Restores the user's HP. More HP in a sandstorm."),
        .effect = EFFECT_SHORE_UP,
        .power = 0,
        .type = TYPE_GROUND,
        .accuracy = 0,
        .pp = B_UPDATED_MOVE_DATA >= GEN_9 ? 5 : 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .healingMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SANDSTORM},
        .battleAnimScript = gBattleAnimMove_ShoreUp,
    },

    [MOVE_FIRST_IMPRESSION] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FIRST IMPRESSION"),
        .description = COMPOUND_STRING(
            "Hits hard and first. Only works first turn."),
        .effect = EFFECT_FIRST_TURN_ONLY,
        .power = 90,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 2,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .argument = { .moveProperty = MOVE_FIRST_IMPRESSION },
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FirstImpression,
    },

    [MOVE_BANEFUL_BUNKER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BANEFUL BUNKER"),
        .description = COMPOUND_STRING(
            "Protects user and poisons foes on contact."),
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 4,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_BanefulBunker,
    },

    [MOVE_SPIRIT_SHACKLE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SPIRIT SHACKLE"),
        .description = COMPOUND_STRING(
            "After being hit, foes can no longer escape."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PREVENT_ESCAPE,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SpiritShackle,
    },

    [MOVE_DARKEST_LARIAT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DARKEST LARIAT"),
        .description = COMPOUND_STRING(
            "Swings the arms to strike It ignores stat changes."),
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresTargetDefenseEvasionStages = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DarkestLariat,
    },

    [MOVE_SPARKLING_ARIA] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SPARKLING ARIA"),
        .description = COMPOUND_STRING(
            "Sings with bubbles. Cures burns on contact."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .argument = { .status = STATUS1_BURN },
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .soundMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_REMOVE_STATUS,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SCALD},
        .battleAnimScript = gBattleAnimMove_SparklingAria,
    },

    [MOVE_ICE_HAMMER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ICE HAMMER"),
        .description = COMPOUND_STRING(
            "Swings the fist to strike. Lowers the user's SPEED."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_ICE,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HAIL},
        .battleAnimScript = gBattleAnimMove_IceHammer,
    },

    [MOVE_FLORAL_HEALING] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FLORAL HEALNG"),
        .description = COMPOUND_STRING(
            "Restores an ally's HP. Heals more on grass."),
        .effect = EFFECT_HEAL_PULSE,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .argument = { .moveProperty = MOVE_EFFECT_FLORAL_HEALING },
        .mirrorMoveBanned = TRUE,
        .healingMove = TRUE,
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FloralHealing,
    },

    [MOVE_HIGH_HORSEPOWER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("HIGH HORSEPOWER"),
        .description = COMPOUND_STRING(
            "Slams hard into the foe with its entire body."),
        .effect = EFFECT_HIT,
        .power = 95,
        .type = TYPE_GROUND,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HighHorsepower,
    },

    [MOVE_STRENGTH_SAP] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("STRENGTH SAP"),
        .description = COMPOUND_STRING(
            "Restores HP by the same amount as the foe's ATTACK stat, and lowers the target's ATTACK."),
        .effect = EFFECT_STRENGTH_SAP,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .magicCoatAffected = TRUE,
        .healingMove = B_HEAL_BLOCKING >= GEN_6,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_StrengthSap,
    },

    [MOVE_SOLAR_BLADE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SOLAR BLADE"),
        .description = COMPOUND_STRING(
            "Charges first turn, then chops with a blade of light."),
        .effect = EFFECT_SOLAR_BEAM,
        .power = 125,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .argument.twoTurnAttack = { .stringId = STRINGID_PKMNTOOKSUNLIGHT, .status = B_WEATHER_SUN },
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_SolarBlade,
    },

    [MOVE_LEAFAGE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("LEAFAGE"),
        .description = COMPOUND_STRING(
            "Attacks with a flurry of small leaves."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GROWTH},
        .battleAnimScript = gBattleAnimMove_Leafage,
    },

    [MOVE_SPOTLIGHT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SPOTLIGHT"),
        .description = COMPOUND_STRING(
            "Makes the foe attack the spotlighted Pokémon."),
        .effect = EFFECT_FOLLOW_ME,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 3,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPDEF_UP_1 },
        .magicCoatAffected = TRUE,
        .mirrorMoveBanned = TRUE,
        //.metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Spotlight,
    },

    [MOVE_TOXIC_THREAD] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TOXIC THREAD"),
        .description = COMPOUND_STRING(
            "Attacks with a thread that poisons and drops SPEED."),
        .effect = EFFECT_TOXIC_THREAD,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_TOXIC},
        .battleAnimScript = gBattleAnimMove_ToxicThread,
    },

    [MOVE_LASER_FOCUS] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("LASER FOCUS"),
        .description = COMPOUND_STRING(
            "Guarantees the next move will be a critical hit."),
        .effect = EFFECT_LASER_FOCUS,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 30,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ATK_UP_1 },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_LaserFocus,
    },

    [MOVE_GEAR_UP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("GEAR UP"),
        .description = COMPOUND_STRING(
            "Boosts the attacks of those with Plus or Minus."),
        .effect = EFFECT_GEAR_UP,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_GearUp,
    },

    [MOVE_THROAT_CHOP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("THROAT CHOP"),
        .description = COMPOUND_STRING(
            "Chops the throat to disable sound moves for a while."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_THROAT_CHOP,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ThroatChop,
    },

    [MOVE_POLLEN_PUFF] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("POLLEN PUFF"),
        .description = COMPOUND_STRING(
            "Explodes on foes, but restores ally's HP."),
        .effect = EFFECT_HIT_ENEMY_HEAL_ALLY,
        .power = 90,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ballisticMove = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PollenPuff,
    },

    [MOVE_ANCHOR_SHOT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ANCHOR SHOT"),
        .description = COMPOUND_STRING(
            "Strangles the foe with a chain. The foe can't escape."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PREVENT_ESCAPE,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_AnchorShot,
    },

    [MOVE_PSYCHIC_TERRAIN] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("PSYCHIC TERRAIN"),
        .description = COMPOUND_STRING(
            "The ground turns weird for 5 turns. Blocks priority."),
        .effect = EFFECT_PSYCHIC_TERRAIN,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_AUDIENCE_EXCITED,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = COMBO_STARTER_PSYCHIC_TERRAIN,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PsychicTerrain,
    },

    [MOVE_LUNGE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("LUNGE"),
        .description = COMPOUND_STRING(
            "Lunges at the foe to lower its ATTACK stat."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_MINUS_1,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Lunge,
    },

    [MOVE_FIRE_LASH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FIRE LASH"),
        .description = COMPOUND_STRING(
            "Whips the foe with fire lowering its DEFENSE."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_FireLash,
    },

    [MOVE_POWER_TRIP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("POWER TRIP"),
        .description = COMPOUND_STRING(
            "It hits harder the more stat boosts the user has."),
        .effect = EFFECT_STORED_POWER,
        .power = 20,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PowerTrip,
    },

    [MOVE_BURN_UP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BURN UP"),
        .description = COMPOUND_STRING(
            "Burns out the user fully removing the Fire type."),
        .effect = EFFECT_FAIL_IF_NOT_ARG_TYPE,
        .power = 130,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .thawsUser = TRUE,
        .argument = { .type = TYPE_FIRE },
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_REMOVE_ARG_TYPE,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SUNNY_DAY},
        .battleAnimScript = gBattleAnimMove_BurnUp,
    },

    [MOVE_SPEED_SWAP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SPEED SWAP"),
        .description = COMPOUND_STRING(
            "Swaps user's SPEED with the target's."),
        .effect = EFFECT_SPEED_SWAP,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresSubstitute = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SpeedSwap,
    },

    [MOVE_SMART_STRIKE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SMART STRIKE"),
        .description = COMPOUND_STRING(
            "Hits with an accurate horn that never misses."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SmartStrike,
    },

    [MOVE_PURIFY] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("PURIFY"),
        .description = COMPOUND_STRING(
            "Cures the foe's status to restore HP."),
        .effect = EFFECT_PURIFY,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_ALL_STATS_UP_1 },
        .mirrorMoveBanned = TRUE,
        .healingMove = TRUE,
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Purify,
    },

    [MOVE_REVELATION_DANCE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("REVELATION DANCE"),
        .description = COMPOUND_STRING(
            "Dances with mystical power. Matches user's first type."),
        .effect = EFFECT_REVELATION_DANCE,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .danceMove = TRUE,
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_RevelationDance,
    },

    [MOVE_CORE_ENFORCER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("CORE ENFORCER"),
        .description = COMPOUND_STRING(
            "Hits with a ray that nullifies the foe's ability."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .zMove = { .powerOverride = 140 },
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CORE_ENFORCER,
        }),
        .contestEffect = CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_CoreEnforcer,
    },

    [MOVE_TROP_KICK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TROP KICK"),
        .description = COMPOUND_STRING(
            "An intense kick from the tropics. Lowers ATTACK."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_MINUS_1,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_TropKick,
    },

    [MOVE_INSTRUCT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("INSTRUCT"),
        .description = COMPOUND_STRING(
            "Orders the target to use its last move again."),
        .effect = EFFECT_INSTRUCT,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPATK_UP_1 },
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        //.metronomeBanned = TRUE,
        .instructBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Instruct,
    },

    [MOVE_BEAK_BLAST] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BEAK BLAST"),
        .description = COMPOUND_STRING(
            "Heats up beak to attack. Burns foe on contact."),
        .effect = EFFECT_BEAK_BLAST,
        .power = 100,
        .type = TYPE_FLYING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = -3,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .mirrorMoveBanned = TRUE,
        .ballisticMove = TRUE,
        .meFirstBanned = TRUE,
        //.metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AFFECTED_BY_PREV_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_BeakBlast,
    },

    [MOVE_CLANGING_SCALES] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("CLANGING SCALES"),
        .description = COMPOUND_STRING(
            "Makes a big noise with its scales. Drops DEFENSE."),
        .effect = EFFECT_HIT,
        .power = 110,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .soundMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ClangingScales,
    },

    [MOVE_DRAGON_HAMMER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DRAGON HAMMER"),
        .description = COMPOUND_STRING(
            "Swings its whole body like a hammer to damage."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_DRAGON_BREATH, COMBO_STARTER_DRAGON_DANCE, COMBO_STARTER_DRAGON_RAGE, COMBO_STARTER_TYRANT_CRUSH, COMBO_STARTER_DRAGON_TAIL},
        .battleAnimScript = gBattleAnimMove_DragonHammer,
    },

    [MOVE_BRUTAL_SWING] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BRUTAL SWING"),
        .description = COMPOUND_STRING(
            "Violently swings around to hurt everyone nearby."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_BrutalSwing,
    },

    [MOVE_AURORA_VEIL] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("AURORA VEIL"),
        .description = COMPOUND_STRING(
            "Weakens all attacks, but only usable with hail."),
        .effect = EFFECT_AURORA_VEIL,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_HAIL},
        .battleAnimScript = gBattleAnimMove_AuroraVeil,
    },

    [MOVE_SHELL_TRAP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SHELL TRAP"),
        .description = COMPOUND_STRING(
            "Sets a shell trap that damages on contact."),
        .effect = EFFECT_SHELL_TRAP,
        .power = 150,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = -3,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .mirrorMoveBanned = TRUE,
        .meFirstBanned = TRUE,
        //.metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .assistBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ShellTrap,
    },

    [MOVE_FLEUR_CANNON] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FLEUR CANNON"),
        .description = COMPOUND_STRING(
            "A strong ray that harshly lowers Sp. ATTACK."),
        .effect = EFFECT_HIT,
        .power = 130,
        .type = TYPE_FAIRY,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_2,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FleurCannon,
    },

    [MOVE_PSYCHIC_FANGS] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("PSYCHIC FANGS"),
        .description = COMPOUND_STRING(
            "Chomps with psychic fangs. Destroys any barriers."),
        .effect = EFFECT_BRICK_BREAK,
        .power = 85,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PsychicFangs,
    },

    [MOVE_STOMPING_TANTRUM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("STOMPING TANTRUM"),
        .description = COMPOUND_STRING(
            "Stomps around angrily. Stronger after a failure."),
        .effect = EFFECT_STOMPING_TANTRUM,
        .power = 75,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .skyBattleBanned = B_EXTRAPOLATED_MOVE_FLAGS,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_StompingTantrum,
    },

    [MOVE_SHADOW_BONE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SHADOW BONE"),
        .description = COMPOUND_STRING(
            "Strikes with a haunted bone. Might drop DEFENSE."),
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 20,
        }),
        .contestEffect = CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_SHADOW_BONE,
        .contestComboMoves = {COMBO_STARTER_BONE_CLUB, COMBO_STARTER_BONEMERANG, COMBO_STARTER_BONE_RUSH},
        .battleAnimScript = gBattleAnimMove_ShadowBone,
    },

    [MOVE_ACCELEROCK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ACCELEROCK"),
        .description = COMPOUND_STRING(
            "Flings a stone at the foe at high speed. This move always goes first."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Accelerock,
    },

    [MOVE_LIQUIDATION] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("LIQUIDATION"),
        .description = COMPOUND_STRING(
            "Slams the foe with water. Can lower DEFENSE."),
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 20,
        }),
        .contestEffect = CONTEST_EFFECT_SHIFT_JUDGE_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_Liquidation,
    },

    [MOVE_PRISMATIC_LASER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("PRISMATIC LASER"),
        .description = COMPOUND_STRING(
            "A high power laser that forces recharge next turn."),
        .effect = EFFECT_HIT,
        .power = 160,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PrismaticLaser,
    },

    [MOVE_SPECTRAL_THIEF] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SPECTRAL THIEF"),
        .description = COMPOUND_STRING(
            "Steals the target's stat boosts, then attacks."),
        .effect = EFFECT_SPECTRAL_THIEF,
        .power = 90,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresSubstitute = TRUE,
        .makesContact = TRUE,
        //.metronomeBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_APPEAL_AS_GOOD_AS_PREV_ONES,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SpectralThief,
    },

    [MOVE_SUNSTEEL_STRIKE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SUNSTEEL STRIKE"),
        .description = COMPOUND_STRING(
            "A sun-fueled strike that ignores abilities."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresTargetAbility = TRUE,
        //.metronomeBanned = B_UPDATED_MOVE_FLAGS >= GEN_8,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SunsteelStrike,
    },

    [MOVE_MOONGEIST_BEAM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MOONGEIST BEAM"),
        .description = COMPOUND_STRING(
            "A moon-powered beam that ignores abilities."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresTargetAbility = TRUE,
        //.metronomeBanned = B_UPDATED_MOVE_FLAGS >= GEN_8,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MoongeistBeam,
    },

    [MOVE_TEARFUL_LOOK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TEARFUL LOOK"),
        .description = COMPOUND_STRING(
            "The user tears up, dropping ATTACK and Sp. ATTACK."),
        .effect = EFFECT_NOBLE_ROAR,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .ignoresProtect = TRUE,
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_TearfulLook,
    },

    [MOVE_ZING_ZAP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ZING ZAP"),
        .description = COMPOUND_STRING(
            "An electrified impact that can cause flinching."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_CHARGE},
        .battleAnimScript = gBattleAnimMove_ZingZap,
    },

    [MOVE_NATURES_MADNESS] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("NATURE's Madness"),
        .description = COMPOUND_STRING(
            "Halves the foe's HP with the power of nature."),
        .effect = EFFECT_SUPER_FANG,
        .power = 1,
        .type = TYPE_FAIRY,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        //.metronomeBanned = B_UPDATED_MOVE_FLAGS >= GEN_8,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_MONS_WITH_GOOD_APPEALS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_NaturesMadness,
    },

    [MOVE_MULTI_ATTACK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MULTI-ATTACK"),
        .description = COMPOUND_STRING(
            "An attack that changes with Memories."),
        .effect = EFFECT_CHANGE_TYPE_ON_ITEM,
        .power = B_UPDATED_MOVE_DATA >= GEN_8 ? 120 : 90,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .argument = { .holdEffect = HOLD_EFFECT_MEMORY },
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_SCRAMBLE_NEXT_TURN_ORDER,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MultiAttack,
    },

    [MOVE_MIND_BLOWN] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MIND BLOWN"),
        .description = COMPOUND_STRING(
            "It explodes the user's head to damage everything around."),
        .effect = EFFECT_MIND_BLOWN,
        .power = 150,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        //.metronomeBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MindBlown,
    },

    [MOVE_PLASMA_FISTS] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("PLASMA FISTS"),
        .description = COMPOUND_STRING(
            "Hits with electrical fists. Normal moves turn Electric."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        //.metronomeBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ION_DELUGE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
        .battleAnimScript = gBattleAnimMove_PlasmaFists,
    },

    [MOVE_PHOTON_GEYSER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("PHOTON GEYSER"),
        .description = COMPOUND_STRING(
            "User's highest attack stat determines its category."),
        .effect = EFFECT_PHOTON_GEYSER,
        .power = 100,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresTargetAbility = TRUE,
        //.metronomeBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PhotonGeyser,
    },

    [MOVE_ZIPPY_ZAP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ZIPPY ZAP"),
        .description = COMPOUND_STRING(
            "Electric bursts always go first and land a critical hit."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_8 ? 80 : 50,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_8 ? 10 : 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 2,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .mirrorMoveBanned = B_UPDATED_MOVE_FLAGS < GEN_8,
        .alwaysCriticalHit = TRUE,
        //.metronomeBanned = TRUE,
        #if B_UPDATED_MOVE_DATA >= GEN_8
            .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_EVS_PLUS_1,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
        #endif
        .battleAnimScript = gBattleAnimMove_ZippyZap,
    },

    [MOVE_SPLISHY_SPLASH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SPLISHY SPLASH"),
        .description = COMPOUND_STRING(
            "A huge electrified wave that may paralyze the foe."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .mirrorMoveBanned = B_UPDATED_MOVE_FLAGS < GEN_8,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
        .battleAnimScript = gBattleAnimMove_SplishySplash,
    },

    [MOVE_FLOATY_FALL] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FLOATY FALL"),
        .description = COMPOUND_STRING(
            "Floats in air and dives at angle. May cause flinching."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_FLYING,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .mirrorMoveBanned = B_UPDATED_MOVE_FLAGS < GEN_8,
        .gravityBanned = TRUE,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
        .battleAnimScript = gBattleAnimMove_FloatyFall,
    },

    [MOVE_PIKA_PAPOW] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("PIKA PAPOW"),
        .description = COMPOUND_STRING(
            "Pikachu's love increases its power. It never misses."),
        .effect = EFFECT_RETURN,
        .power = 1,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .mirrorMoveBanned = B_UPDATED_MOVE_FLAGS < GEN_8,
        //.metronomeBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_PikaPapow,
    },

    [MOVE_BOUNCY_BUBBLE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BOUNCY BUBBLE"),
        .description = COMPOUND_STRING(
            "An attack that absorbs\n"
        #if B_UPDATED_MOVE_DATA >= GEN_8
            "all the damage inflicted."),
        #else
            "half the damage inflicted."),
        #endif
        .effect = EFFECT_ABSORB,
        .power = B_UPDATED_MOVE_DATA >= GEN_8 ? 60 : 90,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_8 ? 20 : 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .argument = { .absorbPercentage = B_UPDATED_MOVE_DATA >= GEN_8 ? 100 : 50 },
        .mirrorMoveBanned = B_UPDATED_MOVE_FLAGS < GEN_8,
        //.metronomeBanned = TRUE,
        .healingMove = B_HEAL_BLOCKING >= GEN_6,
        .battleAnimScript = gBattleAnimMove_BouncyBubble,
    },

    [MOVE_BUZZY_BUZZ] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BUZZY BUZZ"),
        .description = COMPOUND_STRING(
            "Shoots a jolt of electricity that always paralyzes."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_8 ? 60 : 90,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_8 ? 20 : 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .mirrorMoveBanned = B_UPDATED_MOVE_FLAGS < GEN_8,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
        .battleAnimScript = gBattleAnimMove_BuzzyBuzz,
    },

    [MOVE_SIZZLY_SLIDE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SIZZLY SLIDE"),
        .description = COMPOUND_STRING(
            "User cloaked in fire charges. Leaves the foe with a burn."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_8 ? 60 : 90,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_8 ? 20 : 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .mirrorMoveBanned = B_UPDATED_MOVE_FLAGS < GEN_8,
        .thawsUser = TRUE,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
        .battleAnimScript = gBattleAnimMove_SizzlySlide,
    },

    [MOVE_GLITZY_GLOW] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("GLITZY GLOW"),
        .description = COMPOUND_STRING(
            "Telekinetic force that sets wall, lowering SP. ATK damage."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_8 ? 80 : 90,
        .type = TYPE_PSYCHIC,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_8 ? 95 : 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .mirrorMoveBanned = B_UPDATED_MOVE_FLAGS < GEN_8,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_LIGHT_SCREEN,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
        .battleAnimScript = gBattleAnimMove_GlitzyGlow,
    },

    [MOVE_BADDY_BAD] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BADDY BAD"),
        .description = COMPOUND_STRING(
            "Acting badly, attacks. Sets wall, lowering ATTACK damage."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_8 ? 80 : 90,
        .type = TYPE_DARK,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_8 ? 95 : 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .mirrorMoveBanned = B_UPDATED_MOVE_FLAGS < GEN_8,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_REFLECT,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
        .battleAnimScript = gBattleAnimMove_BaddyBad,
    },

    [MOVE_SAPPY_SEED] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SAPPY SEED"),
        .description = COMPOUND_STRING(
            "Giant stalk scatters seeds that drain HP every turn."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_8 ? 100 : 90,
        .type = TYPE_GRASS,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_8 ? 90 : 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_8 ? 10 : 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .mirrorMoveBanned = B_UPDATED_MOVE_FLAGS < GEN_8,
        .magicCoatAffected = TRUE,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_LEECH_SEED,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
        .battleAnimScript = gBattleAnimMove_SappySeed,
    },

    [MOVE_FREEZY_FROST] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FREEZY FROST"),
        .description = COMPOUND_STRING(
            "Crystal from cold haze hits. Eliminates all stat changes."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_8 ? 100 : 90,
        .type = TYPE_ICE,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_8 ? 90 : 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_8 ? 10 : 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .mirrorMoveBanned = B_UPDATED_MOVE_FLAGS < GEN_8,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_HAZE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
        .battleAnimScript = gBattleAnimMove_FreezyFrost,
    },

    [MOVE_SPARKLY_SWIRL] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SPARKLY SWIRL"),
        .description = COMPOUND_STRING(
            "Wrap foe with whirlwind of scent. Heals party's status."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_8 ? 120 : 90,
        .type = TYPE_FAIRY,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_8 ? 85 : 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_8 ? 5 : 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .mirrorMoveBanned = B_UPDATED_MOVE_FLAGS < GEN_8,
        //.metronomeBanned = TRUE,
        // .additionalEffects = ADDITIONAL_EFFECTS({
        //     .moveEffect = 0, // MOVE_EFFECT_AROMATHERAPY, Added 0 for Sheer Force boost
        //     .chance = 100,
        //     .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        // }),
        .battleAnimScript = gBattleAnimMove_SparklySwirl,
    },

    [MOVE_VEEVEE_VOLLEY] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("VEEVEE VOLLEY"),
        .description = COMPOUND_STRING(
            "Eevee's love increases its power. It never misses."),
        .effect = EFFECT_RETURN,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .mirrorMoveBanned = B_UPDATED_MOVE_FLAGS < GEN_8,
        //.metronomeBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_VeeveeVolley,
    },

    [MOVE_DOUBLE_IRON_BASH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DOUBLE IRON BASH"),
        .description = COMPOUND_STRING(
            "The user spins and hits with its arms. May cause flinch."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .strikeCount = 2,
        .minimizeDoubleDamage = B_UPDATED_MOVE_FLAGS < GEN_8,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DoubleIronBash,
    },

    [MOVE_DYNAMAX_CANNON] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DYNAMAX CANNON"),
        .description = COMPOUND_STRING(
            "Unleashes core energy. 2x against Dynamaxed foes."),
        .effect = EFFECT_DYNAMAX_DOUBLE_DMG,
        .power = 100,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .mirrorMoveBanned = TRUE,
        //.metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .mimicBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = B_EXTRAPOLATED_MOVE_FLAGS,
        .parentalBondBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DynamaxCannon,
    },

    [MOVE_SNIPE_SHOT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SNIPE SHOT"),
        .description = COMPOUND_STRING(
            "The user ignores effects that draw in moves."),
        .effect = EFFECT_SNIPE_SHOT,
        .power = 80,
        .type = TYPE_WATER,
        .accuracy = 100,
        .criticalHitStage = 1,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SnipeShot,
    },

    [MOVE_JAW_LOCK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("JAW LOCK"),
        .description = COMPOUND_STRING(
            "Prevents the user and the target from escaping."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_TRAP_BOTH,
        }),
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_JawLock,
    },

    [MOVE_STUFF_CHEEKS] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("STUFF CHEEKS"),
        .description = COMPOUND_STRING(
            "Consumes the user's Berry, then sharply raises Def."),
        .effect = EFFECT_STUFF_CHEEKS,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_StuffCheeks,
    },

    [MOVE_NO_RETREAT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("NO RETREAT"),
        .description = COMPOUND_STRING(
            "Raises all of the user's stats but prevents escape."),
        .effect = EFFECT_NO_RETREAT,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_NoRetreat,
    },

    [MOVE_TAR_SHOT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TAR SHOT"),
        .description = COMPOUND_STRING(
            "Lowers the foe's SPEED and makes it weak to Fire."),
        .effect = EFFECT_TAR_SHOT,
        .power = 0,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_TarShot,
    },

    [MOVE_MAGIC_POWDER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAGIC POWDER"),
        .description = COMPOUND_STRING(
            "Magic powder changes the target into a Psychic-type."),
        .effect = EFFECT_SOAK,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .argument = { .type = TYPE_PSYCHIC },
        .magicCoatAffected = TRUE,
        .powderMove = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MagicPowder,
    },

    [MOVE_DRAGON_DARTS] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DRAGON DARTS"),
        .description = COMPOUND_STRING(
            "The user attacks twice. Two targets are hit once each."),
        .effect = EFFECT_DRAGON_DARTS,
        .power = 50,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .strikeCount = 2,
        .parentalBondBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DragonDarts,
    },

    [MOVE_TEATIME] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TEATIME"),
        .description = COMPOUND_STRING(
            "All Pokémon have teatime and eat their Berries."),
        .effect = EFFECT_TEATIME,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Teatime,
    },

    [MOVE_OCTOLOCK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("OCTOLOCK"),
        .description = COMPOUND_STRING(
            "Traps the foe to lower Def and SP. DEF each turn."),
        .effect = EFFECT_OCTOLOCK,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Octolock,
    },

    [MOVE_BOLT_BEAK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BOLT BEAK"),
        .description = COMPOUND_STRING(
            "Double power if the user moves before the target."),
        .effect = EFFECT_BOLT_BEAK,
        .power = 85,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_BoltBeak,
    },

    [MOVE_FISHIOUS_REND] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FISHIOUS REND"),
        .description = COMPOUND_STRING(
            "Double power if the user moves before the target."),
        .effect = EFFECT_BOLT_BEAK,
        .power = 85,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .bitingMove = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FishiousRend,
    },

    [MOVE_COURT_CHANGE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("COURT CHANGE"),
        .description = COMPOUND_STRING(
            "The user swaps effects on either side of the field."),
        .effect = EFFECT_COURT_CHANGE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .ignoresProtect = TRUE,
        .contestEffect = CONTEST_EFFECT_MAKE_FOLLOWING_MONS_NERVOUS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_CourtChange,
    },

    [MOVE_CLANGOROUS_SOUL] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("CLANGOROUS SOUL"),
        .description = COMPOUND_STRING(
            "The user uses some of its HP to raise all its stats."),
        .effect = EFFECT_CLANGOROUS_SOUL,
        .power = 0,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .soundMove = TRUE,
        .danceMove = TRUE,
        //.metronomeBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ClangorousSoul,
    },

    [MOVE_BODY_PRESS] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BODY PRESS"),
        .description = COMPOUND_STRING(
            "Does more damage the higher the user's Def."),
        .effect = EFFECT_BODY_PRESS,
        .power = 80,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        //.metronomeBanned = TRUE,
        .skyBattleBanned = B_EXTRAPOLATED_MOVE_FLAGS,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_BodyPress,
    },

    [MOVE_DECORATE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DECORATE"),
        .description = COMPOUND_STRING(
            "The user sharply raises the target's Atk and Sp.Atk."),
        .effect = EFFECT_DECORATE,
        .power = 0,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.metronomeBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Decorate,
    },

    [MOVE_DRUM_BEATING] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DRUM BEATING"),
        .description = COMPOUND_STRING(
            "Plays a drum to attack. The foe's SPEED is lowered."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DrumBeating,
    },

    [MOVE_SNAP_TRAP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SNAP TRAP"),
        .description = COMPOUND_STRING(
            "Snares the target in a snap trap for four to five turns."),
        .effect = EFFECT_HIT,
        .power = 35,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        //.metronomeBanned = TRUE,
        .skyBattleBanned = B_EXTRAPOLATED_MOVE_FLAGS,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
        }),
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SnapTrap,
    },

    [MOVE_PYRO_BALL] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("PYRO BALL"),
        .description = COMPOUND_STRING(
            "Launches a fiery ball at the target. It may cause a burn."),
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_FIRE,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .thawsUser = TRUE,
        .ballisticMove = TRUE,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_PyroBall,
    },

    [MOVE_BEHEMOTH_BLADE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BEHEMOTH BLADE"),
        .description = COMPOUND_STRING(
            "Strikes as a sword. Deals 2x damage to Dynamaxed foes."),
        .effect = EFFECT_DYNAMAX_DOUBLE_DMG,
        .power = 100,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        //.metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .mimicBanned = TRUE,
        .assistBanned = B_EXTRAPOLATED_MOVE_FLAGS,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_BehemothBlade,
    },

    [MOVE_BEHEMOTH_BASH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BEHEMOTH BASH"),
        .description = COMPOUND_STRING(
            "Attacks as a shield. Deals 2x damage to Dynamaxed foes."),
        .effect = EFFECT_DYNAMAX_DOUBLE_DMG,
        .power = 100,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        //.metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .mimicBanned = TRUE,
        .assistBanned = B_EXTRAPOLATED_MOVE_FLAGS,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_BehemothBash,
    },

    [MOVE_AURA_WHEEL] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("AURA WHEEL"),
        .description = COMPOUND_STRING(
            "Raises SPEED to attack. The Type is based on its form."),
        .effect = EFFECT_AURA_WHEEL,
        .power = 110,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_AuraWheel,
    },

    [MOVE_BREAKING_SWIPE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BREAKING SWIPE"),
        .description = COMPOUND_STRING(
            "Swings its tail to attack. Lowers the Atk of those hit."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_MINUS_1,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_BreakingSwipe,
    },

    [MOVE_BRANCH_POKE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BRANCH POKE"),
        .description = COMPOUND_STRING(
            "The user pokes the target with a pointed branch."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        //.metronomeBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_BranchPoke,
    },

    [MOVE_OVERDRIVE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("OVERDRIVE"),
        .description = COMPOUND_STRING(
            "The user twangs its guitar, causing strong vibrations."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .soundMove = TRUE,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        //.metronomeBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Overdrive,
    },

    [MOVE_APPLE_ACID] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("APPLE ACID"),
        .description = COMPOUND_STRING(
            "Attacks with tart apple acid to lower the foe's SP. DEF."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_1,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_AppleAcid,
    },

    [MOVE_GRAV_APPLE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("GRAV APPLE"),
        .description = COMPOUND_STRING(
            "Drops an apple from above. Lowers the foe's DEFENSE."),
        .effect = EFFECT_GRAV_APPLE,
        .power = 80,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_GravApple,
    },

    [MOVE_SPIRIT_BREAK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SPIRIT BREAK"),
        .description = COMPOUND_STRING(
            "Attacks with spirit-breaking force. Lowers SP. ATK."),
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_1,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SpiritBreak,
    },

    [MOVE_STRANGE_STEAM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("STRANGE STEAM"),
        .description = COMPOUND_STRING(
            "Emits a strange steam to potentially confuse the foe."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_FAIRY,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 20,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_FRONT_MON,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_StrangeSteam,
    },

    [MOVE_LIFE_DEW] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("LIFE DEW"),
        .description = COMPOUND_STRING(
            "Scatters water to restore the HP of itself and allies."),
        .effect = EFFECT_JUNGLE_HEALING,
        .power = 0,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .healingMove = TRUE,
        //.metronomeBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_LifeDew,
    },

    [MOVE_OBSTRUCT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("OBSTRUCT"),
        .description = COMPOUND_STRING(
            "Protects itself, harshly lowering Def on contact."),
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 4,
        .category = DAMAGE_CATEGORY_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.metronomeBanned = TRUE,
        .instructBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Obstruct,
    },

    [MOVE_FALSE_SURRENDER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FALSE SURRENDER"),
        .description = COMPOUND_STRING(
            "Bows to stab the foe with hair. It never misses."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        //.metronomeBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FalseSurrender,
    },

    [MOVE_METEOR_ASSAULT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("METEOR ASSAULT"),
        .description = COMPOUND_STRING(
            "Attacks with a thick leek. The user must then rest."),
        .effect = EFFECT_HIT,
        .power = 150,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        //.metronomeBanned = TRUE,
        .instructBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MeteorAssault,
    },

    [MOVE_ETERNABEAM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ETERNABEAM"),
        .description = COMPOUND_STRING(
            "Eternatus' strongest move. The user rests next turn."),
        .effect = EFFECT_HIT,
        .power = 160,
        .type = TYPE_DRAGON,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECHARGE,
            .self = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Eternabeam,
    },

    [MOVE_STEEL_BEAM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("STEEL BEAM"),
        .description = COMPOUND_STRING(
            "Fires a beam of steel from its body. It hurts the user."),
        .effect = EFFECT_MAX_HP_50_RECOIL,
        .power = 140,
        .type = TYPE_STEEL,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        //.metronomeBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SteelBeam,
    },

    [MOVE_EXPANDING_FORCE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("EXPANDING FORCE"),
        .description = COMPOUND_STRING(
            "Power goes up and damages all foes on Psychic Terrain."),
        .effect = EFFECT_EXPANDING_FORCE,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_PSYCHIC_TERRAIN},
        .battleAnimScript = gBattleAnimMove_ExpandingForce,
    },

    [MOVE_STEEL_ROLLER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("STEEL ROLLER"),
        .description = COMPOUND_STRING(
            "Destroys terrain. Fails if ground isn't terrain."),
        .effect = EFFECT_HIT_SET_REMOVE_TERRAIN,
        .power = 130,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .argument = { .moveProperty = ARG_TRY_REMOVE_TERRAIN_FAIL }, // Remove a field terrain if there is one and hit, otherwise fail.
        .skyBattleBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SteelRoller,
    },

    [MOVE_SCALE_SHOT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SCALE SHOT"),
        .description = COMPOUND_STRING(
            "Shoots scales 2 to 5 times. Ups SPEED, lowers defense."),
        .effect = EFFECT_MULTI_HIT,
        .power = 25,
        .type = TYPE_DRAGON,
        .accuracy = 90,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .argument = { .moveProperty = MOVE_EFFECT_SCALE_SHOT },
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ScaleShot,
    },

    [MOVE_METEOR_BEAM] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("METEOR BEAM"),
        .description = COMPOUND_STRING(
            "Gathers space power and boosts SP. ATK, then blasts the foe on the next turn."),
        .effect = EFFECT_TWO_TURNS_ATTACK,
        .power = 120,
        .type = TYPE_ROCK,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .instructBanned = TRUE,
        .argument.twoTurnAttack = { .stringId = STRINGID_METEORBEAMCHARGING },
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_PLUS_1,
            .self = TRUE,
            .onChargeTurnOnly = TRUE,
        }),
        .contestEffect = CONTEST_EFFECT_USER_MORE_EASILY_STARTLED,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_MeteorBeam,
    },

    [MOVE_SHELL_SIDE_ARM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SHELL SIDE ARM"),
        .description = COMPOUND_STRING(
            "Deals better of physical and special damage. May poison."),
        .effect = EFFECT_SHELL_SIDE_ARM,
        .power = 90,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 20,
        }),
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ShellSideArm,
    },

    [MOVE_MISTY_EXPLOSION] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MISTY EXPLOSION"),
        .description = COMPOUND_STRING(
            "Hit everything and faint. Powers up on Misty Terrain."),
        .effect = EFFECT_EXPLOSION,
        .power = 100,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_GREAT_APPEAL_BUT_NO_MORE_MOVES,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_MISTY_TERRAIN},
        .battleAnimScript = gBattleAnimMove_MistyExplosion,
    },

    [MOVE_GRASSY_GLIDE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("GRASSY GLIDE"),
        .description = COMPOUND_STRING(
            "Gliding on ground, hits. Goes first on Grassy Terrain."),
        .effect = EFFECT_GRASSY_GLIDE,
        .power = B_UPDATED_MOVE_DATA >= GEN_9 ? 55 : 70,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .skyBattleBanned = B_EXTRAPOLATED_MOVE_FLAGS,
        .contestEffect = CONTEST_EFFECT_NEXT_APPEAL_EARLIER,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_GRASSY_TERRAIN},
        .battleAnimScript = gBattleAnimMove_GrassyGlide,
    },

    [MOVE_RISING_VOLTAGE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("RISING VOLTAGE"),
        .description = COMPOUND_STRING(
            "This move's power doubles when on Electric Terrain."),
        .effect = EFFECT_RISING_VOLTAGE,
        .power = 70,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_ELECTRIC_TERRAIN},
        .battleAnimScript = gBattleAnimMove_RisingVoltage,
    },

    [MOVE_TERRAIN_PULSE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TERRAIN PULSE"),
        .description = COMPOUND_STRING(
            "Type and power changes depending on the terrain."),
        .effect = EFFECT_TERRAIN_PULSE,
        .power = 50,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .pulseMove = TRUE,
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_ELECTRIC_TERRAIN, COMBO_STARTER_MISTY_TERRAIN, COMBO_STARTER_GRASSY_TERRAIN, COMBO_STARTER_PSYCHIC_TERRAIN},
        .battleAnimScript = gBattleAnimMove_TerrainPulse,
    },

    [MOVE_SKITTER_SMACK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SKITTER SMACK"),
        .description = COMPOUND_STRING(
            "User skitters behind foe to attack. Lowers foe's SP. ATK."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_BUG,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_1,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_BADLY_STARTLE_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SkitterSmack,
    },

    [MOVE_BURNING_JEALOUSY] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BURNING JEALOUSY"),
        .description = COMPOUND_STRING(
            "Foes that have stats upped during the turn get burned."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .onlyIfTargetRaisedStats = TRUE,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_BurningJealousy,
    },

    [MOVE_LASH_OUT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("LASH OUT"),
        .description = COMPOUND_STRING(
            "If stats lowered during this turn, power is doubled."),
        .effect = EFFECT_LASH_OUT,
        .power = 75,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_PREV_MON,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_LashOut,
    },

    [MOVE_POLTERGEIST] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("POLTERGEIST"),
        .description = COMPOUND_STRING(
            "Control foe's item to attack. Fails if foe has no item."),
        .effect = EFFECT_POLTERGEIST,
        .power = 110,
        .type = TYPE_GHOST,
        .accuracy = 90,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Poltergeist,
    },

    [MOVE_CORROSIVE_GAS] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("CORROSIVE GAS"),
        .description = COMPOUND_STRING(
            "Highly acidic gas melts items held by surrounding Pokémon."),
        .effect = EFFECT_CORROSIVE_GAS,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 40,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_CorrosiveGas,
    },

    [MOVE_COACHING] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("COACHING"),
        .description = COMPOUND_STRING(
            "Properly coaches allies to up their ATTACK and DEFENSE."),
        .effect = EFFECT_COACHING,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_IMPROVE_CONDITION_PREVENT_NERVOUSNESS,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Coaching,
    },

    [MOVE_FLIP_TURN] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FLIP TURN"),
        .description = COMPOUND_STRING(
            "Attacks and rushes back to switch with a party Pokémon."),
        .effect = EFFECT_HIT_ESCAPE,
        .power = 60,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .contestEffect = CONTEST_EFFECT_AVOID_STARTLE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FlipTurn,
    },

    [MOVE_TRIPLE_AXEL] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TRIPLE AXEL"),
        .description = COMPOUND_STRING(
            "A 3-kick attack that gets more powerful with each hit."),
        .effect = EFFECT_TRIPLE_KICK,
        .power = 20,
        .type = TYPE_ICE,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .strikeCount = 3,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_TripleAxel,
    },

    [MOVE_DUAL_WINGBEAT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DUAL WINGBEAT"),
        .description = COMPOUND_STRING(
            "User slams the target with wings and hits twice in a row."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_FLYING,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .strikeCount = 2,
        .contestEffect = CONTEST_EFFECT_REPETITION_NOT_BORING,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DualWingbeat,
    },

    [MOVE_SCORCHING_SANDS] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SCORCHING SANDS"),
        .description = COMPOUND_STRING(
            "Throws scorching sand at the target. May leave a burn."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .thawsUser = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ScorchingSands,
    },

    [MOVE_JUNGLE_HEALING] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("JUNGLE HEALNG"),
        .description = COMPOUND_STRING(
            "Heals HP and status of itself and allies in battle."),
        .effect = EFFECT_JUNGLE_HEALING,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .ignoresProtect = TRUE,
        .ignoresSubstitute = TRUE,
        .mirrorMoveBanned = TRUE,
        .healingMove = TRUE,
        //.metronomeBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_QUALITY_DEPENDS_ON_TIMING,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_JungleHealing,
    },

    [MOVE_WICKED_BLOW] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("WICKED BLOW"),
        .description = COMPOUND_STRING(
            "Mastering the Dark style, strikes with a critical hit."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_9 ? 75 : 80,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .alwaysCriticalHit = TRUE,
        .punchingMove = TRUE,
        //.metronomeBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_JAMS_OTHERS_BUT_MISS_ONE_TURN,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_WickedBlow,
    },

    [MOVE_SURGING_STRIKES] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SURGING STRIKES"),
        .description = COMPOUND_STRING(
            "Mastering the Water style, strikes with 3 critical hits."),
        .effect = EFFECT_HIT,
        .power = 25,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .alwaysCriticalHit = TRUE,
        .punchingMove = TRUE,
        .strikeCount = 3,
        //.metronomeBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_SurgingStrikes,
    },

    [MOVE_THUNDER_CAGE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("THUNDER CAGE"),
        .description = COMPOUND_STRING(
            "Traps the foe in a cage of electricity for "BINDING_TURNS" turns."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_ELECTRIC,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WRAP,
        }),
        .contestEffect = CONTEST_EFFECT_DONT_EXCITE_AUDIENCE,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ThunderCage,
    },

    [MOVE_DRAGON_ENERGY] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DRAGON ENERGY"),
        .description = COMPOUND_STRING(
            "The higher the user's HP the more damage caused."),
        .effect = EFFECT_POWER_BASED_ON_USER_HP,
        .power = 150,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        //.metronomeBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_DragonEnergy,
    },

    [MOVE_FREEZING_GLARE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FREEZING GLARE"),
        .description = COMPOUND_STRING(
            "Shoots psychic power from\n"
        #if B_USE_FROSTBITE == TRUE
            "the eyes. May frostbite."),
        #else
            "the eyes. May freeze the foe."),
        #endif
        .power = 90,
        .effect = EFFECT_HIT,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FREEZE_OR_FROSTBITE,
            .chance = 10,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_CUTE,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FreezingGlare,
    },

    [MOVE_FIERY_WRATH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FIERY WRATH"),
        .description = COMPOUND_STRING(
            "An attack fueled by your wrath. May cause flinching."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 20,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_FieryWrath,
    },

    [MOVE_THUNDEROUS_KICK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("THUNDEROUS KICK"),
        .description = COMPOUND_STRING(
            "Uses a lightning-like kick to hit. Lowers foe's DEFENSE."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 100,
        }),
        .contestEffect = CONTEST_EFFECT_HIGHLY_APPEALING,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_ThunderousKick,
    },

    [MOVE_GLACIAL_LANCE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("GLACIAL LANCE"),
        .description = COMPOUND_STRING(
            "Hurls a blizzard-cloaked icicle lance at foes."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_9 ? 120 : 130,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        //.metronomeBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_LAST,
        .contestCategory = CONTEST_CATEGORY_BEAUTY,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_GlacialLance,
    },

    [MOVE_ASTRAL_BARRAGE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ASTRAL BARRAGE"),
        .description = COMPOUND_STRING(
            "Sends a frightful amount of small ghosts at foes."),
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        //.metronomeBanned = TRUE,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_FIRST,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_AstralBarrage,
    },

    [MOVE_EERIE_SPELL] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("EERIE SPELL"),
        .description = COMPOUND_STRING(
            "Attacks with psychic power. Foe's last move has 3 PP cut."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .soundMove = TRUE,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .contestEffect = CONTEST_EFFECT_BETTER_WHEN_LATER,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_EERIE_SPELL,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_EerieSpell,
    },

    [MOVE_DIRE_CLAW] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DIRE CLAW"),
        .description = COMPOUND_STRING(
            "High critical hit chance. May paralyze, poison or drowse."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_9 ? 80 : 60,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DIRE_CLAW,
            .chance = 50,
        }),
        .battleAnimScript = gBattleAnimMove_DireClaw,
    },

    [MOVE_PSYSHIELD_BASH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("PSYSHIELD BASH"),
        .description = COMPOUND_STRING(
            "Hits a foe with psychic energy. May raise DEFENSE."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_PSYCHIC,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_PsyshieldBash,
    },

    [MOVE_POWER_SHIFT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("POWER SHIFT"),
        .description = COMPOUND_STRING(
            "The user swaps its ATTACK and DEFENSE stats."),
        .effect = EFFECT_POWER_TRICK,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.metronomeBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_PowerShift,
},

    [MOVE_STONE_AXE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("STONE AXE"),
        .description = COMPOUND_STRING(
            "High critical hit ratio. Sets Splinters that hurt the foe."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_ROCK,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_STEALTH_ROCK,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_StoneAxe,
    },

    [MOVE_SPRINGTIDE_STORM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SPRINGTIDE STORM"),
        .description = COMPOUND_STRING(
            "Wraps a foe in fierce winds. Varies with the user's form."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_9 ? 100 : 95,
        .type = TYPE_FAIRY,
        .accuracy = 80,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .windMove = TRUE,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_MINUS_1,
            .chance = 30,
        }),
        .battleAnimScript = gBattleAnimMove_SpringtideStorm,
    },

    [MOVE_MYSTICAL_POWER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MYSTICAL POWER"),
        .description = COMPOUND_STRING(
            "A mysterious power strikes, raising the user's SP. ATK."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_PSYCHIC,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_MysticalPower,
    },

    [MOVE_RAGING_FURY] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("RAGING FURY"),
        .description = COMPOUND_STRING(
            "A rampage of 2 to 3 turns that confuses the user."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_9 ? 120 : 90,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_RANDOM,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_THRASH,
            .self = TRUE,
        }),
        .battleAnimScript = gBattleAnimMove_RagingFury,
    },

    [MOVE_WAVE_CRASH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("WAVE CRASH"),
        .description = COMPOUND_STRING(
            "A slam shrouded in water. It also hurts the user."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_9 ? 120 : 75,
        .type = TYPE_WATER,
        .accuracy = 100,
        .recoil = 33,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .skyBattleBanned = B_EXTRAPOLATED_MOVE_FLAGS,
        .battleAnimScript = gBattleAnimMove_WaveCrash,
    },

    [MOVE_CHLOROBLAST] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("CHLOROBLAST"),
        .description = COMPOUND_STRING(
            "A user-hurting blast of amassed chlorophyll."),
        .effect = EFFECT_MAX_HP_50_RECOIL,
        .power = B_UPDATED_MOVE_DATA >= GEN_9 ? 150 : 120,
        .type = TYPE_GRASS,
        .accuracy = 95,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .battleAnimScript = gBattleAnimMove_Chloroblast,
    },

    [MOVE_MOUNTAIN_GALE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MOUNTAIN GALE"),
        .description = COMPOUND_STRING(
            "Giant chunks of ice damage the foe. It may flinch."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_ICE,
        .accuracy = 85,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .battleAnimScript = gBattleAnimMove_MountainGale,
    },

    [MOVE_VICTORY_DANCE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("VICTORY DANCE"),
        .description = COMPOUND_STRING(
            "Dances to raise ATTACK, DEFENSE and SPEED."),
        .effect = EFFECT_VICTORY_DANCE,
        .power = 0,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .danceMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_VictoryDance,
    },

    [MOVE_HEADLONG_RUSH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("HEADLONG RUSH"),
        .description = COMPOUND_STRING(
            "Hits with a full-body tackle. Lowers the users's defenses."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_9 ? 120 : 100,
        .type = TYPE_GROUND,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_SPDEF_DOWN,
            .self = TRUE,
        }),
        .battleAnimScript = gBattleAnimMove_HeadlongRush,
    },

    [MOVE_BARB_BARRAGE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BARB BARRAGE"),
        .description = COMPOUND_STRING(
            "Can poison on impact. Powers up against poisoned foes."),
        .effect = EFFECT_DOUBLE_POWER_ON_ARG_STATUS,
        .power = 60,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_9 ? 10 : 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .argument = { .status = STATUS1_PSN_ANY },
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 50,
        }),
        .battleAnimScript = gBattleAnimMove_BarbBarrage,
    },

    [MOVE_ESPER_WING] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ESPER WING"),
        .description = COMPOUND_STRING(
            "High critical hit ratio. Ups the user's SPEED."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_9 ? 80 : 75,
        .type = TYPE_PSYCHIC,
        .accuracy = B_UPDATED_MOVE_DATA >= GEN_9 ? 100 : 90,
        .criticalHitStage = 1,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_EsperWing,
    },

    [MOVE_BITTER_MALICE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BITTER MALICE"),
        .description = COMPOUND_STRING(
            "A spine-chilling resentment. Lowers the foe's ATTACK."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_9 ? 75 : 60,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_MINUS_1,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_BitterMalice,
    },

    [MOVE_SHELTER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SHELTER"),
        .description = COMPOUND_STRING(
            "The user hardens their skin, sharply raising its DEFENSE."),
        .effect = EFFECT_DEFENSE_UP_2,
        .power = 0,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_Shelter,
    },

    [MOVE_TRIPLE_ARROWS] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TRIPLE ARROWS"),
        .description = COMPOUND_STRING(
            "High critical hit ratio. May lower DEFENSE or flinch."),
        .effect = EFFECT_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_9 ? 90 : 50,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = B_UPDATED_MOVE_DATA >= GEN_9 ? 10 : 15,
        .criticalHitStage = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 50,
        },
        {
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .battleAnimScript = gBattleAnimMove_TripleArrows,
    },

    [MOVE_INFERNAL_PARADE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("INFERNAL PARADE"),
        .description = COMPOUND_STRING(
            "Hurts a foe harder if it has an ailment. May leave a burn."),
        .effect = EFFECT_DOUBLE_POWER_ON_ARG_STATUS,
        .power = 60,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .argument = { .status = STATUS1_ANY },
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 30,
        }),
        .battleAnimScript = gBattleAnimMove_InfernalParade,
    },

    [MOVE_CEASELESS_EDGE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("CEASELESS EDGE"),
        .description = COMPOUND_STRING(
            "High critical hit ratio. Sets Splinters that hurt the foe."),
        .effect = EFFECT_HIT,
        .power = 65,
        .type = TYPE_DARK,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPIKES,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_CeaselessEdge,
    },

    [MOVE_BLEAKWIND_STORM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BLEAKWIND STORM"),
        .description = COMPOUND_STRING(
            "Hits with brutal, cold winds. May lower the foe's SPEED."),
        .effect = EFFECT_RAIN_ALWAYS_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_9 ? 100 : 95,
        .type = TYPE_FLYING,
        .accuracy = 80,
        .pp = B_UPDATED_MOVE_DATA >= GEN_9 ? 10 : 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .windMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 30,
        }),
        .battleAnimScript = gBattleAnimMove_BleakwindStorm,
    },

    [MOVE_WILDBOLT_STORM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("WILDBOLT STORM"),
        .description = COMPOUND_STRING(
            "Hits with a brutal tempest. May inflict paralysis."),
        .effect = EFFECT_RAIN_ALWAYS_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_9 ? 100 : 95,
        .type = TYPE_ELECTRIC,
        .accuracy = 80,
        .pp = B_UPDATED_MOVE_DATA >= GEN_9 ? 10 : 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .windMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 20,
        }),
        .battleAnimScript = gBattleAnimMove_WildboltStorm,
    },

    [MOVE_SANDSEAR_STORM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SANDSEAR STORM"),
        .description = COMPOUND_STRING(
            "Hits with brutally hot sand. May inflict a burn."),
        .effect = EFFECT_RAIN_ALWAYS_HIT,
        .power = B_UPDATED_MOVE_DATA >= GEN_9 ? 100 : 95,
        .type = TYPE_GROUND,
        .accuracy = 80,
        .pp = B_UPDATED_MOVE_DATA >= GEN_9 ? 10 : 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .windMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 20,
        }),
        .battleAnimScript = gBattleAnimMove_SandsearStorm,
    },

    [MOVE_LUNAR_BLESSING] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("LUNAR BLESSING"),
        .description = COMPOUND_STRING(
            "The user heals and cures itself and its ally."),
        .effect = EFFECT_JUNGLE_HEALING,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .healingMove = TRUE,
        .battleAnimScript = gBattleAnimMove_LunarBlessing,
    },

    [MOVE_TAKE_HEART] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TAKE HEART"),
        .description = COMPOUND_STRING(
            "The user lifts its spirits to heal and strengthen itself."),
        .effect = EFFECT_TAKE_HEART,
        .power = 0,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_TakeHeart,
    },

    [MOVE_TERA_BLAST] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TERA BLAST"),
        .description = COMPOUND_STRING(
            "If the user's Terastallized, it hits with its Tera-type."),
        .effect = EFFECT_TERA_BLAST,
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .forcePressure = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_TERA_BLAST,
            .self = TRUE,
        }),
        .battleAnimScript = gBattleAnimMove_TeraBlast,
    },

    [MOVE_SILK_TRAP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SILK TRAP"),
        .description = COMPOUND_STRING(
            "Protects itself, lowering SPEED on contact."),
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 4,
        .category = DAMAGE_CATEGORY_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.metronomeBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_SilkTrap,
    },

    [MOVE_AXE_KICK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("AXE KICK"),
        .description = COMPOUND_STRING(
            "May miss and hurt the kicker. May cause confusion."),
        .effect = EFFECT_RECOIL_IF_MISS,
        .power = 120,
        .type = TYPE_FIGHTING,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 30,
        }),
        .battleAnimScript = gBattleAnimMove_AxeKick,
    },

    [MOVE_LAST_RESPECTS] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("LAST RESPECTS"),
        .description = COMPOUND_STRING(
            "This move deals more damage for each defeated ally."),
        .effect = EFFECT_LAST_RESPECTS,
        .power = 50,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        //.metronomeBanned = TRUE, // Only since it isn't implemented yet
        .battleAnimScript = gBattleAnimMove_LastRespects,
    },

    [MOVE_LUMINA_CRASH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("LUMINA CRASH"),
        .description = COMPOUND_STRING(
            "A mind-affecting light harshly lowers SP. DEF."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_DEF_MINUS_2,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_LuminaCrash,
    },

    [MOVE_ORDER_UP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ORDER UP"),
        .description = COMPOUND_STRING(
            "Boosts a user's stats depending on Tatsugiri."),
        .effect = EFFECT_ORDER_UP,
        .power = 80,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .mirrorMoveBanned = TRUE,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ORDER_UP,
            .self = TRUE,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_OrderUp,
    },

    [MOVE_JET_PUNCH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("JET PUNCH"),
        .description = COMPOUND_STRING(
            "A punch is thrown at blinding speed to strike first."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        //.metronomeBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_JetPunch,
    },

    [MOVE_SPICY_EXTRACT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SPICY EXTRACT"),
        .description = COMPOUND_STRING(
            "Sharply ups target's ATTACK, harshly lowers its DEFENSE."),
        .effect = EFFECT_SPICY_EXTRACT,
        .power = 0,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .magicCoatAffected = TRUE,
        //.metronomeBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_SpicyExtract,
    },

    [MOVE_SPIN_OUT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SPIN OUT"),
        .description = COMPOUND_STRING(
            "Furiously strains its legs. Harshly lowers user's SPEED."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .skyBattleBanned = B_EXTRAPOLATED_MOVE_FLAGS,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_2,
            .self = TRUE,
        }),
        .battleAnimScript = gBattleAnimMove_SpinOut,
    },

    [MOVE_POPULATION_BOMB] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("POPULATION BOMB"),
        .description = COMPOUND_STRING(
            "The user's fellows hit one to ten times in a row."),
        .effect = EFFECT_POPULATION_BOMB,
        .power = 20,
        .type = TYPE_NORMAL,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        //.metronomeBanned = TRUE,
        .strikeCount = 10,
        .battleAnimScript = gBattleAnimMove_PopulationBomb,
    },

    [MOVE_ICE_SPINNER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ICE SPINNER"),
        .description = COMPOUND_STRING(
            "Ice-covered feet hit a foe and destroy the terrain."),
        .effect = EFFECT_HIT_SET_REMOVE_TERRAIN,
        .power = 80,
        .type = TYPE_ICE,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .argument = { .moveProperty = ARG_TRY_REMOVE_TERRAIN_HIT }, // Remove the active field terrain if there is one.
        .skyBattleBanned = B_EXTRAPOLATED_MOVE_FLAGS,
        .battleAnimScript = gBattleAnimMove_IceSpinner,
    },

    [MOVE_GLAIVE_RUSH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("GLAIVE RUSH"),
        .description = COMPOUND_STRING(
            "Foe attacks next turn can't miss and do double damage."),
        .effect = EFFECT_GLAIVE_RUSH,
        .power = 120,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .battleAnimScript = gBattleAnimMove_GlaiveRush,
    },

    [MOVE_REVIVAL_BLESSING] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("REVIVAL BLESSING"),
        .description = COMPOUND_STRING(
            "Revives a fainted party {PKMN} and restores half of its HP."),
        .effect = EFFECT_REVIVAL_BLESSING,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.metronomeBanned = TRUE,
        .healingMove = TRUE,
        .sketchBanned = (B_SKETCH_BANS >= GEN_9),
        .battleAnimScript = gBattleAnimMove_RevivalBlessing,
    },

    [MOVE_SALT_CURE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SALT CURE"),
        .description = COMPOUND_STRING(
            "Hurts foe every turn. Double damage to Steel and Water."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SALT_CURE,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_SaltCure,
    },

    [MOVE_TRIPLE_DIVE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TRIPLE DIVE"),
        .description = COMPOUND_STRING(
            "Hits target with splashes of water 3 times in a row."),
        .effect = EFFECT_HIT,
        .power = 30,
        .type = TYPE_WATER,
        .accuracy = 95,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .strikeCount = 3,
        .battleAnimScript = gBattleAnimMove_TripleDive,
    },

    [MOVE_MORTAL_SPIN] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MORTAL SPIN"),
        .description = COMPOUND_STRING(
            "Erases trap moves and Leech Seed. Poisons adjacent foes."),
        .effect = EFFECT_RAPID_SPIN,
        .power = 30,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS(
        {
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_MortalSpin,
    },

    [MOVE_DOODLE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DOODLE"),
        .description = COMPOUND_STRING(
            "Changes user's and ally's Ability into the target's."),
        .effect = EFFECT_DOODLE,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.metronomeBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_Doodle,
    },

    [MOVE_FILLET_AWAY] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FILLET AWAY"),
        .description = COMPOUND_STRING(
            "Sharply boosts offenses and SPEED by using its own HP."),
        .effect = EFFECT_FILLET_AWAY,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RECOVER_HP },
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.metronomeBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_FilletAway,
    },

    [MOVE_KOWTOW_CLEAVE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("KOWTOW CLEAVE"),
        .description = COMPOUND_STRING(
            "User slashes the foe after kowtowing. It never misses."),
        .effect = EFFECT_HIT,
        .power = 85,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .battleAnimScript = gBattleAnimMove_KowtowCleave,
    },

    [MOVE_FLOWER_TRICK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FLOWER TRICK"),
        .description = COMPOUND_STRING(
            "Rigged bouquet. Always gets a critical hit, never missing."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .alwaysCriticalHit = TRUE,
        .battleAnimScript = gBattleAnimMove_FlowerTrick,
    },

    [MOVE_TORCH_SONG] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TORCH SONG"),
        .description = COMPOUND_STRING(
            "Flames scorch the target. Boosts the user's SP. ATK."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .soundMove = TRUE,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_TorchSong,
    },

    [MOVE_AQUA_STEP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("AQUA STEP"),
        .description = COMPOUND_STRING(
            "Hits with light, fluid dance steps. Ups the user's SPEED."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .danceMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_AquaStep,
    },

    [MOVE_RAGING_BULL] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("RAGING BULL"),
        .description = COMPOUND_STRING(
            "Tackle that breaks barriers. User's form determines type."),
        .effect = EFFECT_RAGING_BULL,
        .power = 90,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        //.metronomeBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_RagingBull,
    },

    [MOVE_MAKE_IT_RAIN] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAKE IT RAIN"),
        .description = COMPOUND_STRING(
            "Lowers the user's SP. ATK. Money is recovered after."),
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PAYDAY,
        },
        {
            .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_1,
            .self = TRUE,
        }),
        .battleAnimScript = gBattleAnimMove_MakeItRain,
    },

    [MOVE_RUINATION] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("RUINATION"),
        .description = COMPOUND_STRING(
            "Summons a ruinous disaster and cuts half the foe's HP."),
        .effect = EFFECT_SUPER_FANG,
        .power = 1,
        .type = TYPE_DARK,
        .accuracy = 90,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        //.metronomeBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_Ruination,
    },

    [MOVE_COLLISION_COURSE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("COLLISION COURSE"),
        .description = COMPOUND_STRING(
            "Prehistoric explosion that's stronger if super effective."),
        .effect = EFFECT_COLLISION_COURSE,
        .power = 100,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        //.metronomeBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_CollisionCourse,
    },

    [MOVE_ELECTRO_DRIFT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ELECTRO DRIFT"),
        .description = COMPOUND_STRING(
            "Futuristic electricity. It's stronger if super effective."),
        .effect = EFFECT_COLLISION_COURSE,
        .power = 100,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .makesContact = TRUE,
        //.metronomeBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_ElectroDrift,
    },

    [MOVE_SHED_TAIL] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SHED TAIL"),
        .description = COMPOUND_STRING(
            "Creates a Substitute for itself before switching out."),
        .effect = EFFECT_SHED_TAIL,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.metronomeBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_ShedTail,
    },

    [MOVE_CHILLY_RECEPTION] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("CHILLY RECEPTION"),
        .description = COMPOUND_STRING(
            "Bad joke summons snowstorm. The user also switches out."),
        .effect = EFFECT_CHILLY_RECEPTION,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.metronomeBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_ChillyReception,
    },

    [MOVE_TIDY_UP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TIDY UP"),
        .description = COMPOUND_STRING(
            "User tidies up hazards and raises its ATTACK and SPEED."),
        .effect = EFFECT_TIDY_UP,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.metronomeBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_TidyUp,
    },

    [MOVE_SNOWSCAPE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SNOWSCAPE"),
        .description = COMPOUND_STRING(
            "Summons a snowstorm that lasts for five turns."),
        .effect = EFFECT_SNOWSCAPE,
        .power = 0,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_ALL_BATTLERS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_SPD_UP_1 },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.metronomeBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_Snowscape,
    },

    [MOVE_POUNCE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("POUNCE"),
        .description = COMPOUND_STRING(
            "The user pounces on the foe, lowering its SPEED."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_BUG,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_Pounce,
    },

    [MOVE_TRAILBLAZE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TRAILBLAZE"),
        .description = COMPOUND_STRING(
            "The user attacks suddenly, raising its SPEED."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_PLUS_1,
            .self = TRUE,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_Trailblaze,
    },

    [MOVE_CHILLING_WATER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("CHILLING WATER"),
        .description = COMPOUND_STRING(
            "A shower with ice-cold water lowers the target's ATTACK."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ATK_MINUS_1,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_ChillingWater,
    },

    [MOVE_HYPER_DRILL] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("HYPER DRILL"),
        .description = COMPOUND_STRING(
            "A spinning pointed part bypasses a foe's Protect."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresProtect = TRUE,
        //.metronomeBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_HyperDrill,
    },

    [MOVE_TWIN_BEAM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TWIN BEAM"),
        .description = COMPOUND_STRING(
            "Mystical eye-beams that hit the target twice in a row."),
        .effect = EFFECT_HIT,
        .power = 40,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .strikeCount = 2,
        //.metronomeBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_TwinBeam,
    },

    [MOVE_RAGE_FIST] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("RAGE FIST"),
        .description = COMPOUND_STRING(
            "The more the user has been hit, the stronger the move."),
        .effect = EFFECT_RAGE_FIST,
        .power = 50,
        .type = TYPE_GHOST,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .punchingMove = TRUE,
        //.metronomeBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_RageFist,
    },

    [MOVE_ARMOR_CANNON] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ARMOR CANNON"),
        .description = COMPOUND_STRING(
            "A strong attack but lowers the defensive stats."),
        .effect = EFFECT_HIT,
        .power = 120,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_SPDEF_DOWN,
            .self = TRUE,
        }),
        .battleAnimScript = gBattleAnimMove_ArmorCannon,
    },

    [MOVE_BITTER_BLADE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BITTER BLADE"),
        .description = COMPOUND_STRING(
            "An attack that absorbs half the damage inflicted."),
        .effect = EFFECT_ABSORB,
        .power = 90,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .argument = { .absorbPercentage = 50 },
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .healingMove = TRUE,
        .battleAnimScript = gBattleAnimMove_BitterBlade,
    },

    [MOVE_DOUBLE_SHOCK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DOUBLE SHOCK"),
        .description = COMPOUND_STRING(
            "Discharges all electricity, losing the Electric type."),
        .effect = EFFECT_FAIL_IF_NOT_ARG_TYPE,
        .power = 120,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        //.metronomeBanned = TRUE,
        .argument = { .type = TYPE_ELECTRIC },
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_REMOVE_ARG_TYPE,
            .self = TRUE,
        }),
        .battleAnimScript = gBattleAnimMove_DoubleShock,
    },

    [MOVE_GIGATON_HAMMER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("GIGATON HAMMER"),
        .description = COMPOUND_STRING(
            "Swings a huge hammer. Can't be used twice in a row."),
        .effect = EFFECT_HIT,
        .power = 160,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .cantUseTwice = TRUE,
        .battleAnimScript = gBattleAnimMove_GigatonHammer,
    },

    [MOVE_COMEUPPANCE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("COMEUPPANCE"),
        .description = COMPOUND_STRING(
            "Retaliates strongly against who last hurt the user."),
        .effect = EFFECT_METAL_BURST,
        .power = 1,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_DEPENDS,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .meFirstBanned = TRUE,
        //.metronomeBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_Comeuppance,
    },

    [MOVE_AQUA_CUTTER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("AQUA CUTTER"),
        .description = COMPOUND_STRING(
            "Pressurized water cut with a high critical-hit ratio."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_WATER,
        .accuracy = 100,
        .criticalHitStage = 1,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .slicingMove = TRUE,
        .battleAnimScript = gBattleAnimMove_AquaCutter,
    },

    [MOVE_BLAZING_TORQUE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BLAZING TORQUE"),
        .description = COMPOUND_STRING("---"),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .mirrorMoveBanned = TRUE,
        .meFirstBanned = TRUE,
        .mimicBanned = TRUE,
        //.metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .sketchBanned = (B_SKETCH_BANS >= GEN_9),
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 30,
        }),
        .battleAnimScript = gBattleAnimMove_BlazingTorque,
    },

    [MOVE_WICKED_TORQUE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("WICKED TORQUE"),
        .description = COMPOUND_STRING("---"),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .mirrorMoveBanned = TRUE,
        .meFirstBanned = TRUE,
        .mimicBanned = TRUE,
        //.metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .sketchBanned = (B_SKETCH_BANS >= GEN_9),
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SLEEP,
            .chance = 10,
        }),
        .battleAnimScript = gBattleAnimMove_WickedTorque,
    },

    [MOVE_NOXIOUS_TORQUE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("NOXIOUS TORQUE"),
        .description = COMPOUND_STRING("---"),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .mirrorMoveBanned = TRUE,
        .meFirstBanned = TRUE,
        .mimicBanned = TRUE,
        //.metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .sketchBanned = (B_SKETCH_BANS >= GEN_9),
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON,
            .chance = 30,
        }),
        .battleAnimScript = gBattleAnimMove_NoxiousTorque,
    },

    [MOVE_COMBAT_TORQUE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("COMBAT TORQUE"),
        .description = COMPOUND_STRING("---"),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .mirrorMoveBanned = TRUE,
        .meFirstBanned = TRUE,
        .mimicBanned = TRUE,
        //.metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .sketchBanned = (B_SKETCH_BANS >= GEN_9),
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 30,
        }),
        .battleAnimScript = gBattleAnimMove_CombatTorque,
    },

    [MOVE_MAGICAL_TORQUE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAGICAL TORQUE"),
        .description = COMPOUND_STRING("---"),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .mirrorMoveBanned = TRUE,
        .meFirstBanned = TRUE,
        .mimicBanned = TRUE,
        //.metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .sleepTalkBanned = TRUE,
        .instructBanned = TRUE,
        .encoreBanned = TRUE,
        .assistBanned = TRUE,
        .sketchBanned = (B_SKETCH_BANS >= GEN_9),
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .chance = 30,
        }),
        .battleAnimScript = gBattleAnimMove_MagicalTorque,
    },

    [MOVE_PSYBLADE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("PSYBLADE"),
        .description = COMPOUND_STRING(
            "This move's power increases when on Electric Terrain."),
        .effect = EFFECT_PSYBLADE,
        .power = 80,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .slicingMove = TRUE,
        .battleAnimScript = gBattleAnimMove_Psyblade,
    },

    [MOVE_HYDRO_STEAM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("HYDRO STEAM"),
        .description = COMPOUND_STRING(
            "This move's power increases under harsh sunlight."),
        .effect = EFFECT_HYDRO_STEAM,
        .power = 80,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .thawsUser = TRUE,
        .battleAnimScript = gBattleAnimMove_HydroSteam,
    },

    [MOVE_BLOOD_MOON] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BLOOD MOON"),
        .description = COMPOUND_STRING(
            "Unleashes the blood moon. Can't be used twice in a row."),
        .effect = EFFECT_HIT,
        .power = 140,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .cantUseTwice = TRUE,
        .battleAnimScript = gBattleAnimMove_BloodMoon,
    },

    [MOVE_MATCHA_GOTCHA] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MATCHA GOTCHA"),
        .description = COMPOUND_STRING(
            "Absorbs half the damage inflicted. May cause a burn."),
        .effect = EFFECT_ABSORB,
        .power = 80,
        .type = TYPE_GRASS,
        .accuracy = 90,
        .pp = 15,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .argument = { .absorbPercentage = 50 },
        .thawsUser = TRUE,
        //.metronomeBanned = TRUE,
        .healingMove = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_BURN,
            .chance = 20,
        }),
        .battleAnimScript = gBattleAnimMove_MatchaGotcha,
    },

    [MOVE_SYRUP_BOMB] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SYRUP BOMB"),
        .description = COMPOUND_STRING(
            "Lowers the foe's speed each turn for 3 turns."),
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_GRASS,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ballisticMove = TRUE,
        //.metronomeBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SYRUP_BOMB,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_SyrupBomb,
    },

    [MOVE_IVY_CUDGEL] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("IVY CUDGEL"),
        .description = COMPOUND_STRING(
            "Type changes with held mask. High critical-hit ratio."),
        .effect = EFFECT_IVY_CUDGEL,
        .power = 100,
        .type = TYPE_GRASS,
        .accuracy = 100,
        .pp = 10,
        .criticalHitStage = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        //.metronomeBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_IvyCudgel,
    },

    [MOVE_ELECTRO_SHOT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ELECTRO SHOT"),
        .description = COMPOUND_STRING(
            "Gathers electricity, then fires a high-voltage shot."),
        .effect = EFFECT_TWO_TURNS_ATTACK,
        .power = 130,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .argument.twoTurnAttack = { .stringId = STRINGID_ELECTROSHOTCHARGING, .status = B_WEATHER_RAIN },
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SP_ATK_PLUS_1,
            .self = TRUE,
            .onChargeTurnOnly = TRUE,
            .sheerForceBoost = SHEER_FORCE_BOOST,
        }),
        .battleAnimScript = gBattleAnimMove_ElectroShot,
    },

    [MOVE_TERA_STARSTORM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TERA STARSTORM"),
        .description = COMPOUND_STRING(
            "In Terapagos's Stellar Form, it hits all foes."),
        .effect = EFFECT_TERA_STARSTORM,
        .power = 120,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .assistBanned = TRUE,
        .copycatBanned = TRUE,
        .mimicBanned = TRUE,
        .sketchBanned = (B_SKETCH_BANS >= GEN_9),
        .battleAnimScript = gBattleAnimMove_TeraStarstorm,
    },

    [MOVE_FICKLE_BEAM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("FICKLE BEAM"),
        .description = COMPOUND_STRING(
            "Shoots a beam of light. Sometimes twice as strong."),
        .effect = EFFECT_FICKLE_BEAM,
        .power = 80,
        .type = TYPE_DRAGON,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .battleAnimScript = gBattleAnimMove_FickleBeam,
    },

    [MOVE_BURNING_BULWARK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BURNING BULWARK"),
        .description = COMPOUND_STRING(
            "Evades attack, and burns the foe if struck."),
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_FIRE,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 4,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_RESET_STATS },
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        //.metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_BurningBulwark,
    },

    [MOVE_THUNDERCLAP] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("THUNDERCLAP"),
        .description = sSuckerPunchDescription,
        .effect = EFFECT_SUCKER_PUNCH,
        .power = 70,
        .type = TYPE_ELECTRIC,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 1,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .battleAnimScript = gBattleAnimMove_Thunderclap,
    },

    [MOVE_MIGHTY_CLEAVE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MIGHTY CLEAVE"),
        .description = sFeintDescription,
        .effect = EFFECT_HIT,
        .power = 95,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .ignoresProtect = TRUE,
        .slicingMove = TRUE,
        .battleAnimScript = gBattleAnimMove_MightyCleave,
    },

    [MOVE_TACHYON_CUTTER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TACHYON CUTTER"),
        .description = COMPOUND_STRING(
            "Launches particle blades at the target. Strikes twice."),
        .effect = EFFECT_HIT,
        .power = 50,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .strikeCount = 2,
        .slicingMove = TRUE,
        .battleAnimScript = gBattleAnimMove_TachyonCutter,
    },

    [MOVE_HARD_PRESS] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("HARD PRESS"),
        .description = sWringOutDescription,
        .effect = EFFECT_POWER_BASED_ON_TARGET_HP,
        .power = 100,
        .type = TYPE_STEEL,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .battleAnimScript = gBattleAnimMove_HardPress,
    },

    [MOVE_DRAGON_CHEER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DRAGON CHEER"),
        .description = COMPOUND_STRING(
            "Increases allies' critical hit ratio, especially if Dragons."),
        .effect = EFFECT_DRAGON_CHEER,
        .power = 0,
        .type = TYPE_DRAGON,
        .accuracy = 0,
        .pp = 15,
        .target = MOVE_TARGET_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .ignoresSubstitute = TRUE,
        .battleAnimScript = gBattleAnimMove_DragonCheer,
    },

    [MOVE_ALLURING_VOICE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ALLURING VOICE"),
        .description = COMPOUND_STRING(
            "Confuses foe if its stats were boosted this turn."),
        .effect = EFFECT_HIT,
        .power = 80,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSION,
            .onlyIfTargetRaisedStats = TRUE,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_AlluringVoice,
    },

    [MOVE_TEMPER_FLARE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TEMPER FLARE"),
        .description = COMPOUND_STRING(
            "A desperation attack. Power doubles if last move failed."),
        .effect = EFFECT_STOMPING_TANTRUM,
        .power = 75,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .battleAnimScript = gBattleAnimMove_TemperFlare,
    },

    [MOVE_SUPERCELL_SLAM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SUPERCELL SLAM"),
        .description = COMPOUND_STRING(
            "An electrified slam. If it misses, the user is hurt."),
        .effect = EFFECT_RECOIL_IF_MISS,
        .power = 100,
        .type = TYPE_ELECTRIC,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .minimizeDoubleDamage = TRUE,
        .battleAnimScript = gBattleAnimMove_SupercellSlam,
    },

    [MOVE_PSYCHIC_NOISE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("PSYCHIC NOISE"),
        .description = COMPOUND_STRING(
            "Unpleasant sound waves that damage and prevent healing."),
        .effect = EFFECT_HIT,
        .power = 75,
        .type = TYPE_PSYCHIC,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .soundMove = TRUE,
        .ignoresSubstitute = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PSYCHIC_NOISE,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_PsychicNoise,
    },

    [MOVE_UPPER_HAND] =
    {
        .effect = EFFECT_UPPER_HAND,
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("UPPER HAND"),
        .description = COMPOUND_STRING(
            "Makes the target flinch if readying a priority move."),
        .power = 65,
        .type = TYPE_FIGHTING,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 3,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_UpperHand,
    },

    [MOVE_MALIGNANT_CHAIN] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MALIGNANT CHAIN"),
        .description = COMPOUND_STRING(
            "A corrosive chain attack that may badly poison."),
        .effect = EFFECT_HIT,
        .power = 100,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_TOXIC,
            .chance = 50,
            .sheerForceBoost = SHEER_FORCE_BOOST,
        }),
        .battleAnimScript = gBattleAnimMove_MalignantChain,
    },

    // Customs
    [MOVE_FIRECRACKER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("FIRECRACKER"),
        .description = COMPOUND_STRING(
            "Launches startling explosives at the foe 2-5 times. Each hit has a small chance to flinch."),
        .effect = EFFECT_MULTI_HIT,
        .power = 15,
        .type = TYPE_FIRE,
        .accuracy = 100,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .argument = TYPE_FIRE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 5,
        }),
        .battleAnimScript = gBattleAnimMove_Firecracker,
    },

    [MOVE_SHELL_SHOCK] =
    {
        .name = COMPOUND_STRING("SHELL SHOCK"),
        .description = COMPOUND_STRING(
            "Spins to attack while safely tucked inside its shell. Raises DEFENSE after hitting."),
        .effect = EFFECT_HIT,
        .power = 70,
        .type = TYPE_ROCK,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .makesContact = TRUE,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_PLUS_1,
            .chance = 100,
        }),
    },

    [MOVE_SANDBLAST] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("SANDBLAST"),
        .description = COMPOUND_STRING(
            "Blasts the foe with abrasive sand that may lower its DEFENSE or accuracy."),
        .effect = EFFECT_HIT,
        .power = 30,
        .type = TYPE_GROUND,
        .accuracy = 95,
        .pp = 20,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ACC_MINUS_1,
            .chance = 30,
        },
        {
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 30,
        }
        ),
        .battleAnimScript = gBattleAnimMove_Sandblast,
    },

    [MOVE_NECTAR_SPRAY] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("NECTAR SPRAY"),
        .description = COMPOUND_STRING(
            "Sprays a sticky nectar at the foe, lowering its SPEED. "),
        .effect = EFFECT_HIT,
        .power = 55,
        .type = TYPE_BUG,
        .accuracy = 95,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPD_MINUS_1,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_NectarSpray,
    },

    [MOVE_STAMPEDE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("STAMPEDE"),
        .description = COMPOUND_STRING(
            "Stampedes towards the foe, trampling and striking it twice. "),
        .effect = EFFECT_HIT,
        .power = 35,
        .type = TYPE_GROUND,
        .accuracy = 90,
        .pp = 30,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .makesContact = TRUE,
        .strikeCount = 2,
        .contestEffect = CONTEST_EFFECT_BETTER_IF_SAME_TYPE,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_Stampede,
    },

    [MOVE_STAGNANT_AIR] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("STAGNANT AIR"),
        .description = COMPOUND_STRING(
            "Fills the air with a foul miasma, inflicting poison on all other Pokémon."),
        .effect = EFFECT_POISON,
        .power = 0,
        .type = TYPE_POISON,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_FOES_AND_ALLY,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .zMove = { .effect = Z_EFFECT_DEF_UP_1 },
        .magicCoatAffected = TRUE,
        .contestEffect = CONTEST_EFFECT_WORSEN_CONDITION_OF_PREV_MONS,
        .contestCategory = CONTEST_CATEGORY_SMART,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_SWEET_SCENT},
        .battleAnimScript = gBattleAnimMove_StagnantAir,
    },

    [MOVE_STORM_SURGE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("STORM SURGE"),
        .description = COMPOUND_STRING(
            "Lunges at the foe at lightning speed. This move always goes first, and always hits if it is raining."),
        .effect = EFFECT_RAIN_ALWAYS_HIT,
        .power = 80,
        .type = TYPE_ELECTRIC,
        .accuracy = 80,
        .pp = 5,
        .target = MOVE_TARGET_SELECTED,
        .priority = 2,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_COOL,
        .contestComboStarterId = 0,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_StormSurge
    },
    [MOVE_EXPLOIT] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("EXPLOIT"),
        .description = COMPOUND_STRING(
            "Exploits the foe's weakpoints to attack, targeting their lower defensive stat to deal damage."),
        .effect = EFFECT_EXPLOIT,
        .power = 70,
        .type = TYPE_DARK,
        .accuracy = 100,
        .pp = 15,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .battleAnimScript = gBattleAnimMove_Exploit,
    },

    [MOVE_HEART_BREAKER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("HEART BREAKER"),
        .description = COMPOUND_STRING(
            "Strikes suddenly after charming the foe into dropping its guard. May cause flinching."),
        .priority = 0,
        .makesContact = TRUE,
        .effect = EFFECT_HIT,
        .power = 60,
        .type = TYPE_FAIRY,
        .accuracy = 100,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FLINCH,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_MONS_SAME_TYPE_APPEAL,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = COMBO_STARTER_FAKE_OUT,
        .contestComboMoves = {0},
        .battleAnimScript = gBattleAnimMove_HeartBreaker,
    },

    [MOVE_GULP_MISSILE] =
    {
        // UNDEXITED, only called by ABILITY_GULP_MISSILE
        .name = COMPOUND_STRING("GULP MISSILE"),
        .description = COMPOUND_STRING(
			"if you can see this something\n"
			"broke. yell at me about it\n"
			"ok cool"),
        .effect = EFFECT_HIT,
        .power = 30,
        .type = TYPE_WATER,
        .accuracy = 100,
        .pp = 100,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GulpMissile,
        .metronomeBanned = TRUE,
        .mirrorMoveBanned = TRUE,
        .sketchBanned = TRUE,
        .assistBanned = TRUE,
        .mimicBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEF_MINUS_1,
            .chance = 100,
        }),
    },

    [MOVE_PROVOKE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("PROVOKE"),
        .description = COMPOUND_STRING(
            "Makes a loud, sudden noise to draw attention. Foes only aim at the user this turn."),
        .effect = EFFECT_FOLLOW_ME,
        .power = 0,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 2,
        .category = DAMAGE_CATEGORY_STATUS,
        .soundMove = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .metronomeBanned = TRUE,
        .copycatBanned = TRUE,
        .assistBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_Provoke,
    },

    [MOVE_MUDSLIDE] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("MUDSLIDE"),
        .description = COMPOUND_STRING(
            "Attacks foes with a viscous torrent of mud. This may lower their accuracy."),
        .effect = EFFECT_HIT,
        .power = 90,
        .type = TYPE_GROUND,
        .accuracy = 85,
        .pp = 10,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .skyBattleBanned = TRUE,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ACC_MINUS_1,
            .chance = 30,
        }),
        .contestEffect = CONTEST_EFFECT_STARTLE_MON_WITH_JUDGES_ATTENTION,
        .contestCategory = CONTEST_CATEGORY_TOUGH,
        .contestComboStarterId = 0,
        .contestComboMoves = {COMBO_STARTER_RAIN_DANCE},
        .battleAnimScript = gBattleAnimMove_MuddyWater,
        .validApprenticeMove = TRUE,
    },

    [MOVE_KINDLING] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("KINDLING"),
        .description = COMPOUND_STRING(
            "Builds a warm fire that heals allies a little for 5 turns. Fire-types are healed more."),
        .effect = EFFECT_KINDLING,
        .power = 0,
        .type = TYPE_FIRE,
        .accuracy = 0,
        .pp = 20,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .validApprenticeMove = TRUE,
        .snatchAffected = TRUE,
        .ignoresProtect = TRUE,
        .mirrorMoveBanned = TRUE,
        .battleAnimScript = gBattleAnimMove_Kindling,
    },

    [MOVE_SPOON_BENDER] =
    {
        // UNDEXITED
        .name = COMPOUND_STRING("PROVOKE"),
        .description = COMPOUND_STRING(
            "Attacks with telekinetic power that can bend metal. Super effective on STEEL types."),
        .effect = EFFECT_SUPER_EFFECTIVE_ON_ARG,
        .power = 65,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .argument = { .type = TYPE_STEEL },
        .battleAnimScript = gBattleAnimMove_SpoonBender,
    },

    // Z-Moves
    [MOVE_BREAKNECK_BLITZ] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BREAKNECK BLITZ"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,    //determined from move type
        .battleAnimScript = gBattleAnimMove_BreakneckBlitz,
    },
    [MOVE_ALL_OUT_PUMMELING] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ALL OUT PUMMELING"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_AllOutPummeling,
    },
    [MOVE_SUPERSONIC_SKYSTRIKE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SUPERSONIC SKYSTRIKE"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_FLYING,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_SupersonicSkystrike,
    },
    [MOVE_ACID_DOWNPOUR] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("ACID DOWNPOUR"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_POISON,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_AcidDownpour,
    },
    [MOVE_TECTONIC_RAGE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TECTONIC RAGE"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_GROUND,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .skyBattleBanned = B_EXTRAPOLATED_MOVE_FLAGS,
        .battleAnimScript = gBattleAnimMove_TectonicRage,
    },
    [MOVE_CONTINENTAL_CRUSH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("CONTINENTAL CRUSH"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_ROCK,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_ContinentalCrush,
    },
    [MOVE_SAVAGE_SPIN_OUT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SAVAGE SPIN OUT"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_SavageSpinOut,
    },
    [MOVE_NEVER_ENDING_NIGHTMARE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("NEVER ENDING NIGHTMARE"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_GHOST,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_NeverEndingNightmare,
    },
    [MOVE_CORKSCREW_CRASH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("CORKSCREW CRASH"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_CorkscrewCrash,
    },
    [MOVE_INFERNO_OVERDRIVE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("INFERNO OVERDRIVE"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_FIRE,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_InfernoOverdrive,
    },
    [MOVE_HYDRO_VORTEX] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("HYDRO VORTEX"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_HydroVortex,
    },
    [MOVE_BLOOM_DOOM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BLOOM DOOM"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_BloomDoom,
    },
    [MOVE_GIGAVOLT_HAVOC] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("GIGAVOLT HAVOC"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GigavoltHavoc,
    },
    [MOVE_SHATTERED_PSYCHE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SHATTERED PSYCHE"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_ShatteredPsyche,
    },
    [MOVE_SUBZERO_SLAMMER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SUBZERO SLAMMER"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_SubzeroSlammer,
    },
    [MOVE_DEVASTATING_DRAKE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("DEVASTATING DRAKE"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_DRAGON,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_DevastatingDrake,
    },
    [MOVE_BLACK_HOLE_ECLIPSE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("BLACK HOLE ECLIPSE"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_BlackHoleEclipse,
    },
    [MOVE_TWINKLE_TACKLE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("TWINKLE TACKLE"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 1,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_TwinkleTackle,
    },
    [MOVE_CATASTROPIKA] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("CATASTROPIKA"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 210,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_Catastropika,
    },
    [MOVE_10000000_VOLT_THUNDERBOLT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("10000000 VOLT THUNDERBOLT"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 195,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .criticalHitStage = 2,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .battleAnimScript = gBattleAnimMove_10000000VoltThunderbolt,
    },
    [MOVE_STOKED_SPARKSURFER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("STOKED SPARKSURFER"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 175,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYSIS,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_StokedSparksurfer,
    },
    [MOVE_EXTREME_EVOBOOST] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("EXTREME EVOBOOST"),
        .description = sNullDescription,
        .effect = EFFECT_EXTREME_EVOBOOST,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_USER,
        .priority = 0,
        .category = DAMAGE_CATEGORY_STATUS,
        .battleAnimScript = gBattleAnimMove_ExtremeEvoboost,
    },
    [MOVE_PULVERIZING_PANCAKE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("PULVERIZING PANCAKE"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 210,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_PulverizingPancake,
    },
    [MOVE_GENESIS_SUPERNOVA] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("GENESIS SUPERNOVA"),
        .description = sNullDescription,
        .effect = EFFECT_HIT_SET_REMOVE_TERRAIN,
        .power = 185,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .argument = { .moveProperty = ARG_SET_PSYCHIC_TERRAIN }, // Set Psychic Terrain. If there's a different field terrain active, overwrite it.
        .battleAnimScript = gBattleAnimMove_GenesisSupernova,
    },
    [MOVE_SINISTER_ARROW_RAID] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SINISTER ARROW RAID"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 180,
        .type = TYPE_GHOST,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_SinisterArrowRaid,
    },
    [MOVE_MALICIOUS_MOONSAULT] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MALICIOUS MOONSAULT"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 180,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_MaliciousMoonsault,
    },
    [MOVE_OCEANIC_OPERETTA] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("OCEANING OPERETTA"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 195,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .battleAnimScript = gBattleAnimMove_OceanicOperetta,
    },
    [MOVE_SPLINTERED_STORMSHARDS] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SPLINTERED STORMSHARDS"),
        .description = sNullDescription,
        .effect = EFFECT_HIT_SET_REMOVE_TERRAIN,
        .power = 190,
        .type = TYPE_ROCK,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .argument = { .moveProperty = ARG_TRY_REMOVE_TERRAIN_HIT },  // Remove the active field terrain if there is one.
        .battleAnimScript = gBattleAnimMove_SplinteredStormshards,
    },
    [MOVE_LETS_SNUGGLE_FOREVER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("LET's Snuggle Forever"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 190,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_LetsSnuggleForever,
    },
    [MOVE_CLANGOROUS_SOULBLAZE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("CLANGOROUS SOULBLAZE"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 185,
        .type = TYPE_DRAGON,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_BOTH,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .soundMove = TRUE,
        .ignoresSubstitute = B_UPDATED_MOVE_FLAGS >= GEN_6,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ALL_STATS_UP,
            .self = TRUE,
            .chance = 100,
        }),
        .battleAnimScript = gBattleAnimMove_ClangorousSoulblaze,
    },
    [MOVE_GUARDIAN_OF_ALOLA] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("GUARDIAN OF ALOLA"),
        .description = sNullDescription,
        .effect = EFFECT_GUARDIAN_OF_ALOLA,
        .power = 1,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .battleAnimScript = gBattleAnimMove_GuardianOfAlola,
    },
    [MOVE_SEARING_SUNRAZE_SMASH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SEARING SUNRAZE SMASH"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 200,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresTargetAbility = TRUE,
        .battleAnimScript = gBattleAnimMove_SearingSunrazeSmash,
    },
    [MOVE_MENACING_MOONRAZE_MAELSTROM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MENACING MOONRAZE MAELSTROM"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 200,
        .type = TYPE_GHOST,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresTargetAbility = TRUE,
        .battleAnimScript = gBattleAnimMove_MenacingMoonrazeMaelstrom,
    },
    [MOVE_LIGHT_THAT_BURNS_THE_SKY] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("LIGHT THAT BURNS THE SKY"),
        .description = sNullDescription,
        .effect = EFFECT_PHOTON_GEYSER,
        .power = 200,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_SPECIAL,
        .ignoresTargetAbility = TRUE,
        .battleAnimScript = gBattleAnimMove_LightThatBurnsTheSky,
    },
    [MOVE_SOUL_STEALING_7_STAR_STRIKE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("SOUL STEALING 7 STAR STRIKE"),
        .description = sNullDescription,
        .effect = EFFECT_HIT,
        .power = 195,
        .type = TYPE_GHOST,
        .accuracy = 0,
        .pp = 1,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_SoulStealing7StarStrike,
    },

    [MOVE_MAX_GUARD] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAX GUARD"),
        .description = sNullDescription,
        .effect = EFFECT_PROTECT,
        .power = 0,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_USER,
        .priority = 4,
        .category = DAMAGE_CATEGORY_STATUS,
        .battleAnimScript = gBattleAnimMove_MaxGuard,
    },

    [MOVE_MAX_FLARE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAX FLARE"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 1,
        .type = TYPE_FIRE,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_MaxFlare,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SUN,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_MAX_FLUTTERBY] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAX FLUTTERBY"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 1,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_MaxFlutterby,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_LOWER_SP_ATK_SIDE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_MAX_LIGHTNING] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAX LIGHTNING"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 1,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_MaxLightning,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_ELECTRIC_TERRAIN,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_MAX_STRIKE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAX STRIKE"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 1,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_MaxStrike,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_LOWER_SPEED_SIDE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_MAX_KNUCKLE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAX KNUCKLE"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 1,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_MaxKnuckle,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RAISE_TEAM_ATTACK,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_MAX_PHANTASM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAX PHANTASM"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 1,
        .type = TYPE_GHOST,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_MaxPhantasm,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_LOWER_DEFENSE_SIDE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_MAX_HAILSTORM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAX HAILSTORM"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 1,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_MaxHailstorm,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_HAIL,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_MAX_OOZE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAX OOZE"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 1,
        .type = TYPE_POISON,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_MaxOoze,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RAISE_TEAM_SP_ATK,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_MAX_GEYSER] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAX GEYSER"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 1,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_MaxGeyser,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RAIN,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_MAX_AIRSTREAM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAX AIRSTREAM"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 1,
        .type = TYPE_FLYING,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_MaxAirstream,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RAISE_TEAM_SPEED,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_MAX_STARFALL] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAX STARFALL"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 1,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_MaxStarfall,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_MISTY_TERRAIN,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_MAX_WYRMWIND] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAX WYRMWIND"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 1,
        .type = TYPE_DRAGON,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_MaxWyrmwind,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_LOWER_ATTACK_SIDE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_MAX_MINDSTORM] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAX MINDSTORM"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 1,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_MaxMindstorm,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PSYCHIC_TERRAIN,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_MAX_ROCKFALL] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAX ROCKFALL"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 1,
        .type = TYPE_ROCK,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_MaxRockfall,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SANDSTORM,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_MAX_QUAKE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAX QUAKE"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 1,
        .type = TYPE_GROUND,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .skyBattleBanned = B_EXTRAPOLATED_MOVE_FLAGS,
        .battleAnimScript = gBattleAnimMove_MaxQuake,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RAISE_TEAM_SP_DEF,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_MAX_DARKNESS] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAX DARKNESS"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 1,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_MaxDarkness,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_LOWER_SP_DEF_SIDE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_MAX_OVERGROWTH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAX OVERGROWTH"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_MaxOvergrowth,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_GRASSY_TERRAIN,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_MAX_STEELSPIKE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("MAX STEELSPIKE"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_MaxSteelspike,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RAISE_TEAM_DEFENSE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_VINE_LASH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX VINE LASH"),
        .description = sNullDescription,    //ANIM TODO
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxVineLash,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_VINE_LASH,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_WILDFIRE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX WILDFIRE"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_FIRE,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxWildfire,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_WILDFIRE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_CANNONADE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX CANONADE"),
        .description = sNullDescription,    //ANIM TODO
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxCannonade,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CANNONADE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_BEFUDDLE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX BEFUDDLE"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_BUG,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxBefuddle,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_EFFECT_SPORE_SIDE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_VOLT_CRASH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX VOLT CRASH"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxVoltCrash,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PARALYZE_SIDE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_GOLD_RUSH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX GOLD RUSH"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxGoldRush,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSE_PAY_DAY_SIDE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_CHI_STRIKE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX CHI STRIKE"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_FIGHTING,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxChiStrike,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CRIT_PLUS_SIDE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_TERROR] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX TERROR"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_GHOST,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxTerror,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_PREVENT_ESCAPE_SIDE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_FOAM_BURST] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX FOAM BURST"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxFoamBurst,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_LOWER_SPEED_2_SIDE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_RESONANCE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX RESONANCE"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_ICE,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxResonance,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_AURORA_VEIL,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_CUDDLE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX CUDDLE"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxCuddle,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_INFATUATE_SIDE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_REPLENISH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX REPLENISH"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_NORMAL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxReplenish,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_RECYCLE_BERRIES,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_MALODOR] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX MALODOR"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_POISON,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxMalodor,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON_SIDE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_MELTDOWN] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX MELTDOWN"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxMeltdown,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_TORMENT_SIDE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_DRUM_SOLO] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX DRUM SOLO"),
        .description = sNullDescription,    //ANIM TODO
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresTargetAbility = TRUE,
        .battleAnimScript = gBattleAnimMove_GMaxDrumSolo,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FIXED_POWER,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_FIREBALL] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX FIREBALL"),
        .description = sNullDescription,    //ANIM TODO
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_FIRE,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresTargetAbility = TRUE,
        .battleAnimScript = gBattleAnimMove_GMaxFireball,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FIXED_POWER,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_HYDROSNIPE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX HYDROSNIPE"),
        .description = sNullDescription,    //ANIM TODO
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresTargetAbility = TRUE,
        .battleAnimScript = gBattleAnimMove_GMaxHydrosnipe,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FIXED_POWER,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_WIND_RAGE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX WIND RAGE"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_FLYING,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxWindRage,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_DEFOG,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_GRAVITAS] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX GRAVITAS"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_PSYCHIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxGravitas,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_GRAVITY,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_STONESURGE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX STONESURGE"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxStonesurge,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_STEALTH_ROCK,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_VOLCALITH] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX VOLCALITH"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_ROCK,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxVolcalith,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_VOLCALITH,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_TARTNESS] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX TARTNESS"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxTartness,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_LOWER_EVASIVENESS_SIDE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_SWEETNESS] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX SWEETNESS"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_GRASS,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxSweetness,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_AROMATHERAPY,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_SANDBLAST] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX SANDBLAST"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_GROUND,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxSandblast,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SANDBLAST_SIDE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_STUN_SHOCK] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX STUN SHOCK"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_ELECTRIC,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxStunShock,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_POISON_PARALYZE_SIDE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_CENTIFERNO] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX CENTIFERNO"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_FIRE,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxCentiferno,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_FIRE_SPIN_SIDE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_SMITE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX SMITE"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxSmite,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_CONFUSE_SIDE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },


    [MOVE_G_MAX_SNOOZE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX SNOOZE"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxSnooze,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_YAWN_FOE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_FINALE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX FINALE"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_FAIRY,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxFinale,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_HEAL_TEAM,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_STEELSURGE] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX STEELSURGE"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_STEEL,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxSteelsurge,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_STEELSURGE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_DEPLETION] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX DEPLETION"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_DRAGON,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .battleAnimScript = gBattleAnimMove_GMaxDepletion,
        .additionalEffects = ADDITIONAL_EFFECTS({
            .moveEffect = MOVE_EFFECT_SPITE,
            .chance = 100,
            .sheerForceBoost = SHEER_FORCE_NO_BOOST,
        }),
    },

    [MOVE_G_MAX_ONE_BLOW] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX ONE BLOW"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_DARK,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .battleAnimScript = gBattleAnimMove_GMaxOneBlow,
    },

    [MOVE_G_MAX_RAPID_FLOW] =
    {
        .metronomeBanned = TRUE, // DEXITED
        .name = COMPOUND_STRING("G-MAX RAPID FLOW"),
        .description = sNullDescription,
        .effect = EFFECT_MAX_MOVE,
        .power = 10,
        .type = TYPE_WATER,
        .accuracy = 0,
        .pp = 10,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .category = DAMAGE_CATEGORY_PHYSICAL,
        .ignoresProtect = TRUE,
        .battleAnimScript = gBattleAnimMove_GMaxRapidFlow,
    },
};
