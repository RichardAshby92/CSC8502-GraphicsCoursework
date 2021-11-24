#include "Renderer.h"
//#include "../NCLGL/OGLRenderer.h"
#include "../nclgl/Camera.h"
#include "../nclgl/HeightMap.h"
#include "../nclgl/SceneNode.h"
#include "../nclgl/Light.h"
#include "../nclgl/Shader.h"
#include "../nclgl/MeshMaterial.h"
#include "../nclgl/Particle.h"

#include "../nclgl/CubeRobot.h"
#include "../nclgl/Island.h"
#include "../nclgl/Markers.h"
#include "../nclgl/Plants.h"


Renderer::Renderer(Window &parent) : OGLRenderer(parent)	{
	//load meshses
	quad = Mesh::GenerateQuad();
	//plant = Mesh::LoadFromMeshFile("P_Bush01.msh");

	//load textures
	waterTex = SOIL_load_OGL_texture(TEXTUREDIR"water.TGA", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	sandTex = SOIL_load_OGL_texture(TEXTUREDIR"sand.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	rockTex = SOIL_load_OGL_texture(TEXTUREDIR"rock.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	grassTex = SOIL_load_OGL_texture(TEXTUREDIR"grass2.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	rainTex = SOIL_load_OGL_texture(TEXTUREDIR"Rain Drop.PNG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	waterBump = SOIL_load_OGL_texture(TEXTUREDIR"Barren RedsDOT3.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	sandBump = SOIL_load_OGL_texture(TEXTUREDIR"Barren RedsDOT3.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	rockBump = SOIL_load_OGL_texture(TEXTUREDIR"Barren RedsDOT3.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	grassBump = SOIL_load_OGL_texture(TEXTUREDIR"Barren RedsDOT3.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	cubeMap = SOIL_load_OGL_cubemap(TEXTUREDIR"yellowcloud_ft.JPG", TEXTUREDIR"yellowcloud_bk.JPG", TEXTUREDIR"yellowcloud_up.JPG",
		TEXTUREDIR"yellowcloud_dn.JPG", TEXTUREDIR"yellowcloud_rt.JPG", TEXTUREDIR"yellowcloud_lf.JPG", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);

	if (!waterTex || !sandTex || !rockTex || !grassTex || !cubeMap || !rainTex ) { return; } //check all checks are in place

	SetTextureRepeating(waterTex, true);
	SetTextureRepeating(sandTex, true);

	//load heightmaps
	heightmap = new HeightMap(TEXTUREDIR"islandMap.JPG");
	if (!heightmap) { return; }
	heightmapSize = heightmap->GetHeightmapSize();

	//load camera
	camera = new Camera(0.0f, 0.0f, heightmapSize * Vector3(0.3f, 0.2f, 0.65f));

	projMatrix = Matrix4::Perspective(1.0f, 15000.0f, (float)width / (float)height, 45.0f);
	//othographic projmatrix here

	//load shaders
	sceneShader = new Shader("SceneVertex.glsl", "SceneFragment.glsl");
	skyboxShader = new Shader("skyboxVertex.glsl", "skyboxFragment.glsl");
	reflectShader = new Shader("reflectVertex.glsl", "reflectFragment.glsl");
	terrainShader = new Shader("TerrainVertex.glsl", "TerrainFragment.glsl");
	rainShader = new Shader("RainVertex.glsl","RainFragment.glsl");

	if (!sceneShader->LoadSuccess()) { return; }
	if (!skyboxShader->LoadSuccess()) { return; } 
	if (!reflectShader->LoadSuccess()) {return;} 
	if (!terrainShader->LoadSuccess()) { return; }
	//if (!rainShader->LoadSuccess()) { return; }

	//load root
	root = new SceneNode();
	Plants* p = new Plants(heightmapSize);
	root->AddChild(p);
	Markers* s = new Markers(heightmapSize);
	root->AddChild(s);

	//load particle effects
	rain = new ParticleControl(heightmapSize);

	//load lights
	sun = new Light(heightmapSize * Vector3(0.0f, 5.0f, 0.55f), Vector4(1, 0.6, 0.0, 1), heightmapSize.x * 1.5f);

	//PostProcessing Buffers

	//GL States
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	// Bools and such
	waterMov = 0.1f;
	waterRot = 0.0f;

	autoCam = false;
	init = true;
}
Renderer::~Renderer()	{
	//delete meshses
	//delete textures
	//delete heightmaps
	//delete camera
	//delete shaders
	//delete lights
	//delete particle effects

	//FBOs
}

void Renderer::UpdateScene(float dt) {
	camera->UpdateCamera(autoCam, dt);
	viewMatrix = camera->BuildViewMatrix();
	root->Update(dt);
	rain->Update(dt);

	waterMov += dt * 0.025f;
	waterRot += dt * 0.01f;
}

void Renderer::RenderScene()	{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	//disable culling etc

	DrawSkyBox();
	DrawHeightMap();

	

	DrawRain(rain);
	DrawWater();
	DrawNode(root);

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
	BindShader(terrainShader);
	SetShaderLight(*sun);
	
	glUniform3fv(glGetUniformLocation(terrainShader->GetProgram(), "cameraPos"), 1, (float*)&camera->GetPosition());

	glUniform1i(glGetUniformLocation(terrainShader->GetProgram(), "diffuseTex"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sandTex);

	glUniform1i(glGetUniformLocation(terrainShader->GetProgram(), "diffuseTex1"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, grassTex);

	glUniform1i(glGetUniformLocation(terrainShader->GetProgram(), "diffuseTex2"), 2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, rockTex);

	modelMatrix.ToIdentity();
	textureMatrix.ToIdentity();
	
	UpdateShaderMatrices();
	heightmap->Draw();
}

void Renderer::DrawNode(SceneNode* n) {
	glBindTexture(GL_TEXTURE_2D, 0);
	if (n->GetMesh()) {
		BindShader(sceneShader);
		UpdateShaderMatrices();

		Matrix4 model = n->GetWorldTransform() * Matrix4::Scale(n->GetModelScale());
		glUniformMatrix4fv(glGetUniformLocation(sceneShader->GetProgram(), "modelMatrix"), 1, false, model.values);
		glUniform4fv(glGetUniformLocation(sceneShader->GetProgram(), "nodeColour"), 1, (float*)& n->GetColour());
		glUniform1i(glGetUniformLocation(sceneShader->GetProgram(), "useTexture"), n->GetTexture());

		if(n->GetMesh()->GetSubMeshCount() > 1){
			for (int i = 0; i < n->GetMesh()->GetSubMeshCount(); ++i)
			{
				std::vector<GLuint> temp = n->GetSubTextures();
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, temp[i]);
				n->GetMesh()->DrawSubMesh(i);
			}
		}
		else{ n->Draw(*this); }
	}

	for (vector<SceneNode*>::const_iterator i = n->GetChildIteratorStart(); i != n->GetChildIteratorEnd(); ++i) {
		DrawNode(*i);
	}
}

void Renderer::DrawWater() {
	BindShader(reflectShader);

	glUniform3fv(glGetUniformLocation(reflectShader->GetProgram(), "cameraPos"), 1, (float*)&camera->GetPosition());

	glUniform1i(glGetUniformLocation(reflectShader->GetProgram(), "diffuseTex"), 0);
	glUniform1i(glGetUniformLocation(reflectShader->GetProgram(), "cubeTex"), 2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, waterTex);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);

	modelMatrix =
		Matrix4::Translation(heightmapSize * Vector3(0.5f, 0.05f, 0.5f)) *
		Matrix4::Scale(heightmapSize * 1.0f) *
		Matrix4::Rotation(90, Vector3(1, 0, 0));

	textureMatrix =
		Matrix4::Translation(Vector3(waterMov, 0.0f, waterMov)) *
		Matrix4::Scale(Vector3(10, 10, 10)) *
		Matrix4::Rotation(waterRot, Vector3(0, 0, 1));

	UpdateShaderMatrices();
	quad->Draw();
}

void Renderer::DrawRain(ParticleControl* rain) {
	glBindTexture(GL_TEXTURE_2D, 0);
	
	BindShader(sceneShader);
	UpdateShaderMatrices();

	glUniform4fv(glGetUniformLocation(sceneShader->GetProgram(), "nodeColour"), 1, (float*)&rain->GetColour());
	//glUniform1i(glGetUniformLocation(sceneShader->GetProgram(), "useTexture"), rain->GetTexture());
	//glUniform1i(glGetUniformLocation(rainShader->GetProgram(), "diffuseTex"), 0);
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, rainTex);

	rain->Draw();
}

void Renderer::toggleAutoCam() {
	autoCam = !autoCam;
	camera->SetPosition(heightmapSize * Vector3(0.3f, 0.2f, 0.65f));
	camera->SetYaw(0.0f);
}