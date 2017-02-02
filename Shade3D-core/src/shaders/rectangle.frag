#version 330 core

out vec4 color;
in vec3 myColor;
in vec2 myTexCoord;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
	//color = mix(texture(ourTexture1, myTexCoord), texture(outTexture2, myTexCoord), 0.2);
	color = vec4(myColor, 1.0f);
}