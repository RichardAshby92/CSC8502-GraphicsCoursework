#pragma once

#include "../nclgl/OGLRenderer.h"
#include "../nclgl/Vector3.h"
#include "../nclgl/Mesh.h"

struct Particle {

	Vector3 particlePosition;
	Vector4 particleColour;
};

class ParticleControl : public Mesh {
public:
	ParticleControl(Vector3 heightmapSize);
	~ParticleControl();

	void Update(float dt);
	virtual void Draw();

	Vector3* GetWorldTransform();
	Vector3 GetModelScale();
	Vector4 GetColour() { return particleColour; }
	GLuint GetTexture() { return texture; }

	int GetParticleAmount() { return particleAmount; }

	int FindUnusedParticles();
	
	void ResetParticle(int i);
	bool cmpr(float a, float b, float c) { return fabs(a - b) < c; }

protected:
	const static int particleAmount = 10000;

	GLuint vertexBuffer;
	GLuint positionBuffer;
	GLuint colourBuffer;

	Particle* ParticleContainer[particleAmount];

	int lastParticle;

	Vector3 particleSpeed;
	Vector3 particleScale;
	Vector3 particleOrigin[particleAmount];
	Vector4 particleColour;

	GLuint texture;
};
