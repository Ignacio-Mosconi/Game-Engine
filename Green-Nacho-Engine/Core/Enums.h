#pragma once

// Input Manager
enum class Key
{
	UP_KEY = 265,
	DOWN_KEY = 264,
	LEFT_KEY = 263,
	RIGHT_KEY = 262,

	W_KEY = 87,
	A_KEY = 65,
	S_KEY = 83,
	D_KEY = 68,

	E_KEY = 69,
	Q_KEY = 81
};

enum class InputAxis
{
	HORIZONTAL,
	VERTICAL
};

// Bounding Boxes
enum class CollisionDir
{
	LEFT, 
	RIGHT, 
	UP, 
	DOWN
};

// Tilemap
enum class TileType
{
	BACKGROUND,
	WALL
};

// Renderer
enum class Projection
{
	ORTHOGRAPHIC,
	PERSPECTIVE
};

enum class PrimitiveType
{
	LINES = 1,
	TRIANGLE = 4,
	TRIANGLE_STRIP = 5,
	TRIANGLE_FAN = 6,
	QUAD = 7
};

// Camera
enum class MoveDir
{
	FORWARD,
	BACKWARDS,
	LEFT,
	RIGHT,
	UP,
	DOWN
};