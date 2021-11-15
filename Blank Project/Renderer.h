#pragma once
#include "../nclgl/OGLRenderer.h"

class Camera;
class Mesh;
class HeightMap;
class SceneNode;
class Light;

class Renderer : public OGLRenderer	{
public:
	Renderer(Window &parent);
	 ~Renderer(void);
	 
	 void RenderScene()			override;
	 void UpdateScene(float dt)	override;
protected:
	
	void DrawSkyBox();
	void DrawHeightMap();
	void DrawLights();
	void DrawWater();
	void DrawNode(SceneNode* n);

	HeightMap* heightmap;
	Vector3	heightmapSize;

	Mesh* quad;
	Mesh* cube;

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

	Light* sun;

	float waterMov;
	float waterRot;
};
