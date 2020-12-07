#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using std::cout, std::cin, std::endl;

struct coin{
    short index;
    int value;
    int weight;
};

int f, c;
coin coins[102];
short max[1000010], min[1000010];
long int maxv[1000010], minv[1000010];
short weights[1000010][2];
std::vector<short> check;

void fill(){
    for(int i = 0; i < f + 1; i++){
        max[i] = -1; min[i] = -1;
        maxv[i] = -1; minv[i] = -1;
        weights[i][0] = -1;
        weights[i][1] = -1;
    }
}

bool ascend(const short &c1,const short &c2){
    if(coins[c1].weight == coins[c2].weight) return coins[c1].value < coins[c2].value;
    else return coins[c1].weight < coins[c2].weight;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> f >> c;
    fill();
    coin tmp; tmp.value = 0; tmp.weight = 0; tmp.index = 0; coins[0] = tmp;
    for(short i = 1; i < c + 1; i++){
        cin >> tmp.value >> tmp.weight;
        tmp.index = i; coins[i] = tmp;
        if(weights[tmp.weight][0] == -1 && weights[tmp.weight][1] == -1){
            weights[tmp.weight][0] = tmp.index;
        }
        else if(weights[tmp.weight][1] == -1){
            weights[tmp.weight][1] = tmp.index;
        }
        else{
            if(coins[weights[tmp.weight][0]].value < coins[weights[tmp.weight][1]].value){
                if(coins[weights[tmp.weight][0]].value > tmp.index){
                    weights[tmp.weight][0] = tmp.index;
                }
                else if(coins[weights[tmp.weight][1]].value < tmp.index){
                    weights[tmp.weight][1] = tmp.index;
                }
            }
            else{
                if(coins[weights[tmp.weight][0]].value < tmp.index){
                    int x = weights[tmp.weight][1];
                    weights[tmp.weight][1] = tmp.index;
                    weights[tmp.weight][0] = x;
                }
                else if(coins[weights[tmp.weight][1]].value > tmp.index){
                    int x = weights[tmp.weight][0];
                    weights[tmp.weight][0] = tmp.index;
                    weights[tmp.weight][1] = x;
                }
            }
        }
    }
    for(int i = 1; i < f + 1; i++){
        if(weights[i][0] != -1){
            check.push_back(weights[i][0]);
            if(weights[i][1] != -1){
                check.push_back(weights[i][1]);
            }
        }
    }
    std::sort(check.begin(), check.end(), ascend);
    int init = -1;
    while(init == -1){
        for(int i = 1; i < f; i++){
            if(weights[i][0] != -1){
                init = i;
                break;
            }
        }
    }
    long int maxtmp[2], mintmp[2];
    for(int i = init; i < f + 1; i++){
        maxtmp[0] = -1; mintmp[0] = 10e12;
        maxtmp[1] = -1; mintmp[1] = 10e12;
        int imax = -1; int imin = -1;
        int jmax = -1; int jmin = -1;
        if(weights[i][0] != -1){
            if(weights[i][1] == -1){
                maxtmp[0] = coins[weights[i][0]].value;
                jmax = weights[i][0];
                mintmp[0] = coins[weights[i][0]].value;
                jmin = weights[i][0];
            }
            else{
                maxtmp[0] = coins[weights[i][1]].value;
                jmax = weights[i][1];
                mintmp[0] = coins[weights[i][0]].value;
                jmin = weights[i][0];
            }
        }
        for(auto j = check.begin(); j < check.end(); j++){
            long int jfirst = maxv[coins[*j].weight];
            long int rest = maxv[i - coins[*j].weight];
            if(rest != -1 && jfirst != -1){
                if(maxtmp[1] < jfirst + rest){
                    maxtmp[1] = jfirst + rest;
                    imax = max[i - coins[*j].weight];
                }
            }
            jfirst = minv[coins[*j].weight];
            rest = minv[i - coins[*j].weight];
            if(rest != -1 && jfirst != -1){
                if(mintmp[1] > jfirst + rest){
                    mintmp[1] = jfirst + rest;
                    imin = min[i - coins[*j].weight];
                }
            }
        }
        if(std::max(maxtmp[0], maxtmp[1]) == maxtmp[0]){
            max[i] = jmax; maxv[i] = maxtmp[0];
        }
        else{
            max[i] = imax; maxv[i] = maxtmp[1];
        }
        if(std::min(mintmp[0], mintmp[1]) == mintmp[0]){
            min[i] = jmin; minv[i] = mintmp[0];
        }
        else{
            min[i] = imin; minv[i] = mintmp[1];
        }
    }
    int retmax[102], retmin[102];
    for(int i = 0; i < c + 1; i++){
        retmax[i] = 0; retmin[i] = 0;
    }
    int wmax = f, wmin = f;

    while(wmax > 0 || wmin > 0){
        if(wmax > 0){
            if(max[wmax] == -1){
                cout << "NIE" << endl;
                return 0;
            }
            retmax[max[wmax]]++;
            wmax -= coins[max[wmax]].weight;
        }
        if(wmin > 0){
            if(min[wmin] == -1){
                cout << "NIE" << endl;
                return 0;
            }
            retmin[min[wmin]]++;
            wmin -= coins[min[wmin]].weight;
        }
    }
    cout << "TAK" << endl << minv[f] << endl;
    for(int i = 1; i < c + 1; i++){
        cout << retmin[i] << " ";
    }
    cout << endl << maxv[f] << endl;
    for(int i = 1; i < c + 1; i++){
        cout << retmax[i] << " ";
    }
    cout << endl;
}