#include "../nclgl/Markers.h"
#include "../nclgl/Mesh.h"

Markers::Markers(Vector3 heightmapSize) {

	//markers
	Mesh* cube = Mesh::LoadFromMeshFile("OffsetCubeY.msh");

	camStart = new SceneNode(cube, Vector4(1, 0, 0, 1)); //camera
	camStart->SetModelScale(Vector3(10, 10, 10));
	camStart->SetTransform(Matrix4::Translation(heightmapSize * Vector3(0.3f, 0.2f, 0.65f)));
	camStart->SetTexture(0);
	camStart->SetBoundingRadius(1);
	AddChild(camStart);

	camEnd = new SceneNode(cube, Vector4(1, 0, 0, 1)); //cam marker
	camEnd->SetModelScale(Vector3(10, 10, 10));
	camEnd->SetTransform(Matrix4::Translation(heightmapSize * Vector3(0.6f, 1.5f, 0.35f)));
	camEnd->SetTexture(0);
	camEnd->SetBoundingRadius(1);
	AddChild(camEnd);

	marker1 = new SceneNode(cube, Vector4(1, 0, 0, 1)); //Top Left
	marker1->SetModelScale(Vector3(10, 10, 10));
	marker1->SetTransform(Matrix4::Translation(heightmapSize * Vector3(0.0f, 0.5f, 0.0f)));
	//marker1->SetColour(Vector4(1, 0, 0, 1));
	marker1->SetTexture(0);
	marker1->SetBoundingRadius(1);
	AddChild(marker1);

	marker2 = new SceneNode(cube, Vector4(0, 1, 0, 1)); //Bottom Left
	marker2->SetModelScale(Vector3(10, 10, 10));
	marker2->SetTransform(Matrix4::Translation(heightmapSize * Vector3(0.0f, 0.5f, 1.0f)));
	//marker2->SetColour(Vector4(1, 0, 0, 1));
	marker2->SetTexture(0);
	marker2->SetBoundingRadius(1);
	AddChild(marker2);

	marker3 = new SceneNode(cube, Vector4(0, 0, 1, 1));  //Bottom Right
	marker3->SetModelScale(Vector3(10, 10, 10));
	marker3->SetTransform(Matrix4::Translation(heightmapSize * Vector3(1.0f, 0.5f, 1.0f)));
	//marker3->SetColour(Vector4(1, 0, 0, 1));
	marker3->SetTexture(0);
	marker3->SetBoundingRadius(1);
	AddChild(marker3);

	marker4 = new SceneNode(cube, Vector4(1, 1, 1, 1)); //Top Right
	marker4->SetModelScale(Vector3(10, 10, 10));
	marker4->SetTransform(Matrix4::Translation(heightmapSize * Vector3(1.0f, 0.5f, 0.0f)));
	//marker4->SetColour(Vector4(1, 0, 0, 1));
	marker4->SetTexture(0);
	marker4->SetBoundingRadius(1);
	AddChild(marker4);

	marker4 = new SceneNode(cube, Vector4(0, 0, 0, 1)); //Light marker
	marker4->SetModelScale(Vector3(10, 10, 10));
	marker4->SetTransform(Matrix4::Translation(heightmapSize * Vector3(0.0f, 5.0f, 0.55f)));
	//marker4->SetColour(Vector4(1, 0, 0, 1));
	marker4->SetTexture(0);
	marker4->SetBoundingRadius(1);
	AddChild(marker4);



}

void Markers::Update(float dt) {

	SceneNode::Update(dt);
}

Vector3 GetCameraPos();