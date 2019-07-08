#pragma once

// Input Manager
enum class Key
{
	UP = 265,
	DOWN = 264,
	LEFT = 263,
	RIGHT = 262,

	W = 87,
	A = 65,
	S = 83,
	D = 68,

	E = 69,
	Q = 81,

	SPACE = 32,
	LEFT_SHIFT = 340
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

// Physics
enum class ForceMode
{
	FORCE,
	IMPULSE,
	VELOCITY_CHANGE,
	ACCELERATION
};