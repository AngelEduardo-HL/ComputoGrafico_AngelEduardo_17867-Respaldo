#include "Application.h"
#include "ShaderFuncs.h"
#include <iostream>

//Geometria del cubo 3D
void Application::SetUpCubeGeometry()
{
	std::vector<float> geometry = {
	//Cara Frontal
	 -1.0f, 1.0f, 1.0f, 1.0f, //0
	 -1.0f, -1.0f, 1.0f, 1.0f, //1
	 1.0f, -1.0f, 1.0f, 1.0f,  //2
	 -1.0f, 1.0f, 1.0f, 1.0f, //0
	 1.0f, -1.0f, 1.0f, 1.0f, //1
	 1.0f, 1.0f, 1.0f, 1.0f, //3

	 //Cara - Atras
	 1.0f, 1.0f, -1.0f, 1.0f, //4
	 1.0f, -1.0f, -1.0f, 1.0f, //5
	 -1.0f, -1.0f, -1.0f, 1.0f, //6
	 1.0f, 1.0f, -1.0f, 1.0f, //4
	 -1.0f, -1.0f, -1.0f, 1.0f, //5
	 -1.0f, 1.0f, -1.0f, 1.0f, //6

	 //Cara - Izquierda
	 -1.0f, 1.0f, -1.0f, 1.0f, //8
	 -1.0f, -1.0f, -1.0f, 1.0f, //9
	 -1.0f, -1.0f, 1.0f, 1.0f, //10
	 -1.0f, 1.0f, -1.0f, 1.0f, //8
	 -1.0f, -1.0f, 1.0f, 1.0f, //9
	 -1.0f, 1.0f, 1.0f, 1.0f, //10

	 //Cara - Derecha
	 1.0f, 1.0f, 1.0f, 1.0f, //12
	 1.0f, -1.0f, 1.0f, 1.0f, //13
	 1.0f, -1.0f, -1.0f, 1.0f, //14
	 1.0f, 1.0f, 1.0f, 1.0f, //12
	 1.0f, -1.0f, -1.0f, 1.0f, //13
	 1.0f, 1.0f, -1.0f, 1.0f, //14

	 //Cara - Arriba
	 -1.0f, 1.0f, -1.0f, 1.0f, //16
	 -1.0f, 1.0f, 1.0f, 1.0f, //17
	 1.0f, 1.0f, 1.0f, 1.0f, //18
	 -1.0f, 1.0f, -1.0f, 1.0f, //16
	 1.0f, 1.0f, 1.0f, 1.0f, //17
	 1.0f, 1.0f, -1.0f, 1.0f, //18

	 //Cara - Abajo
	 -1.0f, -1.0f, 1.0f, 1.0f, //20
	 -1.0f, -1.0f, -1.0f, 1.0f, //21
	 1.0f, -1.0f, -1.0f, 1.0f, //22
	 -1.0f, -1.0f, 1.0f, 1.0f, //20
	 1.0f, -1.0f, -1.0f, 1.0f, //21
	 1.0f, -1.0f, 1.0f, 1.0f, //22


	 //Colores
	 // Frente - Rojo
	 1.0f, 0.0f, 0.0f, 1.0f, // V0
	 1.0f, 0.0f, 0.0f, 1.0f, // V1
	 1.0f, 0.0f, 0.0f, 1.0f, // V2
	 1.0f, 0.0f, 0.0f, 1.0f, // V3
	 1.0f, 0.0f, 0.0f, 1.0f, // V2
	 1.0f, 0.0f, 0.0f, 1.0f, // V3

	 // Atras - Verde
	 0.0f, 1.0f, 0.0f, 1.0f, // V4
	 0.0f, 1.0f, 0.0f, 1.0f, // V5
	 0.0f, 1.0f, 0.0f, 1.0f, // V6
	 0.0f, 1.0f, 0.0f, 1.0f, // V7
	 0.0f, 1.0f, 0.0f, 1.0f, // V6
	 0.0f, 1.0f, 0.0f, 1.0f, // V7

	 //Izquierda - Azul
	 0.0f, 0.0f, 1.0f, 1.0f, // V8
	 0.0f, 0.0f, 1.0f, 1.0f, // V9
	 0.0f, 0.0f, 1.0f, 1.0f, // V10
	 0.0f, 0.0f, 1.0f, 1.0f, // V11
	 0.0f, 0.0f, 1.0f, 1.0f, // V10
	 0.0f, 0.0f, 1.0f, 1.0f, // V11

	 //Derecha - Amarillo
	 1.0f, 1.0f, 0.0f, 1.0f, // V12
	 1.0f, 1.0f, 0.0f, 1.0f, // V13
	 1.0f, 1.0f, 0.0f, 1.0f, // V14
	 1.0f, 1.0f, 0.0f, 1.0f, // V15
	 1.0f, 1.0f, 0.0f, 1.0f, // V14
	 1.0f, 1.0f, 0.0f, 1.0f, // V15

	 //Arriba - Cyan
	 0.0f, 1.0f, 1.0f, 1.0f, // V16
	 0.0f, 1.0f, 1.0f, 1.0f, // V17
	 0.0f, 1.0f, 1.0f, 1.0f, // V18
	 0.0f, 1.0f, 1.0f, 1.0f, // V19
	 0.0f, 1.0f, 1.0f, 1.0f, // V18
	 0.0f, 1.0f, 1.0f, 1.0f, // V19

	 //Abajo - Magenta
	 1.0f, 0.0f, 1.0f, 1.0f, // V20
	 1.0f, 0.0f, 1.0f, 1.0f, // V21
	 1.0f, 0.0f, 1.0f, 1.0f, // V22
	 1.0f, 0.0f, 1.0f, 1.0f,  // V23
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
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const void*)((144) * sizeof(float))); //(index, size, type, normalized, stride, pointer)
	glEnableVertexAttribArray(1);
}

//Geometria para el Triangulo3D
void Application::SetUpTriangleGeometry()
{
	// 6 triángulos * 3 vértices = 18 vértices
	// Cada vértice lleva (x, y, z, w)
	std::vector<float> geometry = {

	 // Vértices
	
	// Base del triángulo
	 -1.0f, -1.0f,  1.0f, 1.0f,
	  1.0f, -1.0f,  1.0f, 1.0f,
	  0.0f,  1.0f,  0.0f, 1.0f,

	//Derecha
	 1.0f, -1.0f,  1.0f, 1.0f,
	 1.0f, -1.0f, -1.0f, 1.0f,
	 0.0f,  1.0f,  0.0f, 1.0f,

	 //Atras
	  1.0f, -1.0f, -1.0f, 1.0f,
	 -1.0f, -1.0f, -1.0f, 1.0f,
	  0.0f,  1.0f,  0.0f, 1.0f,

	  //Izquierda
	 -1.0f, -1.0f, -1.0f, 1.0f,
	 -1.0f, -1.0f,  1.0f, 1.0f,
	 0.0f,  1.0f,  0.0f, 1.0f,

	 //Base
	 -1.0f, -1.0f,  1.0f, 1.0f,
	  1.0f, -1.0f,  1.0f, 1.0f,
	  1.0f, -1.0f, -1.0f, 1.0f,
	  
	 -1.0f, -1.0f,  1.0f, 1.0f,
	  1.0f, -1.0f, -1.0f, 1.0f,
	 -1.0f, -1.0f, -1.0f, 1.0f,


	 1.0f, 0.0f, 0.0f, 1.0f,
	 1.0f, 0.0f, 0.0f, 1.0f,
	 1.0f, 0.0f, 0.0f, 1.0f,

	 0.0f, 1.0f, 0.0f, 1.0f,
	 0.0f, 1.0f, 0.0f, 1.0f,
	 0.0f, 1.0f, 0.0f, 1.0f,

	 0.0f, 0.0f, 1.0f, 1.0f,
	 0.0f, 0.0f, 1.0f, 1.0f,
	 0.0f, 0.0f, 1.0f, 1.0f,

	 1.0f, 1.0f, 0.0f, 1.0f,
	 1.0f, 1.0f, 0.0f, 1.0f,
	 1.0f, 1.0f, 0.0f, 1.0f,

	 1.0f, 0.0f, 1.0f, 1.0f,
	 1.0f, 0.0f, 1.0f, 1.0f,
	 1.0f, 0.0f, 1.0f, 1.0f,
	 
	 1.0f, 0.0f, 1.0f, 1.0f,
	 1.0f, 0.0f, 1.0f, 1.0f,
	 1.0f, 0.0f, 1.0f, 1.0f
	};

	// Crear VAO/VBO
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	ids["triangulo"] = VAO;

	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER,
		sizeof(GLfloat) * geometry.size(),
		geometry.data(),
		GL_STATIC_DRAW);

	// Atributo 0: posiciones (vec4)
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (const void*)0);
	glEnableVertexAttribArray(0);

	// Atributo 1: colores (vec4)
	// Offset = 72 floats (18 vértices * 4 componentes)
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const void*)(72 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Application::SetUpProgram1()
{
	GLuint ShadersID = InitializeProgramFromFiles("Shaders/VertextShader.glsl", "Shaders/FragmentShader.glsl"); //Cargo y compilo los shaders
	ids["program"] = ShadersID; //Guardo el ID del programa de shaders
	ids["time1"] = glGetUniformLocation(ids["program"], "time"); //Obtengo la localizacion de la variable time en el shader
	ids["DesX1"] = glGetUniformLocation(ids["program"], "DesX");
	ids["camera1"] = glGetUniformLocation(ids["program"], "camera");
	ids["projection1"] = glGetUniformLocation(ids["program"], "projection");
	ids["model1"] = glGetUniformLocation(ids["program"], "model");
}

//lo mismo que el 1 pero con la camara y proyeccion
void Application::SetUpProgram2()
{
	GLuint ShadersID = InitializeProgramFromFiles("Shaders/VertextCamera.glsl", "Shaders/FragmentShaderCamera.glsl"); //Cargo y compilo los shaders
	ids["program2"] = ShadersID; //Guardo el ID del programa de shaders
	ids["time2"] = glGetUniformLocation(ids["program2"], "time");
	ids["DesX2"] = glGetUniformLocation(ids["program2"], "DesX"); 
	ids["camera2"] = glGetUniformLocation(ids["program2"], "camera");
	ids["projection2"] = glGetUniformLocation(ids["program2"], "projection");
	ids["model2"] = glGetUniformLocation(ids["program2"], "model"); 
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

	//Tecla para cambiar de geometrias
	if (key == GLFW_KEY_R && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		//Cambia a false y true para alternar entre los programas de shaders
		currentProgram = !currentProgram;
		if (currentProgram)
		{
			std::cout << "Programa 2 activado + CUBO\n " << std::endl;
		}
		else
		{
			std::cout << "Programa 1 activado + TRIANGULO\n " << std::endl;
		}
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
	//Hace zoom modificado el Eye de la camara
	if (yoffset > 0) // Zoom in
	{
		zoom /= zoomSensitivity;
	}
	else if (yoffset < 0) // Zoom out
	{
		zoom *= zoomSensitivity;
	}

	zoom = glm::clamp(zoom, 0.1f, 10.0f); // Limitar el zoom

	std::cout << "Zoom: " << zoom << std::endl;
}

void Application::Setup()
{
	SetUpTriangleGeometry(); // Llamo a la funcion que crea la geometria
	SetUpProgram1(); // Llamo a la funcion que crea el programa de shaders
	SetUpProgram2(); // Llamo a la funcion que crea el programa de shaders con camara
	SetUpCubeGeometry(); // Llamo a la funcion que crea la geometria del cubo
	glEnable(GL_DEPTH_TEST); //Habilita el z-buffer
	projection = glm::perspective(45.0f, 1024.0f / 768.0f, 0.1f, 100.0f); //Matriz de proyeccion perspectiva
}

void Application::Update()
{
	time += 0.01f;
	eye = glm::vec3(2.0f, 2.0f, 2.0f) * zoom;
	center = glm::vec3(0.0f, 0.0f, 0.0f);
	camera = glm::lookAt(eye, center, glm::vec3(0.0f, 1.0f, 0.0f));

	//Transformaciones del modelo
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f), glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f)); //Eje X
	glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f), glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f)); //Eje Y

	model = rotateY * rotateX * translate * scale;
}

void Application::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpia el buffer de color y el z-buffer

	const bool useProgram = this->currentProgram;
	const GLuint programID = useProgram ? ids["program2"] : ids["program"];
	glUseProgram(programID);

	// Uniforms por programa (usa 1f si 'time' es float en el shader)
	if (useProgram) {
		glUniform1f(ids["time2"], (float)time);
		glUniform1f(ids["DesX2"], DesX);
		glUniformMatrix4fv(ids["model2"], 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(ids["camera2"], 1, GL_FALSE, &camera[0][0]);
		glUniformMatrix4fv(ids["projection2"], 1, GL_FALSE, &projection[0][0]);
	}
	else {
		glUniform1f(ids["time1"], (float)time);
		glUniform1f(ids["DesX1"], DesX);
		glUniformMatrix4fv(ids["model1"], 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(ids["camera1"], 1, GL_FALSE, &camera[0][0]);
		glUniformMatrix4fv(ids["projection1"], 1, GL_FALSE, &projection[0][0]);
	}

	// Elegir VAO correcto (ahora 'triangulo' existe)
	const GLuint VAO = useProgram ? ids["cubo"] : ids["triangulo"];
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, useProgram ? 36 : 18);
}
