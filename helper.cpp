#include "helper.h"
#include<QDebug>
#include<bits/stdc++.h>
Helper::Helper(QObject *parent) : QObject(parent)
{

}

QVector<int> Helper::newGame()
{
    QVector<int>bricks = {
        1, 5, 5, 5, 5, 5, 5, 5, 5, 6,
        3, 5, 5, 5, 5, 5, 5, 5, 5, 12,
        9, 5, 5, 5, 5, 5, 5, 5, 5, 6,
        3, 5, 5, 5, 5, 5, 5, 5, 5, 12,
        9, 5, 5, 5, 5, 5, 5, 5, 5, 6,
        3, 5, 5, 5, 5, 5, 5, 5, 5, 12,
        9, 5, 5, 5, 5, 5, 5, 5, 5, 6,
        3, 5, 5, 5, 5, 5, 5, 5, 5, 12,
        9, 5, 5, 5, 5, 5, 5, 5, 5, 6,
        3, 5, 5, 5, 5, 5, 5, 5, 5, 12

    };

    do{
        for(int i = 0; i < 10; i ++){
            for(int j = 0; j < 10; j++){
                forDFS1[i][j] = 0;
                was1[i][j] = 0;

            }
        }
        cells.resize(0);
        dfs1(0, 0, -1, -1);

    }while(cells.size() != 100);

    for(int i = 0; i < 10; i++){
        for(int j =0; j < 10; j ++){
           bricks[i*10 + j] = forDFS1[i][j];
        }
    }

    QVector<int>v = bricks;
    //if(cells.size() !=100)

    //qDebug() << v.size();
    //qDebug() << cells.size();


    /*рандомайзер состояния изначального */
 //   bricks[1] = (bricks[1] >> 1)|((bricks[1] & 1) << 3); //отдельно повращать


//    for(int i = 0; i < 100; i+=4){
//        int randCount = rand() % 4;
//        for(int j = 0; j <= randCount; j++){
//            bricks[i] = (bricks[i] >> 1)|((bricks[i] & 1) << 3);
//        }
//    }

    return bricks;
}




void Helper::dfs1( int i, int j,int pri, int prj){
    using namespace std;
    std::vector<std::pair<int, int>>vp;
    int cell[4];
    was1[i][j] = 1;
    vp.push_back({i, j+1});
    vp.push_back({i+1, j});
    vp.push_back({i, j-1});
    vp.push_back({i-1, j});
    int cou = 0;
    //right
    if(j + 1 < 10 && was1[i][j+1] == 0){
        cell[0] = 1;
        cou++;
    }else{
            cell[0] = 0;
    }
    //down
    if(i + 1 < 10 && was1[i+1][j] == 0){
        cou++;
        cell[1] = 1;
    }else{
            cell[1] = 0;
    }
    //left
    if(j - 1 >=0 && was1[i][j-1] == 0){
        cou++;
        cell[2] = 1;

    }else{
            cell[2] = 0;
    }
    //up
    if(i - 1 >= 0 && was1[i-1][j] == 0){
        cou++;
        cell[3] = 1;
    }else{
            cell[3] = 0;
    }
    int curCell = 0;
        /*пошел рандом*/
    set<int>sp;

    if(cou != 0){

        int pathCount = rand() % (cou+1);

        pathCount = pathCount == 0 ? 1 : pathCount;

        while((int)sp.size() != pathCount){
            int cur = rand() % 4;
            if(cell[cur] == 1 ){
                was1[vp[cur].first][vp[cur].second] = 1;
                sp.insert(cur);
            }
        }
    }

    for(int k = 0; k < 4; k++){
        if(sp.count(k) == 1 || (vp[k].first == pri && vp[k].second == prj))
            curCell+=((cell[k]|1) << k);
    }
    cells.push_back(curCell);

    forDFS1[i][j] = curCell;
    int forRand[4];
    for(int k = 0; k < 4; k++){
        forRand[k] = 1;
    }

    if(cell[0] == 1 && j + 1 != prj && sp.count(0) == 1/* && vp[0].first != pri && vp[0].second != prj*/ ){
        dfs1(i, j+1, i, j);
    }

    if(cell[1] == 1 && i+1 != pri&& sp.count(1) == 1 /*&& vp[1].first != pri && vp[1].second != prj*/){
        dfs1(i+1, j, i, j);
    }

    if(cell[2] == 1 && j-1 !=prj && sp.count(2) == 1 /*&& vp[2].first != pri && vp[2].second != prj*/){
        dfs1( i, j-1, i, j);
    }

    if(cell[3] == 1 && i-1 != pri && sp.count(3) == 1/*&& vp[3].first != pri && vp[3].second != prj*/){
        dfs1( i-1, j, i, j);
    }
}

QVector<bool> Helper::light(QVector<int>bricks)
{
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            wasli[i][j] = 0;
            lightsDfs[i][j] = false;
        }
    }
    lightCount = -1;
    for(int i = 0 ; i< 100; i++){
        int r, c;
        r = i /10;
        c = i  % 10;
        forli[r][c] = bricks[i];
    }

    dfsLi(0, 0, -1, -1);

    QVector<bool> lights;

    lights.push_back(true);

    for(int i = 1; i < 100; i++){
        lights.push_back(lightsDfs[i/10][i%10]);
    }

    if(lightCount == 100){
        //todo
    }

    return lights;
}

void Helper::dfsLi(int i, int j, int pri, int prj){

    int curNum = forli[i][j];
    lightsDfs[i][j] = true;
    lightCount++;
    //right
    if(j + 1 < 10 && wasli[i][j+1] == 0 && ((curNum&1) == 1) && (forli[i][j+1] & 4) == 4){

       wasli[i][j+1] = 1;
        dfsLi(i, j+1, i, j);
    }
    //down
    if(i + 1 < 10 && wasli[i+1][j] == 0 && ((curNum&2) == 2) && (forli[i+1][j] & 8) == 8){
        wasli[i+1][j] = 1;
        dfsLi(i+1, j, i, j);
    }
    //left
    if(j - 1 >=0 && wasli[i][j-1] == 0 && ((curNum&4) == 4) && (forli[i][j-1] & 1) == 1){

      wasli[i][j-1] = 1;
        dfsLi(i, j-1, i, j);
    }
    //up
    if(i - 1 >= 0 && wasli[i-1][j] == 0 && ((curNum&8) == 8)&& (forli[i-1][j] & 2) == 2){
       wasli[i-1][j] = 1;
        dfsLi(i-1, j, i, j);
    }

}

int Helper::getLight(){
    return lightCount;
}
