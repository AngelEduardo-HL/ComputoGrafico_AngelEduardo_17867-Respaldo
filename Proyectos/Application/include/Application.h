#pragma once
#include <vector>
#include <map>
#include "glad.h"
#include <iostream>
#include "GLFW/glfw3.h"
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Application
{
private:
	

	std::map<std::string, GLuint> ids;

	// Refactorizacion de la Geometria que estaba en Setup
	void SetUpCubeGeometry();
	void SetUpGeometry();
	void SetUpProgram1();
	void SetUpProgram2();

	float DesX{ 0.0f }; // Variable para controlar el desplazamiento en X
	float time{ 0.0f }; // Variable para controlar el tiempo

	float mouseSensitivity = 1.5f; // Sensibilidad del mouse
	float yaw = 0.0f;     // grados, rotación sobre Y
	float pitch = 0.0f;   // grados, rotación sobre X
	float yawRangeDeg = 180.0f; // de borde a borde de ventana
	float pitchRangeDeg = 180.0f;  // de borde a borde de ventana

	bool currentProgram = true; // Programa actual (true: programa 1, false: programa 2)

	float zoom = 2.0f; // Escala acual del cubo
	float zoomSensitivity = 1.1f; // Sensibilidad del zoom

	glm::mat4 camera;
	glm::mat4 projection;
	glm::mat4 model;
	glm::vec3 eye{0.0f, 0.0f, 2.0f};
	glm::vec3 center{0.1f, 0.1f, 0.5f};


public:

	GLFWwindow* window;
	void Setup();
	void Update();
	void Draw();
	void keyCallBack(int key, int scancode, int action, int mods);
	void mouseCallBack(double mouseX, double mouseY);
	void MouseScrollCallback(double xoffset, double yoffset);

};