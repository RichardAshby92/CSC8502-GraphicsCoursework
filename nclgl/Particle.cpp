#include "../nclgl/Particle.h"

ParticleControl::ParticleControl(Vector3 heightmapSize) {

	static const GLfloat vertexData[12] =
	{ -0.5f, -0.5f, 0.0f,
	   0.5f, -0.5f, 0.0f,
	  -0.5f, 0.5f, 0.0f,
	   0.5f, 0.5f, 0.0f };

	//static const GLfloat colourData[4] = { 0.2f, 0.2f, 0.2f, 1.0f };

	particleSpeed = Vector3(0.0f, -100.0f, 0.0f);
	particleColour = Vector4(0.6f, 0.6f, 0.6f, 1.0f);

	//GLuint particleTexture = 0;

	for (int i = 0; i < particleAmount; ++i) {
			
		float posX = rand() % 6000 + 2000;
		float posY = rand() % 255 + 50;
		float posZ = rand() % 6000 + 2000;

		ParticleContainer[i] = new Particle;
		ParticleContainer[i]->particlePosition = Vector3(posX, posY, posZ);
	}

	glGenBuffers(1, &bufferObject[VERTEX_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, bufferObject[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, particleAmount * sizeof(Vector3), 0, GL_DYNAMIC_DRAW);

	/*
	glGenBuffers(1, &bufferObject[COLOUR_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, bufferObject[COLOUR_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, particleAmount * sizeof(Vector4), 0, GL_DYNAMIC_DRAW);*/

}


ParticleControl::~ParticleControl() {
	//delete all instances
	//delete all buffers
}

void ParticleControl::Draw() {

	vertices = new Vector3[particleAmount];

	for (int i = 0; i < particleAmount; ++i) {
		vertices[i] = ParticleContainer[i]->particlePosition;
	}

	glBindVertexArray(arrayObject);
	//Send Data
	glBindBuffer(GL_ARRAY_BUFFER, bufferObject[VERTEX_BUFFER]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, particleAmount * sizeof(Vector3), (void*)vertices);
	glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), 0);
	glEnableVertexAttribArray(VERTEX_BUFFER);

	glDrawArrays(GL_POINTS, 0, particleAmount);
}

void ParticleControl::Update(float dt) {

	for (int i = 0; i < particleAmount; ++i)
	{
		if (cmpr(ParticleContainer[i]->particlePosition.y, 0.0f, 1.0f)) { ResetParticle(i); }
		else { ParticleContainer[i]->particlePosition += (particleSpeed * dt); }
	}
}

void ParticleControl::ResetParticle(int i) {
	ParticleContainer[i]->particlePosition.y = 255;
}

/*
Vector3* ParticleControl::GetWorldTransform() {
	for (int i = 0; i < particleAmount; ++i) {
		particleOrigin[i] = p[i]->particlePosition;
	}

	return particleOrigin;
}
Vector3 ParticleControl::GetModelScale() {
	return particleScale;
}*/