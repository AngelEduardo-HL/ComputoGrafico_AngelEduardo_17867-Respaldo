#version 460 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor; // Atributo de color

out vec4 vertexColor; // Salida del color al fragment shader
uniform float time; // Variable de tiempo
uniform float DesX; // Desplazamiento en X


void main()
{
	vertexColor = vColor;
	vec4 newPosition = vPosition; 
	newPosition.x = newPosition.x + DesX; //Hace que se mueva con el valor que le pasamos desde la aplicacion
	gl_Position = newPosition; // Asignar la posición transformada
}