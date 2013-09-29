#include "nifs.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	nifs w;
	w.show();
	return a.exec();
}
