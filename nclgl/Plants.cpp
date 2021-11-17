#include "../nclgl/Plants.h"
#include "../nclgl/Mesh.h"

Plants::Plants(Vector3 heightmapSize) {

	plant = Mesh::LoadFromMeshFile("PalmTreeSingleStraightOneSided.msh");


	tree = new SceneNode(plant, Vector4(1, 0, 0, 1)); //camera
	tree->SetModelScale(Vector3(20, 20, 20));
	tree->SetTransform(Matrix4::Translation(heightmapSize * Vector3(0.5f, 0.5f, 0.5f)));
	//marker->SetColour(Vector4(1, 0, 0, 1));
	tree->SetTexture(0);
	tree->SetBoundingRadius(1);
	AddChild(tree);
}

void Plants::Update(float dt) {

	SceneNode::Update(dt);
}