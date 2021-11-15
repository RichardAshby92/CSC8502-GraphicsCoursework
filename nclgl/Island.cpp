#include "../nclgl/Island.h"


Island::Island(Mesh* cube) {

	marker = new SceneNode(cube, Vector4(1,0,0,1));
	marker->SetModelScale(Vector3(30,30,30));
	marker->SetTransform(Matrix4::Translation(Vector3(256,256,0)));
	marker->SetTexture(0);
	//marker->SetBoundingRadius();
	AddChild(marker);
}

void Island::Update(float dt) {

	SceneNode::Update(dt);
}