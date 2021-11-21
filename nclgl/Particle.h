#pragma once

#include "../nclgl/OGLRenderer.h"
#include "../nclgl/Vector3.h"
#include "../nclgl/Mesh.h"

struct Particle {

	Vector3 particlePosition;
};

class ParticleControl : public Mesh {
public:
	ParticleControl(Vector3 heightmapSize);
	~ParticleControl();

	void Update(float dt);
	virtual void Draw();

	Vector3* GetWorldTransform();
	Vector3 GetModelScale();
	int GetParticleAmount() { return particleAmount; }

	int FindUnusedParticles();
	
	void ResetParticle();
	bool cmpr(float a, float b, float c) { return fabs(a - b) < c; }

protected:
	const static int particleAmount = 500;

	GLuint vertexBuffer;
	GLuint positionBuffer;
	GLuint colourBuffer;

	Particle* ParticleContainer[particleAmount];

	int lastParticle;

	Vector4 particleColour;
	Vector3 particleSpeed;
	Vector3 particleScale;
	Vector3 particleOrigin[particleAmount];
	Vector4 particleColour;
};
