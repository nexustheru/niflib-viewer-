#include "graph.h"

graph::graph(QWidget *parent) :
    QGraphicsView(parent)
{
    
    time.start(16);
	setMouseTracking(true);
}

graph::~graph(void)
{
}
