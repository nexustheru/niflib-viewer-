#pragma once
#include <QGraphicsView>
#include <QTimer>
class graph : public QGraphicsView
{
	Q_OBJECT
public:
	explicit graph(QWidget *parent = 0);
	~graph(void);

	public slots:

	private:
QTimer time;
};

