#pragma once
#include <QGLWidget>
#include <QTimer>
#include <assimp\Importer.hpp>
#include <assimp\Exporter.hpp>
#include <assimp\scene.h>
#include <assimp\mesh.h>
#include <assimp\config.h>
#include <assimp\material.h>
#include <assimp\cimport.h>
#include <assimp\postprocess.h>
#include <gl\glut.h>
#include <QEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QVector>
#include <QVector3D>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QGLShaderProgram>
#include <QList>
#include <QListWidgetItem>



class opengl :public QGLWidget
{
	Q_OBJECT

public:
	explicit opengl(QWidget *parent = 0);
	 void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
	/*void updateGL();*/
	void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void movingstuff(void);
	void glenables(void);
	
	static void determinefiltype(QString fname);
	static void gettree(QTreeWidget* wid);
	static void grabthekey(QKeyEvent* event);
	static void selectedshader(QList<QListWidgetItem *> items);

	public slots:
    void activateshader(void);
private:
QTimer time;
QTimer time1;
QGLShaderProgram* shader;

};

