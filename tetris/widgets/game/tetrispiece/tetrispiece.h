#ifndef TETRISPIECE_H
#define TETRISPIECE_H

#include <QObject>
#include <QPoint>

class TetrisPiece : public QObject
{
    Q_OBJECT
public:
    explicit TetrisPiece(QObject *parent = nullptr, char _type='I');
    void setType(char type);
    QVector <QPoint> const getCells() {return cells;}

    void rotate(bool dir);
private:
    QVector <QPoint> cells;
    char type;

    int getRightCoord();
signals:

};

#endif // TETRISPIECE_H
