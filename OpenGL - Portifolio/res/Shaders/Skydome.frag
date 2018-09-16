#version 430

uniform sampler2D uTexCloud1;
uniform sampler2D uTexCloud2;

uniform vec2 uTexOffset1;
uniform vec2 uTexOffset2;

in float vY;
in vec2 vTexCoord;

out vec4 outColor;
void main()
{
	vec3 colorLow = vec3(.516, .986, 1.0);
	vec3 colorHigh = vec3(.133, .353, .725);

	vec3 texCloud1 = texture(uTexCloud1, vTexCoord + uTexOffset1).rgb;
	vec3 texCloud2 = texture(uTexCloud2, vTexCoord + uTexOffset2).rgb;

	vec3 color = clamp(mix(colorLow, colorHigh, vY) + texCloud1 + texCloud2, 0.0, 1.0);
	outColor = vec4(color, 1.0);
}