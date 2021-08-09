#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QTimer>

#include "tetrispiece/tetrispiece.h"


class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
private:
    QGraphicsScene scene;
    QGraphicsView *view;
    QVBoxLayout *layout;

    TetrisPiece *curPiece;

    bool board[20][10] = {};

    void mainCycle();

    void drawGame();
    void makeLogic();


    void addPiece(TetrisPiece *piece);

signals:

};

#endif // GAMEWIDGET_H
