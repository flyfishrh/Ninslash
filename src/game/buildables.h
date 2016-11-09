#ifndef GAME_BUILDABLES_H
#define GAME_BUILDABLES_H

#include <cstring>
#include <game/generated/protocol.h>

enum Buildables
{
	BUILDABLE_BARREL,
	BUILDABLE_TURRET,
	BUILDABLE_FLAMETRAP,
	NUM_BUILDABLES
};

const int BuildableCost[NUM_BUILDABLES] =
{
	1, // BUILDABLE_BARREL,
	2, // BUILDABLE_TURRET,
	2, // BUILDABLE_FLAMETRAP,
};

const int BuildableSize[NUM_BUILDABLES] =
{
	108, // BUILDABLE_BARREL,
	128, // BUILDABLE_TURRET,
	92, // BUILDABLE_FLAMETRAP,
};

const int BuildableOffset[NUM_BUILDABLES] =
{
	-45, // BUILDABLE_BARREL,
	-49, // BUILDABLE_TURRET,
	28, // BUILDABLE_FLAMETRAP,
};

#endif
