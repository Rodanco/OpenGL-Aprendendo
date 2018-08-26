#pragma once

class Scene
{
public:
	virtual void init() = 0;
	virtual void update(float secs) = 0;
	virtual void draw() = 0;
	virtual void deinit() = 0;
	virtual ~Scene() = default;
};