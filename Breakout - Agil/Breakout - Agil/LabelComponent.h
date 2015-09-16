#pragma once

enum Label
{
	None,
	Pad,
	Box,
};

struct LabelComponent
{
	LabelComponent()
	{
		mLabel = None;
	}
	Label mLabel;
};