#include "GameEngine.h"
#include "BuildShaderProgram.h"
#include "MeshComponent.h"

#define VERBOSE false
int mScreenWidth = 1024;
int mScreenHeight = 768;
GLFWwindow* mWindow;
GLuint shaderProgram;
SubMesh subMesh;

//********************* Initialization Methods *****************************************

Game::Game(std::string windowTitle)
	: windowTitle(windowTitle)
{

} // end Game Constructor

void Game::runGame()
{
	// Set the owning game to this game. The will be passed to all
	// other GameObject when addChildGameObject is called
	this->owningGame = this;

	// The Game is the root of the scene graph. It has no parent.
	this->parent = nullptr;

	// Initialize the game
	bool success = initializeGame();

	// Enter the game loop
	if (success) {
		gameLoop();
	}

	// Free up resources
	shutdown();

} // end runGame

Game::~Game()
{
	if (VERBOSE) cout << "Game destructor " << endl;

} // end Game Destructor

bool Game::initializeGame()
{
	// Initialize the various libararies
	bool windowInit = initializeRenderWindow();
	bool graphicsInit = initializeGraphics();

	// Check if all libraries initialized correctly
	if (windowInit && graphicsInit)
	{
		// Set the owner of all the GameObject (temporary)
		GameObject::SetOwningGame(this);

		// Build the scene graph
		loadScene();

		// Explicitly call the resize method to set the initial projection transformation
		// and viewport based on framebuffer size.
		framebuffer_size_callback(this->renderWindow, initialScreenWidth, initialScreenHeight);

		this->initialize();

		// Return true to indicate the game has initialized
		return true;
	}
	else
	{
		std::cerr << "Game Initialization Failure." << endl;

		// Return false to indicate the game did not initialize correctly
		return false;
	}

} // end initialize

bool Game::initializeRenderWindow()
{
	// Initialize the GLFW and create a rendering window. If a failure, then exit
	// TODO
	if (!glfwInit()) {
		throw std::runtime_error("Could not initilize GLFW!");
	}
	glfwSetErrorCallback(glfw_error_callback);
	// Specify that OpenGL will be the client API for the rendering context
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

	// Specify the OpenGL major and minor version and use the core OpenGL profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Create window in debug mode for additional error and diagnostic reporting
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	// Flush the rendering pipeline when the context is released from being current
	glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR,
		GLFW_RELEASE_BEHAVIOR_FLUSH);
	// Explicitly request double buffers i.e. two frame buffers
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

	// Create rendering window and the OpenGL context.
	renderWindow = glfwCreateWindow(initialScreenWidth, initialScreenHeight, windowTitle.c_str(), NULL, NULL);
	if (!renderWindow) {
		std::cerr << "Render Window Creation Failure." << endl;
		std::cerr << "Make sure requested OpenGL version is supported." << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(renderWindow);

	glfwSwapInterval(1);

	if (VERBOSE) cout << "Render Window Initialized" << endl;
	bindCallBacks();
	return true;

} // end initializeRenderWindow

bool Game::initializeGraphics()
{
	// ****** Initialize GLEW *********
	// TODO
	
	glewExperimental = GL_TRUE;
	GLenum res = glewInit(); // Must be done after glut is initialized!
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return false;
	}
	// On some platforms, GLEW will emit a benign error code. So clear it.
	glGetError();

	// ********* Initialize OpenGL **************
	// TODO
	// 
	// On some platforms, GLEW will emit a benign error code. So clear it.
	glGetError();
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDebugMessageCallback(openglMessageCallback, 0);
	// Cull back faces of polygons
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	// Render "filled in" polygons
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// Set source and destination blending functions
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// 
	displayOpenGlInfo();

	glClearColor(1.0f, 1.0f, 1.0f,1.0f);

	
	
	return true;

} // end initializeGraphics

void Game::bindCallBacks()
{
	// Set this game as the user defined window associated with the 
	// rendering window.
	glfwSetWindowUserPointer(renderWindow, this);

	glfwSetKeyCallback(renderWindow, keyCallback);

	glfwSetCursorPosCallback(renderWindow, cursorPositionCallback);

	glfwSetMouseButtonCallback(renderWindow, mouseButtonCallback);

	// Register window resize callback function
	glfwSetFramebufferSizeCallback(renderWindow, framebufferResizeCallback);

	// Register window close function
	glfwSetWindowCloseCallback(renderWindow, windowCloseCallback);

	//GLFWcursorposfun glfwSetCursorPosCallback(GLFWwindow * mWindow, GLFWcursorposfun cursor_position_callback);

	//glfwSetCursorPosCallback(renderWindow, cursor_position_callback);

} // end bindCallBacks


//********************* Run Methods *****************************************

void Game::gameLoop()
{
	isRunning = true;

	while (isRunning) {

		processGameInput();
		updateGame();
		renderScene();
	}

	if (VERBOSE) cout << "Exited Game Loop" << endl;

} // end gameLoop

void Game::processGameInput()
{
	glfwPollEvents();
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE)) {

		isRunning = false;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_I)) {
		cout << "polled i" << endl;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) && WireFrame_KeyDown == false) {

		GLint mode;
		glGetIntegerv(GL_POLYGON_MODE, &mode);

		if (mode == GL_FILL) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		WireFrame_KeyDown = true;

	}
	else if (!glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W)) {
		WireFrame_KeyDown = false;
	}

	// Start an input traversal of all SceneGrapNode/GameObjects in the game
	GameObject::processInput();

	// Add pending, delete removed, and reparent
	GameObject::UpdateSceneGraph();

} // end processInput

void Game::updateGame()
{
	// Compute delta time
	static double lastRenderTime = glfwGetTime(); // static initilization only occurs once
	double currentTime = glfwGetTime();
	float deltaTime = static_cast<float>(currentTime - lastRenderTime);

	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}

	if (deltaTime >= FRAME_INTERVAL) {

		// Must be called in order for callback functions
		// to be called for registered events.
		glfwPollEvents();

		// Start an update traversal of all SceneGrapNode/GameObjects in the game
		GameObject::update(deltaTime);

		// Add pending, delete removed, and reparent
		GameObject::UpdateSceneGraph();

		// Update the last time the game was updated
		lastRenderTime = currentTime;
	}

} // end updateGame()

void Game::renderScene()
{
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render loop
	// 
	//glDrawArrays(subMesh.primitiveMode, 0, subMesh.count);

	for (auto& mesh : MeshComponent::GetMeshComponents()) {

		mesh->draw();
	}

	// Swap the front and back buffers
	glfwSwapBuffers(renderWindow);



} // end renderScene

//********************* Shutdown Methods *****************************************

void Game::shutdown()
{
	// Destroy the window
	// TODO

	glfwDestroyWindow(mWindow);
	//glfwDestroyWindow();
	
	// Frees other glfw allocated resources
	// TODO
	windowCloseCallback(mWindow);
	deleteAllShaderPrograms();
	glfwTerminate();

} // end shutDown

//********************* Accessor Methods *****************************************

glm::ivec2 Game::getWindowDimensions()
{
	int width, height;
	glfwGetFramebufferSize(this->renderWindow, &width, &height);

	return glm::ivec2(width, height);

} // end getWindowDimensions

//********************* Event Handlers *****************************************

void Game::window_close_callback(GLFWwindow* window)
{
	cout << "close" << endl;
	// Stop the game loop
	this->isRunning = false;

} // end window_close_callback

void Game::cursor_position_callback(GLFWwindow* window,double xpos, double ypos)
{
	glm::ivec2 dims = getWindowDimensions();
	//if((xpos > 0 && xpos < dims.x) && (ypos > 0 && ypos < dims.y))
	//	cout << "mouseevent x: "<<xpos<<"y: " << ypos << endl;

} // end window_close_callback

void Game::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_J && action == GLFW_PRESS)
		cout << "j ";
	
}
void Game::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		cout << "rmb press" << endl;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		cout << "lmb press" << endl;
	}
}


void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// Set parameters for the window transformation ...
	// TODO


	// Set the projection transformation ...
	// TODO


} // end framebuffer_size_callback

//********************* static function definitions *****************************************

void GLAPIENTRY openglMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar* message, const void* userParam)
{
	if (severity != 0x826B) {
		fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
			type, severity, message);
	}
} // end MessageCallback


void glfw_error_callback(int error, const char* description) {

	fprintf(stderr, "Error: %s\n", description);

} // end error_callback


void displayOpenGlInfo(void)
{
	// Display the company responsible for this GL implementation
	fprintf(stdout, "OpenGL INFO:\n\tOpenGL Implementor: %s\n",
		glGetString(GL_VENDOR));
	// Display the renderer/graphics card
	fprintf(stdout, "\tRenderer: %s\n", glGetString(GL_RENDERER));
	// Display the OpenGL version that is implemented
	fprintf(stdout, "\tOpenGL Version: %s\n", glGetString(GL_VERSION));
	// Display the GLSL version
	fprintf(stdout, "\tGLSL Version: %s\n\n",
		glGetString(GL_SHADING_LANGUAGE_VERSION));

} // end displayOpenGlInfo


static void framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
	cout << "ewefw" << endl;
	Game* that = static_cast<Game*>(glfwGetWindowUserPointer(window));
	that->framebuffer_size_callback(window, width, height);
	cout << "Window resized to " << width << "x " << height << " pixels." << endl;

}

static void windowCloseCallback(GLFWwindow* window)
{
	Game* that = static_cast<Game*>(glfwGetWindowUserPointer(window));
	that->window_close_callback(window);
	cout << "render window closed" << endl;
}

static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	Game* that = static_cast<Game*>(glfwGetWindowUserPointer(window));
	that->cursor_position_callback(window,xpos,ypos);
	if (VERBOSE) cout << "mouseoverevent" << endl;
}
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Game* that = static_cast<Game*>(glfwGetWindowUserPointer(window));
	that->key_callback(window,  key,  scancode,  action,  mods);
	if (VERBOSE) cout << "key event" << endl;
}
static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	Game* that = static_cast<Game*>(glfwGetWindowUserPointer(window));
	that->mouse_button_callback(window, button, action, mods);
	if (VERBOSE) cout << "key event" << endl;
}