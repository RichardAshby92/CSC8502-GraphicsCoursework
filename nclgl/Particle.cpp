#include "../nclgl/Particle.h"

ParticleControl::ParticleControl(Vector3 heightmapSize) {

	static const GLfloat vertexData[12] =
	{ -0.5f, -0.5f, 0.0f,
	   0.5f, -0.5f, 0.0f,
	  -0.5f, 0.5f, 0.0f,
	   0.5f, 0.5f, 0.0f };

	static const GLfloat colourData[4] = { 0.2f, 0.2f, 0.2f, 1.0f };

	particleSpeed = Vector3(0.0f, -10.0f, 0.0f);

	//GLuint particleTexture = 0;

	for (int i = 0; i < particleAmount; ++i) {
			
		float posX = rand() % 6000 + 2000;
		float posY = rand() % 55 + 255;
		float posZ = rand() % 6000 + 2000;

		ParticleContainer[i] = new Particle;
		ParticleContainer[i]->particlePosition = Vector3(posX, posY, posZ);
	}

	//first buffer - vertexs

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	//second buffer - positions

	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, particleAmount * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

	//third buffer - colours

	glGenBuffers(1, &colourBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
	glBufferData(GL_ARRAY_BUFFER, particleAmount * 4 * sizeof(GLubyte), colourData, GL_STREAM_DRAW);

}


ParticleControl::~ParticleControl() {
	//delete all instances
	//delete all buffers
}

void ParticleControl::Draw() {

	for (int i = 0; i < particleAmount; ++i) {

		float positionData[i * 4 + 0] = ParticleContainer[i]->particlePosition.x;
		float positionData[i * 4 + 0] = ParticleContainer[i]->particlePosition.y;
		float positionData[i * 4 + 0] = ParticleContainer[i]->particlePosition.z;
	}

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, particleAmount * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, particleAmount * 4 * sizeof(GLfloat), positionData);

	glVertexAttribDivisor(0, 0);
	glVertexAttribDivisor(1, 1);
	glVertexAttribDivisor(2, 1);

	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, particleAmount);
}

void ParticleControl::Update(float dt) {

	for (int i = 0; i < particleAmount; ++i)
	{
		ParticleContainer[i]->particlePosition += (particleSpeed * dt);
	}
}

/*void ParticleControl::ResetParticle() {
	for (int i = 0; i < particleAmount; ++i)
	{
		if (cmpr(p[i]->particlePosition.y, 0.0f, 1.0f)) {
			p[i]->particlePosition.y = 255;
		}
	}
}*/

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