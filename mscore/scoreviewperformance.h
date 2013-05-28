#ifndef __SCOREVIEWPERFORMANCE_H__
#define __SCOREVIEWPERFORMANCE_H__

#include "globals.h"


namespace Ms {

class ScoreTab;
class Score;
class ScoreView;



class scoreViewPerformance : public QMainWindow
{
      Q_OBJECT

      ScoreView* sv;

   public:
      scoreViewPerformance(QWidget *parent = 0, QList<Score*>* ls = 0);
      void keyPressEvent(QKeyEvent* e);

   private:
      ScoreTab *tab1;

   public slots:
      void pageLeft();
      void pageRight();
};

}
#endif

