#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QTimer>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QMessageBox>

#include "tetrispiece/tetrispiece.h"


class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
protected:
    void keyPressEvent(QKeyEvent *event);
private:
    QGraphicsScene scene;
    QGraphicsView *view;
    QVBoxLayout *layout;

    TetrisPiece *curPiece;

    bool board[20][10] = {};
    bool gameover=0;

    const QString piecesTypes = "ZSLJOIT";

    void mainCycle();

    void drawGame();
    void makeLogic();


    void addPiece();
    void removePiece();
    void clearLines();

    bool isGoingDown();
    bool isGoingLeft();
    bool isGoingRight();
    bool isRotating(bool dir);

    QChar randomTetrisPiece() {
        return piecesTypes[QRandomGenerator::global()->generate() % 7];}
    //return 'I';}

signals:

};

#endif // GAMEWIDGET_H
