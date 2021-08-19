#ifndef TETRISPIECE_H
#define TETRISPIECE_H

#include <QObject>
#include <QPoint>
#include <QDebug>
#include <QTime>

class TetrisPiece : public QObject
{
    Q_OBJECT
public:
    explicit TetrisPiece(QObject *parent = nullptr, QChar _type='I');
    void setType(char type);
    QVector <QPoint> const getCells() {return cells;}

    void rotate(bool dir);
    void move(char dir);


    int getRightCoord();
    int getLeftCoord();
    int getTopCoord();
    int getDownCoord();
private:
    QVector <QPoint> cells;
    QChar type;
signals:

};

#endif // TETRISPIECE_H
