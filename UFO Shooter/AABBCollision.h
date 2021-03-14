#pragma once
#ifndef Collision_h
#define Collision_h

static bool checkCollide(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	// AABB 1
	int x1Min = x1;
	int x1Max = x1 + w1;
	int y1Max = y1 + h1;
	int y1Min = y1;

	// AABB 2
	int x2Min = x2;
	int x2Max = x2 + w2;
	int y2Max = y2 + h2;
	int y2Min = y2;

	// Collision tests
	if (x1Max < x2Min || x1Min > x2Max) return false;
	if (y1Max < y2Min || y1Min > y2Max) return false;

	return true;
}

#endif