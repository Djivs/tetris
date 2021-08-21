#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QTimer>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QSpacerItem>
#include <QSpinBox>
#include <QLabel>

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
    QGridLayout *layout;
    QSpinBox *linesBox;
    QLabel *linesLabel;
    QVBoxLayout *linesLayout;


    TetrisPiece *curPiece;

    int board[20][10] = {};
    bool gameover=0;

    int maxHeight = 19;
    int lines = 0;

    const QString piecesTypes = "ZSLJOIT";
    const QColor colors[5] = {Qt::white, Qt::red, Qt::blue, Qt::darkGreen, Qt::magenta};

    void mainCycle();

    void drawGame();
    void makeLogic();
    void drawPause();


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
