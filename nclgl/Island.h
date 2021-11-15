#pragma once
#include "../nclgl/SceneNode.h"

class Mesh;

class Island : public SceneNode {
public:
	Island(Mesh* cube);
	~Island() {};
	
	void Update(float dt) override;

protected:
	SceneNode* marker;


};