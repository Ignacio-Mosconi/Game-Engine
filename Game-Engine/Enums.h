#pragma once

// Input Manager
enum class Key
{
	UP_KEY = 265,
	DOWN_KEY = 264,
	LEFT_KEY = 263,
	RIGHT_KEY = 262
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
enum class ProjectionType
{
	ORTHOGRAPHIC,
	PERSPECTIVE
};

enum class PrimitiveType
{
	TRIANGLE = 4,
	TRIANGLE_STRIP = 5,
	TRIANGLE_FAN = 6,
	QUAD = 7
};