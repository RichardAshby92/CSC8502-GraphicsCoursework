#include "Renderer.h"
#include "../NCLGL/OGLRenderer.h"
#include "../nclgl/Camera.h"
#include "../nclgl/HeightMap.h"

Renderer::Renderer(Window &parent) : OGLRenderer(parent)	{
	//load meshses
	quad = Mesh::GenerateQuad();

	//load textures
	waterTex = SOIL_load_OGL_texture(TEXTUREDIR"water.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	sandTex = SOIL_load_OGL_texture(TEXTUREDIR"Barren Reds.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	cubeMap = SOIL_load_OGL_cubemap(TEXTUREDIR"rusted_west.JPG", TEXTUREDIR"rusted_east.JPG", TEXTUREDIR"rusted_up.JPG", TEXTUREDIR"rusted_down.JPG",
		TEXTUREDIR"rusted_south.JPG", TEXTUREDIR"rusted_north.JPG", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);

	if (!waterTex || !sandTex || !cubeMap) { return; }
	//load heightmaps
	heightmap = new HeightMap(TEXTUREDIR"noise.png");

	//load camera
	camera = new Camera();

	//load shaders
	lightShader = new Shader("basicVertex.glsl", "colourFragment.glsl");
	reflectShader = new Shader("basicVertex.glsl", "colourFragment.glsl");
	skyboxShader = new Shader("basicVertex.glsl", "colourFragment.glsl");

	if(!lightShader->LoadSuccess() || !reflectShader->LoadSuccess() || !skyboxShader->LoadSuccess()) {return;}

	//load lights

	init = true;
}
Renderer::~Renderer()	{
	//delete meshses
	//delete textures
	//delete heightmaps
	//delete camera
	//delete shaders
}

void Renderer::UpdateScene(float dt) {

}

void Renderer::RenderScene()	{
	glClearColor(0.2f,0.2f,0.2f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);	

	BindShader(basicShader);
	triangle->Draw();
}

//helper functions