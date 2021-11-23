#pragma once
#include "../nclgl/SceneNode.h"

class Mesh;

class Markers : public SceneNode {
public:
	Markers(){}
	Markers(Vector3	heightmapSize);
	~Markers() {};

	void Update(float dt) override;
	std::vector<Vector3> GetMarkers() { return markers; };


protected:
	SceneNode* camStart;
	SceneNode* camEnd;
	SceneNode* wayPoint1;
	SceneNode* wayPoint2;
	SceneNode* wayPoint3;
	SceneNode* wayPoint4;

	SceneNode* marker;
	SceneNode* marker1;
	SceneNode* marker2;
	SceneNode* marker3;
	SceneNode* marker4;

	Mesh* cube;

	std::vector<Vector3> markers;
};
