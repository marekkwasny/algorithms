#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#define STOP_DIV 5
#define MAX 10e20
using std::cout, std::cin, std::vector, std::pair, std::endl, std::sort;

struct point{
    int x; int y;
    bool operator == (const point &tmp) const{
        if(x == tmp.x && y == tmp.y){
            return 1;
        }
        else return 0;
    }
    bool operator != (const point &tmp) const{
        if(x != tmp.x || y != tmp.y){
            return 1;
        }
        else return 0;
    }
};

struct triangle{
    point a; point b; point c;
    double per;
};

point ax[500050];
point ay[500050];
int n, x, y;
triangle final;

bool compx(const point &p1,const point &p2){
    if(p1.x == p2.x) return p1.y < p2.y;
    else return p1.x < p2.x;
}

bool compy(const point &p1,const point &p2){
    if(p1.y == p2.y) return p1.x < p2.x;
    else return p1.y < p2.y;
}

int dist(const point p1,const point p2){
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

int per(point a, point b, point c){
    return dist(a, b) + dist(b, c) + dist(c, a);
}

pair<vector<int>, vector<int>> split(int begin, int end, vector<int> &vect){
    if(begin == 0 && end == n){
        int mid = ceil((double)end / 2);
        int line = ax[mid].x;
        vector<int> vl; vector<int> vr;
        for(int i = 0; i < n; i++){
            if(ay[i].x < line) vl.push_back(i);
            else vr.push_back(i);
        }
        return make_pair(vl, vr);
    }
    else{
        vector<int> newl; vector<int> newr;
        int mid = begin + ceil((double)(end - begin) / 2);
        int line = ax[mid].x;
        for(int i = 0; i < (int)vect.size(); i++){
            if(ay[vect[i]].x < line) newl.push_back(vect[i]);
            else newr.push_back(vect[i]);
        }
        return make_pair(newl, newr);
    }
}

triangle brute(int begin, int end){
    triangle best;
    vector<point> points;
    best.per = MAX;
    int current;
    for(int i = begin; i < end; i++){
        for(int j = begin; j < end; j++){
            if(j != i){
                points.push_back(ax[j]);
            }
        }
        current = per(points[0], points[1], points[2]);
        if(current < best.per){
            best.a = points[0]; best.b = points[1]; best.c = points[2];
            best.per = current;
        }
        points.clear();
    }
    return best;
}

triangle calc(int begin, int end){
    int range = end - begin;
    triangle best;
    best.per = MAX;
    if(range > 2){
        if(range == 3){
            best.a = ax[begin]; best.b = ax[begin + 1]; best.c = ax[begin + 2];
            best.per = per(best.a, best.b, best.c);
            return best;
        }
        else{
            return brute(begin, end);
        }
    }
    else return best;
}

triangle mergefromside(vector<point> &vect, vector<point> &other, double half, triangle best){
    vector<triangle> possible; triangle tmp; int pertmp;
    for(int i = 0; i < (int)vect.size(); i++){
        for(int j = i + 1; j < (int)vect.size() && j < i + 20; j++){
            if( dist(vect[i], vect[j]) <= half){
                tmp.a = vect[i]; tmp.b = vect[j];
                possible.push_back(tmp);
            }
        }
    }
    for(int i = 0; i < (int)possible.size(); i++){
        for(int j = 0; j < (int)other.size(); j++){
            pertmp = per(possible[i].a, possible[i].b, other[j]);
            if(pertmp < best.per){
                best.a = possible[i].a; best.b = possible[i].b; best.c = other[j];
                best.per = pertmp;
            }
        }
    }
    return best;
}

triangle merge(int mid, triangle l, triangle r, vector<int> &vl, vector<int> &vr){
    triangle best; double half; int line = ax[mid].x;
    if(l.per < r.per){
        best.a = l.a; best.b = l.b; best.c = l.c;
        best.per = l.per;
    }
    else{
        best.a = r.a; best.b = r.b; best.c = r.c;
        best.per = r.per;
    }
    half = best.per / 2;
    vector<point> closel; vector<point> closer;
    for(int i = 0; i < (int)vl.size(); i++){
        if(abs(ay[vl[i]].x - line) <= half){
            closel.push_back(ay[vl[i]]);
        }
    }
    for(int i = 0; i < (int)vr.size(); i++){
        if(abs(ay[vr[i]].x - line) <= half){
            closer.push_back(ay[vr[i]]);
        }
    }
    best = mergefromside(closel, closer, half, best);
    best = mergefromside(closer, closel, half, best);
    return best;
}

triangle divide(int begin, int end, vector<int> &vect){
    int range = end - begin;
    if(range < STOP_DIV){
        return calc(begin, end);
    }
    else{
        pair<vector<int>, vector<int>> pair = split(begin, end, vect);
        vector<int> left = pair.first; vector<int> right = pair.second;
        int midl = begin + ceil((double)(end - begin) / 2);
        int midr = begin + floor((double)(end - begin) / 2);
        triangle l = divide(begin, midl, left);
        triangle r = divide(midr, end, right);
        triangle best = merge(midl, l, r, left, right);
        if(best.per < final.per || final.per == -1) final = best;
        return best;
    }
}

int main(){
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; i++){
        point tmp;
        cin >> tmp.x >> tmp.y;
        ax[i] = tmp; ay[i] = tmp;
    }
    
    sort(&ax[0], &ax[n], compx);
    sort(&ay[0], &ay[n], compy);  

    vector<int> vect; final.per = -1;
    triangle div = divide(0, n, vect);
    if(div.per < final.per || final.per == -1) final = div;

    cout << final.a.x << " " << final.a.y << endl;
    cout << final.b.x << " " << final.b.y << endl;
    cout << final.c.x << " " << final.c.y << endl;
}