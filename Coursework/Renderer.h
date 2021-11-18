#pragma once
#include "../nclgl/OGLRenderer.h"

class Camera;
class Mesh;
class MeshMaterial;
class HeightMap;
class SceneNode;
class Light;
class Island;

class Renderer : public OGLRenderer	{
public:
	Renderer(Window &parent);
	 ~Renderer(void);
	 
	 void RenderScene()			override;
	 void UpdateScene(float dt)	override;
protected:
	
	void DrawSkyBox();
	void DrawHeightMap();
	void DrawWater();
	void DrawNode(SceneNode* n);

	HeightMap* heightmap;
	Vector3	heightmapSize;

	Mesh* quad;
	Mesh* cube;
	Mesh* plant;

	MeshMaterial* plantMat;

	vector<GLuint> plantTextures;

	Shader* sceneShader;
	Shader* basicShader;
	Shader* lightShader;
	Shader* reflectShader;
	Shader* skyboxShader;
	Shader* postProcess;

	Camera* camera;

	GLuint sandTex;
	GLuint waterTex;
	GLuint rockTex;
	GLuint grassTex;

	GLuint sandBump;
	GLuint waterBump;
	GLuint rockBump;
	GLuint grassBump;

	GLuint cubeMap;

	SceneNode* root;
	Island* island;

	Light* sun;

	float waterMov;
	float waterRot;

	bool autoCam;
};
