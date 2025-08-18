#ifdef __INTELLISENSE__
const struct SpeciesInfo gSpeciesInfoRealmons[] =
{
#endif
    [SPECIES_BUDEW] =
    {
        .baseHP        = 40,
        .baseAttack    = 30,
        .baseDefense   = 35,
        .baseSpeed     = 55,
        .baseSpAttack  = 50,
        .baseSpDefense = 70,
        .types = MON_TYPES(TYPE_GRASS, TYPE_POISON),
        .catchRate = 255,
        .expYield = 56,
        .itemRare = ITEM_POISON_BARB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_NATURAL_CURE, ABILITY_POISON_POINT, ABILITY_LEAF_GUARD },
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = TRUE,
        .speciesName = _("BUDEW"),
        .cryId = CRY_BUDEW,
        .natDexNum = NATIONAL_DEX_BUDEW,
        .categoryName = _("BUD"),
        .height = 2,
        .weight = 12,
        .description = COMPOUND_STRING(
            "Its bud closes in winter to endure the cold.\n"
            "When spring comes, its bud opens again and\n"
            "releases pollen that has the unfortunate\n"
            "side-effect of aggravating seasonal allergies.\n"
            "It lives on the shore of clean ponds."),
        .pokemonScale = 682,
        .pokemonOffset = 24,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Budew,
        .frontPicSize = MON_COORDS_SIZE(32, 40),
        .frontPicYOffset = 14,
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(0, 30),
            ANIMCMD_FRAME(1, 30),
            ANIMCMD_FRAME(0, 20),
        ),
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE_SLOW,
        .backPic = gMonBackPic_Budew,
        .backPicSize = MON_COORDS_SIZE(40, 56),
        .backPicYOffset = 8,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_SMALL,
        .palette = gMonPalette_Budew,
        .shinyPalette = gMonShinyPalette_Budew,
        .iconSprite = gMonIcon_Budew,
        .iconPalIndex = 1,
        SHADOW(-3, 0, SHADOW_SIZE_S)
        FOOTPRINT(Budew)
        .levelUpLearnset = sBudewLevelUpLearnset,
        .teachableLearnset = sBudewTeachableLearnset,
        .eggMoveLearnset = sBudewEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 19, SPECIES_ROSELIA}),
    },

    [SPECIES_ROSELIA] =
    {
        .baseHP        = 50,
        .baseAttack    = 60,
        .baseDefense   = 45,
        .baseSpeed     = 65,
        .baseSpAttack  = 100,
        .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_GRASS, TYPE_POISON),
        .catchRate = 150,
        .expYield = 140,
        .itemRare = ITEM_POISON_BARB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FAIRY, EGG_GROUP_GRASS),
        .abilities = { ABILITY_NATURAL_CURE, ABILITY_POISON_POINT, ABILITY_LEAF_GUARD },
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = TRUE,
        .speciesName = _("ROSELIA"),
        .cryId = CRY_ROSELIA,
        .natDexNum = NATIONAL_DEX_ROSELIA,
        .categoryName = _("THORN"),
        .height = 3,
        .weight = 20,
        .description = COMPOUND_STRING(
            "ROSELIA shoots sharp, poisonous thorns at\n"
            "anything that dares to try and steal the\n"
            "flowers that adorn its arms. It emits a\n"
            "soothing aroma that calms living things nearby.\n"
            "Healthier ROSELIA have a stronger aroma."),
        .pokemonScale = 677,
        .pokemonOffset = 20,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Roselia,
        .frontPicSize = MON_COORDS_SIZE(56, 48),
        .frontPicYOffset = 8,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE_SLOW,
        .backPic = gMonBackPic_Roselia,
        .backPicSize =MON_COORDS_SIZE(64, 48),
        .backPicYOffset = 8,
        .backAnimId = BACK_ANIM_SHAKE_GLOW_GREEN,
        .palette = gMonPalette_Roselia,
        .shinyPalette = gMonShinyPalette_Roselia,
        .iconSprite = gMonIcon_Roselia,
        .iconPalIndex = 0,
        SHADOW(-2, 3, SHADOW_SIZE_S)
        FOOTPRINT(Roselia)
        .levelUpLearnset = sRoseliaLevelUpLearnset,
        .teachableLearnset = sRoseliaTeachableLearnset,
        .eggMoveLearnset = sRoseliaEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_LEAF_STONE, SPECIES_ROSERADE}),
    },

    [SPECIES_ROSERADE] =
    {
        .baseHP        = 60,
        .baseAttack    = 70,
        .baseDefense   = 65,
        .baseSpeed     = 90,
        .baseSpAttack  = 125,
        .baseSpDefense = 105,
        .types = MON_TYPES(TYPE_GRASS, TYPE_POISON),
        .catchRate = 75,
        .expYield = 232,
        .itemRare = ITEM_POISON_BARB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FAIRY, EGG_GROUP_GRASS),
        .abilities = { ABILITY_NATURAL_CURE, ABILITY_POISON_POINT, ABILITY_LEAF_GUARD },
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = TRUE,
        .speciesName = _("ROSERADE"),
        .cryId = CRY_ROSERADE,
        .natDexNum = NATIONAL_DEX_ROSERADE,
        .categoryName = _("BOUQUET"),
        .height = 9,
        .weight = 145,
        .description = COMPOUND_STRING(
            "It attracts prey with a sweet aroma. When the\n"
            "prey is cornered, ROSERADE moves with poise and\n"
            "grace as it mercilessly lashes them with the\n"
            "poisonous, thorny whips concealed within the\n"
            "bouquets on its hands."),
        .pokemonScale = 338,
        .pokemonOffset = 10,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Roserade,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimId = ANIM_H_VIBRATE,
        .backPic = gMonBackPic_Roserade,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 10,
        .backAnimId = BACK_ANIM_SHRINK_GROW_VIBRATE,
        .palette = gMonPalette_Roserade,
        .shinyPalette = gMonShinyPalette_Roserade,
        .iconSprite = gMonIcon_Roserade,
        .iconPalIndex = 0,
        SHADOW(0, 6, SHADOW_SIZE_S)
        FOOTPRINT(Roserade)
        .levelUpLearnset = sRoseradeLevelUpLearnset,
        .teachableLearnset = sRoseradeTeachableLearnset,
    },
#ifdef __INTELLISENSE__
};
#endif