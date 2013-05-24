#include "scoreviewperformance.h"
#include "scoretab.h"

 
 
namespace Ms {
 
scoreViewPerformance::scoreViewPerformance(QWidget *parent, QList<Score*>* sl)
     : QDialog(parent)
 {
     tab1 = new ScoreTab(sl);
     tab1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
     tab1->initScoreView(0, 10, 10, 10, 10);
     connect(tab1, SIGNAL(tabCloseRequested(int)), SLOT(removeTab(int)));

     
     QPushButton *button1 = new QPushButton("One");
     QPushButton *button2 = new QPushButton("Two");
     
     QHBoxLayout* qhbl = new QHBoxLayout;
     qhbl->setMargin(0);
     qhbl->setSpacing(0);
     qhbl->addWidget(button1);
     qhbl->addWidget(button2);
    
     QSplitter* mainWindow = new QSplitter;
     mainWindow->setChildrenCollapsible(false);
     mainWindow->setOrientation(Qt::Vertical);

     QGridLayout *mlayout = new QGridLayout;
     mlayout->setSizeConstraint(QLayout::SetDefaultConstraint);
 //    mlayout->addWidget(qhbl, 0, 0);
     mlayout->addWidget(tab1, 1, 0);
    
     
     mainWindow->setLayout(mlayout);

     //QWidget* mainScore = new QWidget;
     //mainScore->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

     
     setLayout(mlayout);
     setSizeGripEnabled(true);
     resize( 1000, 1000 );




/*

     QGridLayout *mainLayout = new QGridLayout;
     mainLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
     mainLayout->addWidget(tab1, 0, 0);
     setLayout(mainLayout);
     setSizeGripEnabled(true);
     resize( 1000, 1000 );
*/
     setWindowTitle(tr("Performance Score"));
 }

}