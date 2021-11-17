#pragma once
#pragma once
#include "../nclgl/SceneNode.h"

class Mesh;

class Plants : public SceneNode {
public:
	Plants(Vector3	heightmapSize);
	~Plants() {};

	void Update(float dt) override;

protected:
	SceneNode* tree;


	Mesh* plant;

};

