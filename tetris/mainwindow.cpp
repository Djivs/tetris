#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(250, 250);
    setMenu();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setMenu() {
    menu = new MenuWidget;
    connect(menu, &MenuWidget::gameButtonPressed, this, [this] {delete menu; setGame();});

    setCentralWidget(menu);
}

void MainWindow::setGame() {
    game = new GameWidget();

    setCentralWidget(game);
}

