#include "../nclgl/Particle.h"

ParticleControl::ParticleControl(Vector3 heightmapSize) {
	particleSpeed = 10.0f;
	particleLife = 100.0f;
	particleScale = Vector3(1, 1, 1);
	particleColour = Vector4(0.2, 0.2, 0.2, 1);
	GLuint particleTexture = 0;

	for (int i = 0; i < particleAmount; ++i) {
			
		float posX = rand() % 6000 + 2000;
		float posY = rand() % 6000 + 2000;

		p[i] = new Particle;
		p[i]->particlePosition = Vector3(posX, 255, posY);
		p[i]->particleDirection = Vector3(0, -1, 0);
		p[i]->particleMesh = Mesh::GenerateQuad();
	}
}

ParticleControl::~ParticleControl() {
	//delete all particles
}

void ParticleControl::Draw() {

	for (int i = 0; i < particleAmount; ++i) {
		p[i]->particleMesh->Draw();
	}
}

void ParticleControl::Update(float dt) {
	for (int i = 0; i < particleAmount; ++i) 
	{
		p[i]->particlePosition += (p[i]->particleDirection) * dt;
	}
}

void ParticleControl::ResetParticle() {
	for (int i = 0; i < particleAmount; ++i)
	{
		if (p[i]->particlePosition.y == 0.0f) {
			p[i]->particlePosition.y = 255;
		}
	}
}

Vector3* ParticleControl::GetWorldTransform() {
	for (int i = 0; i < particleAmount; ++i) {
		particleOrigin[i] = p[i]->particlePosition;
	}

	return particleOrigin;
}
Vector3 ParticleControl::GetModelScale() {
	return particleScale;
}