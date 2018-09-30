#version 430

in vec3 aPosition;
in vec2 aTexCoord;
		
out vec2 vTexCoord;

uniform mat4 uWorld;
uniform mat4 uView;
uniform mat4 uProjection;

void main(void) 
{
    gl_Position = 
        uProjection * uView * uWorld *
        vec4(aPosition, 1.0);

	vTexCoord = aTexCoord;
}