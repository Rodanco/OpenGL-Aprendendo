#version 430

in vec3 aPosition;
in vec2 aTexCoord;

uniform mat4 uWorld;
//Matrizes de transformação da camera
uniform mat4 uView;         //Posicionamento
uniform mat4 uProjection;   //Abertura
uniform vec3 uCameraPos;


out float vY;
out vec2 vTexCoord;

void main()
{
	gl_Position = uProjection * uView * uWorld * vec4(aPosition, 1.0);
	vY = aPosition.y;
	vTexCoord = aTexCoord;
}