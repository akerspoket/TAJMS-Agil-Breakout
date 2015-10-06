#pragma once

enum Label
{
	None,
	Pad,
	Box,
	Ball,
	GoalBlock,
	BottomArea,
	MenuPointer,
};

struct LabelComponent
{
	LabelComponent()
	{
		mLabel = None;
	}
	Label mLabel;
};