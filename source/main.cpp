#include <iostream>

//GLAD
#define GLAD_STATIC
#include <glad/glad.h>

//GLFW
#include <GLFW/glfw3.h>

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";


const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main(void)
{

    ///* Initialize the library */
    //if (!glfwInit())
    //{
    //    std::cout << "glfw init failed!" << std::endl;
    //    return -1;
    //}
    //    
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    ///* Create a windowed mode window and its OpenGL context */
    //GLFWwindow* window = glfwCreateWindow(640, 480, "VesPet", NULL, NULL);
    //if (!window)
    //{
    //    glfwTerminate();
    //    return -1;
    //}

    ///* Make the window's context current */
    //glfwMakeContextCurrent(window);

    //if (!gladLoadGL())
    //{
    //    std::cout << "Can't load GLAD!" << std::endl;
    //    return -1;
    //}

    //std::cout << "OpenGL" << GLVersion.major << "." << GLVersion.minor << std::endl;

    //glClearColor(0, 1, 0, 1);

    ///* Loop until the user closes the window */
    //while (!glfwWindowShouldClose(window))
    //{
    //    /* Render here */
    //    glClear(GL_COLOR_BUFFER_BIT);

    //    /* Swap front and back buffers */
    //    glfwSwapBuffers(window);

    //    /* Poll for and process events */
    //    glfwPollEvents();
    //}

    //glfwTerminate();
    //return 0;



    //������������� GLFW
    glfwInit();
    //��������� GLFW
    //�������� ����������� ��������� ������ OpenGL. 
    //�������� 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    //��������
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    //��������� �������� ��� �������� ��������� ��������
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //���������� ����������� ��������� ������� ����
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    //�������� �����
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //������������� GLAD
    if (!gladLoadGL())
    {
        std::cout << "Can't load GLAD!" << std::endl;
        return -1;
    }

    //std::cout << "OpenGL" << GLVersion.major << "." << GLVersion.minor << std::endl;
    
    //�������� ������� ��������� ������� ������ � �����
    glfwSetKeyCallback(window, key_callback);

    //��������� ������� �����
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    //
    glViewport(0, 0, width, height);

    //������ ���� ������� �����
    float x = 0.1f;
    float y = 0.3f;
    glClearColor(x, 0.3f, 0.3f, 1.0f);

    //������ ������� ������
    GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };

    //������� ����������� ������
    GLuint VBO;
    glGenBuffers(1, &VBO);

    //�������� ������
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //����������� ��������� ������ � ���� �����.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //�������� ����������� �������
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //�������� ��������� ���� ������� � �������
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //����� ��� �������� ���������� ������ �������
    GLint success;
    GLchar infoLog[512]; 
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    //���� ��� �����
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //�������� ������������ ������� 
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    //�������� ������� � �������
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //�������� ��������� ���������
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();

    //���������� �������� (���������� � ������������) � ����������
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    //����� ��� �������� ���������� ��������� ��������
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //������ ���������� ��������
    glUseProgram(shaderProgram);

    //�������� ��� �������� ��������
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //��� OpenGL ���������������� ��������� ������, ���������� ����� ���������� ������?
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    //��������� ���������� �������� ������� ���������:
    glEnableVertexAttribArray(0);

    //��������� ���������� �������
    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    // 1. ����������� VAO
    glBindVertexArray(VAO);
    // 2. �������� ��� ������ ������ � ����� ��� OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. ������������� ��������� �� ��������� �������� 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    //4. ���������� VAO
    glBindVertexArray(0);

    //������� ����
    while (!glfwWindowShouldClose(window))
    {
        //���������� �������
        glfwPollEvents();

        //������� �����
        x += 0.0001f;
        y += 0.0001f;
        glClearColor(x, y, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //// 0. �������� ������ � ��������� � ����� OpenGL
        //glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        //// 1. ����� ��������� ��������� �� ��������� ��������
        //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        //// 2. ���������� ���� ��������� ���������
        //glUseProgram(shaderProgram);
        //// 3. ������ ��� ������������ ������

        // 5. ������������ ������
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        //������ ������� - ����������� �� ������������
        glfwSwapBuffers(window);
    }

    
    //������� �������
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // ����� ������������ �������� ESC, �� ������������� �������� WindowShouldClose � true, 
    // � ���������� ����� ����� ���������
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
