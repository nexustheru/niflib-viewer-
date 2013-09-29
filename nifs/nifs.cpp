#include <gl\glew.h>
#include "nifs.h"
#include <QtGui/QApplication>
#include <QFileDialog>
#include <iostream> 
#include <fstream>
#include <QKeyEvent>
#include <string>
#include <QEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QVector>
#include <QVector3D>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QApplication>
#include <QtGui/QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QPixmap>
#include <QGLPixelBuffer>
#include <QString>
#include <opengl.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>


nifs::nifs(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	QObject::connect(ui.pushButton, SIGNAL(clicked(bool)), this, SLOT(loadfile()));
	QObject::connect(ui.pushButton_3, SIGNAL(clicked(bool)), this, SLOT(loadtexture()));
	QObject::connect(ui.listWidget, SIGNAL(itemSelectionChanged()), this, SLOT(shadesel()));
	
	addshaders();
}
void nifs::shadesel()
{
    if(ui.listWidget->selectedItems().count()==2)
	{
    opengl::selectedshader(ui.listWidget->selectedItems());
	}
	else if(ui.listWidget->selectedItems().count()==1)
	{
	
	}
	else
	{
		
	ui.listWidget->clearSelection();
	}
}

void nifs::loadtexture(void)
{
	
	QString ddfileName = QFileDialog::getOpenFileName(this,
	QObject::tr("Import Images"), " ", QObject::tr("File formats (*.*)"));
	ui.label_2->setText(ddfileName);
	ILuint ImageName;
	ilGenImages(1, &ImageName);
	ilBindImage(ImageName);
	ilLoadImage(ddfileName.toStdString().c_str());
	qDebug(ddfileName.toStdString().c_str());
	iluFlipImage();
	ILubyte *Data = ilGetData();
	ilutRenderer(ILUT_OPENGL);
	ilutGLBindTexImage();

qDebug("file ok");
}

void nifs::addshaders(void)
{
	QDir myDir("shaders/");
	QStringList fl = myDir.entryList(QDir::NoFilter);
	for(int i=0 ;i < fl.count();i++)
	{
		ui.listWidget->addItem(fl[i]);
	}
	
}

void nifs::loadfile(void)
{
	QString sfileName = QFileDialog::getOpenFileName(this,
	QObject::tr("Import File"), " ", QObject::tr("File formats (*.nif *.kfm *.hkx *.tri *.hkt *.3DS *.BLEND *.DAE *.FBX *.IFC-STEP *.ASE *.DXF *.HMP *.MD2 *.MD3 *.MD5 *.MDC *.MDL *.NFF *.PLY *.STL *.X *.OBJ *.SMD *.LWO *.LXO *.LWS *.TER *.AC3D *.MS3D *.COB *.Q3BSP *.XGL *.CSM *.BVH *.B3D *.NDO *.Ogre *.XML *.Q3D)"));
	ui.label->setText(sfileName);
	opengl::gettree(ui.treeWidgetMesh);
	opengl::determinefiltype(sfileName);
	
}

void nifs::keyPressEvent(QKeyEvent* event)
{

	opengl::grabthekey(event);

}

nifs::~nifs()
{
	
}
int main(int argc, char *argv[])
{
	ilInit();
	iluInit();
	ilutInit();
	QApplication a(argc, argv);
	nifs w;
	//w.setWindowFlags(Qt::CustomizeWindowHint);
	w.show();
	w.setFixedSize(w.size());

	return a.exec();
}
