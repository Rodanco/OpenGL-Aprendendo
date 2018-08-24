#version 430


uniform mat4 uWorld;
//Matrizes de transforma��o da camera
uniform mat4 uView;         //Posicionamento
uniform mat4 uProjection;   //Abertura
uniform vec3 uCameraPos;

//Atributos do vertice
in vec3 aPosition;
in vec3 aColor;


out vec3 vColor;

void main() {
    //Posicao do v�rtice no mundo
	vec4 worldPos = uWorld * vec4(aPosition, 1.0);

	//Posi��o com camera e proje��o
	gl_Position = uProjection * uView * worldPos;

	vColor = aColor;
}