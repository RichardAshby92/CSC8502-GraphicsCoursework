#pragma once
#include "../nclgl/OGLRenderer.h"

class Camera;
class Mesh;
class HeightMap;

class Renderer : public OGLRenderer	{
public:
	Renderer(Window &parent);
	 ~Renderer(void);
	 
	 void RenderScene()			override;
	 void UpdateScene(float dt)	override;
protected:
	
	HeightMap* heightmap;

	Mesh* quad;

	Shader* lightShader;
	Shader* reflectShader;
	Shader* skyboxShader;

	Camera* camera;

	GLuint sandTex;
	GLuint waterTex;
	GLuint cubeMap;
};
