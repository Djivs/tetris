#include "tetrispiece.h"

TetrisPiece::TetrisPiece(QObject *parent, QChar _type) : QObject(parent) {
    type = _type;
    switch (type.toLatin1()) {
        case 'O':
            cells.push_back(QPoint(5, 20));
            cells.push_back(QPoint(5, 19));
            cells.push_back(QPoint(6, 20));
            cells.push_back(QPoint(6, 19));
        break;
        case 'I':
            cells.push_back(QPoint(6, 18));
            cells.push_back(QPoint(6, 20));
            cells.push_back(QPoint(6, 19));
            cells.push_back(QPoint(6, 17));
        break;
        case 'S':
            cells.push_back(QPoint(6, 19));
            cells.push_back(QPoint(7, 20));
            cells.push_back(QPoint(5, 19));
            cells.push_back(QPoint(6, 20));
        break;
        case 'Z':
            cells.push_back(QPoint(6, 19));
            cells.push_back(QPoint(5, 20));
            cells.push_back(QPoint(7, 19));
            cells.push_back(QPoint(6, 20));
        break;
        case 'L':
            cells.push_back(QPoint(6, 19));
            cells.push_back(QPoint(7, 18));
            cells.push_back(QPoint(6, 20));
            cells.push_back(QPoint(6, 18));
        break;
        case 'J':
            cells.push_back(QPoint(6, 19));
            cells.push_back(QPoint(5, 18));
            cells.push_back(QPoint(6, 20));
            cells.push_back(QPoint(6, 18));
        break;
        case 'T':
            cells.push_back(QPoint(6, 20));
            cells.push_back(QPoint(5, 20));
            cells.push_back(QPoint(7, 20));
            cells.push_back(QPoint(6, 19));
        break;

    }

}

void TetrisPiece::rotate(bool dir) {
    if (type == 'O')
        return;
    int board[4][4] = {};
    int l = getLeftCoord(), d = getDownCoord();
    for (int i = 0; i < 4; ++i) {
        board[3 - (cells[i].y() - d)][cells[i].x() - l] = 1;
    }

    int temp[4][4] = {};
    if (dir) { //clockwise
        d -= 1;
        if (board[0][3])
            d -=1;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                temp[j][3-i] = board[i][j];
            }
        }
    } else {
        l -=1;
        if (type == 'I') {
            if (!board[0][0])
                d -= 1;
            else
                l -=1;
        }
        else if (board[3][0]) {
            if (QString("ZSTI").indexOf(type) != -1) {
                l -=1;
            } else if (type == 'L' || type == 'J') {
                if (!board[1][0])
                    l -= 1;
            }
        }
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                temp[3 - j][i] = board[i][j];
            }
        }
    }

    QVector <QPoint> c;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (temp[i][j]) {
                int x = j + l, y = 2 - i + d;
                if (x > 10 || x < 1 || y > 20 || y < 1)
                    return;
                c.push_back(QPoint(x, y));
            }
        }
    }


    cells = c;
}

void TetrisPiece::move(char dir) {
    switch(dir) {
    case 'd':
        if (getDownCoord() == 1)
            return;
        for (int i = 0; i < 4; ++i)
            cells[i] = QPoint(cells[i].x(), cells[i].y() - 1);
        break;
    case 'l':
        if (getLeftCoord() == 1)
            return;
        for (int i = 0; i < 4; ++i)
            cells[i] = QPoint(cells[i].x() - 1, cells[i].y());
        break;
    case 'r':
        if (getRightCoord() == 10)
            return;
        for (int i = 0; i < 4; ++i)
            cells[i] = QPoint(cells[i].x() +1, cells[i].y());
        break;
    }
}

int TetrisPiece::getRightCoord() {
    int right = cells[0].x();
    for (int i = 1; i < 4; ++i) {
        right = std::max(right, cells[i].x());
    }
    return right;
}
int TetrisPiece::getLeftCoord() {
    int left = cells[0].x();
    for (int i = 1; i < 4; ++i) {
        left = std::min(left, cells[i].x());
    }
    return left;
}
int TetrisPiece::getTopCoord() {
    int top = cells[0].y();
    for (int i = 1; i < 4; ++i) {
        top = std::max(top, cells[i].y());
    }
    return top;
}
int TetrisPiece::getDownCoord() {
    int down = cells[0].y();
    for (int i = 1; i < 4; ++i) {
        down = std::min(down, cells[i].y());
    }
    return down;
}
