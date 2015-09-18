#pragma once

enum Label
{
	None,
	Pad,
	Box,
	Ball,
	Goal,
};

struct LabelComponent
{
	LabelComponent()
	{
		mLabel = None;
	}
	Label mLabel;
};