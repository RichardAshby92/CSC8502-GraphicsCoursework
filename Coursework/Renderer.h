#pragma once
#include "../nclgl/OGLRenderer.h"

class Camera;
class Mesh;
class MeshMaterial;
class HeightMap;
class SceneNode;
class Light;
class Island;
class ParticleControl;

class Renderer : public OGLRenderer	{
public:
	Renderer(Window &parent);
	 ~Renderer(void);
	 
	 void RenderScene()			override;
	 void UpdateScene(float dt)	override;

	 void toggleAutoCam();
protected:
	
	void DrawSkyBox();
	void DrawHeightMap();
	void DrawNode(SceneNode* n);
	void DrawWater();
	void DrawRain(ParticleControl* rain);


	HeightMap* heightmap;
	Vector3	heightmapSize;

	Mesh* quad;
	Mesh* cube;
	Mesh* plant;

	MeshMaterial* plantMat;

	vector<GLuint> plantTextures;

	Shader* sceneShader;
	Shader* basicShader;
	Shader* terrainShader;
	Shader* reflectShader;
	Shader* skyboxShader;
	Shader* postProcess;

	Camera* camera;

	ParticleControl* rain;

	GLuint sandTex;
	GLuint waterTex;
	GLuint rockTex;
	GLuint grassTex;
	GLuint rainTex;

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
