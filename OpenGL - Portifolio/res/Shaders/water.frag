#version 430

in vec2 vTexCoord;

out vec4 outColor;

void main(void) 
{
	vec2 ok = vTexCoord;
    outColor = vec4(0.0, 0.0, 1.0, 1.0);
}