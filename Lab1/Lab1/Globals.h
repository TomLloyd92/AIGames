#pragma once
#ifndef GLOBALS
#define GLOBALS

enum class  GameMode
{
	Gameplay
};

const static int SCREEN_WIDTH = 1800;
const static int SCREEN_HEIGHT = 1000;
const static int MS_PER_UPDATE = 10;

const static float PI = 3.14159265359;
float const DEG_TO_RAD = PI / 180.0f;
float const RAD_TO_DEG = 180.0f / PI;


#endif