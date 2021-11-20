#pragma once

#include "../nclgl/OGLRenderer.h"
#include "../nclgl/Vector3.h"
#include "../nclgl/Mesh.h"

struct Particle {

	Vector3 particlePosition;
	Vector3 particleDirection;
	Mesh* particleMesh;
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

	void ResetParticle();

protected:
	float particleSpeed;
	float particleLife;
	//float particleSize;
	const static int particleAmount = 1000;

	Particle* p[particleAmount];

	Vector3 particleScale;
	Vector3 particleOrigin[particleAmount];
	Vector4 particleColour;
};
