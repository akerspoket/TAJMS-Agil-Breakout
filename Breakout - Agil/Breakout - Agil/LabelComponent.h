#pragma once

enum Label
{
	None,
	Pad,
	Box,
	Ball,
	GoalBlock,
};

struct LabelComponent
{
	LabelComponent()
	{
		mLabel = None;
	}
	Label mLabel;
};