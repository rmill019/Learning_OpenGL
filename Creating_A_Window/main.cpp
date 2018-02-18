// IMPORTANT TO INCLUDE glad.h BEFORE glfw3.h. If not then we get a compile error
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>

// Function prototypes
void framebuffer_size_callback (GLFWwindow* window, int width, int height);
void processInput (GLFWwindow* window);

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

int main()
{
	glfwInit();
	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	
	// Create a window object
	GLFWwindow* window = glfwCreateWindow (800, 600, "LearnOpenGL", NULL, NULL);
	// If the window if Null (failed to be created)
	if (window == NULL)
	{
		// Display a message to the terminal saying the window creation failed
		std::cout << "Failed to create GLFW window" << std::endl;
		// End GLFW
		glfwTerminate ();
		return -1;
	}

	glfwMakeContextCurrent (window);
	glfwSetFramebufferSizeCallback (window, framebuffer_size_callback);

	// GLAD manages function pointers for OpenGL so we want to initialize GLAD before we call any OpenGL function
	if (!gladLoadGLLoader ((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Build and compile our shader program
	// ------------------------------------

	// VERTEX SHADER
	unsigned int vertexShader;
	vertexShader = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource (vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader (vertexShader);

	// Check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv (vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog (vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// FRAGMENT SHADER
	unsigned int fragmentShader;
	fragmentShader = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource (fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader (fragmentShader);
	// Check for shader compile errors
	glGetShaderiv (fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog (fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// LINK SHADERS
	unsigned int shaderProgram = glCreateProgram ();
	glAttachShader (shaderProgram, vertexShader);
	glAttachShader (shaderProgram, fragmentShader);
	glLinkProgram (shaderProgram);

	// Check for linking errors
	glGetProgramiv (shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog (shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINKING::FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader (vertexShader);
	glDeleteShader (fragmentShader);

	// Set up vertex data (and buffer(s)) and configure vertex attributes
	//-------------------------------------------------------------------
	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left

	};

	// Before we can start rendering we must tell OpenGL the size of the rendering window.
	// This needs to match the dimensions we passed to GLFWWindow* above?
	glViewport (0, 0, 800, 600);		// First two parameters set the location of the lower left corner of the window. 

	// This while loop is known as the render loop
	while (!glfwWindowShouldClose (window))
	{
		// Check for input
		processInput (window);

		// Rendering commands here
		glClearColor (0.2f, 0.3f, 0.3f, 1.0f);
		glClear (GL_COLOR_BUFFER_BIT);

		unsigned int VBO;
		glGenBuffers (1, &VBO);

		glBindBuffer (GL_ARRAY_BUFFER, VBO);
		glBufferData (GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);

		// check and call events and swap the buffers
		glfwSwapBuffers (window);
		glfwPollEvents ();
	}

	// Once the while loop ("Render Loop") finishes then the window should close and OpenGL release all resources
	glfwTerminate ();

	return 0;
}


// Function definitions
void framebuffer_size_callback (GLFWwindow* window, int width, int height)
{
	glViewport (0, 0, width, height);
}

void processInput (GLFWwindow* window)
{
	if (glfwGetKey (window, GLFW_KEY_E) == GLFW_PRESS)
		glfwSetWindowShouldClose (window, true);
}