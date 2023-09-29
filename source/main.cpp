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



    //Инициализация GLFW
    glfwInit();
    //Настройка GLFW
    //Задается минимальная требуемая версия OpenGL. 
    //Мажорная 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    //Минорная
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    //Установка профайла для которого создается контекст
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //Выключение возможности изменения размера окна
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    //создание формы
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //инициализация GLAD
    if (!gladLoadGL())
    {
        std::cout << "Can't load GLAD!" << std::endl;
        return -1;
    }

    //std::cout << "OpenGL" << GLVersion.major << "." << GLVersion.minor << std::endl;
    
    //привязка функции обработки нажатых клавиш к форме
    glfwSetKeyCallback(window, key_callback);

    //получение размера формы
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    //
    glViewport(0, 0, width, height);

    //задаем цвет очистки формы
    float x = 0.1f;
    float y = 0.3f;
    glClearColor(x, 0.3f, 0.3f, 1.0f);

    //задаем вершины фигуры
    GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };

    //задание вертексного буфера
    GLuint VBO;
    glGenBuffers(1, &VBO);

    //привязка буфера
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //копирование вершинных данных в этот буфер.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //создание вертексного шейдера
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //привзяка исходного кода шейдера к объекту
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //фигня для проверки успешности сборки шейдера
    GLint success;
    GLchar infoLog[512]; 
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    //если все плохо
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //создание фрагментного шейдера 
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    //привязка шейдера к объекту
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //создание шейдерной программы
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();

    //связывание шейдоров (векторного и фрагментного) с программой
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    //фигня для проверки успешности программы шейдеров
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //запуск проограммы шейдеров
    glUseProgram(shaderProgram);

    //удаление уже ненужных шейдеров
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //как OpenGL интерпритировать вершинные данные, переданные через вертексный шейдер?
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    //передадим вершинному атрибуту позицию аргумента:
    glEnableVertexAttribArray(0);

    //генерация вершинного массива
    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    // 1. Привязываем VAO
    glBindVertexArray(VAO);
    // 2. Копируем наш массив вершин в буфер для OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. Устанавливаем указатели на вершинные атрибуты 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    //4. Отвязываем VAO
    glBindVertexArray(0);

    //игровой цикл
    while (!glfwWindowShouldClose(window))
    {
        //обработчик событий
        glfwPollEvents();

        //очистка формы
        x += 0.0001f;
        y += 0.0001f;
        glClearColor(x, y, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //// 0. Копируем массив с вершинами в буфер OpenGL
        //glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        //// 1. Затем установим указатели на вершинные атрибуты
        //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        //// 2. Используем нашу шейдерную программу
        //glUseProgram(shaderProgram);
        //// 3. Теперь уже отрисовываем объект

        // 5. Отрисовываем объект
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        //замена буферов - выведенного на отрисованный
        glfwSwapBuffers(window);
    }

    
    //очистка буферов
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true, 
    // и приложение после этого закроется
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
