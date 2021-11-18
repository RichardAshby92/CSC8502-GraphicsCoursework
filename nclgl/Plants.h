#pragma once
#include "../nclgl/SceneNode.h"

class Mesh;
class MeshMaterial;

class Plants : public SceneNode {
public:
	Plants(Vector3	heightmapSize);
	~Plants() {};

	void Update(float dt) override;

protected:
	SceneNode* tree;


	Mesh* plant;

	MeshMaterial* plantMat;

	vector<GLuint> plantTextures;
};

