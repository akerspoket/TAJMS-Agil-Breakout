#pragma once

enum Label
{
	None,
	Pad,
	Box,
	Ball,
	GoalBlock,
	BottomArea,
};

struct LabelComponent
{
	LabelComponent()
	{
		mLabel = None;
	}
	Label mLabel;
};