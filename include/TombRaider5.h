/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: t; c-basic-offset: 3 -*- */
/*================================================================
 *
 * Project : OpenRaider
 * Author  : Mongoose
 * Website : http://www.westga.edu/~stu7440/
 * Email   : stu7440@westga.edu
 * Object  :
 * License : GPL, also (C) 2002 Mongoose
 * Comments:
 *
 *-- History ------------------------------------------------
 *
 * 2002.04.04:
 * Mongoose - Created, based on work by ? ( one of the TRE guys )
 ================================================================*/

#ifndef _TOMBRAIDER5_H_
#define _TOMBRAIDER5_H_

typedef enum
{
		TR4_OBJ_LARA = 0,
		TR4_OBJ_PISTOLS_ANIM = 1,
		TR4_OBJ_UZI_ANIM = 2,
		TR4_OBJ_SHOTGUN_ANIM = 3,
		TR4_OBJ_CROSSBOW_ANIM = 4,
		TR4_OBJ_GRENADE_GUN_ANIM = 5,
		TR4_OBJ_SIXSHOOTER_ANIM = 6,
		TR4_OBJ_FLARE_ANIM = 7,
		TR4_OBJ_LARA_SKIN = 8,
		TR4_OBJ_LARA_SKIN_JOINTS = 9,
		TR4_OBJ_LARA_SCREAM = 10,
		TR4_OBJ_LARA_CROSSBOW_LASER = 11,
		TR4_OBJ_LARA_REVOLVER_LASER = 12,
		TR4_OBJ_LARA_HOLSTERS = 13,
		TR4_OBJ_LARA_HOLSTERS_PISTOLS = 14,
		TR4_OBJ_LARA_HOLSTERS_UZIS = 15,
		TR4_OBJ_LARA_HOLSTERS_SIXSHOOTER = 16,
		TR4_OBJ_LARA_SPEECH_HEAD1 = 17,
		TR4_OBJ_LARA_SPEECH_HEAD2 = 18,
		TR4_OBJ_LARA_SPEECH_HEAD3 = 19,
		TR4_OBJ_LARA_SPEECH_HEAD4 = 20,
		TR4_OBJ_ACTOR1_SPEECH_HEAD1 = 21,
		TR4_OBJ_ACTOR1_SPEECH_HEAD2 = 22,
		TR4_OBJ_ACTOR2_SPEECH_HEAD1 = 23,
		TR4_OBJ_ACTOR2_SPEECH_HEAD2 = 24,
		TR4_OBJ_LARA_WATER_MESH = 25,
		TR4_OBJ_LARA_PETROL_MESH = 26,
		TR4_OBJ_LARA_DIRT_MESH = 27,
		TR4_OBJ_CROWBAR_ANIM = 28,
		TR4_OBJ_TORCH_ANIM = 29,
		TR4_OBJ_HAIR = 30,
		TR4_OBJ_MOTORBIKE = 31,
		TR4_OBJ_JEEP = 32,
		TR4_OBJ_VEHICLE_EXTRA = 33,
		TR4_OBJ_ENEMY_JEEP = 34,
		TR4_OBJ_SKELETON = 35,
		TR4_OBJ_SKELETON_MIP = 36,
		TR4_OBJ_GUIDE = 37,
		TR4_OBJ_GUIDE_MIP = 38,
		TR4_OBJ_VON_CROY = 39,
		TR4_OBJ_VON_CROY_MIP = 40,
		TR4_OBJ_BADDY_1 = 41,
		TR4_OBJ_BADDY_1_MIP = 42,
		TR4_OBJ_BADDY_2 = 43,
		TR4_OBJ_BADDY_2_MIP = 44,
		TR4_OBJ_SETHA = 45,
		TR4_OBJ_SETHA_MIP = 46,
		TR4_OBJ_MUMMY = 47,
		TR4_OBJ_MUMMY_MIP = 48,
		TR4_OBJ_SPHINX = 49,
		TR4_OBJ_SPHINX_MIP = 50,
		TR4_OBJ_CROCODILE = 51,
		TR4_OBJ_CROCODILE_MIP = 52,
		TR4_OBJ_HORSEMAN = 53,
		TR4_OBJ_HORSEMAN_MIP = 54,
		TR4_OBJ_SCORPION = 55,
		TR4_OBJ_SCORPION_MIP = 56,
		TR4_OBJ_JEAN_YVES = 57,
		TR4_OBJ_JEAN_YVES_MIP = 58,
		TR4_OBJ_TROOPS = 59,
		TR4_OBJ_TROOPS_MIP = 60,
		TR4_OBJ_KNIGHTS_TEMPLAR = 61,
		TR4_OBJ_KNIGHTS_TEMPLAR_MIP = 62,
		TR4_OBJ_MUTANT = 63,
		TR4_OBJ_MUTANT_MIP = 64,
		TR4_OBJ_HORSE = 65,
		TR4_OBJ_HORSE_MIP = 66,
		TR4_OBJ_BABOON_NORMAL = 67,
		TR4_OBJ_BABOON_NORMAL_MIP = 68,
		TR4_OBJ_BABOON_INV = 69,
		TR4_OBJ_BABOON_INV_MIP = 70,
		TR4_OBJ_BABOON_SILENT = 71,
		TR4_OBJ_BABOON_SILENT_MIP = 72,
		TR4_OBJ_WILD_BOAR = 73,
		TR4_OBJ_WILD_BOAR_MIP = 74,
		TR4_OBJ_HARPY = 75,
		TR4_OBJ_HARPY_MIP = 76,
		TR4_OBJ_DEMIGOD1 = 77,
		TR4_OBJ_DEMIGOD1_MIP = 78,
		TR4_OBJ_DEMIGOD2 = 79,
		TR4_OBJ_DEMIGOD2_MIP = 80,
		TR4_OBJ_DEMIGOD3 = 81,
		TR4_OBJ_DEMIGOD3_MIP = 82,
		TR4_OBJ_LITTLE_BEETLE = 83,
		TR4_OBJ_BIG_BEETLE = 84,
		TR4_OBJ_BIG_BEETLE_MIP = 85,
		TR4_OBJ_WRAITH1 = 86,
		TR4_OBJ_WRAITH2 = 87,
		TR4_OBJ_WRAITH3 = 88,
		TR4_OBJ_WRAITH4 = 89,
		TR4_OBJ_BAT = 90,
		TR4_OBJ_DOG = 91,
		TR4_OBJ_DOG_MIP = 92,
		TR4_OBJ_HAMMERHEAD = 93,
		TR4_OBJ_HAMMERHEAD_MIP = 94,
		TR4_OBJ_SAS = 95,
		TR4_OBJ_SAS_MIP = 96,
		TR4_OBJ_SAS_DYING = 97,
		TR4_OBJ_SAS_DYING_MIP = 98,
		TR4_OBJ_SAS_CAPTAIN = 99,
		TR4_OBJ_SAS_CAPTAIN_MIP = 100,
		TR4_OBJ_SAS_DRAG_BLOKE = 101,
		TR4_OBJ_AHMET = 102,
		TR4_OBJ_AHMET_MIP = 103,
		TR4_OBJ_LARA_DOUBLE = 104,
		TR4_OBJ_LARA_DOUBLE_MIP = 105,
		TR4_OBJ_SMALL_SCORPION = 106,
		TR4_OBJ_FISH = 107,
		TR4_OBJ_GAME_PIECE1 = 108,
		TR4_OBJ_GAME_PIECE2 = 109,
		TR4_OBJ_GAME_PIECE3 = 110,
		TR4_OBJ_ENEMY_PIECE = 111,
		TR4_OBJ_WHEEL_OF_FORTUNE = 112,
		TR4_OBJ_SCALES = 113,
		TR4_OBJ_DARTS = 114,
		TR4_OBJ_DART_EMITTER = 115,
		TR4_OBJ_HOMING_DART_EMITTER = 116,
		TR4_OBJ_FALLING_CEILING = 117,
		TR4_OBJ_FALLING_BLOCK = 118,
		TR4_OBJ_FALLING_BLOCK2 = 119,
		TR4_OBJ_SMASHABLE_BIKE_WALL = 120,
		TR4_OBJ_SMASHABLE_BIKE_FLOOR = 121,
		TR4_OBJ_TRAPDOOR1 = 122,
		TR4_OBJ_TRAPDOOR2 = 123,
		TR4_OBJ_TRAPDOOR3 = 124,
		TR4_OBJ_FLOOR_TRAPDOOR1 = 125,
		TR4_OBJ_FLOOR_TRAPDOOR2 = 126,
		TR4_OBJ_CEILING_TRAPDOOR1 = 127,
		TR4_OBJ_CEILING_TRAPDOOR2 = 128,
		TR4_OBJ_SCALING_TRAPDOOR = 129,
		TR4_OBJ_ROLLINGBALL = 130,
		TR4_OBJ_SPIKEY_FLOOR = 131,
		TR4_OBJ_TEETH_SPIKES = 132,
		TR4_OBJ_JOBY_SPIKES = 133,
		TR4_OBJ_SLICER_DICER = 134,
		TR4_OBJ_CHAIN = 135,
		TR4_OBJ_PLOUGH = 136,
		TR4_OBJ_STARGATE = 137,
		TR4_OBJ_HAMMER = 138,
		TR4_OBJ_BURNING_FLOOR = 139,
		TR4_OBJ_COG = 140,
		TR4_OBJ_SPIKEBALL = 141,
		TR4_OBJ_FLAME = 142,
		TR4_OBJ_FLAME_EMITTER = 143,
		TR4_OBJ_FLAME_EMITTER2 = 144,
		TR4_OBJ_FLAME_EMITTER3 = 145,
		TR4_OBJ_ROPE = 146,
		TR4_OBJ_FIREROPE = 147,
		TR4_OBJ_POLEROPE = 148,
		TR4_OBJ_ONEBLOCK_PLATFORM = 149,
		TR4_OBJ_TWOBLOCK_PLATFORM = 150,
		TR4_OBJ_RAISING_BLOCK1 = 151,
		TR4_OBJ_RAISING_BLOCK2 = 152,
		TR4_OBJ_EXPANDING_PLATFORM = 153,
		TR4_OBJ_SQUISHY_BLOCK1 = 154,
		TR4_OBJ_SQUISHY_BLOCK2 = 155,
		TR4_OBJ_PUSHABLE_OBJECT1 = 156,
		TR4_OBJ_PUSHABLE_OBJECT2 = 157,
		TR4_OBJ_PUSHABLE_OBJECT3 = 158,
		TR4_OBJ_PUSHABLE_OBJECT4 = 159,
		TR4_OBJ_PUSHABLE_OBJECT5 = 160,
		TR4_OBJ_TRIPWIRE = 161,
		TR4_OBJ_SENTRY_GUN = 162,
		TR4_OBJ_MINE = 163,
		TR4_OBJ_MAPPER = 164,
		TR4_OBJ_OBELISK = 165,
		TR4_OBJ_FLOOR_4BLADE = 166,
		TR4_OBJ_ROOF_4BLADE = 167,
		TR4_OBJ_BIRD_BLADE = 168,
		TR4_OBJ_CATWALK_BLADE = 169,
		TR4_OBJ_MOVING_BLADE = 170,
		TR4_OBJ_PLINTH_BLADE = 171,
		TR4_OBJ_SETH_BLADE = 172,
		TR4_OBJ_LIGHTNING_CONDUCTOR = 173,
		TR4_OBJ_ELEMENT_PUZZLE = 174,
		TR4_OBJ_PUZZLE_ITEM1 = 175,
		TR4_OBJ_PUZZLE_ITEM2 = 176,
		TR4_OBJ_PUZZLE_ITEM3 = 177,
		TR4_OBJ_PUZZLE_ITEM4 = 178,
		TR4_OBJ_PUZZLE_ITEM5 = 179,
		TR4_OBJ_PUZZLE_ITEM6 = 180,
		TR4_OBJ_PUZZLE_ITEM7 = 181,
		TR4_OBJ_PUZZLE_ITEM8 = 182,
		TR4_OBJ_PUZZLE_ITEM9 = 183,
		TR4_OBJ_PUZZLE_ITEM10 = 184,
		TR4_OBJ_PUZZLE_ITEM11 = 185,
		TR4_OBJ_PUZZLE_ITEM12 = 186,
		TR4_OBJ_PUZZLE_ITEM1_COMBO1 = 187,
		TR4_OBJ_PUZZLE_ITEM1_COMBO2 = 188,
		TR4_OBJ_PUZZLE_ITEM2_COMBO1 = 189,
		TR4_OBJ_PUZZLE_ITEM2_COMBO2 = 190,
		TR4_OBJ_PUZZLE_ITEM3_COMBO1 = 191,
		TR4_OBJ_PUZZLE_ITEM3_COMBO2 = 192,
		TR4_OBJ_PUZZLE_ITEM4_COMBO1 = 193,
		TR4_OBJ_PUZZLE_ITEM4_COMBO2 = 194,
		TR4_OBJ_PUZZLE_ITEM5_COMBO1 = 195,
		TR4_OBJ_PUZZLE_ITEM5_COMBO2 = 196,
		TR4_OBJ_PUZZLE_ITEM6_COMBO1 = 197,
		TR4_OBJ_PUZZLE_ITEM6_COMBO2 = 198,
		TR4_OBJ_PUZZLE_ITEM7_COMBO1 = 199,
		TR4_OBJ_PUZZLE_ITEM7_COMBO2 = 200,
		TR4_OBJ_PUZZLE_ITEM8_COMBO1 = 201,
		TR4_OBJ_PUZZLE_ITEM8_COMBO2 = 202,
		TR4_OBJ_KEY_ITEM1 = 203,
		TR4_OBJ_KEY_ITEM2 = 204,
		TR4_OBJ_KEY_ITEM3 = 205,
		TR4_OBJ_KEY_ITEM4 = 206,
		TR4_OBJ_KEY_ITEM5 = 207,
		TR4_OBJ_KEY_ITEM6 = 208,
		TR4_OBJ_KEY_ITEM7 = 209,
		TR4_OBJ_KEY_ITEM8 = 210,
		TR4_OBJ_KEY_ITEM9 = 211,
		TR4_OBJ_KEY_ITEM10 = 212,
		TR4_OBJ_KEY_ITEM11 = 213,
		TR4_OBJ_KEY_ITEM12 = 214,
		TR4_OBJ_KEY_ITEM1_COMBO1 = 215,
		TR4_OBJ_KEY_ITEM1_COMBO2 = 216,
		TR4_OBJ_KEY_ITEM2_COMBO1 = 217,
		TR4_OBJ_KEY_ITEM2_COMBO2 = 218,
		TR4_OBJ_KEY_ITEM3_COMBO1 = 219,
		TR4_OBJ_KEY_ITEM3_COMBO2 = 220,
		TR4_OBJ_KEY_ITEM4_COMBO1 = 221,
		TR4_OBJ_KEY_ITEM4_COMBO2 = 222,
		TR4_OBJ_KEY_ITEM5_COMBO1 = 223,
		TR4_OBJ_KEY_ITEM5_COMBO2 = 224,
		TR4_OBJ_KEY_ITEM6_COMBO1 = 225,
		TR4_OBJ_KEY_ITEM6_COMBO2 = 226,
		TR4_OBJ_KEY_ITEM7_COMBO1 = 227,
		TR4_OBJ_KEY_ITEM7_COMBO2 = 228,
		TR4_OBJ_KEY_ITEM8_COMBO1 = 229,
		TR4_OBJ_KEY_ITEM8_COMBO2 = 230,
		TR4_OBJ_PICKUP_ITEM1 = 231,
		TR4_OBJ_PICKUP_ITEM2 = 232,
		TR4_OBJ_PICKUP_ITEM3 = 233,
		TR4_OBJ_PICKUP_ITEM4 = 234,
		TR4_OBJ_PICKUP_ITEM1_COMBO1 = 235,
		TR4_OBJ_PICKUP_ITEM1_COMBO2 = 236,
		TR4_OBJ_PICKUP_ITEM2_COMBO1 = 237,
		TR4_OBJ_PICKUP_ITEM2_COMBO2 = 238,
		TR4_OBJ_PICKUP_ITEM3_COMBO1 = 239,
		TR4_OBJ_PICKUP_ITEM3_COMBO2 = 240,
		TR4_OBJ_PICKUP_ITEM4_COMBO1 = 241,
		TR4_OBJ_PICKUP_ITEM4_COMBO2 = 242,
		TR4_OBJ_EXAMINE1 = 243,
		TR4_OBJ_EXAMINE2 = 244,
		TR4_OBJ_EXAMINE3 = 245,
		TR4_OBJ_CROWBAR_ITEM = 246,
		TR4_OBJ_BURNING_TORCH_ITEM = 247,
		TR4_OBJ_CLOCKWORK_BEETLE = 248,
		TR4_OBJ_CLOCKWORK_BEETLE_COMBO1 = 249,
		TR4_OBJ_CLOCKWORK_BEETLE_COMBO2 = 250,
		TR4_OBJ_MINE_DETECTOR = 251,
		TR4_OBJ_QUEST_ITEM1 = 252,
		TR4_OBJ_QUEST_ITEM2 = 253,
		TR4_OBJ_QUEST_ITEM3 = 254,
		TR4_OBJ_QUEST_ITEM4 = 255,
		TR4_OBJ_QUEST_ITEM5 = 256,
		TR4_OBJ_QUEST_ITEM6 = 257,
		TR4_OBJ_MAP = 258,
		TR4_OBJ_SECRET_MAP = 259,
		TR4_OBJ_PUZZLE_HOLE1 = 260,
		TR4_OBJ_PUZZLE_HOLE2 = 261,
		TR4_OBJ_PUZZLE_HOLE3 = 262,
		TR4_OBJ_PUZZLE_HOLE4 = 263,
		TR4_OBJ_PUZZLE_HOLE5 = 264,
		TR4_OBJ_PUZZLE_HOLE6 = 265,
		TR4_OBJ_PUZZLE_HOLE7 = 266,
		TR4_OBJ_PUZZLE_HOLE8 = 267,
		TR4_OBJ_PUZZLE_HOLE9 = 268,
		TR4_OBJ_PUZZLE_HOLE10 = 269,
		TR4_OBJ_PUZZLE_HOLE11 = 270,
		TR4_OBJ_PUZZLE_HOLE12 = 271,
		TR4_OBJ_PUZZLE_DONE1 = 272,
		TR4_OBJ_PUZZLE_DONE2 = 273,
		TR4_OBJ_PUZZLE_DONE3 = 274,
		TR4_OBJ_PUZZLE_DONE4 = 275,
		TR4_OBJ_PUZZLE_DONE5 = 276,
		TR4_OBJ_PUZZLE_DONE6 = 277,
		TR4_OBJ_PUZZLE_DONE7 = 278,
		TR4_OBJ_PUZZLE_DONE8 = 279,
		TR4_OBJ_PUZZLE_DONE9 = 280,
		TR4_OBJ_PUZZLE_DONE10 = 281,
		TR4_OBJ_PUZZLE_DONE11 = 282,
		TR4_OBJ_PUZZLE_DONE12 = 283,
		TR4_OBJ_KEY_HOLE1 = 284,
		TR4_OBJ_KEY_HOLE2 = 285,
		TR4_OBJ_KEY_HOLE3 = 286,
		TR4_OBJ_KEY_HOLE4 = 287,
		TR4_OBJ_KEY_HOLE5 = 288,
		TR4_OBJ_KEY_HOLE6 = 289,
		TR4_OBJ_KEY_HOLE7 = 290,
		TR4_OBJ_KEY_HOLE8 = 291,
		TR4_OBJ_KEY_HOLE9 = 292,
		TR4_OBJ_KEY_HOLE10 = 293,
		TR4_OBJ_KEY_HOLE11 = 294,
		TR4_OBJ_KEY_HOLE12 = 295,
		TR4_OBJ_WATERSKIN1_EMPTY = 296,
		TR4_OBJ_WATERSKIN1_1 = 297,
		TR4_OBJ_WATERSKIN1_2 = 298,
		TR4_OBJ_WATERSKIN1_3 = 299,
		TR4_OBJ_WATERSKIN2_EMPTY = 300,
		TR4_OBJ_WATERSKIN2_1 = 301,
		TR4_OBJ_WATERSKIN2_2 = 302,
		TR4_OBJ_WATERSKIN2_3 = 303,
		TR4_OBJ_WATERSKIN2_4 = 304,
		TR4_OBJ_WATERSKIN2_5 = 305,
		TR4_OBJ_SWITCH_TYPE1 = 306,
		TR4_OBJ_SWITCH_TYPE2 = 307,
		TR4_OBJ_SWITCH_TYPE3 = 308,
		TR4_OBJ_SWITCH_TYPE4 = 309,
		TR4_OBJ_SWITCH_TYPE5 = 310,
		TR4_OBJ_SWITCH_TYPE6 = 311,
		TR4_OBJ_SWITCH_TYPE7 = 312,
		TR4_OBJ_SWITCH_TYPE8 = 313,
		TR4_OBJ_UNDERWATER_SWITCH1 = 314,
		TR4_OBJ_UNDERWATER_SWITCH2 = 315,
		TR4_OBJ_TURN_SWITCH = 316,
		TR4_OBJ_COG_SWITCH = 317,
		TR4_OBJ_LEVER_SWITCH = 318,
		TR4_OBJ_JUMP_SWITCH = 319,
		TR4_OBJ_CROWBAR_SWITCH = 320,
		TR4_OBJ_PULLEY = 321,
		TR4_OBJ_DOOR_TYPE1 = 322,
		TR4_OBJ_DOOR_TYPE2 = 323,
		TR4_OBJ_DOOR_TYPE3 = 324,
		TR4_OBJ_DOOR_TYPE4 = 325,
		TR4_OBJ_DOOR_TYPE5 = 326,
		TR4_OBJ_DOOR_TYPE6 = 327,
		TR4_OBJ_DOOR_TYPE7 = 328,
		TR4_OBJ_DOOR_TYPE8 = 329,
		TR4_OBJ_PUSHPULL_DOOR1 = 330,
		TR4_OBJ_PUSHPULL_DOOR2 = 331,
		TR4_OBJ_KICK_DOOR1 = 332,
		TR4_OBJ_KICK_DOOR2 = 333,
		TR4_OBJ_UNDERWATER_DOOR = 334,
		TR4_OBJ_DOUBLE_DOORS = 335,
		TR4_OBJ_BRIDGE_FLAT = 336,
		TR4_OBJ_BRIDGE_TILT1 = 337,
		TR4_OBJ_BRIDGE_TILT2 = 338,
		TR4_OBJ_SARCOPHAGUS = 339,
		TR4_OBJ_SEQUENCE_DOOR1 = 340,
		TR4_OBJ_SEQUENCE_SWITCH1 = 341,
		TR4_OBJ_SEQUENCE_SWITCH2 = 342,
		TR4_OBJ_SEQUENCE_SWITCH3 = 343,
		TR4_OBJ_SARCOPHAGUS_CUT = 344,
		TR4_OBJ_HORUS_STATUE = 345,
		TR4_OBJ_GOD_HEAD = 346,
		TR4_OBJ_SETH_DOOR = 347,
		TR4_OBJ_STATUE_PLINTH = 348,
		TR4_OBJ_PISTOLS_ITEM = 349,
		TR4_OBJ_PISTOLS_AMMO_ITEM = 350,
		TR4_OBJ_UZI_ITEM = 351,
		TR4_OBJ_UZI_AMMO_ITEM = 352,
		TR4_OBJ_SHOTGUN_ITEM = 353,
		TR4_OBJ_SHOTGUN_AMMO1_ITEM = 354,
		TR4_OBJ_SHOTGUN_AMMO2_ITEM = 355,
		TR4_OBJ_CROSSBOW_ITEM = 356,
		TR4_OBJ_CROSSBOW_AMMO1_ITEM = 357,
		TR4_OBJ_CROSSBOW_AMMO2_ITEM = 358,
		TR4_OBJ_CROSSBOW_AMMO3_ITEM = 359,
		TR4_OBJ_CROSSBOW_BOLT = 360,
		TR4_OBJ_GRENADE_GUN_ITEM = 361,
		TR4_OBJ_GRENADE_GUN_AMMO1_ITEM = 362,
		TR4_OBJ_GRENADE_GUN_AMMO2_ITEM = 363,
		TR4_OBJ_GRENADE_GUN_AMMO3_ITEM = 364,
		TR4_OBJ_GRENADE = 365,
		TR4_OBJ_SIXSHOOTER_ITEM = 366,
		TR4_OBJ_SIXSHOOTER_AMMO_ITEM = 367,
		TR4_OBJ_BIGMEDI_ITEM = 368,
		TR4_OBJ_SMALLMEDI_ITEM = 369,
		TR4_OBJ_LASERSIGHT_ITEM = 370,
		TR4_OBJ_BINOCULARS_ITEM = 371,
		TR4_OBJ_FLARE_ITEM = 372,
		TR4_OBJ_FLARE_INV_ITEM = 373,
		TR4_OBJ_DIARY_ITEM = 374,
		TR4_OBJ_COMPASS_ITEM = 375,
		TR4_OBJ_MEMCARD_LOAD_INV_ITEM = 376,
		TR4_OBJ_MEMCARD_SAVE_INV_ITEM = 377,
		TR4_OBJ_PC_LOAD_INV_ITEM = 378,
		TR4_OBJ_PC_SAVE_INV_ITEM = 379,
		TR4_OBJ_SMOKE_EMITTER_WHITE = 380,
		TR4_OBJ_SMOKE_EMITTER_BLACK = 381,
		TR4_OBJ_STEAM_EMITTER = 382,
		TR4_OBJ_EARTHQUAKE = 383,
		TR4_OBJ_BUBBLES = 384,
		TR4_OBJ_WATERFALLMIST = 385,
		TR4_OBJ_GUNSHELL = 386,
		TR4_OBJ_SHOTGUNSHELL = 387,
		TR4_OBJ_GUN_FLASH = 388,
		TR4_OBJ_BUTTERFLY = 389,
		TR4_OBJ_SPRINKLER = 390,
		TR4_OBJ_RED_LIGHT = 391,
		TR4_OBJ_GREEN_LIGHT = 392,
		TR4_OBJ_BLUE_LIGHT = 393,
		TR4_OBJ_AMBER_LIGHT = 394,
		TR4_OBJ_WHITE_LIGHT = 395,
		TR4_OBJ_BLINKING_LIGHT = 396,
		TR4_OBJ_LENS_FLARE = 397,
		TR4_OBJ_AI_GUARD = 398,
		TR4_OBJ_AI_AMBUSH = 399,
		TR4_OBJ_AI_PATROL1 = 400,
		TR4_OBJ_AI_MODIFY = 401,
		TR4_OBJ_AI_FOLLOW = 402,
		TR4_OBJ_AI_PATROL2 = 403,
		TR4_OBJ_AI_X1 = 404,
		TR4_OBJ_AI_X2 = 405,
		TR4_OBJ_LARA_START_POS = 406,
		TR4_OBJ_KILL_ALL_TRIGGERS = 407,
		TR4_OBJ_TRIGGER_TRIGGERER = 408,
		TR4_OBJ_SMASH_OBJECT1 = 409,
		TR4_OBJ_SMASH_OBJECT2 = 410,
		TR4_OBJ_SMASH_OBJECT3 = 411,
		TR4_OBJ_SMASH_OBJECT4 = 412,
		TR4_OBJ_SMASH_OBJECT5 = 413,
		TR4_OBJ_SMASH_OBJECT6 = 414,
		TR4_OBJ_SMASH_OBJECT7 = 415,
		TR4_OBJ_SMASH_OBJECT8 = 416,
		TR4_OBJ_MESHSWAP1 = 417,
		TR4_OBJ_MESHSWAP2 = 418,
		TR4_OBJ_MESHSWAP3 = 419,
		TR4_OBJ_DEATH_SLIDE = 420,
		TR4_OBJ_BODY_PART = 421,
		TR4_OBJ_CAMERA_TARGET = 422,
		TR4_OBJ_WATERFALL1 = 423,
		TR4_OBJ_WATERFALL2 = 424,
		TR4_OBJ_WATERFALL3 = 425,
		TR4_OBJ_PLANET_EFFECT = 426,
		TR4_OBJ_ANIMATING1 = 427,
		TR4_OBJ_ANIMATING1_MIP = 428,
		TR4_OBJ_ANIMATING2 = 429,
		TR4_OBJ_ANIMATING2_MIP = 430,
		TR4_OBJ_ANIMATING3 = 431,
		TR4_OBJ_ANIMATING3_MIP = 432,
		TR4_OBJ_ANIMATING4 = 433,
		TR4_OBJ_ANIMATING4_MIP = 434,
		TR4_OBJ_ANIMATING5 = 435,
		TR4_OBJ_ANIMATING5_MIP = 436,
		TR4_OBJ_ANIMATING6 = 437,
		TR4_OBJ_ANIMATING6_MIP = 438,
		TR4_OBJ_ANIMATING7 = 439,
		TR4_OBJ_ANIMATING7_MIP = 440,
		TR4_OBJ_ANIMATING8 = 441,
		TR4_OBJ_ANIMATING8_MIP = 442,
		TR4_OBJ_ANIMATING9 = 443,
		TR4_OBJ_ANIMATING9_MIP = 444,
		TR4_OBJ_ANIMATING10 = 445,
		TR4_OBJ_ANIMATING10_MIP = 446,
		TR4_OBJ_ANIMATING11 = 447,
		TR4_OBJ_ANIMATING11_MIP = 448,
		TR4_OBJ_ANIMATING12 = 449,
		TR4_OBJ_ANIMATING12_MIP = 450,
		TR4_OBJ_ANIMATING13 = 451,
		TR4_OBJ_ANIMATING13_MIP = 452,
		TR4_OBJ_ANIMATING14 = 453,
		TR4_OBJ_ANIMATING14_MIP = 454,
		TR4_OBJ_ANIMATING15 = 455,
		TR4_OBJ_ANIMATING15_MIP = 456,
		TR4_OBJ_ANIMATING16 = 457,
		TR4_OBJ_ANIMATING16_MIP = 458,
		TR4_OBJ_HORIZON = 459,
		TR4_OBJ_SKY_GRAPHICS = 460,				   // Sprite (in SWD file)
		TR4_OBJ_BINOCULAR_GRAPHICS = 461,
		TR4_OBJ_TARGET_GRAPHICS = 462,
		TR4_OBJ_DEFAULT_SPRITES = 463,				// Sprite (in SWD file)
		TR4_OBJ_MISC_SPRITES = 464

} tr4_objects_t;

#endif
