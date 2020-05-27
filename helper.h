#ifndef HELPER_H
#define HELPER_H

#include <QObject>

class Helper : public QObject
{
    Q_OBJECT
public:
    explicit Helper(QObject *parent = nullptr);

signals:

public:
    //void dfs(int was1[10][10], int forDFS1[10][10], int i, int j);
    void dfs1(int i, int j, int pri, int prj);
    int forDFS1[10][10];
    int was1[10][10];


    void dfsLi(int i, int j, int pri, int prj);
    int forli[10][10];
    int wasli[10][10];
    QVector<int>cells;
    bool lightsDfs[10][10];
    int lightCount;
public slots:
    QVector<int> newGame();
    QVector<bool> light(QVector<int>bricks);
    int getLight();
};

#endif // HELPER_H
