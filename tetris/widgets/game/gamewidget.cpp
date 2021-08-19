#include "gamewidget.h"

GameWidget::GameWidget(QWidget *parent) : QWidget(parent) {
    view = new QGraphicsView(this);

    layout = new QVBoxLayout();
    layout->addWidget(view);

    curPiece = new TetrisPiece(nullptr, randomTetrisPiece());
    addPiece();

    mainCycle();
}

void GameWidget::mainCycle() {
    makeLogic();
    drawGame();
    if (!gameover)
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
    if (isGoingDown()) {
        removePiece();
        curPiece->move('d');
        addPiece();
        return;
    } else {
        clearLines();
        delete curPiece;
        curPiece = new TetrisPiece(nullptr, randomTetrisPiece());
        addPiece();
        if (!isGoingDown()) {
            gameover = true;
            QMessageBox msgBox;
            msgBox.setText("You failed");
            msgBox.exec();
        }
    }
}

void GameWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_K && isGoingDown()) {
        removePiece();
        curPiece->move('d');
        addPiece();
        drawGame();
    } else if(event->key() == Qt::Key_J && isGoingLeft()) {
        removePiece();
        curPiece->move('l');
        addPiece();
        drawGame();
    } else if(event->key() == Qt::Key_L && isGoingRight()) {
        removePiece();
        curPiece->move('r');
        addPiece();
        drawGame();
    } else if(event->key() == Qt::Key_F && isRotating(1)) {
        removePiece();
        curPiece->rotate(1);
        addPiece();
        drawGame();
    } else if(event->key() == Qt::Key_D && isRotating(0)) {
        removePiece();
        curPiece->rotate(0);
        addPiece();
        drawGame();
    }
}

void GameWidget::clearLines() {
    //status = CLEARINGLINES;
    for (int i = 19; i >= 0; --i) {
        int count = 0;
        for (int j = 0; j < 10; ++j) {
            count += board[i][j];
        }
        if (count == 10) {
            for (int j = i - 1; j > 0; --j) {
                for (int jj = 0; jj < 10; ++jj) {
                    board[j+1][jj] = board[j][jj];
                }
            }
            ++i;
        } else if (!count)
            break;
    }
    //status = GAME;
}


void GameWidget::addPiece() {
    QVector <QPoint> pieceCells = curPiece->getCells();
    for(auto &i: pieceCells) {
        board[20 - i.y()][i.x()-1] = 1;
    }
}

void GameWidget::removePiece() {
    QVector <QPoint> pieceCells = curPiece->getCells();
    for(auto &i: pieceCells) {
        board[20 - i.y()][i.x()-1] = 0;
    }
}

bool GameWidget::isGoingDown() {

    QVector <QPoint> cells = curPiece->getCells();
    for (int i = 0; i < 4; ++i) {
        int x = cells[i].x(), y = cells[i].y()-1;
        if (cells[i].y() == 1 || (cells.indexOf(QPoint(x, y)) == -1 && board[20 - y][x-1]))
            return 0;

    }
    return true;
}

bool GameWidget::isGoingLeft() {

    QVector <QPoint> cells = curPiece->getCells();
    for (int i = 0; i < 4; ++i) {
        int x = cells[i].x()-1, y = cells[i].y();
        if (!x || ((cells.indexOf(QPoint(x, y)) == -1) && board[20 - y][x-1]))
            return 0;

    }
    return true;
}

bool GameWidget::isGoingRight() {

    QVector <QPoint> cells = curPiece->getCells();
    for (int i = 0; i < 4; ++i) {
        int x = cells[i].x()+1, y = cells[i].y();
        if ((x == 11) || ((cells.indexOf(QPoint(x, y)) == -1) && board[20 - y][x-1]))
            return 0;

    }
    return true;
}
bool GameWidget::isRotating(bool dir) {
    TetrisPiece *buf = new TetrisPiece(curPiece);
    buf->rotate(dir);
    auto cells = buf->getCells();
    for (int i = 0; i < 4; ++i) {
        int x = cells[i].x(), y = cells[i].y();
        if ((cells.indexOf(QPoint(x, y)) == -1) && board[20 - y][x-1])
            return 0;
    }
    delete buf;
    return true;
}
