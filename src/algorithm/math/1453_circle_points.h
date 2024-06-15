#include <vector>
#include <math.hpp>
#include <numeric>
#include <algorithm>

using namespace std;

// numeric: epsilon

// Maximum points that can be enclosed in a circle of given radius
// https://www.geeksforgeeks.org/angular-sweep-maximum-points-can-enclosed-circle-given-radius/?ref=lbp

// 1. brutal force

// 2. angle sweep

struct Circle
{
    float c;
    float r;
};

struct Vector2f
{
    float x;
    float y;
    Vector2f(float x, float y) : x(x), y(y)
    {
    }

    float length() const
    {
        return sqrt(x * x + y * y);
    }
};

Vector2f normalize(const Vector2f &v)
{
    const auto length = v.length();
    return Vector2f(v.x / length, v.y / length);
}

Vector2f operator*(const Vector2f &v1, const float &s)
{
    return Vector2f(v1.x * s, v1.y * s);
}

Vector2f operator+(const Vector2f &v1, const Vector2f &v2)
{
    return Vector2f(v1.x + v2.x, v1.y + v2.y);
}

Vector2f operator-(const Vector2f &v1, const Vector2f &v2)
{
    return Vector2f(v1.x - v2.x, v1.y - v2.y);
}

class Solution
{
public:
    int numPoints(vector<vector<int>> &pts, int radius)
    {
        //1 <= r <= 5000
        // at least itself
        int maxPtsIncluded = 1;
        // step1. construct circle from pair of points, radius
        for (int i = 0; i < pts.size(); ++i)
        {
            for (int j = i + 1; j < pts.size(); ++j)
            {
                const auto v1 = pts[i], v2 = pts[j];
                Vector2f e12(v2[0] - v1[0], v2[1] - v1[1]);
                float e12HalfLength = e12.length() * 0.5;

                Vector2f e12Center((v1[0] + v2[0]) / 2, (v1[1] + v2[1]) / 2);

                // normal // two circles
                Vector2f normal1 = normalize(Vector2f(e12.y, -e12.x));
                Vector2f normal2 = normalize(Vector2f(-e12.y, e12.x));
                // key edge case
                float l2 = radius * radius - e12HalfLength * e12HalfLength;
                if(l2 < 0) {
                    continue;
                }

                float l = sqrt(l2);
                //cout << l << endl;

                Vector2f center1 = e12Center + normal1 * l;
                Vector2f center2 = e12Center + normal2 * l;

                // distance <= radias
                int count = 0;
                for (const auto &p : pts)
                {
                    auto x = p[0], y = p[1];
                    auto dist2 = (x - center1.x) * (x - center1.x) + (y - center1.y) * (y - center1.y);
                    cout << dist2 - radius * radius << endl;
                    auto eps =  std::numeric_limits<int>::epsilon();
                    if (dist2 <= radius * radius +0.1)
                    {
                        ++count;
                    } 
                }
                maxPtsIncluded = std::max({count, maxPtsIncluded});

                count = 0;
                for (const auto &p : pts)
                {
                    auto x = p[0], y = p[1];
                    auto dist2 = (x - center2.x) * (x - center2.x) + (y - center2.y) * (y - center2.y);
                     auto eps =  std::numeric_limits<int>::epsilon();
                     cout << dist2 - radius * radius << endl;
                    if (dist2 <= radius * radius+0.1)
                    {
                        ++count;
                    }
                }
                maxPtsIncluded = std::max({count, maxPtsIncluded});
            }
        }
        return maxPtsIncluded;
    }
};