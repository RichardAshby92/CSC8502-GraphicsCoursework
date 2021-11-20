#version 330 core

uniform sampler2D diffuseTex;
uniform sampler2D diffuseTex1;
uniform sampler2D diffuseTex2;

uniform vec3 cameraPos;
uniform vec4 lightColour;
uniform vec3 lightPos;
uniform float lightRadius;

in Vertex {
	vec3 colour;
	vec2 texCoord;
	vec3 normal;
	vec3 worldPos;
} IN;

float temp;

out vec4 fragColour;
out vec2 texCoord;
out vec3 normal;
out vec3 worldPos;

vec4 tempColour1 = texture(diffuseTex, texCoord);
vec4 tempColour2 = texture(diffuseTex1, texCoord);
vec4 tempColour3 = texture(diffuseTex2, texCoord);

float a = smoothstep(0.0f, 40.0f, worldPos.y);
float b = smoothstep(40.0f, 255.0f, worldPos.y);

vec4 blend1 = mix(tempColour1, tempColour2, a);
vec4 blend2 = mix(tempColour2, tempColour3, b);

void main(void)	{
	vec3 incident = normalize(lightPos - IN.worldPos);
	vec3 viewDir = normalize(cameraPos - IN.worldPos);
	vec3 halfDir = normalize(incident + viewDir);
	
	vec4 diffuse;
	
	if(IN.worldPos.y <= 38.0f) {
		diffuse = texture(diffuseTex, IN.texCoord);
	}
	else if (IN.worldPos.y > 38.0f && IN.worldPos.y <= 40.0f){
		diffuse = blend1;
	}
	else if(IN.worldPos.y > 40.0f && IN.worldPos.y <= 198.0f){
		diffuse = texture(diffuseTex1, IN.texCoord);
	}
	else if(IN.worldPos.y > 198.0f && IN.worldPos.y < 200.0f){
		diffuse = blend2;
	}
	else if(IN.worldPos.y >= 200.0f){
		diffuse = texture(diffuseTex2, IN.texCoord);
	}



	float lambert = max(dot(incident, IN.normal), 0.0f);
	float distance = length(lightPos - IN.worldPos);
	float attenuation = 1.0 - clamp(distance / lightRadius, 0.0, 1.0);
	
	float specFactor = clamp(dot(halfDir, IN.normal), 0.0, 1.0);
	specFactor = pow(specFactor, 60.0);
	
	vec3 surface = (diffuse.rgb * lightColour.rgb);
	fragColour.rgb = surface * lambert * attenuation;
	fragColour.rgb += (lightColour.rgb * specFactor)*attenuation*0.33;
	fragColour.rgb += surface * 0.1f;
	fragColour.a = diffuse.a;
}