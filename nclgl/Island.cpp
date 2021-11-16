#include "../nclgl/Island.h"
#include "../nclgl/Mesh.h"


Island::Island() {

	Mesh* cube = Mesh::LoadFromMeshFile("OffsetCubeY.msh"); //TEMP!
	//GLuint sandTex = SOIL_load_OGL_texture(TEXTUREDIR"sand.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS); //TEMP!

	marker = new SceneNode(cube, Vector4(1,0,0,1));
	marker->SetModelScale(Vector3(30,30,30));
	marker->SetTransform(Matrix4::Translation(Vector3(0,0,0)));
	//marker->SetTexture(sandTex);
	//marker->SetBoundingRadius();
	AddChild(marker);
}

void Island::Update(float dt) {

	SceneNode::Update(dt);
}