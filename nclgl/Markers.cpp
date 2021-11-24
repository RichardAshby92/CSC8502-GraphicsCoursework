#include "../nclgl/Markers.h"
#include "../nclgl/Mesh.h"

Markers::Markers(Vector3 heightmapSize) {

	//markers
	Mesh* cube = Mesh::LoadFromMeshFile("OffsetCubeY.msh");

	camStart = new SceneNode(cube, Vector4(1, 0, 0, 1)); //camera Start
	camStart->SetModelScale(Vector3(10, 10, 10));
	camStart->SetTransform(Matrix4::Translation(heightmapSize * Vector3(0.3f, 0.2f, 0.65f)));
	camStart->SetTexture(0);
	camStart->SetBoundingRadius(1);
	//markers.emplace_back(camStart->GetTransform());
	AddChild(camStart);

	wayPoint1 = new SceneNode(cube, Vector4(1, 0, 0, 1)); 
	wayPoint1->SetModelScale(Vector3(10, 10, 10));
	wayPoint1->SetTransform(Matrix4::Translation(heightmapSize * Vector3(0.4f, 0.2f, 0.65f)));
	wayPoint1->SetTexture(0);
	wayPoint1->SetBoundingRadius(1);
	//markers.emplace_back(wayPoint1->GetTransform());
	AddChild(wayPoint1);

	wayPoint2 = new SceneNode(cube, Vector4(1, 0, 0, 1)); 
	wayPoint2->SetModelScale(Vector3(10, 10, 10));
	wayPoint2->SetTransform(Matrix4::Translation(heightmapSize * Vector3(0.5f, 0.2f, 0.65f)));
	wayPoint2->SetTexture(0);
	wayPoint2->SetBoundingRadius(1);
	//markers.emplace_back(wayPoint2->GetTransform());
	AddChild(wayPoint2);

	wayPoint3 = new SceneNode(cube, Vector4(1, 0, 0, 1)); 
	wayPoint3->SetModelScale(Vector3(10, 10, 10));
	wayPoint3->SetTransform(Matrix4::Translation(heightmapSize * Vector3(0.5f, 0.2f, 0.5f)));
	wayPoint3->SetTexture(0);
	wayPoint3->SetBoundingRadius(1);
	//markers.emplace_back(wayPoint3->GetTransform());
	AddChild(wayPoint3);

	wayPoint4 = new SceneNode(cube, Vector4(1, 0, 0, 1)); 
	wayPoint4->SetModelScale(Vector3(10, 10, 10));
	wayPoint4->SetTransform(Matrix4::Translation(heightmapSize * Vector3(0.6f, 1.0f, 0.4f)));
	wayPoint4->SetTexture(0);
	wayPoint4->SetBoundingRadius(1);
	//markers.emplace_back(wayPoint4->GetTransform());
	AddChild(wayPoint4);

	camEnd = new SceneNode(cube, Vector4(1, 0, 0, 1)); //cam End
	camEnd->SetModelScale(Vector3(10, 10, 10));
	camEnd->SetTransform(Matrix4::Translation(heightmapSize * Vector3(0.6f, 1.5f, 0.35f)));
	camEnd->SetTexture(0);
	camEnd->SetBoundingRadius(1);
	//markers.emplace_back(camEnd->GetTransform());
	AddChild(camEnd);

	//reference only

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