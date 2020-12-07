#include <iostream>
#include <vector>
using std::cout, std::cin, std::endl, std::vector, std::pair, std::make_pair;

int n, l, m, r, left[200020], mid[200020], right[200020], len = 0, cur, pre;
bool visited[200020];
vector<int> graph[10001];
vector<int> start, end;
vector<pair<int, int>> path;

int dfs(int node, int prev, int tmp){
    if(len) return 0;
    visited[node] = 1; path.push_back(make_pair(node, prev));
    if(!right[node]){
        len = tmp;
    }
    else{
        for(int i = 0; i < (int)graph[right[node]].size(); i++){
            if(!visited[graph[right[node]][i]]){
                if(!dfs(graph[right[node]][i], node, tmp + 1)){
                }
            }
        }
    }
    return 0;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> left[i] >> mid[i] >> right[i];
        if(!left[i]) start.push_back(i);
        graph[left[i]].push_back(i);
    }

    for(int i = 0; i < (int)start.size(); i++){
        dfs(start[i], start[i], 1);
        if(!len) path.clear();
        else break;
    }

    cur = path.back().first;
    pre = path.back().second;
    if(cur != pre) end.push_back(cur);
    for(int i = path.size()-1; i >= 0; i--){
        if(path[i].first == path[i].second){
            end.push_back(path[i].second);
            break;
        }
        else{
            cur = path[i].first;
            if(cur == pre){
                end.push_back(cur);
                pre = path[i].second;       
            }
        }
    }

    if(!len){
        cout << "BRAK" << endl;
        return 0;
    }
    else{
        cout << end.size() << endl;
        while(!end.empty()){
            cout << left[end.back()] << " " << mid[end.back()] << " " << right[end.back()] << endl;
            end.pop_back();
        }
    }
}