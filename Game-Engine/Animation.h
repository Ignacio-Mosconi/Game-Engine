#pragma once

#include <queue>
#include "Exports.h"

namespace gn
{
	class Sprite;
/*
	The "Animation" class represents an animation that can be a part of a "GameEntity".
	It handles the logic behind the swapping of different frames from a spritesheet.
*/
	class ENGINE_API Animation
	{
		std::queue<unsigned int>* _frames;
		Sprite* _sprite;
	
		std::string _name;
		
		unsigned int _currentFrame;
		unsigned int _lastFrame;
		
		float _speed;
		float _frameTime;
		bool _looped;
		bool _stopped;
		bool _finished;
		float _timer;

	public:
		Animation(const std::string& name, unsigned int frames[], float speed, bool _looped);
		~Animation();

		void update(float deltaTime);

		void play(bool resume = true);
		void stop();

		inline std::string getName() const { return _name; }
		inline bool isPlaying() const { return !_stopped && !_finished; }

		inline void setSprite(Sprite* sprite) { _sprite = sprite; }
		inline void setSpeed(float speed) { _speed = speed; _frameTime = 1.0f / speed; }
		inline void setLooped(bool looped) { _looped = looped; }
	};
}