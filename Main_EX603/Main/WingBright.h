#pragma once
// ---------------------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------------------

class Wings
{
public:
	void Load();
	static bool		IsCustomWings(WORD ItemID, bool Preview);
	static bool		IsCustomItem(WORD ItemID, bool Preview);
	// ----
}; extern Wings gWings;
// ---------------------------------------------------------------------------------------------