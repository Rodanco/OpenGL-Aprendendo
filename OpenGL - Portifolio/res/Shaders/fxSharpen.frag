#version 430

uniform sampler2D uTexture;
uniform int width;
uniform int height;

uniform float uPercent;

in vec2 vTexCoord;
out vec4 outColor;

void main(void)
{
    float dx = 1.0 / width;
    float dy = 1.0 / height;

	vec3 topColor = -2 * texture(uTexture, vTexCoord + vec2(-dx, 0)).rgb;
	vec3 leftColor = -2 * texture(uTexture, vTexCoord + vec2(0, -dy)).rgb;
	vec3 downColor = -2 * texture(uTexture, vTexCoord + vec2(dx, 0)).rgb;
	vec3 rightColor = -2 * texture(uTexture, vTexCoord + vec2(0, dy)).rgb;
	vec3 centerColor = texture(uTexture, vTexCoord).rgb * 10;

	vec3 kernelColor = topColor + leftColor + downColor + rightColor + centerColor;

	vec3 originalColor = texture(uTexture, vTexCoord).rgb;

	vec3 result = mix(originalColor, kernelColor, uPercent);

	outColor = vec4(result, 1.0);


    #/vec3 color1 = texture(uTexture, vTexCoord + vec2(-dx, -dy)).rgb;
    #/vec3 color2 = 2.0 * texture(uTexture, vTexCoord + vec2(-dx, 0)).rgb;
    #/vec3 color3 = texture(uTexture, vTexCoord + vec2(-dx, dy)).rgb;

    #/vec3 color4 = texture(uTexture, vTexCoord + vec2(dx, -dy)).rgb;
    #/vec3 color5 = 2.0 * texture(uTexture, vTexCoord + vec2(dx, 0)).rgb;
    #/vec3 color6 = texture(uTexture, vTexCoord + vec2(dx, dy)).rgb;

    #/outColor = vec4((color1 + color2 + color3 - color4 - color5 - color6).rrr, 1.0);
}