#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStyle>
#include "widgets/menu/menuwidget.h"
#include "widgets/game/gamewidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    MenuWidget *menu;
    GameWidget *game;

    void setMenu();
    void setGame();

};
#endif // MAINWINDOW_H
