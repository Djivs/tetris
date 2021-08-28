#include "gamewidget.h"

GameWidget::GameWidget(QWidget *parent) : QWidget(parent) {
    view = new QGraphicsView(this);
    view->setMaximumSize(25 * 10 + 10, 25 * 20 + 3);

    linesBox = new QSpinBox();
    linesBox->setEnabled(false);
    linesBox->setMaximum(1000);
    linesBox->setValue(0);
    linesBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    linesLabel = new QLabel("Lines cleared:");
    linesLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    levelBox = new QSpinBox();
    levelBox->setEnabled(false);
    levelBox->setValue(0);
    levelBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    levelLabel = new QLabel("Level:");
    levelLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    speedBox = new QSpinBox();
    speedBox->setEnabled(false);
    speedBox->setMaximum(1000);
    speedBox->setValue(speed);
    speedBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    speedLabel = new QLabel("Current speed(ms):");
    speedLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    nextPieceLabel = new QLabel("Next piece:");
    nextPiecePic = new QLabel();

    statsLayout = new QVBoxLayout();
    statsLayout->addStretch();
    statsLayout->addWidget(linesLabel);;
    statsLayout->addWidget(linesBox);
    statsLayout->addWidget(levelLabel);
    statsLayout->addWidget(levelBox);
    statsLayout->addWidget(speedLabel);
    statsLayout->addWidget(speedBox);
    statsLayout->addWidget(nextPieceLabel);
    statsLayout->addWidget(nextPiecePic);
    statsLayout->addStretch();
    statsLayout->setAlignment(Qt::AlignCenter);

    auto spacer_right = new QSpacerItem(10, 10, QSizePolicy::Expanding);


    layout = new QGridLayout();
    layout->addWidget(view, 0, 1);
    layout->addLayout(statsLayout, 0, 0);
    layout->addItem(spacer_right, 1, 2);
    view->setAlignment(Qt::AlignCenter);

    setLayout(layout);

    piecesImage.load("/home/dmitriy/Загрузки/D7UtvBQWsAAiLzb.jpg");

    nextPiece = randomTetrisPiece();
    setNextPiecePic();

    makeNewPiece();
    addPiece();

    mainCycle();
}

void GameWidget::mainCycle() {
    if (gameover)
        return;
    makeLogic();
    drawGame();
    QTimer::singleShot(speed, this, [this] {mainCycle();});
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
        makeNewPiece();
        addPiece();
        if (!isGoingDown()) {
            gameover = true;
            speed = startingSpeed;
            speedBox->setValue(startingSpeed);
            lines = 0;
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
                makeNewPiece();
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
    level = lines / 2;
    levelBox->setValue(level);
    speed = startingSpeed - level * 30;
    speedBox->setValue(speed);
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

void GameWidget::makeNewPiece() {
    curPiece = new TetrisPiece(nullptr, nextPiece);
    nextPiece = randomTetrisPiece();
    setNextPiecePic();
}

void GameWidget::setNextPiecePic() {
    QPixmap p = QPixmap::fromImage(piecesImage);
    int startingIndex = piecesTypes.indexOf(nextPiece);
    p = p.copy(QRect(piecesCoords[startingIndex], 0, piecesCoords[startingIndex+1] - piecesCoords[startingIndex], 240));
    nextPiecePic->setPixmap(p.scaled(75, 75 , Qt::KeepAspectRatio));
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
