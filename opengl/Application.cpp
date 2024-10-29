#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "window", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "glew init not ok Error!";

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        float positions[] = {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f, 0.5f,
             -0.5f, 0.5f,
        };

        unsigned int indices[] = {
            0, 1 , 2,
            2, 3 , 0
        };


        VertexArray va;
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));

       

        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        Shader Shader("res/shaders/basic.shader");
        Shader.Bind();
        Shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

        Renderer renderer;


        va.Unbond();
        vb.UnBind();
        ib.UnBind();
        Shader.Unbind();


        float r = 1.0f;
        float increment = 0.05f;
        float g = 1.0f;
        float increment2 = 0.03f;
        float b = 1.0f;
        float increment3 = 0.02f;
        float a = 1.0f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            Shader.Bind();
            Shader.SetUniform4f("u_Color", r, g, b, a);

            renderer.Draw(va, ib, Shader);

            bool test = false;
            float max = 0.5f;
            if (test)
            {
                if (r > max)
                    increment = -0.005f;
                else if (r < 0.0f)
                    increment = 0.005f;

                r += increment;

                if (g > max)
                    increment2 = -0.006f;
                else if (g < 0.0f)
                    increment2 = 0.006f;

                g += increment2;

                if (b > max)
                    increment3 = -0.003f;
                else if (b < 0.0f)
                    increment3 = 0.003f;

                b += increment3;
            }
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

    }
    glfwTerminate();
    return 0;
}
