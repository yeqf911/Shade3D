#version 330 core

out vec4 color;

in DATA
{
	vec4 position;
	vec4 color;
} fs_in;

uniform vec2 light_pos;


void main()
{
	float intensity = 1.0 / length(fs_in.position.xy - light_pos.xy);
	//color = mix(texture(ourTexture1, myTexCoord), texture(outTexture2, myTexCoord), 0.2);
	color = fs_in.color * intensity;
}