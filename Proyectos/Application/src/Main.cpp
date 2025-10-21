#include "glad.h"
#include "GLFW/glfw3.h"
#include "Application.h"

Application app;

// Callback que se ejecuta cuando se presiona una tecla
void AppCloseCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	app.keyCallBack(key, scancode, action, mods);
}

void AppMouseCallBack(GLFWwindow* window, double mouseX, double mouseY)
{
    app.mouseCallBack(mouseX, mouseY);
}

void AppScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    app.MouseScrollCallback(xoffset, yoffset);
}

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    app.window = glfwCreateWindow(1024, 768, "Hello Application", NULL, NULL);
    if (!app.window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(app.window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
		return -1;
    }

    glfwSetKeyCallback(app.window, AppCloseCallBack);
	glfwSetCursorPosCallback(app.window, AppMouseCallBack);
	glfwSetScrollCallback(app.window, AppScrollCallback);


	app.Setup();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(app.window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* Poll for and process events */
        glfwPollEvents();
        app.Update();

		//Llama a la funcion para cerrar la ventana con la tecla escape
        

		app.Draw();
        /* Swap front and back buffers */
        glfwSwapBuffers(app.window);
    }

    glfwTerminate();
    return 0;
}