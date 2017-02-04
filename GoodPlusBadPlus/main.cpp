#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>

using namespace std;

struct Plus {
    Plus(int i, int j, int p) : y(i), x(j), area(p) {

    }

    int getLen() {
        return (area - 1) / 4;
    }

    unsigned long long square(unsigned long long a) {
        return a * a;
    }

    bool doesOverlap(Plus p) {
        int len = getLen();
        int len2 = p.getLen();
        int distx = abs(x - p.x);
        int disty = abs(y - p.y);
        //return square(distx) + square(disty) < square(len + len2);
        return (distx<(len+len2)) && (disty<(len+len2));
    }

    int x, y;
    int area;
};

bool cmp(Plus p1, Plus p2) {
    return p1.area < p2.area;
}

bool eq(Plus p1, Plus p2) {
    return (p1.area == p2.area);
}

class Solution {
private:
    int R, C;
    string *str;
public:
    Solution(int R, int C) : R(R), C(C) {
        str = new string[R];
    }


    ~Solution() {
        delete[]str;
    }

    void processInput() {
        for (int i = 0; i < R; i++) {
            cin >> str[i];
        }

        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++)
                cout << str[i][j] << " ";
            cout << endl;

        }

    }

    int getProdofPlus() {


        vector<Plus> pluses;

        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                int plus = givePlus(i, j);
                if (plus) {
                    Plus p(i, j, plus);
                    pluses.push_back(p);
                    //cout<<"("<<i<<","<<j<<")->"<<str[i][j]<<"->"<<plus<<endl;
                }
                cout << plus << " ";
            }
            cout << endl;
        }
        int maxprod = 1;
        for (int i = 0; i < pluses.size() - 1; i++) {
            for (int j = i + 1; j < pluses.size(); j++) {
                if (pluses[i].doesOverlap(pluses[j])) {
                    maxprod = max(maxprod, max(pluses[i].area, pluses[j].area));
                } else {
                    maxprod = max(maxprod, pluses[i].area * pluses[j].area);
                }
            }
        }

        return maxprod;
    }

private:
    bool canMoveLeft(int i, int j) {
        return (j - 1) >= 0 && str[i][j - 1] != 'B';
    }

    bool canMoveRight(int i, int j) {
        return (j + 1) < C && str[i][j + 1] != 'B';;
    }


    bool canMoveUp(int i, int j) {
        return (i - 1) >= 0 && str[i - 1][j] != 'B';
    }

    bool canMoveDown(int i, int j) {
        return (i + 1) < R && str[i + 1][j] != 'B';
    }

    int getLeftLen(int i, int j) {
        int left = 0;
        while (canMoveLeft(i, j)) {
            j--;
            left++;
        }
        return left;
    }

    int getRightLen(int i, int j) {
        int right = 0;
        while (canMoveRight(i, j)) {
            j++;
            right++;
        }
        return right;
    }

    int getTopLen(int i, int j) {
        int top = 0;
        while (canMoveUp(i, j)) {
            top++;
            i--;
        }
        return top;
    }

    int getDownLen(int i, int j) {
        int bot = 0;
        while (canMoveDown(i, j)) {
            bot++;
            i++;
        }
        return bot;
    }

    int givePlus(int i, int j) {
        if (str[i][j] == 'B') return 0;
        int len = 0;
        int topLen = getTopLen(i, j), botLen = getDownLen(i, j), rightLen = getRightLen(i, j),
                leftLen = getLeftLen(i, j);
        if (topLen > 0 && botLen > 0 && rightLen > 0 && leftLen > 0) {
            len = 1 + 4 * min(topLen, min(botLen, min(rightLen, leftLen)));
        } else {
            len = 1;
        }
        return len;
    }
};


int main() {
    int R, C;
    cin >> R >> C;

    Solution s(R, C);
    s.processInput();
    cout << s.getProdofPlus();
    return 0;
}