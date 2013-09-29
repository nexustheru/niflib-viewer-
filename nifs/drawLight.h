#include <QApplication>
#include <QtGui/QWidget>

class nlight : public QWidget
{
protected :
  virtual void draw();
  virtual void init();
  virtual QString helpString() const;

private:
  nlight* light1;
  nlight* light2;
};
