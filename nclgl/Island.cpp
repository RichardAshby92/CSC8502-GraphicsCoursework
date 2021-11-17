#include "../nclgl/Island.h"
#include "../nclgl/Mesh.h"



Island::Island() {

	Mesh* cube = Mesh::LoadFromMeshFile("OffsetCubeY.msh"); //TEMP!

	//markers
	marker = new SceneNode(cube, Vector4(1,0,0,1));
	marker->SetModelScale(Vector3(1,1,1));
	marker->SetTransform(Matrix4::Translation(Vector3(0,0,0)));
	marker->SetColour(Vector4(1, 0, 0, 1));
	marker->SetTexture(0);
	//marker->SetBoundingRadius();
	AddChild(marker);

	//Plants


	//Rocks


	//
}

void Island::Update(float dt) {

	SceneNode::Update(dt);
}