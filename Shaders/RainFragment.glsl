#version 330 core

uniform sampler2D diffuseTex;

in Vertex	{
	vec4 colour;
	vec2 texCoord;
} IN;

out vec4 fragColour;

void main(void)	{
	//fragColor = IN.colour* texture(diffuseTex, IN.texCoord);

	fragColour = IN.colour;
}
