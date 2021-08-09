#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class MenuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MenuWidget(QWidget *parent = nullptr);

signals:
    void gameButtonPressed();
    void settingsButtonPressed();
    void aboutButtonPressed();
private:
    QPushButton *gameButton;
    QPushButton *settingsButton;
    QPushButton *aboutButton;

    QVBoxLayout *layout;

};

#endif // MENUWIDGET_H
