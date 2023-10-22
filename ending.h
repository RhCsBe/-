#ifndef ENDING_H
#define ENDING_H

#include <QDialog>

namespace Ui {
class Ending;
}

class Ending : public QDialog
{
    Q_OBJECT

public:
    explicit Ending(QWidget *parent = nullptr);
    ~Ending();
    Ui::Ending *getUi();

private:
    Ui::Ending *ui;
};

#endif // ENDING_H
