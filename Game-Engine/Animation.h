#pragma once

#include <queue>
#include "Exports.h"

using namespace std;

class Sprite;

class ENGINE_API Animation
{
	queue<unsigned int>* _frames;
	Sprite* _sprite;
	unsigned int _currentFrame;
	unsigned int _lastFrame;
	float _speed;
	float _frameTime;
	bool _looped;
	bool _stopped;
	bool _finished;
	float _timer;

public:
	Animation(Sprite* sprite, unsigned int frames[], float speed, bool _looped);
	~Animation();

	void update(float deltaTime);

	void play(bool resume = true);
	void stop();

	inline void setSprite(Sprite* sprite) { _sprite = sprite; }
	inline void setSpeed(float speed) { _speed = speed; _frameTime = 1.0f / speed; }
	inline void setLooped(bool looped) { _looped = looped; }
};