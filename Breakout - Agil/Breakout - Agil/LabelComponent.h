#pragma once

enum Label
{
	None,
	Pad,
	Box,
	Ball,
};

struct LabelComponent
{
	LabelComponent()
	{
		mLabel = None;
	}
	Label mLabel;
};