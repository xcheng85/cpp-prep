#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

using Greyscale = float;

float FindMedian(vector<float> &in)
{
    assert(in.size() % 2 == 1);
    sort(in.begin(), in.end());
    return in.at(in.size() / 2);
}

template <int KERNAL_SIZE>
void kernel(const vector<vector<Greyscale>> &in, vector<vector<Greyscale>> &out, int i, int j)
{
    vector<float> allGs(KERNAL_SIZE * KERNAL_SIZE);

    int offset = KERNAL_SIZE / 2;

    int index = 0;
    for (int r = i - offset; r <= i + offset; r++)
    {
        for (int c = j - offset; c <= j + offset; c++)
        {
            allGs[index] = in[r][c];
            index++;
        }
    }

    float medianG;
    medianG = FindMedian(allGs);

    for (int r = i - offset; r <= i + offset; r++)
    {
        for (int c = j - offset; c <= j + offset; c++)
        {
            out[r][c] = medianG;
        }
    }
}


vector<vector<Greyscale>> applyMedianFilter3x3(const vector<vector<Greyscale>> &image)
{
    assert(image.size() > 0);
    assert(image.size() % 3 == 0);
    assert(image[0].size() % 3 == 0);

    vector<vector<Greyscale>> out(image.size(), vector<Greyscale>(image[0].size()));

    for (int r = 1; r < image.size(); r += 3)
    {
        for (int c = 1; c < image[0].size(); c += 3)
        {
            std::cout << "running kernel: " << r << "," << c << std::endl;
            kernel<3>(image, out, r, c);
        }
    }

    return out;
}

int main()
{
    auto res = applyMedianFilter3x3({{1, 4, 7, 1, 4, 7}, {8, 9, 5, 8, 9, 5}, {2, 3, 6, 2, 3, 6}, {1, 4, 7, 1, 4, 7}, {8, 9, 5, 8, 9, 5}, {2, 3, 6, 2, 3, 6}});

    for (int i = 0; i < res.size(); i++)
    {
        for (int j = 0; j < res[0].size(); j++)
        {
            std::cout << res[i][j] << std::endl;
        }
    }

    return 0;
}