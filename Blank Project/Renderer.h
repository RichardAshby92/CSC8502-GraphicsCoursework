#pragma once
#include "../nclgl/OGLRenderer.h"

class Camera;
class Mesh;
class HeightMap;
class SceneNode;

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

	Mesh* quad;

	Shader* basicShader;
	Shader* lightShader;
	Shader* reflectShader;
	Shader* skyboxShader;

	Camera* camera;

	GLuint sandTex;
	GLuint sandBump;
	GLuint waterTex;
	GLuint waterBump;
	GLuint cubeMap;

	SceneNode* root;
};
