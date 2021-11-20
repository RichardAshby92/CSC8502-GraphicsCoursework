#include "../nclgl/Plants.h"
#include "../nclgl/Mesh.h"
#include "../nclgl/MeshMaterial.h"

Plants::Plants(Vector3 heightmapSize) {

	//load Files
	plant = Mesh::LoadFromMeshFile("P_Bush02.msh");
	plantMat = new MeshMaterial("P_Bush02.mat");

	//loop for every material
	for (int i = 0; i < plant->GetSubMeshCount(); ++i) {
		const MeshMaterialEntry* matEntry = plantMat->GetMaterialForLayer(i);
		const string* filename = nullptr;
		matEntry->GetEntry("Diffuse", &filename);
		if(filename){
			string path = TEXTUREDIR + *filename;
			GLuint texID = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
			plantTextures.emplace_back(texID);
		}
		else{ plantTextures.emplace_back(0); }
	}

	//need deconstructor

	//loop for every placement
	tree = new SceneNode(plant, Vector4(1, 1, 1, 1)); //camera
	tree->SetModelScale(Vector3(20, 20, 20));
	tree->SetTransform(Matrix4::Translation(heightmapSize * Vector3(0.3f, 0.45f, 0.65f)));
	tree->SetTexture(1);
	tree->SetSubTextures(plantTextures);
	tree->SetBoundingRadius(20);
	AddChild(tree);
}

void Plants::Update(float dt) {

	SceneNode::Update(dt);
}

