#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>

using namespace std;

//Point - A data structure used to denote the row and column indices of an element in the Plus' formed
// from the 2D array of input, as a coordinate
// for use in collision(/overlap) test with the points formed by the other pluses in consideration.
struct Point {
    int x;
    int y;
};

// Plus - It stores the center coordinates (row and column indices) and the area of a particular plus
struct Plus {

    Plus(int i, int j, int p) : y(i), x(j), area(p) {
    }

    // getLen() - Returns the length of the edge of the Plus from the center
    // Length of the edge is the number of cells/steps that we can travel  without
    // encountering a Bad cell or bounds of the 2D array in
    // all 4 directions(Left , Right, Top, Bottom) safely from the center of the plus.
    int getLen() {
        return (area - 1) / 4;
    }

    //bool doesOverlap(Plus p)-Given another Plus object as an argument,the function that returns whether
    //there is a intersection of any of the Points of 'this' Plus with the given Plus.
    //Returns true when there is an intersection found , otherwise false.
    bool doesOverlap(Plus p) {
        int len = getLen();
        int len2 = p.getLen();
        // Construct the horizontal and vertical end points of the given Plus and 'this' Plus
        // from their respective centers.
        // These points form the line segments which we will use for collision test.
        Point p1 = {x - len, y}, q1 = {x + len, y}, p2 = {p.x - len2, p.y}, q2 = {p.x + len2, p.y},
                p3 = {x, y - len}, q3 = {x, y + len}, p4 = {p.x, p.y - len2}, q4 = {p.x, p.y + len2};

        // Perform collision test between all the line segments
        // If any collision found between any two line segments combinations taken
        // from both the pluses, return true.
        //Possible combinations are:
        // horizontal line of the other plus with horizontal line of 'this' plus
        // horizontal line of the other plus with vertical line of 'this' plus
        // vertical line of the other plus with vertical line of 'this' plus
        // vertical line of the other plus with horizontal line of 'this' plus
        return doIntersect(p1, q1, p2, q2) || doIntersect(p3, q3, p4, q4) ||
               doIntersect(p1, q1, p4, q4) || doIntersect(p3, q3, p2, q2);
    }

    // Given three colinear points p, q, r, the function checks if
    // point q lies on line segment 'pr'
    bool onSegment(Point p, Point q, Point r) {
        return q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
               q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y);

    }

    // To find orientation of ordered triplet (p, q, r).
    // The function returns following values
    // 0 --> p, q and r are colinear
    // 1 --> Clockwise
    // 2 --> Counterclockwise
    int orientation(Point p, Point q, Point r) {
        int val = (q.y - p.y) * (r.x - q.x) -
                  (q.x - p.x) * (r.y - q.y);

        if (val == 0) return 0;  // colinear

        return (val > 0) ? 1 : 2; // clock or counterclock wise
    }

    // The main function that returns true if line segment 'p1q1'
    // and 'p2q2' intersect.
    bool doIntersect(Point p1, Point q1, Point p2, Point q2) {
        //find out if the point p2 oriented ClockWise/CCW/colinear to the line segment p1q1
        int o1 = orientation(p1, q1, p2);
        //find out if the point q2 oriented ClockWise/CCW/colinear to the line segment p1q1
        int o2 = orientation(p1, q1, q2);
        //find out if the point p1 oriented ClockWise/CCW/colinear to the line segment p2q2
        int o3 = orientation(p2, q2, p1);
        //find out if the point q1 oriented ClockWise/CCW/colinear to the line segment p2q2
        int o4 = orientation(p2, q2, q1);

        if (o1 != o2 && o3 != o4)
            return true;

        // p1, q1 and p2 are colinear and p2 lies on segment p1q1
        if (o1 == 0 && onSegment(p1, p2, q1)) return true;

        // p1, q1 and p2 are colinear and q2 lies on segment p1q1
        if (o2 == 0 && onSegment(p1, q2, q1)) return true;

        // p2, q2 and p1 are colinear and p1 lies on segment p2q2
        if (o3 == 0 && onSegment(p2, p1, q2)) return true;

        // p2, q2 and q1 are colinear and q1 lies on segment p2q2
        if (o4 == 0 && onSegment(p2, q1, q2)) return true;

        return false; // Doesn't fall in any of the above cases
    }

    int x, y;
    int area;
};

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
        // Get the strings that contain the contents of this 2D grid
        for (int i = 0; i < R; i++) {
            cin >> str[i];
        }
    }

    int getProdofPlus() {

        vector<Plus> pluses;
        //for each cell find the possible Pluses
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                int plus = givePlus(i, j);
                if (plus) {
                    Plus p(i, j, plus);
                    pluses.push_back(p);// If plus found push it to the vector of pluses
                }
            }
        }
        int maxprod = 1;//By default , set the maxprod to 1, with the assumption that
        // there will be at least one plus
        //From all the pluses found, find the maximum prod of the areas of the top two valid pluses
        for (int i = 0; i < pluses.size() - 1; i++) {
            for (int j = i + 1; j < pluses.size(); j++) {
                if (pluses[i].doesOverlap(pluses[j])) {// check if there is a overlap with another plus
                    // if overlap is found the maxium prod is the maximum between the current maxprod and
                    //  maximum area of the two pluses in question.
                    maxprod = max(maxprod, max(pluses[i].area, pluses[j].area));
                } else {
                    // if there no collison the maxium prod is the maximum between the current maxprod and
                    // the product of the two valid pluses.
                    maxprod = max(maxprod, pluses[i].area * pluses[j].area);
                }
            }
        }
        //Return the max prod.
        return maxprod;
    }

private:
    //canMoveLeft - returns true as long as there is a valid cell to the left side of the given coordinate
    bool canMoveLeft(int i, int j) {
        return (j - 1) >= 0 && str[i][j - 1] != 'B';
    }

    //canMoveRight - returns true as long as there is a valid cell to the right side of the given coordinate
    bool canMoveRight(int i, int j) {
        return (j + 1) < C && str[i][j + 1] != 'B';;
    }


    //canMoveUp - returns true as long as there is a valid cell to the up side of the given coordinate
    bool canMoveUp(int i, int j) {
        return (i - 1) >= 0 && str[i - 1][j] != 'B';
    }

    //canMoveDown - returns true as long as there is a valid cell to the down side of the given coordinate
    bool canMoveDown(int i, int j) {
        return (i + 1) < R && str[i + 1][j] != 'B';
    }

    //getLeftLen - returns the safest number of steps we can take towards the left direction of the given cell
    // before hitting the bounds of the array or a bad cell
    int getLeftLen(int i, int j) {
        int left = 0;
        while (canMoveLeft(i, j)) {
            j--;
            left++;
        }
        return left;
    }

    //getRightLen - returns the safest number of steps we can take towards the right direction of the given cell
    // before hitting the bounds of the array or a bad cell
    int getRightLen(int i, int j) {
        int right = 0;
        while (canMoveRight(i, j)) {
            j++;
            right++;
        }
        return right;
    }

    //getTopLen - returns the safest number of steps we can take towards the top direction of the given cell
    // before hitting the bounds of the array or a bad cell
    int getTopLen(int i, int j) {
        int top = 0;
        while (canMoveUp(i, j)) {
            top++;
            i--;
        }
        return top;
    }

    //getDownLen - returns the safest number of steps we can take towards the down direction of the given cell
    // before hitting the bounds of the array or a bad cell
    int getDownLen(int i, int j) {
        int bot = 0;
        while (canMoveDown(i, j)) {
            bot++;
            i++;
        }
        return bot;
    }

    //returns the area of the plus that can be formed at the give cell(i,j)
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
    while (cin >> R >> C) {
        Solution s(R, C);
        s.processInput();
        cout << s.getProdofPlus() << endl;
    }
    return 0;
}