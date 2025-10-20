#include "Application.h"
#include "ShaderFuncs.h"
#include <iostream>

//Geometria del cubo 3D
void Application::SetUpCubeGeometry()
{
	std::vector<float> geometry = {
	//Frente
	 -1.0f, -1.0f,  1.0f, 1.0f,
	  1.0f, -1.0f,  1.0f, 1.0f,
	 -1.0f,  1.0f,  1.0f, 1.0f,
	  1.0f,  1.0f,  1.0f, 1.0f,

	//Atrás
	 -1.0f, -1.0f, -1.0f, 1.0f,
	 1.0f, -1.0f, -1.0f, 1.0f,
	 -1.0f,  1.0f, -1.0f, 1.0f,
	 1.0f,  1.0f, -1.0f, 1.0f,

	//Izquierda
	 -1.0f, -1.0f, -1.0f, 1.0f,
	 -1.0f, -1.0f,  1.0f, 1.0f,
	 -1.0f,  1.0f, -1.0f, 1.0f,
	 -1.0f,  1.0f,  1.0f, 1.0f,

	//Derecha 
	 1.0f, -1.0f,  1.0f, 1.0f,
	 1.0f, -1.0f, -1.0f, 1.0f,
	 1.0f,  1.0f,  1.0f, 1.0f,
	 1.0f,  1.0f, -1.0f, 1.0f,

	//Arriba
	 -1.0f,  1.0f,  1.0f, 1.0f,
	 1.0f,  1.0f,  1.0f, 1.0f,
	 -1.0f,  1.0f, -1.0f, 1.0f,
	 1.0f,  1.0f, -1.0f, 1.0f,

	//Abajo
	 -1.0f, -1.0f, -1.0f, 1.0f,
	 1.0f, -1.0f, -1.0f, 1.0f,
	 -1.0f, -1.0f,  1.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 1.0f,

		 
	 //Colores

	// Frente - Rojo
	 1.0f, 0.0f, 0.0f, 1.0f, // V0
	 1.0f, 0.0f, 0.0f, 1.0f, // V1
	 1.0f, 0.0f, 0.0f, 1.0f, // V2
	 1.0f, 0.0f, 0.0f, 1.0f, // V3

	// Atras - Verde
	 0.0f, 1.0f, 0.0f, 1.0f, // V4
	 0.0f, 1.0f, 0.0f, 1.0f, // V5
	 0.0f, 1.0f, 0.0f, 1.0f, // V6
	 0.0f, 1.0f, 0.0f, 1.0f, // V7

	//Izquierda - Azul
	 0.0f, 0.0f, 1.0f, 1.0f, // V8
	 0.0f, 0.0f, 1.0f, 1.0f, // V9
	 0.0f, 0.0f, 1.0f, 1.0f, // V10
	 0.0f, 0.0f, 1.0f, 1.0f, // V11

	 //Derecha - Amarillo
	 1.0f, 1.0f, 0.0f, 1.0f, // V12
	 1.0f, 1.0f, 0.0f, 1.0f, // V13
	 1.0f, 1.0f, 0.0f, 1.0f, // V14
	 1.0f, 1.0f, 0.0f, 1.0f, // V15

	//Arriba - Cyan
	 0.0f, 1.0f, 1.0f, 1.0f, // V16
	 0.0f, 1.0f, 1.0f, 1.0f, // V17
	 0.0f, 1.0f, 1.0f, 1.0f, // V18
	 0.0f, 1.0f, 1.0f, 1.0f, // V19

	//Abajo - Magenta
	 1.0f, 0.0f, 1.0f, 1.0f, // V20
	 1.0f, 0.0f, 1.0f, 1.0f, // V21
	 1.0f, 0.0f, 1.0f, 1.0f, // V22
	 1.0f, 0.0f, 1.0f, 1.0f  // V23


	};
	//Crear VAO
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	ids["cubo"] = VAO;

	glBindVertexArray(VAO);

	//Crear VBO vertices
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //Esto aun no manda nada a la GPU

	//Pasar arreglo de vertices a la memoria de la GPU
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(GLfloat) * geometry.size(), //Calculo el tamaño en bytes del arreglo
		&geometry[0],
		GL_STATIC_DRAW); //Mandamos la geometria el Buffer

	//Vertices
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0); //(index, size, type, normalized, stride, pointer)
	glEnableVertexAttribArray(0);

	//Colores
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const void*)((16 * 6) * sizeof(float))); //(index, size, type, normalized, stride, pointer)
	glEnableVertexAttribArray(1);
}

// Refactorizacion de la Geometria que estaba en Setup
void Application::SetUpGeometry()
{
	//Arreglo de vertices y colores del cuadrado
	std::vector<float> geometry
	{
		//X,    Y,    Z,    W
		//Cuadrado
		-1.0f, -1.0f, 0.0f, 1.0f, //Vertice 1
		-1.0f,  1.0f, 0.0f, 1.0f, //Vertice 2
		 1.0f, -1.0f, 0.0f, 1.0f, //Vertice 3
		 1.0f,  1.0f, 0.0f, 1.0f, //Vertice 4


		1.0f, 0.0f, 0.0f, 1.0f,   //Color Rojo Vertice 1
		0.0f, 1.0f, 0.0f, 1.0f,   //Color Verde Vertice 2
		0.0f, 0.0f, 1.0f, 1.0f,    //Color Azul Vertice 3
		1.0f, 1.0f, 0.0f, 1.0f    //Color Amarillo Vertice 4
	};

	//Crear VAO
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	ids["cuadrado"] = VAO;

	glBindVertexArray(VAO);

	//Crear VBO vertices
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //Esto aun no manda nada a la GPU

	//Pasar arreglo de vertices a la memoria de la GPU
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(GLfloat) * geometry.size(), //Calculo el tamaño en bytes del arreglo
		&geometry[0],
		GL_STATIC_DRAW); //Mandamos la geometria el Buffer

	//Vertices
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0); //(index, size, type, normalized, stride, pointer)
	glEnableVertexAttribArray(0);

	//Colores
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const void*)(16*sizeof(float))); //(index, size, type, normalized, stride, pointer)
	glEnableVertexAttribArray(1);
}

void Application::SetUpProgram1()
{
	GLuint ShadersID = InitializeProgramFromFiles("Shaders/VertextShader.glsl", "Shaders/FragmentShader.glsl"); //Cargo y compilo los shaders
	ids["program"] = ShadersID; //Guardo el ID del programa de shaders
	ids["time"] = glGetUniformLocation(ids["program"], "time"); //Obtengo la localizacion de la variable time en el shader
}

//lo mismo que el 1 pero con la camara y proyeccion
void Application::SetUpProgram2()
{
	GLuint ShadersID = InitializeProgramFromFiles("Shaders/VertextCamera.glsl", "Shaders/FragmentShaderCamera.glsl"); //Cargo y compilo los shaders
	ids["program2"] = ShadersID; //Guardo el ID del programa de shaders
	ids["time2"] = glGetUniformLocation(ids["program2"], "time");
	ids["DesX"] = glGetUniformLocation(ids["program2"], "DesX"); 
	ids["camera"] = glGetUniformLocation(ids["program2"], "camera");
	ids["projection"] = glGetUniformLocation(ids["program2"], "projection");
	ids["model"] = glGetUniformLocation(ids["program2"], "model"); 
}

void Application::keyCallBack(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window, true);
	}

	//Teclas para mover hacia la derecha
	if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)) 
	{
		DesX += 0.01f;
		std::cout << "Mover a la derecha" << std::endl;
	}

	//Teclas para mover hacia la izquierda
	if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)) 
	{
		DesX -= 0.01f;
		std::cout << "Mover a la izquierda" << std::endl;
	}
}

void Application::mouseCallBack(double mouseX, double mouseY)
{
	//Detecta la posicion del mouse en la ventana
	glfwGetCursorPos(window, &mouseX, &mouseY);

	int winW, winH;
	glfwGetWindowSize(window, &winW, &winH);
	if (winW <= 0) winW = 1;
	if (winH <= 0) winH = 1;

	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	//Normalizar las coordenadas del mouse a rango [-1, 1]
	float nx = 2.0f * float(mouseX) / float(winW) - 1.0f; 
	float ny = -2.0f * float(mouseY) / float(winH) + 1.0f;

	//Mapear a aungulos de rotacion
	yaw = nx * (yawRangeDeg * 0.5f) * mouseSensitivity;
	pitch = -ny * (pitchRangeDeg * 0.5f) * mouseSensitivity;

	//Coordenadas del mouse
	std::cout << "Mouse X: " << mouseX << " Mouse Y: " << mouseY << std::endl;
}

void Application::MouseScrollCallback(double xoffset, double yoffset)
{
	float factor = std::pow(zoomSensitivity, static_cast<float>(yoffset));
	zoom *= factor;

	std::cout << "Zoom: " << zoom << std::endl;
}

void Application::Setup()
{
	SetUpGeometry(); // Llamo a la funcion que crea la geometria
	SetUpProgram1(); // Llamo a la funcion que crea el programa de shaders
	SetUpProgram2(); // Llamo a la funcion que crea el programa de shaders con camara
	SetUpCubeGeometry(); // Llamo a la funcion que crea la geometria del cubo
	glEnable(GL_DEPTH_TEST); //Habilita el z-buffer
	projection = glm::perspective(45.0f, 1024.0f / 768.0f, 0.1f, 100.0f); //Matriz de proyeccion perspectiva
}

void Application::Update()
{
	time += 0.01f;
	eye = glm::vec3(2.0f, 2.0f, 2.0f);
	center = glm::vec3(0.0f, 0.0f, 0.0f);
	camera = glm::lookAt(eye, center, glm::vec3(0.0f, 1.0f, 0.0f));

	//Transformaciones del modelo
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.5f, 1.0f) * zoom);
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f), glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f)); //Eje X
	glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f), glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f)); //Eje Y

	model = rotateY * rotateX * translate * scale;
}

void Application::Draw()
{
	glUseProgram(ids["program2"]); //Uso el programa de shaders
	glBindVertexArray(ids["cubo"]); //Digo que geometria voy a usar
	
	glUniform1f(ids["time2"], time); //Paso el valor de time al shader
	glUniform1f(ids["DesX"], DesX); //Paso el valor de DesX al shader

	glUniformMatrix4fv(ids["model"], 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(ids["camera"], 1, GL_FALSE, &camera[0][0]); //Paso la matriz de la camara al shader
	glUniformMatrix4fv(ids["projection"], 1, GL_FALSE, &projection[0][0]); //Paso la matriz de proyeccion al shader

	//Dibujo la geometria del cubo
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 29); //Dibujo el cubo 
}