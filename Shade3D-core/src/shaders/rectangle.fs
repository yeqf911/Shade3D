#version 330 core

out vec4 color;
in vec4 pos;

uniform vec2 light_pos;
uniform vec4 colour;

void main()
{

	float intensity = 1.0 / length(pos.xy - light_pos);
	//color = mix(texture(ourTexture1, myTexCoord), texture(outTexture2, myTexCoord), 0.2);
	color = colour * intensity;
}