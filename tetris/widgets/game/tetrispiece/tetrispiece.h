#ifndef TETRISPIECE_H
#define TETRISPIECE_H

#include <QObject>
#include <QPoint>
#include <QDebug>
#include <QTime>
#include <QRandomGenerator>

class TetrisPiece : public QObject
{
    Q_OBJECT
public:
    explicit TetrisPiece(TetrisPiece *parent = nullptr, QChar _type='I');
    void setType(char type);
    QVector <QPoint> const getCells() {return cells;}

    void rotate(bool dir);
    void move(char dir);


    int getRightCoord();
    int getLeftCoord();
    int getTopCoord();
    int getDownCoord();

    int getColor() const {return color;}
protected:
    QVector <QPoint> cells;
    QChar type;
    int color;
signals:

};

#endif // TETRISPIECE_H
