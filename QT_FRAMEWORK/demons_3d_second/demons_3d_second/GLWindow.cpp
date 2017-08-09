#include "GLWindow.h"
#include"Camera.h"

#include<iostream>

#include<string>

#include"Trackball.h"

using namespace std;

GLuint screenWidth = 800, screenHeight = 600;

#define trivial  1e-10

// Setup and compile our shaders


// Set up our vertex data (and buffer(s)) and attribute pointers
GLfloat vertices[] = {
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};
glm::vec3 cubePositions[] = {
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(2.0f, 5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f, 3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f, 2.0f, -2.5f),
	glm::vec3(1.5f, 0.2f, -1.5f),
	glm::vec3(-1.3f, 1.0f, -1.5f)
};




void OPENGL::GLWindow::getNDC(float &rx, float &ry, float sx, float sy, int width, int height)
{
	
	 rx =2*( (height - sy)/height)-1;
	 ry = 2*(sx / height)-1;



}




OPENGL::GLWindow::GLWindow(QWidget*parent) : QGLWidget(parent), rotate_x(0)
{
	m_xRot = 0;
	m_yRot = 0;
	m_zRot = 0;

	m_xTrans = 0;
	m_yTrans = 0;
	m_zTrans = 0;
	scale = 1;
    zoom = 5;
	isMouseBeingPressedAndHold = false;
	oldmouse = glm::vec2(0);
	newmouse = glm::vec2(0);
	rotation = glm::mat4(1.0);

	dlg = new QDialog(this);

	//dig->setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);

	dlg->setWindowTitle("result");
	dlg->setMinimumHeight(450);
	dlg->setMinimumWidth(600);
	dlg->hide();

}


OPENGL::GLWindow::~GLWindow()
{
}


void OPENGL::GLWindow::initializeGL()
{
	if (glewInit())
	{
		std::cerr << "unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH);
	shader =new Shader("shader/vert.glsl", "shader/frag.glsl");


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind our Vertex Array Object first, then bind and set our buffers and pointers.
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	// Load and create a texture 
	
	// --== TEXTURE 1 == --
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image("resource/mikasa.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	// --== TEXTURE 2 == --
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	image = SOIL_load_image("resource/mikasa.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	camera = new OPENGL::PerspectiveCamera(glm::vec3(0.0f, 0.0f, 3.0f));
	trackball = new OPENGL::Trackball(camera,this);


}
void OPENGL::GLWindow::paintGL()
{

	int size = 1;
	


	
	//glDepthFunc(GL_LEQUAL);

	// Clear the colorbuffer
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	

	// Draw our first triangle
	shader->Use();

	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(shader->Program, "ourTexture1"), 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(shader->Program, "ourTexture2"), 1);

	// Create camera transformation
	glm::mat4 view;
	//cout << "zoom:" << zoom << endl;
	view = camera->getViewMatrix();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//cout << view[i][j] << "\t";
		}

		//cout << endl;
	}

	cout << "********************************" << endl;
	glm::mat4 projection;
	projection = camera->getProjectionMatrix();
	//= glm::perspective(camera.Zoom, (float)screenWidth / (float)screenHeight, 0.1f, 1000.0f);
	// Get the uniform locations
	GLint modelLoc = glGetUniformLocation(shader->Program, "model");
	GLint viewLoc = glGetUniformLocation(shader->Program, "view");
	GLint projLoc = glGetUniformLocation(shader->Program, "projection");
	// Pass the matrices to the shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(VAO);
	
		// Calculate the model matrix for each object and pass it to shader before drawing
	glm::mat4 model;

	//model = rotation;
	model = glm::scale(model, glm::vec3(scale*0.1f, scale*0.1f, scale*0.1f));
	model = glm::translate(model, cubePositions[0]);
	model = glm::rotate(model, 180.0f - (m_xRot / 64.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, 180.0f - (m_yRot / 64.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::rotate(model, 180.0f - (m_zRot / 64.0f), glm::vec3(0.0f, 0.0f, 1.0f));


	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);

}


void OPENGL::GLWindow::resizeGL(int width, int height)
{

	glViewport(0, 0, width, height);
}


void OPENGL::GLWindow::mousePressEvent(QMouseEvent *event)
{
	m_lastPos = event->pos();
	
	
	if (event->buttons() & Qt::LeftButton)
	{
		if (isMouseBeingPressedAndHold == false) // first press
		{
			oldmouse.y = (event->y()) / (this->height() + 0.0);
			oldmouse.x =  (event->x() / (this->width() + 0.0));
			isMouseBeingPressedAndHold = true;
		}
	}


	//dlg->show();
}

void OPENGL::GLWindow::mouseReleaseEvent(QMouseEvent * event)
{
	isMouseBeingPressedAndHold = false;
}
void OPENGL::GLWindow::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - m_lastPos.x();
	int dy = -(event->y() - m_lastPos.y());

	if (event->buttons() & Qt::LeftButton) {
		setXRotation(m_xRot + 1 * dy);
		setYRotation(m_yRot + 1 * dx);
	}
	else if (event->buttons() & Qt::RightButton) {
		setXRotation(m_xRot + 1 * dy);
		setZRotation(m_zRot + 1 * dx);
	}
	m_lastPos = event->pos();

	// rotation;


	/*newmouse.y =  (event->y()) / (this->height() + 0.0);
	newmouse.x = (event->x() / (this->width() + 0.0));
	
	trackball->rotate(newmouse, oldmouse);

	oldmouse.y = newmouse.y;
	oldmouse.x = newmouse.x;*/
}
void OPENGL::GLWindow::wheelEvent(QWheelEvent *event)
{
	QPoint numDegrees = event->angleDelta() / 8;
	if (!numDegrees.isNull())
	{
		scale += (numDegrees.ry()/15); // scaling

		if (scale < trivial)
		{
			scale = 1;
		}
		/*zoom  += (numDegrees.ry() / 15); // scaling
		if (zoom == 0)
			zoom = rand() % 3;*/
	}

	event->accept();
	updateGL();
		
}





static void qNormalizeAngle(int &angle)
{
	while (angle < 0)
		angle += 360 * 16;
	while (angle > 360 * 16)
		angle -= 360 * 16;
}

void OPENGL::GLWindow::setXRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != m_xRot) {
		m_xRot = angle;
		//emit xRotationChanged(angle);
		update();
	}
}

void OPENGL::GLWindow::setYRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != m_yRot) {
		m_yRot = angle;
		//emit yRotationChanged(angle);
		update();
	}
}

void OPENGL::GLWindow::setZRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != m_zRot) {
		m_zRot = angle;
		//emit zRotationChanged(angle);
		update();
	}
}


