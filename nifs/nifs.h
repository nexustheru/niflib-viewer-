#ifndef NIFS_H
#define NIFS_H

#include <QTreeWidget>
#include <QtGui/QWidget>
#include <QKeyEvent>
#include "ui_nifs.h"


class nifs : public QWidget
{
	Q_OBJECT
	 

public:
	nifs(QWidget *parent = 0, Qt::WFlags flags = 0);
	~nifs();
void paintq(void);
void addshaders(void);

public slots:
	void loadfile(void);
	void loadtexture(void);
	void keyPressEvent(QKeyEvent* event);
	void shadesel();
private:
	Ui::nifsClass ui;
};

#endif // NIFS_H
