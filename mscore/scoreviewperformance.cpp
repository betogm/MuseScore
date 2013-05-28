#include "scoreviewperformance.h"
#include "scoretab.h"
#include "scoreview.h"

 
 
namespace Ms {
 
scoreViewPerformance::scoreViewPerformance(QWidget *parent, QList<Score*>* sl) : QMainWindow(parent)
      {
      tab1 = new ScoreTab(sl);
      tab1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
      tab1->initScoreView(0, 10, 10, 10, 10);
      connect(tab1, SIGNAL(tabCloseRequested(int)), SLOT(removeTab(int)));
      sv = tab1->view();

      QWidget* mainWindow = new QWidget();
      mainWindow->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


      // Controls
      QWidget* controls = new QWidget();
      controls->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

      QPushButton *button1 = new QPushButton("One");
      QPushButton *button2 = new QPushButton("Two");

      QHBoxLayout* qhbl = new QHBoxLayout;
      qhbl->setMargin(0);
      qhbl->setSpacing(0);
      qhbl->addWidget(button1);
      qhbl->addWidget(button2);

      controls->setLayout(qhbl);

      // Central Widget Layout 
      QVBoxLayout *mlayout = new QVBoxLayout;
      mlayout->setSizeConstraint(QLayout::SetMinimumSize);
      mlayout->addWidget(controls);
      mlayout->addWidget(tab1);

      mainWindow->setLayout(mlayout);
      setCentralWidget(mainWindow);

      setWindowTitle(tr("Performance Score"));
      showFullScreen();

      sv->setFocus(Qt::OtherFocusReason);
      }

void scoreViewPerformance::pageLeft() 
      {
      sv->pagePrev();
      }

void scoreViewPerformance::pageRight() 
      {
      sv->pageNext();
      }

void scoreViewPerformance::keyPressEvent(QKeyEvent* e)
      {

      if (e->key() == Qt::Key_Left) {
            pageLeft();
            }
      else if (e->key() == Qt::Key_Right) {
            pageRight();
            }

      }



}