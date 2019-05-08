//English patch for BATTLE TRAVERSE
//Written by YAM, July 2018

/*
 * Image filenames
 */
 
str(0x3814B8, "data\\en01\\name_back.png")
str(0x3814A0, "data\\en01\\nameentry.png")
str(0x37DE60, "data\\en01\\serif.png")

/*
 * en01/serif.png drawing coordinates
 */
 
//st02-1
double(0x3F34C0, 154.0-12.0)	//dest x - 12
	ptr(0x3D29E, 0x3F34C0)
double(0x3F34C8, 218.0+2.0)	//dest y + 2
	ptr(0x3D282, 0x3F34C8)

//st02-2
byte(0x3D2FE, 0xE5)		//src x2
int(0x3D2F9, 0x165)		//src y2
ptr(0x3D318, 0x3F34C0)		//match st02-1's dest x
ptr(0x3D2EE, 0x3F34C8)		//match st02-1's dest y

/*
 * Practice mode
 */
 
//Stages
str(0x38039C, "Practice Stage 1, \"Operation Eagle Strike\".")
str(0x38036C, "Practice the Stage 1 boss, \"Karaburan\".")
str(0x380340, "Practice Stage 2, \"Scramble\".")
str(0x380308, "Practice the Stage 2 boss, \"Gartenzauber\".")
str(0x3802D8, "Practice Stage 3, \"Sunset Raider\".")
str(0x3802A4, "Practice the Stage 3 boss, \"Jet Blower\".")
str(0x380274, "Practice Stage 4, \"Restless Night\".")
str(0x380244, "Practice the Stage 4 boss, \"Migrant\".")
str(0x38020C, "Practice Stage 5, \"Daybreak of Fire\".")
str(0x3801D0, "Practice the Stage 5 boss, \"New Valentine\".")

//Tutorials
str(0x3801A4, "Begin Tutorial 1, \"Basic Operation\".")
str(0x380170, "Begin Tutorial 2, \"Score System\".")
str(0x380134, "Begin Tutorial 3, \"System of \"Extreme\"\".")

//Practice run
str(0x3F3A64, "Start a practice run from Stage 1.")
	ptr(0x1DBFB, 0x3F3A64)
str(0x3800C8, "You can reproduce the second loop of arcade mode, or play using special rules.")

//High scores
str(0x3800B0, "High score (Easy):")
str(0x380098, "High score (Normal):")
str(0x380084, "High score (Hard):")
str(0x3F3938, "High score (Very Hard):")
	ptr(0x1DE3F, 0x3F3938)
	ptr(0x1E26C, 0x3F3938)
str(0x380054, "High score (Extreme):")
str(0x38003C, "High score (Simple):")

//Other
str(0x380014, "Edit practice mode settings.")
str(0x37FFF8, "Return to main menu.")
str(0x37FFE0, "No data.")
str(0x37FFC0, "Please select a character.")

/*
 * Practice settings
 */

//Difficulty (TODO: move descriptions to main settings)
str(0x37FE80, "Set the difficulty level. (Changes will also be applied to arcade mode.)")
str(0x3F3904, "Easy: Even a beginner can do a ten-minute clear.")
	ptr(0x212CE, 0x3F3904)
	ptr(0x277D2, 0x3F3904)
str(0x37FE1C, "Normal: A difficulty level intended for novices.")
str(0x3F39CB, "Hard: Difficulty on par with the first loop of an arcade shooter.")
	ptr(0x21361, 0x3F39CB)
	ptr(0x27865, 0x3F39CB)
str(0x37FDB4,"Very Hard: Much faster bullets, considerably difficult.")
str(0x3F3A0D, "Extreme: Difficulty pushed to the utmost limit.")
	ptr(0x213F5, 0x3F3A0D)
	ptr(0x27936, 0x3F3A0D)

//Remaining
str(0x3F3A40, "Set the number of remaining lives.")
	ptr(0x2143F, 0x3F3A40)
str(0x37FD44, "Infinite: You can resurrect infinitely.")
str(0x3F3958, "However, the clear bonus will be worth 0 lives.")
	ptr(0x214DB, 0x3F3958)

//Shot power
str(0x37FCF8, "Set shot power.")
str(0x37FCB0, "Auto: Automatically adjusts power for each stage based on arcade mode.")

//Bomb stock
str(0x37FC8C, "Set bomb stock.")

//Auto-bomb
str(0x37FC70, "Use auto-bomb.")
str(0x37FC54, "Do not use auto-bomb.")
str(0x3F398C, "(Auto-bomb: Automatically uses a bomb the moment you are hit.)")
	ptr(0x216DC, 0x3F398C)
str(0x37FBDC, "The auto-bomb will always activate when you are hit by counterfire.")

//Counterfire
str(0x3F38E0, "Counterfire bullets are enabled.")
	ptr(0x217D8, 0x3F38E0)
str(0x37FBA4, "Counterfire bullets are disabled.")

//Simple mode
str(0x37FB84, "Simple mode is enabled.")
str(0x37FB40, "In simple mode, score can only be earned by defeating enemies.")
str(0x3F3A87, "Because enemy bullets do not cancel, the difficulty is generally higher.")
	ptr(0x21934, 0x3F3A87)
str(0x37FAE8, "Simple mode is disabled.")

//Other
str(0x37FACC, "Save settings and return.")
str(0x37FAAC, "Discard settings and return.")
str(0x37FA90, "Reset settings to default.")

/*
 * Ranking screen
 */

//Statistics:
str(0x37F9A4, "Player:")
str(0x37F980, "Stage:")
str(0x37F948, "Score:")
str(0x37F93C, "Date:")
str(0x37F934, "\x81\x46") //SJIS ':'
str(0x37F930, "")

/*
 * Config screen
 */

str(0x380BC4, "Set difficulty level.")
str(0x380BA4, "Hard mode has a second loop.")
str(0x380B7C, "Set the ingame framerate.")
str(0x3F3AD0, "(Framerate: The number of times the screen updates in one second)")
	ptr(0x279BA, 0x3F3AD0)
str(0x380B1C, "Boss caption text will be displayed.")
str(0x380AE8, "Boss caption text will not be displayed.")
str(0x380AB8, "Replay data will be recorded in arcade mode.")
str(0x380A68, "Only for single-player runs where no continues are used.")
str(0x380A2C, "Either the 1P or 2P side can be used.")
str(0x380A0C, "Unavailable in trial version.")
str(0x3809D8, "Replay data will not be recorded in arcade mode.")
str(0x3809B8, "Player hitbox will be visible.")
str(0x380994, "Player hitbox will not be visible.")
str(0x38096C, "SPECIFIC: Only visible while focused.")
str(0x380950, "ALWAYS: Constantly visible.")
str(0x3F3B78, "FPS (Frames Per Second) will be displayed.")
	ptr(0x27DD9, 0x3F3B78)
str(0x380904, "FPS (Frames Per Second) will not be displayed.")
str(0x3F3B14, "(FPS: A measurement of framerate. Low values may indicate heavy CPU load.)")
	ptr(0x27E4B, 0x3F3B14)

/*
 * Second loop
 */

str(0x385C84, "Good work!")
str(0x385C54, "Thus concludes the simulation of the operation.")
str(0x3F3804, "Were you able to get the hang of the strategy?")
	ptr(0x19D028, 0x3F3804)
str(0x385C0C, "In the end, though, this was just a simulation.")
str(0x3F3868, "In actual battle, the attacks will be much more violent, so please be careful.")
	ptr(0x19D06A, 0x385C0C)
str(0x3F3778, "...It's almost time to begin the operation.")
str(0x3F37B8, "Please, be sure to return safely and successfully.")
	ptr(0x19D084, 0x3F37B8)
str(0x385B70, "Well then, I wish you good luck in battle!")