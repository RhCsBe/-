#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include <QBrush>
#include <QPen>
#include <QMessageBox>
#include <QButtonGroup>

namespace Ui {
class Setting;
}

class Setting : public QDialog
{
    Q_OBJECT

public:
    //explicit Setting(QWidget *parent = nullptr);
    Setting(QBrush* brush_red,QBrush* brush_black,QPen* background_pen,QWidget *parent = nullptr);
    //Setting(int* id,QWidget *parent = nullptr);
    QBrush* brush_red=nullptr;//红方画刷
    QBrush* brush_black=nullptr;//黑方画刷
    QPen* background_pen=nullptr;//棋盘线条画笔
    //int *id=nullptr;
    QButtonGroup* redGroup=nullptr;
    QButtonGroup* blackGroup=nullptr;
    QButtonGroup* boardGroup=nullptr;
    ~Setting();
private:
    Ui::Setting *ui;
};

#endif // SETTING_H
