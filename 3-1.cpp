#include <iostream>
#include <iomanip>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

//find parent(representative)
int find(int x, vector<int> &parent){
    if(x == parent[x]) return parent[x];                //找到parent , return
    return parent[x] = find(parent[x], parent);     //不斷找parent
}
//union by rank
void uni(int x, int y, vector<int> &parent, vector<int> &rank){
    if(rank[x] <= rank[y]){
        if(rank[x] == rank[y]) rank[y]++;
        parent[x] = y;
    }else parent[y] = x;          //attach the smaller to the larger one
}
//Kruskal
void MST_Kruskal(vector<vector<int>> &adjMatrix){
    int n = adjMatrix.size();

    //把所有邊的組合放到edges  (cost, node i, node j)
    vector<vector<int>> edges;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(adjMatrix[i][j]>0 && adjMatrix[i][j]<INT_MAX)
                edges.push_back(vector<int>({adjMatrix[i][j], i, j}));
        }
    }

    sort(edges.begin(), edges.end());   //將邊依照cost大小排序

    vector<int> rank(n, 1);    //initialize rank to 1
    vector<int> parent(n);
    for(int i=0; i<n; i++) parent[i] = i;  //initialize parent to itself

    int cost = 0;
    vector<vector<int>> treeMatrix(n, vector<int>(n, INT_MAX));   //initialize treeMatrix(final output adjacency matrix)to INT_MAX
    for(int i=0; i<n; i++) treeMatrix[i][i] = 0;              //自己到自己 填cost=0
    for(auto &e: edges){
        int w = e[0], i = e[1], j = e[2];                     //w :挑中的edge的weight ,i: 挑中的edge的其中一端點 ,j: 挑中的edge的另一端點
        int x = find(i, parent), y = find(j, parent);  //find parent 看是否相同
        if(x == y) continue;                                  //若parent相同，代表MST中不需要這條邊
        uni(x, y, parent, rank);                       //若parent不同，union，並且加入這條邊至答案中
        cost += w;
        treeMatrix[i][j] = w;                                    //mark treeMatrix to the edge cost
        treeMatrix[j][i] = w;
    }

    cout << "minimum cost: " << cost << endl;
    cout << "tree:" << endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(treeMatrix[i][j] < INT_MAX)
                cout << setw(5) << treeMatrix[i][j] ;
            else
                cout << setw(5) << "INF";
        }
        cout << endl;
    }
}

int main()
{
    vector<vector<int>> graph = {{0, 14, 6, 8, INT_MAX, INT_MAX, INT_MAX, INT_MAX},
                                 {14, 0, 10, INT_MAX, 12, INT_MAX, INT_MAX, INT_MAX},
                                 {6, 10, 0, 9, INT_MAX, 14, INT_MAX, INT_MAX},
                                 {8, INT_MAX, 9, 0, INT_MAX, INT_MAX, 18, INT_MAX},
                                 {INT_MAX, 12, INT_MAX, INT_MAX, 0, 7, INT_MAX, 17},
                                 {INT_MAX, INT_MAX, 14, INT_MAX, 7, 0, 5, 3},
                                 {INT_MAX, INT_MAX, INT_MAX, 18, INT_MAX, 5, 0, 19},
                                 {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 17, 3, 19, 0}};

    MST_Kruskal(graph);
}