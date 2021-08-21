#include "gamewidget.h"

GameWidget::GameWidget(QWidget *parent) : QWidget(parent) {
    view = new QGraphicsView(this);
    view->setMaximumSize(25 * 10 + 10, 25 * 20 + 10);

    linesBox = new QSpinBox();
    linesBox->setEnabled(false);
    linesBox->setValue(0);
    linesBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    linesLabel = new QLabel("Lines cleared:");
    linesLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    linesLayout = new QVBoxLayout();
    linesLayout->addStretch();
    linesLayout->addWidget(linesLabel);
    linesLayout->addWidget(linesBox);
    linesLayout->addStretch();
    linesLayout->setAlignment(Qt::AlignCenter);

    //auto spacer_left = new QSpacerItem(10, 10, QSizePolicy::Expanding);
    auto spacer_right = new QSpacerItem(10, 10, QSizePolicy::Expanding);


    layout = new QGridLayout();
    layout->addWidget(view, 0, 1);
    layout->addLayout(linesLayout, 0, 0);
    layout->addItem(spacer_right, 1, 2);
    view->setAlignment(Qt::AlignCenter);

    setLayout(layout);

    curPiece = new TetrisPiece(nullptr, randomTetrisPiece());
    addPiece();

    mainCycle();
}

void GameWidget::mainCycle() {
    makeLogic();
    drawGame();
    if (!gameover)
        QTimer::singleShot(900 - 30 * (lines % 10), this, [this] {mainCycle();});
}
void GameWidget::drawGame() {
    scene.clear();

    ///<- Draw board ->///
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 10; ++j) {
            QRect cubeRect(25 * j, 25 * i, 25, 25);
            QPen pen;
            pen.setColor(colors[board[i][j]]);
            scene.addRect(cubeRect, pen, QBrush(pen.color()));
        }
    }

    view->setScene(&scene);
    view->show();

}

void GameWidget::drawPause() {
    scene.clear();
    scene.addText("Pause");
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
            msgBox.setText("You failed.\n Wanna try again?");
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            if (msgBox.exec()) {
                gameover = false;
                delete curPiece;
                lines = 0;
                for (int i = 0; i < 20; ++i) {
                    for (int j = 0; j < 10; ++j) {
                        board[i][j] = 0;
                    }
                }
                curPiece = new TetrisPiece(nullptr, randomTetrisPiece());
                addPiece();

                mainCycle();

            }
        }
    }
}

void GameWidget::keyPressEvent(QKeyEvent *event) {

    switch (event->key()) {
    case Qt::Key_K:
        if (isGoingDown()) {
            removePiece();
            curPiece->move('d');
            addPiece();
            drawGame();
        }
        break;
    case Qt::Key_J:
        if(isGoingLeft()) {
            removePiece();
            curPiece->move('l');
            addPiece();
            drawGame();
        }
        break;
    case Qt::Key_L:
        if(isGoingRight()) {
            removePiece();
            curPiece->move('r');
            addPiece();
            drawGame();
        }
        break;
    case Qt::Key_F:
        if(isRotating(1)) {
            removePiece();
            curPiece->rotate(1);
            addPiece();
            drawGame();
        }
        break;
    case Qt::Key_D:
        if(isRotating(0)) {
            removePiece();
            curPiece->rotate(0);
            addPiece();
            drawGame();
        }
        break;
    case Qt::Key_P:
        gameover = !gameover;
        if (!gameover)
            mainCycle();
        else
            drawPause();
        break;
    }
}

void GameWidget::clearLines() {
    maxHeight = std::min(maxHeight, 20 - curPiece->getTopCoord() - 1);
    for (int i = 20 - curPiece->getDownCoord(); i > maxHeight; --i) {
        int count = 0;
        for (int j = 0; j < 10; ++j) {
            count += (bool)board[i][j];
        }
        if (count == 10) {
            ++lines;
            for (int j = i - 1; j >= maxHeight; --j) {
                for (int jj = 0; jj < 10; ++jj) {
                    board[j+1][jj] = board[j][jj];
                }
            }
            ++maxHeight;
            ++i;
        }
    }
    linesBox->setValue(lines);
}


void GameWidget::addPiece() {
    QVector <QPoint> pieceCells = curPiece->getCells();
    int k = curPiece->getColor();
    for(auto &i: pieceCells) {
        board[20 - i.y()][i.x()-1] = k;
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
