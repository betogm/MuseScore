#include "globals.h"


namespace Ms {

class ScoreTab;
class Score;



 class scoreViewPerformance : public QDialog
 {
     Q_OBJECT

 public:
     scoreViewPerformance(QWidget *parent = 0, QList<Score*>* ls = 0);

 private:
     ScoreTab *tab1;
     //QWidget *extension;
 };

}