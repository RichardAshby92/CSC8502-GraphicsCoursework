#include "Renderer.h"
#include "../NCLGL/OGLRenderer.h"
#include "../nclgl/Camera.h"
#include "../nclgl/HeightMap.h"
#include "../nclgl/SceneNode.h"

Renderer::Renderer(Window &parent) : OGLRenderer(parent)	{
	//load meshses
	quad = Mesh::GenerateQuad();

	//load textures
	//waterTex = SOIL_load_OGL_texture(TEXTUREDIR"water.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS); old texture not working? 
	waterTex = SOIL_load_OGL_texture(TEXTUREDIR"water.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	sandTex = SOIL_load_OGL_texture(TEXTUREDIR"sand.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	rockTex = SOIL_load_OGL_texture(TEXTUREDIR"rock.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	grassTex = SOIL_load_OGL_texture(TEXTUREDIR"grass2.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	waterBump = SOIL_load_OGL_texture(TEXTUREDIR"Barren RedsDOT3.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	sandBump = SOIL_load_OGL_texture(TEXTUREDIR"Barren RedsDOT3.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	rockBump = SOIL_load_OGL_texture(TEXTUREDIR"Barren RedsDOT3.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	grassBump = SOIL_load_OGL_texture(TEXTUREDIR"Barren RedsDOT3.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	cubeMap = SOIL_load_OGL_cubemap(TEXTUREDIR"yellowcloud_ft.JPG", TEXTUREDIR"yellowcloud_bk.JPG", TEXTUREDIR"yellowcloud_up.JPG",
		TEXTUREDIR"yellowcloud_dn.JPG", TEXTUREDIR"yellowcloud_rt.JPG", TEXTUREDIR"yellowcloud_lf.JPG", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);

	if (!waterTex || !sandTex || !rockTex || !grassTex || !cubeMap ) { return; }

	SetTextureRepeating(waterTex, true);
	SetTextureRepeating(sandTex, true);


	//load heightmaps
	heightmap = new HeightMap(TEXTUREDIR"islandMap.JPG");
	if (!heightmap) { return; }
	Vector3	heightmapSize = heightmap->GetHeightmapSize();

	//load camera
	camera = new Camera(0.0f, 0.0f, heightmapSize * Vector3(0.5f, 0.5f, 0.5f));
	projMatrix = Matrix4::Perspective(1.0f, 15000.0f, (float)width / (float)height, 45.0f);
	//othographic projmatrix here

	//load shaders
	//lightShader = new Shader("PerPixelVertex.glsl", "PerPixelFragment.glsl"); To be Added Later
	basicShader = new Shader("TexturedVertex.glsl", "TexturedFragment.glsl");
	reflectShader = new Shader("reflectVertex.glsl", "reflectFragment.glsl");
	skyboxShader = new Shader("skyboxVertex.glsl", "skyboxFragment.glsl");

	if(/*!lightShader->LoadSuccess() */ !basicShader->LoadSuccess() || !reflectShader->LoadSuccess() || !skyboxShader->LoadSuccess()) { return; }

	//load root
	root = new SceneNode();

	//load lights

	//GL States
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	// Bools and such
	waterMov = 0.0f;
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
	camera->UpdateCamera(dt);
	viewMatrix = camera->BuildViewMatrix();
}

void Renderer::RenderScene()	{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	//disable culling etc

	DrawSkyBox();
	DrawHeightMap();
	DrawNode(root);
	DrawWater();
	//renable culling etc
}

//helper functions
void Renderer::DrawSkyBox() {
	glDepthMask(GL_FALSE);

	BindShader(skyboxShader);
	UpdateShaderMatrices();

	quad->Draw();

	glDepthMask(GL_TRUE);
}

void Renderer::DrawHeightMap() {
	BindShader(basicShader); //change later
	UpdateShaderMatrices();

	glUniform1i(glGetUniformLocation(basicShader->GetProgram(), "diffuseTex"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sandTex);

	heightmap->Draw();
}

void Renderer::DrawNode(SceneNode* n) {

}

void Renderer::DrawWater() {
	BindShader(reflectShader);

}
