#include "../nclgl/Particle.h"

ParticleControl::ParticleControl(Vector3 heightmapSize) {

	static const GLfloat vertexData[12] =
	{ -0.5f, -0.5f, 0.0f,
	   0.5f, -0.5f, 0.0f,
	  -0.5f, 0.5f, 0.0f,
	   0.5f, 0.5f, 0.0f };

	//static const GLfloat colourData[4] = { 0.2f, 0.2f, 0.2f, 1.0f };

	particleSpeed = Vector3(0.0f, -400.0f, 0.0f);
	particleColour = Vector4(0.8f, 0.7f, 0.5f, 1.0f);
	vertices = new Vector3[particleAmount];
	colours = new Vector4[particleAmount];

	//GLuint particleTexture = 0;

	for (int i = 0; i < particleAmount; ++i) {
			
		float posX = rand() % 7000 + 500;
		float posY = rand() % 2000;
		float posZ = rand() % 7000 + 500;

		ParticleContainer[i] = new Particle;
		ParticleContainer[i]->particlePosition = Vector3(posX, posY, posZ);
		ParticleContainer[i]->particleColour = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	}

	glGenBuffers(1, &bufferObject[VERTEX_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, bufferObject[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, particleAmount * sizeof(Vector3), 0, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &bufferObject[COLOUR_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, bufferObject[COLOUR_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, particleAmount * sizeof(Vector4), 0, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


ParticleControl::~ParticleControl() {
	//delete all instances
	//delete all buffers
}

void ParticleControl::Draw() {

	for (int i = 0; i < particleAmount; ++i) {
		vertices[i] = ParticleContainer[i]->particlePosition;
		colours[i] = ParticleContainer[i]->particleColour;
	}

	glBindVertexArray(arrayObject);
	//Send Data
	glBindBuffer(GL_ARRAY_BUFFER, bufferObject[VERTEX_BUFFER]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, particleAmount * sizeof(Vector3), (void*)vertices);
	glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), 0);
	glEnableVertexAttribArray(VERTEX_BUFFER);

	glBindBuffer(GL_ARRAY_BUFFER, bufferObject[COLOUR_BUFFER]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, particleAmount * sizeof(Vector4), (void*)colours);
	glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE, sizeof(Vector4), 0);
	glEnableVertexAttribArray(COLOUR_BUFFER);

	glDrawArrays(GL_POINTS, 0, particleAmount);
	glBindVertexArray(0);
}

void ParticleControl::Update(float dt) {

	for (int i = 0; i < particleAmount; ++i)
	{
		if (cmpr(ParticleContainer[i]->particlePosition.y, 0.0f, 5.0f)) { ResetParticle(i); }
		else { ParticleContainer[i]->particlePosition += (particleSpeed * dt); }
	}
}

void ParticleControl::ResetParticle(int i) {
	ParticleContainer[i]->particlePosition.y = rand() % 1000 + 1000;
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