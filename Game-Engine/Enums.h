#pragma once

// Input Manager
enum Key
{
	UpKey = 265,
	DownKey = 264,
	LeftKey = 263,
	RightKey = 262
};

// Bounding Boxes
enum CollisionDir
{
	LeftCollision, 
	RightCollision, 
	UpCollision, 
	DownCollision
};

// Tilemap
enum TileType
{
	Background,
	Wall
};

// Renderer
enum ProjectionType
{
	ORTHOGRAPHIC,
	PERSPECTIVE
};

enum PrimitiveType
{
	TRIANGLE = 4,
	TRIANGLE_STRIP = 5,
	TRIANGLE_FAN = 6,
	QUAD = 7
};