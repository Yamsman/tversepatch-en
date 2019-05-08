/*
 * Image filenames
 */
 
str(0x3814B8, "data\\en01\\name_back.png")
str(0x3814A0, "data\\en01\\nameentry.png")
str(0x37DE60, "data\\en01\\serif.png")

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
str_rloc(0x3F3A64, "Start a practice run from Stage 1.", 0x1DBFB)
str(0x3800C8, "You can reproduce the second loop of arcade mode, or play using special rules.")

//High scores
str(0x3800B0, "High score (Easy):")
str(0x380098, "High score (Normal):")
str(0x380084, "High score (Hard):")
str_rloc(0x3F3938, "High score (Very Hard):", 0x1DE3F)
	rloc(0x3F3938, 0x1E26C)
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
str_rloc(0x3F3904, "Easy: Even a beginner can do a ten-minute clear.", 0x212CE)
	rloc(0x3F3904, 0x277D2)
str(0x37FE1C, "Normal: A difficulty level intended for novices.")
str_rloc(0x3F39CB, "Hard: Difficulty on par with the first loop of an arcade shooter.", 0x21361)
	rloc(0x3F39CB, 0x27865)
str(0x37FDB4,"Very Hard: Much faster bullets, considerably difficult.")
str_rloc(0x3F3A0D, "Extreme: Difficulty pushed to the utmost limit.", 0x0213F5)
	rloc(0x3F3A0D, 0x27936)

//Remaining
str_rloc(0x3F3A40, "Set the number of remaining lives.", 0x02143F)
str(0x37FD44, "Infinite: You can resurrect infinitely.")
str_rloc(0x3F3958, "However, the clear bonus will be worth 0 lives.", 0x0214DB)

//Shot power
str(0x37FCF8, "Set shot power.")
str(0x37FCB0, "Auto: Automatically adjusts power for each stage based on arcade mode.")

//Bomb stock
str(0x37FC8C, "Set bomb stock.")

//Auto-bomb
str(0x37FC70, "Use auto-bomb.")
str(0x37FC54, "Do not use auto-bomb.")
str_rloc(0x3F398C, "(Auto-bomb: Automatically uses a bomb the moment you are hit.)", 0x0216DC)
str(0x37FBDC, "The auto-bomb will always activate when you are hit by counterfire.")

//Counterfire
str_rloc(0x3F38E0, "Counterfire bullets are enabled.", 0x217D8)
str(0x37FBA4, "Counterfire bullets are disabled.")

//Simple mode
str(0x37FB84, "Simple mode is enabled.")
str(0x37FB40, "In simple mode, score can only be earned by defeating enemies.")
str_rloc(0x3F3A87, "Because enemy bullets do not cancel, the difficulty is generally higher.", 0x21934)
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
str_rloc(0x3F3AD0, "(Framerate: The number of times the screen updates in one second)", 0x279BA)
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
str_rloc(0x3F3B78, "FPS (Frames Per Second) will be displayed.", 0x27DD9)
str(0x380904, "FPS (Frames Per Second) will not be displayed.")
str_rloc(0x3F3B14, "(FPS: A measurement of framerate. Low values may indicate heavy CPU load.)", 0x27E4B)
//str(

/*
 * Second loop
 */

str(0x385C84, "Good work!")
str(0x385C54, "Thus concludes the simulation of the operation.")
str_rloc(0x3F3804, "Were you able to get the hang of the strategy?", 0x19D028)
str(0x385C0C, "In the end, though, this was just a simulation.")
str_rloc(0x3F3868, "In actual battle, the attacks will be much more violent, so please be careful.", 0x19D06A)
str(0x3F3778, "...It's almost time to begin the operation.")
str_rloc(0x3F37B8, "Please, be sure to return safely and successfully.", 0x19D084)
str(0x385B70, "Well then, I wish you good luck in battle!")