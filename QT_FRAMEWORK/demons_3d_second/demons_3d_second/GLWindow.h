#pragma once
#include"GL\glew.h"
#include<QtOpenGL/QGLWidget>
#include"DockWidget.h"
#include"QtCore\QString"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"Shader.h"
#include <SOIL.h>
#include<QtGui/QMouseEvent>
#include"Camera.h"
#include<QtWidgets/QDialog>
#include<QtCore/qpoint.h>




namespace OPENGL
{ class Trackball;
	class GLWindow : public QGLWidget
	{
		Q_OBJECT
	public:
		void initializeGL();
		void paintGL();
		void resizeGL(int width, int height) override;
		void mousePressEvent(QMouseEvent *event) override;
		void mouseMoveEvent(QMouseEvent *event) override;
		void wheelEvent(QWheelEvent *event) override;
		void mouseReleaseEvent(QMouseEvent * event) override;
		GLWindow(QWidget*parent);
		~GLWindow();

		static void getNDC(float &rx, float &ry, float sx, float sy, int width, int height);

	public:
		GLuint VBO, VAO;
		GLuint texture1;
		GLuint texture2;

		Shader* shader;
		PerspectiveCamera* camera;
		Trackball* trackball;


		float rotate_x;

		public slots:
		void setXRotation(int angle);
		void setYRotation(int angle);
		void setZRotation(int angle);

	signals:
		void xRotationChanged(int angle);
		void yRotationChanged(int angle);
		void zRotationChanged(int angle);

	public:
		bool m_core;
		int m_xRot;
		int m_yRot;
		int m_zRot;
		int m_xTrans;
		int m_yTrans;
		int m_zTrans;
		QPoint m_lastPos;
		int zoom;
		int scale;

		bool isMouseBeingPressedAndHold;
	protected:

		QDialog* dlg;

		glm::mat4 rotation;
		glm::vec2 oldmouse;
		glm::vec2 newmouse;

	};
}


