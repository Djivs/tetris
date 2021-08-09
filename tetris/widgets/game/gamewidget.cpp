#include "gamewidget.h"

GameWidget::GameWidget(QWidget *parent) : QWidget(parent) {
    view = new QGraphicsView(this);

    layout = new QVBoxLayout();
    layout->addWidget(view);


    mainCycle();
}

void GameWidget::mainCycle() {
    makeLogic();
    drawGame();
    QTimer::singleShot(1000, this, [this] {mainCycle();});
}
void GameWidget::drawGame() {
    scene.clear();

    ///<- Draw board ->///
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 10; ++j) {
            QRect cubeRect(10 * j, 10 * i, 10, 10);
            QPen pen;
            if (board[i][j]) {
                pen.setColor(Qt::black);
            } else {
                pen.setColor(Qt::white);
            }
            scene.addRect(cubeRect, pen, QBrush(pen.color()));
        }
    }

    view->setScene(&scene);
    view->show();

}

void GameWidget::makeLogic() {
    if (curPiece == nullptr) {
        curPiece = new TetrisPiece(nullptr, 'T');
        addPiece(curPiece);
    } else {
        return;
    }

}

void GameWidget::addPiece(TetrisPiece *piece) {
    QVector <QPoint> pieceCells = piece->getCells();
    for(auto &i: pieceCells) {
        board[20 - i.y()][i.x()-1] = 1;
    }
}
