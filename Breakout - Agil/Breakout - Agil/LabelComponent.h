#pragma once

enum Label
{
	None = 0x01,
	Pad = 0x02,
	Box = 0x04,
	Ball = 0x08,
	GoalBlock = 0x10,
	BottomArea = 0x20,
	MenuPointer = 0x40,
	Wall = 0x80,
	PowerUpDown = 0x100,
	Cannon = 0x200,
};


struct LabelComponent
{
	LabelComponent()
	{
		mLabel = None;
	}
	short mLabel;

	bool HasLabel(short pMask)
	{
		return ((mLabel & pMask) == pMask);
	}

	void AddLabel(short pMask)
	{
		mLabel = mLabel | pMask;
	}
	void RemoveLabel(short pMask)
	{
		short tAnd = mLabel & pMask;
		mLabel = mLabel ^ tAnd;
	}
};