#include <GL\glew.h>
#include "opengl.h"
#include <GL/glut.h>
#include <nifh.h>
#include <iostream> 
#include <fstream>
#include <string>
#include <QEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QVector>
#include <QVector3D>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QApplication>
#include <QtGui/QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QCoreApplication>
#include <QString>
#include <array>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include <math.h>
#include <nvImage.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <map>
#include <QGLShaderProgram>
#include <QList>
#include <QListWidgetItem>
#include <tri.h>
#define _USE_MATH_DEFINES

QVector<trifile::fCOORDS> trivertices;
QVector<trifile::triCOORDS> tritriangles;
QVector<trifile::uvCOORDS> triuvvert;
QVector<trifile::triCOORDS> triuvtriangles;
QVector<trifile::morphdata> morps;
vector<INT32> sised;

const char* fnam;
const aiScene* di;
const aiMesh* amesh;
vector<const char*> textureIdMap;
vector<const char*> textureIdMap1;
Niflib::NiTriBasedGeomRef nshape;
Niflib::NiAVObjectRef nav;
Niflib::NiNodeRef nroot;
Niflib::NiTriBasedGeomDataRef ndata;
vector<Niflib::NiTriBasedGeomRef> nshapes;
Niflib::NiPropertyRef niProp;
Niflib::BSShaderTextureSetRef bsTexProp;
Niflib::NiAlphaPropertyRef bsalpha;
Niflib::BSLightingShaderPropertyRef bs_shader;
Niflib::array<2, Niflib::NiPropertyRef> bs_properties;
Niflib::BSDismemberSkinInstanceRef bskin;
vector<Niflib::NiNodeRef> bonelist;
GLuint*	textureIds;
GLuint texture;

float Dist;
float m_distance;
float mx=NULL;
float my=NULL;
int lastX;
int lastY;
int xRot;
int yRot;
int lastzoom;
int xmove;
int ymove;
int lastmovex;
int lastmovey;
float keyx=0.0f;
float keyy=0.0f;
float keyz=0.0f;
QString fname1;
QVector<Niflib::Vector3> vertices1;
QVector<Niflib::Vector3> bittang;
QVector<Niflib::Vector3> tang;
QVector<Niflib::Triangle> trias;
QVector<Niflib::Vector3> norms;
QVector<Niflib::TexCoord> cols;
QVector<Niflib::Vector3> ve;
QVector<float> fa;
QVector<float> ainorms;
QVector<Niflib::TexCoord> aitex;
QTreeWidget* wwidnmesh;
GLfloat angle = 0.0;
QString shadersv=NULL;
QString shadersf=NULL;
const aiScene* basesc=aiImportFile("SnowTerrain/skybox.DAE",aiProcessPreset_TargetRealtime_MaxQuality|aiProcess_Triangulate);

opengl::opengl(QWidget *parent) :
    QGLWidget(parent)
{
    connect(&time,SIGNAL(timeout()),this,SLOT(updateGL()));
	connect(&time1,SIGNAL(timeout()),this,SLOT(activateshader()));
    time.start(10);
	time1.start(6000);
	setMouseTracking(true);
	
}
void opengl::activateshader(void)
{
    std::string a=shadersf.toStdString();
	std::string b=shadersv.toStdString();
	if(strcmp (a.c_str(),b.c_str()) == NULL)
	{
		qDebug("no shaders applied");
	}
	else if(a.empty()==true)
	{
		shadersf.clear();
	}
	else if(b.empty()==true)
	{
		shadersv.clear();
	}
	else
	{
	shader = new QGLShaderProgram(this);
    shader->addShaderFromSourceFile(QGLShader::Vertex,shadersv);
	shader->addShaderFromSourceFile(QGLShader::Fragment,shadersf);
	shader->link();
	shader->bind();
	
	}
	
}
void opengl::mousePressEvent(QMouseEvent *event)
{
    lastX = event->pos().x();
    lastY = event->pos().y();
    lastmovex=event->pos().x();
    lastmovey=event->pos().y();

}
void opengl::wheelEvent(QWheelEvent *event)

{

    m_distance += (event->delta()/120);

}
void opengl::mouseMoveEvent(QMouseEvent* event)
{
    int dx = event->x() - lastX;
       int dy = event->y() - lastY;

       if (event->buttons() & Qt::LeftButton)
       {
           xRot += 3 * dy;
           yRot += 3 * dx;
       }
       else if (event->buttons() & Qt::RightButton)
       {
           xRot += 3 * dy;
           yRot += 3 * dx;
       }
       else if (event->buttons() & Qt::MiddleButton)
       {
           xmove += 3 * dx;
           ymove -= 3 * dy;

       }

       lastX = event->pos().x();
       lastY = event->pos().y();
       lastmovex = event->pos().x();
       lastmovey = event->pos().y();

}
void opengl::gettree(QTreeWidget* wid)
{
	wwidnmesh=wid;
}
void opengl::grabthekey(QKeyEvent* event)
{
	//x=höger y=upp/ner z=fram/från
	
	switch(event->key())
	{
	case Qt::Key_Escape:
		exit(0);
		break;
	
	}
}
void opengl::initializeGL()
{
    glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glClearColor(0,0,0,1);
	
}
void opengl::selectedshader(QList<QListWidgetItem *> items)
{
	for(int i=0 ;i < items.count() ;i++)
	{
	QString temp=items[i]->text();

	if(temp.contains("vert",Qt::CaseSensitive)==true)
	{
		shadersv=QString("shaders/")+temp;
	
	}
	else if(temp.contains("frag",Qt::CaseSensitive)==true)
	{
        shadersf=QString("shaders/")+temp;
		
	}
	else
	{
    qDebug("name must contain either frag or vert");

	}
	
	}
	
}
void mylight(float x,float y,float z,float scale)
{
	
	 float pos[]={x,y,z};
     float mat_ambient[] = {0.0f, 0.0f, 0.0f, 0.0f};
     float mat_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
     float mat_specular[] = {float(bs_shader->GetSpecularColor().r), float(bs_shader->GetSpecularColor().g), float(bs_shader->GetSpecularColor().b),1.0f};
	 float mat_em[]={float(bs_shader->GetEmissiveColor().r),float(bs_shader->GetEmissiveColor().g),float(bs_shader->GetEmissiveColor().b)};
	 float mat_shine[]={float(bs_shader->GetGlossiness())};
	 glLightfv(GL_LIGHT7,GL_POSITION,pos);
	 glLightfv(GL_LIGHT7, GL_AMBIENT, mat_ambient);
	 glLightfv(GL_LIGHT7, GL_DIFFUSE, mat_diffuse);
	 glLightfv(GL_LIGHT7, GL_SPECULAR, mat_specular);
	 glLightfv(GL_LIGHT7, GL_SHININESS, mat_shine);
	 glLightfv(GL_LIGHT7, GL_EMISSION, mat_em);
	 
	 glPushMatrix();
	 
	 glTranslatef(0.0f, -3.0f, 0.0f); // Translate our object along the y axis
     glRotatef(+0.005f, 0.0f, 1.0f, 0.0f); 
	 glScalef(1.0f *scale,1.0f *scale,1.0f *scale);
	 glDisable(GL_TEXTURE_2D);
	 glDisable(GL_BLEND);
	 glBegin( GL_LINE_STRIP );
				{
					const int circlePoints = 24;
					for(int is=0; is <= circlePoints; is++ )
					{
						const double angle = (double(is)/double(circlePoints))*(2.0*PI);
						glVertex3d( cos(angle), sin(angle), 0.0 );
						glColor3f(1.0f,1.0f,0.0f);

					}
				}
				glEnd();

				glBegin( GL_LINES );
				{
					const int numLines = 8;
					for(int i=0; i < numLines; i++ )
					{ 
						const double angle = (double(i)/double(numLines))*(2.0*PI);
						glVertex3d( 1.3*cos(angle), 1.3*sin(angle), 0.0 );
						//glColor3f(1.0f,1.0f,0.0f);
						glVertex3d( 2.0*cos(angle), 2.0*sin(angle), 0.0 );
						//glColor3f(1.0f,1.0f,0.0f);
					}
				}
				glEnd();
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_BLEND);
				glEnable(GL_LIGHT7) ;
				glPopMatrix();
}
void recursicebonelist(vector<Niflib::Ref<Niflib::NiNode>> boneroot)
{
	for(vector<Niflib::NiNodeRef>::iterator nith=boneroot.begin();nith != boneroot.end(); ++nith )
	{
		if(((*nith))->IsDerivedType(Niflib::NiNode::TYPE))
		{

			bonelist.push_back(Niflib::DynamicCast<Niflib::NiNode>((*nith)));
		}
	}
}
void niftex()
{
	using namespace nv;
	QString temp1=QString("C:\\Program Files (x86)\\Steam\\steamapps\\common\\skyrim\\Data\\");
	
	 for(int i=0 ; i< bsTexProp->GetTextures().size() ; i++)
    {
     if(bsTexProp->GetTextures()[i]=="")
	 {
		 qDebug("empty string");
	 }
	 else
	 {
    QString mehe=QString::fromStdString(bsTexProp->GetTextures()[0]);
    QString result = temp1+mehe;
	result.replace(QString("\\"),QString("/"));
	 qDebug(result.toStdString().c_str());
	ILuint ImageName;
    ilGenImages(1, &ImageName);
    ilBindImage(ImageName);
    ilLoadImage(result.toStdString().c_str());
    iluFlipImage();
    ILubyte *Data = ilGetData();
    ilutRenderer(ILUT_OPENGL);
    ilutGLBindTexImage();
	////////////////////normalsmap///////////////////////
	ILboolean success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
	if (!success)
		{
			qDebug("failed to convert"); 
		}
	GLuint textureID;
	glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    // Set texture interpolation method to use linear interpolation (no MIPMAPS)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,ilGetInteger(IL_IMAGE_BPP),
		ilGetInteger(IL_IMAGE_WIDTH),
		ilGetInteger(IL_IMAGE_HEIGHT),
		0,ilGetInteger(IL_IMAGE_FORMAT),
		GL_UNSIGNED_BYTE,Data);	
	qDebug("converted to ogl format");
	ilDeleteImages(1, &ImageName); 
	}
  
	}
  }
void asstex()
{
 for(int i=0 ; i< textureIdMap.size() ; i++)
  {
	ILuint texid;
	ilGenImages(1, &texid); /* Generation of one image name */
    ilBindImage(texid); /* Binding of image name */
    ILboolean success = ilLoadImage(textureIdMap[i]); /* Loading of image "image.jpg" */
    if (success) /* If no error occured: */
    {
     success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE); /* Convert every colour component into
     unsigned byte. If your image contains alpha channel you can replace IL_RGB with IL_RGBA */
    if (!success)
    {
    qDebug("error");
    }
    GLuint image;
    glGenTextures(1, &image);
    glBindTexture(GL_TEXTURE_2D, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
    ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
    ilGetData());
    }
    ilDeleteImages(1, &texid); 
  }
}
void nifbuild()
{
	using namespace Niflib;
	    ndata=NULL;
	    trias.clear();
	    vertices1.clear();
		cols.clear();
		nroot=NULL;
		nshapes.clear();
		nshape=NULL;
		bsTexProp=NULL;
		bskin=NULL;
		bonelist.clear();
	    NiObjectRef niparentobject=ReadNifTree(fname1.toStdString().c_str());
		nroot=Niflib::DynamicCast<NiNode>(niparentobject);
		vector<NiAVObjectRef> children=nroot->GetChildren();
		
		for ( unsigned int child = 0; child < children.size(); ++child ) 
		{
			if ( children[child]->IsDerivedType( NiTriBasedGeom::TYPE ) ) 
			{
				nshapes.push_back( DynamicCast<NiTriBasedGeom>(children[child]) );
			}
      
        }
			for ( vector<NiTriBasedGeomRef>::iterator geom = nshapes.begin(); geom != nshapes.end(); ++geom ) 
			{
				bs_properties = (*geom)->GetBSProperties();
				nshape = DynamicCast<NiTriBasedGeom>( (*geom));
				
				if((*geom)->GetSkinInstance() > NULL)
				{
                bskin=DynamicCast<BSDismemberSkinInstance>((*geom)->GetSkinInstance());
				recursicebonelist(bskin->GetBones());
				}
				ndata = DynamicCast<NiTriBasedGeomData>( (*geom)->GetData() );
				vector<Niflib::TexCoord> teecc=ndata->GetUVSet(0);
				for( int ith=0 ; ith < 2 ;ith++)
				{
                 niProp = nshape->GetBSProperties()[ith];
				 if(niProp != NULL &&  niProp->GetType().IsSameType(BSLightingShaderProperty::TYPE)) 
				  {
			       bs_shader = DynamicCast<BSLightingShaderProperty>(niProp);
			       bsTexProp = bs_shader->GetTextureSet();
				   niftex();
			      }
				 else if(niProp != NULL &&  niProp->GetType().IsSameType(NiAlphaProperty::TYPE)) 
				  {
					 bsalpha=DynamicCast<NiAlphaProperty>(niProp);
				  }

				}

				for(unsigned int ik=0 ;ik < ndata->GetVertexCount();ik++)
                 {
                     vertices1.push_back(ndata->GetVertices()[ik]);

					 cols.push_back(teecc[ik]);
                 }
                 for(unsigned int is=0 ;is < ndata->GetTriangles().size();is++)
                 {
                     trias.push_back(ndata->GetTriangles()[is]);

                 }
                 for(unsigned int ip=0 ;ip < ndata->GetNormals().size();ip++)
                 {
                     norms.push_back(ndata->GetNormals()[ip]);

                 }
				 if(ndata->GetBitangents().empty()==false)
				 {
				   for(unsigned int btb=0 ;btb < ndata->GetBitangents().size();btb++)
                   {
                     bittang.push_back(ndata->GetBitangents()[btb]);
                   }
				 }

				 if(ndata->GetTangents().empty()==false)
				 {
				   for(unsigned int tangs=0 ;tangs < ndata->GetTangents().size();tangs++)
                   {
                     tang.push_back(ndata->GetTangents()[tangs]);
                   }
				 }
				 
			}
		
}
void assimpbuild(void)
{

	aiMatrix4x4 m = di->mRootNode->mTransformation;
    aiMatrix4x4 m2;
    aiMatrix4x4::Scaling(aiVector3D(0.5, 0.5,0.5), m2);
    m = m * m2;

    // update transform
    m.Transpose();
    glPushMatrix();
    glMultMatrixf((float*)&m);
	for(unsigned int is=0 ; is < di->mNumMeshes; is++)
	{
		const aiMesh* mesh=di->mMeshes[is];
		amesh=mesh;
        for (unsigned int t = 0; t < mesh->mNumFaces; ++t)
        {
            const struct aiFace* face = &mesh->mFaces[t];
            GLenum face_mode;

            switch(face->mNumIndices)
            {
                case 1: face_mode = GL_POINTS; break;
                case 2: face_mode = GL_LINES; break;
                case 3: face_mode = GL_TRIANGLES; break;
                default: face_mode = GL_POLYGON; break;
            }

            glBegin(face_mode);

            for(unsigned int i = 0; i < face->mNumIndices; i++)		// go through all vertices in face
            {
                int vertexIndex = face->mIndices[i];	// get group index for current index
                if(mesh->mNormals != NULL)

                    if(mesh->HasTextureCoords(0))		//HasTextureCoords(texture_coordinates_set)
                    {
                        glTexCoord2f(mesh->mTextureCoords[0][vertexIndex].x, 1 - mesh->mTextureCoords[0][vertexIndex].y); //mTextureCoords[channel][vertex]
                    }

                    glNormal3fv(&mesh->mNormals[vertexIndex].x);
                    glVertex3fv(&mesh->mVertices[vertexIndex].x);
            }

            glEnd();

        }
asstex();
    glPopMatrix();

	}
	

}
void opengl::movingstuff(void)
{
glTranslatef(0.0f, -6.0f, -50.0f);	// Move 40 Units And Into The Screen
    glTranslatef(0, 0, -m_distance);
    time.stop();
    glTranslatef(xmove/100,ymove/100,0);
    time.stop();
    glRotatef(xRot, 1, 0, 0);
    time.stop();
    glRotatef(yRot, 0, 1, 0);
    time.stop();
}
void buildtrifilestuff(void)
{
	         for (int t = 0; t < tritriangles.count(); ++t)
            {
            Niflib::Triangle face;
			face.Set(tritriangles[t].a,tritriangles[t].b,tritriangles[t].c);
            glBegin(GL_TRIANGLES);

            for(int i = 0; i < 3; i++)		// go through all vertices in face
            {
                int vertexIndex = face[i];	// get group index for current index
                 glVertex2iv(&tritriangles[vertexIndex].a);
            }

            glEnd();

        }
}
void tribuild()
{
	  
	  INT32 headvert;
	  INT32 polytr;
	  INT32 numbermorph;
      std::filebuf tribuf;
      tribuf.open ("eyeskhajiitfemale.tri",std::ios::in|std::ios::binary);
	  std::istream readtri(&tribuf);
	  readtri.seekg(0x08,readtri.beg);
	  readtri.read(reinterpret_cast<char*>(&headvert), sizeof(headvert));
	  readtri.seekg(0x0c,readtri.beg);
	  readtri.read(reinterpret_cast<char*>(&polytr), sizeof(polytr));
	  ///vertices
	  readtri.seekg(0x40,readtri.beg);
	  for (int i=0; i<headvert; i++)
		{
			trifile::fCOORDS ft;
			readtri.read(reinterpret_cast<char*>(&ft), sizeof(ft));
			//readtri.read(reinterpret_cast<char*>(&ft.y), sizeof(ft.y));
			//readtri.read(reinterpret_cast<char*>(&ft.z), sizeof(ft.z));
			trivertices.push_back(ft);
	    }
	  ///triangles
	  readtri.seekg(0x298,readtri.beg);
	  for (int i=0; i<polytr; i++)
		{
			trifile::triCOORDS tt;
			readtri.read(reinterpret_cast<char*>(&tt), sizeof(tt));
			//readtri.read(reinterpret_cast<char*>(&tt.b), sizeof(tt.b));
			//readtri.read(reinterpret_cast<char*>(&tt.c), sizeof(tt.c));
			
			tritriangles.push_back(tt);
	    }

	  ///uvvertices
	  readtri.seekg(0x658,readtri.beg);
	   for (int i=0; i<headvert; i++)
		{
			trifile::uvCOORDS uft;
			readtri.read(reinterpret_cast<char*>(&uft), sizeof(uft));
			
			//readtri.read(reinterpret_cast<char*>(&uft.v), sizeof(uft.v));
			triuvvert.push_back(uft);
	    }
	  ///uvtriangles
	   readtri.seekg(0x7E8,readtri.beg);
	  for (int i=0; i<polytr; i++)
		{
			trifile::triCOORDS uvf;
			readtri.read(reinterpret_cast<char*>(&uvf), sizeof(uvf));
			//readtri.read(reinterpret_cast<char*>(&uvf.b), sizeof(uvf.b));
			//readtri.read(reinterpret_cast<char*>(&uvf.c), sizeof(uvf.c));
			triuvtriangles.push_back(uvf);
	    }
	  ///morphs
	  
	 // buildtrifilestuff();
}
void opengl::determinefiltype(QString fname)
{
	const char * temp=fname.toStdString().c_str();
	fnam=temp;
	
	if(fname.contains(".nif",Qt::CaseSensitive)==true)
	{
		
		qDebug("nif import");
		fname1=fname;
		nifbuild();
	}
	else if(fname.contains(".tri",Qt::CaseSensitive)==true)
	{
		 qDebug("trifile import");
         fname1=fname;
		 tribuild();
          
	}
	else 
	{
		qDebug("assimp import");
		 di=aiImportFile(fname.toStdString().c_str(),aiProcessPreset_TargetRealtime_MaxQuality|aiProcess_Triangulate);
		 for (unsigned int m=0; m<di->mNumMaterials; m++)
	      {
		   aiString path;	// filename
		   int count=0;
           di->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE,count, &path);
			if(path.length==NULL)
			{
             qDebug("empty string");
			}
			else
			{
             textureIdMap.push_back(path.C_Str());
			
			}
			 count++;
	      }
        assimpbuild();
	}
}
void drawskeleton(void)
{
	
	if(bonelist.empty() ==false)
	{
		glPushMatrix();
		glLineWidth(3.0f);
        glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		
		glBegin(GL_LINES);
		
		for(unsigned int i=0; i < bonelist.size();i++)
		{
		  glVertex3f(bonelist[i]->GetParent()->GetLocalTransform().GetTranslation().x,bonelist[i]->GetParent()->GetLocalTransform().GetTranslation().y,bonelist[i]->GetParent()->GetLocalTransform().GetTranslation().z);
          glColor3f(1.0f,1.0f,1.0f);
		  glVertex3f(bonelist[i]->GetLocalTransform().GetTranslation().x,bonelist[i]->GetLocalTransform().GetTranslation().y,bonelist[i]->GetLocalTransform().GetTranslation().z);
		  glColor3f(1.0f,1.0f,1.0f);
		}
		glEnd();
		glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
		glPopMatrix();
	}
}
void opengl::glenables(void)
{
glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_SPECULAR);
	glEnable(GL_AMBIENT);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DIFFUSE);
	glEnable(GL_SHININESS);
	glEnable(GL_COLOR);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
}
void opengl::paintGL()
{
	glenables();

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer

	
	if(ndata > NULL)
	{
    di=NULL;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	 glEnableClientState( GL_VERTEX_ARRAY );
     glEnableClientState( GL_NORMAL_ARRAY );
	 glEnableClientState(GL_TEXTURE_COORD_ARRAY);
     glVertexPointer( 3, GL_FLOAT, 0, vertices1.data());
     glNormalPointer(GL_FLOAT, 0, norms.data() );
     glTexCoordPointer(2, GL_FLOAT, 0 ,cols.data());
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
	  //x=höger y=upp/ner z=fram/från
     glTranslatef(0.0f,-6.0f,-150.0f);
	 glRotatef(-80.0f,+90.0f,0.0f,0.0f);
	 movingstuff();
	 Niflib::Matrix44 m=nroot->GetLocalTransform();
	 m.Transpose();
	 mylight(1.0f,+45.0f,-170.0f,1.0f);
     glPushMatrix();
     glMultMatrixf((float*)&m);
     drawskeleton();
     glDrawElements( GL_TRIANGLES, trias.count() * 3, GL_UNSIGNED_SHORT, trias.data() );
	  glPopMatrix();
	 
	 glDisable(GL_VERTEX_ARRAY );
	 glDisable(GL_NORMAL_ARRAY );
	 glDisable(GL_TEXTURE_COORD_ARRAY);
	
	}
	else if(trivertices.count() >0 )
	{
	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	 glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
	  //x=höger y=upp/ner z=fram/från
     glTranslatef(0.0f,-6.0f,-3.0f);
	 glRotatef(-80.0f,0.0f,0.0f,0.0f);
	 movingstuff();
	 buildtrifilestuff();
	}
	else if(di > NULL)
	{
	 ndata=NULL;
	 trias.clear();
	 vertices1.clear();
	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
	  //x=höger y=upp/ner z=fram/från
     glTranslatef(0.0f,-6.0f,-3.0f);
	 glRotatef(-80.0f,0.0f,0.0f,0.0f);
	 movingstuff();

	 assimpbuild();
	
	}
	else
	{
		di=NULL;
		ndata=NULL;
	    trias.clear();
	    vertices1.clear();
		 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		 glMatrixMode(GL_MODELVIEW);
         glLoadIdentity();
		 movingstuff();
		 glutSolidTeapot(10.0);

	}
	
time.start();
 }
void opengl::resizeGL(int w, int h)
{
glViewport(0,0,w,h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(80.0f,(float)w/h,0.01,1000.0f);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(0,0,5,0,0,0,0,1,0);
}