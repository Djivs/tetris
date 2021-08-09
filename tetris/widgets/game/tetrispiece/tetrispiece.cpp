#include "tetrispiece.h"

TetrisPiece::TetrisPiece(QObject *parent, char _type) : QObject(parent) {
    type = _type;
    switch (type) {
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
    switch(type) {
    case 'O':
        break;
    case 'I':
        if (cells[1].y() != cells[0].y()) {
            cells[1] = QPoint(cells[0].x(), cells[0].y() - 1);
            cells[2] = QPoint(cells[0].x(), cells[0].y() + 1);
            cells[3] = QPoint(cells[0].x(), cells[0].y() + 2);
        } else {
            int right = getRightCoord();
            if (right > 18 || right < 2)
                break;
            cells[1] = QPoint(cells[0].x() + 1, cells[0].y());
            cells[2] = QPoint(cells[0].x() + 2, cells[0].y());
            cells[3] = QPoint(cells[0].x() - 1, cells[0].y());
        }
        break;
    case 'S':
        if (cells[1].x() < cells[0].x()) {
            cells[1] = QPoint(cells[1].y(), cells[1].x() + 2);
            cells[2] = QPoint(cells[2].y()+1, cells[2].x()-1);
            cells[3] = QPoint(cells[3].y()+1, cells[3].x() +1);
        } else {
            cells[1] = QPoint(cells[1].y(), cells[1].x() - 2);
            cells[2] = QPoint(cells[2].y()-1, cells[2].x()+1);
            cells[3] = QPoint(cells[3].y()-1, cells[3].x() -1);
        }
        break;
    case 'Z':
        if (cells[1].x() < cells[0].x()) {
            cells[1] = QPoint(cells[1].y(), cells[1].x() + 2);
            cells[2] = QPoint(cells[2].y()-1, cells[2].x()+1);
            cells[3] = QPoint(cells[3].y()-1, cells[3].x() -1);
        } else {
            cells[1] = QPoint(cells[1].y(), cells[1].x() - 2);
            cells[2] = QPoint(cells[2].y()+1, cells[2].x()-1);
            cells[3] = QPoint(cells[3].y()+1, cells[3].x() +1);
        }
        break;
    case 'L':
        if (cells[2].x() == cells[0].x()) {
            cells[2] = QPoint(cells[0].x() - 1, cells[0].y());
            cells[3] = QPoint(cells[0].x() + 1, cells[0].y());
            if (cells[1].y() < cells[0].y()) {
                cells[1] = QPoint(cells[1].x(), cells[1].y() + 2);
            } else {
                cells[1] = QPoint(cells[1].x(), cells[1].y() - 2);
            }
        } else {
            cells[2] = QPoint(cells[0].x(), cells[0].y()-1);
            cells[3] = QPoint(cells[0].x(), cells[0].y()+1);
            if (cells[1].y() < cells[0].y()) {
                cells[1] = QPoint(cells[1].x(), cells[1].y() + 2);
            } else {
                cells[1] = QPoint(cells[1].x(), cells[1].y() - 2);
            }
        }
    }
}

int TetrisPiece::getRightCoord() {
    int right = cells[0].x();
    for (int i = 1; i < 4; ++i) {
        right = std::max(right, cells[i].x());
    }
    return right;
}
