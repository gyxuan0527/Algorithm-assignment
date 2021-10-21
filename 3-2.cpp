#include <iostream>
#include <iomanip>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

//Bellman Ford
void BellmanFord(vector<vector<int>> &adjMatrix, int s, int t, int i){
    int n = adjMatrix.size();
    vector<vector<pair<int, int>>> adjList(n);        //將相連的鄰居及distance存成list樣子
    for(int a=0; a<n; a++){
        for(int j=0; j<n; j++){
            if(a!=j && adjMatrix[a][j] < INT_MAX)
                adjList[a].push_back({j, adjMatrix[a][j]});
        }
    } //找鄰居


    vector<vector<int>> D(i+1, vector<int>(n));   //D為最終輸出的adjacency matrix ((i+1)*n)
    //initialize row0
    for(int j=0; j<n; j++){
        if(j == t) D[0][j] = 0;     //將限制只能用0條邊下，終點t到終點t的距離 initialize成0
        else D[0][j] = INT_MAX;     //將限制只能用0條邊下，其他點到終點t的距離 initialize成INT_MAX(impossible)
    }

    //**dynamic programming
    for(int a=1; a<=i; a++){
        for(int j=0; j<n; j++){
            D[a][j] = D[a-1][j];      //先把邊數限制為a的最短距離 填成邊數限制為a-1的(上一回合找出)
            for(auto &adj: adjList[j]){
                int k = adj.first, w = adj.second;   //k :與j相連的鄰居,w :和鄰居之間的distance
                if(D[a-1][k] < INT_MAX)
                    D[a][j] = min(D[a][j], w+D[a-1][k]);
            }
        }
    }
    //考慮上一回合結果(最多只用a-1條邊) vs 走經過鄰居k(最多可用a條邊)取小的

    cout << "Shortest distance:" ;
    if(D[i][s] == INT_MAX) cout << "INF" << endl;
    else cout << D[i][s] << endl;

    cout << "Table:" << endl;
    for(int a=0; a<=i; a++){
        for(int j =0; j<n; j++){
            if(D[a][j] == INT_MAX)
                cout << setw(5) << "INF";
            else
                cout << setw(5) << D[a][j];
        }
        cout << endl;
    }
}

int main()
{
    vector<vector<int>> graph = {{0, 12, 6, 8, INT_MAX, INT_MAX, INT_MAX, INT_MAX},
                                 {INT_MAX, 0, -7, INT_MAX, -4, INT_MAX, INT_MAX, INT_MAX},
                                 {INT_MAX, INT_MAX, 0, INT_MAX, 5, 5, INT_MAX, INT_MAX},
                                 {INT_MAX, INT_MAX, INT_MAX, 0, INT_MAX, 3, 6, INT_MAX},
                                 {INT_MAX, INT_MAX, -4, INT_MAX, 0, 3, INT_MAX, 6},
                                 {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 0, 2, INT_MAX},
                                 {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 0, 2},
                                 {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 0}};

    BellmanFord(graph, 0, 7, 7);
}