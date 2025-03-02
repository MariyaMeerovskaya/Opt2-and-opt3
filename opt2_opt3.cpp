#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct Point{
    double x;
    double y;
    Point(double k_x = 0, double k_y = 0) : x(k_x), y(k_y) {}
};

double lenn(const vector<int>& path, const vector<Point>& points){
    int i = 0;
    int len = path.size() - 1;
    int back = path.back(), front = path.front();
    double lenn = 0.0;
    for (i; i < len; ++i) lenn += sqrt(pow(points[path[i]].x - points[path[i + 1]].x, 2) + pow(points[path[i]].y - points[path[i + 1]].y, 2));
    return lenn + sqrt(pow(points[back].x - points[front].x, 2) + pow(points[back].y - points[front].y, 2));
}

void opt_2(vector<int>& path, const vector<Point>& points, int n){
    int i, j, k, l;
    double len, newlen;
    int N1 = n - 2, N2 = N1 + 1;
    bool flag = true;
    while (flag){
        len = lenn(path, points);
        flag = false;
        for (i = 1; i < N1; i++){
            for (j = i + 1; j < N2; j++){
                k = i, l = j;
                while (k < l) swap(path[k++], path[l--]);
                newlen = lenn(path, points);
                if (newlen < len){
                    len = newlen; 
                    flag = true;
                }
                else {
                    k = i, l = j;
                    while (k < l) swap(path[k++], path[l--]);
                }
            }
        }
    }
}

void opt_3(vector<int>& path, const vector<Point>& points, int n){
    int i, j, k;
    double len, newlen;
    int N1 = n - 2, N2 = n - 1;
    bool flag = true;
    while (flag){
        len = lenn(path, points);
        flag = false;
        for (i = 1; i < N1; i++){
            for (j = i + 1; j < N2; ++j){
                for (k = j + 1; k < n; k++){
                    reverse(path.begin() + i, path.begin() + j + 1);
                    reverse(path.begin() + j + 1, path.begin() + k + 1);
                    newlen = lenn(path, points);
                    if (newlen < len){
                        len = newlen;
                        flag = true;
                    }
                    else{
                        reverse(path.begin() + i, path.begin() + j + 1);
                        reverse(path.begin() + j + 1, path.begin() + k + 1);
                    }
                }
            }
        }
    }
}


int main(){
    int n;
    cin >> n;
    vector<Point> points(n);
    for (int i = 0; i < n; ++i) cin >> points[i].x >> points[i].y;

    vector<int> path(n + 1);
    for (int i = 0; i < n; ++i) path[i] = i;
    path[n] = 0;
    opt_2(path, points, n + 1);
    //opt_3(path, points, n + 1);

    double l = lenn(path, points);
    cout << l << " 1" << endl;

    for (int i = 0; i < n + 1; ++i) cout << path[i] << " ";
    cout << endl;
    return 0;
}