#include <vector>
#include <string>
#include <unordered_set>
#include <queue>

using namespace std;

// no need to build the adjList, give
class HtmlParser
{
public:
    vector<string> getUrls(string url);
};

class Solution
{
public:

// m be the number of edges in the graph, and l be the maximum length of a URL
// Time complexity: O(m⋅l)

    // startUrl: start node
    vector<string> crawl(string startUrl, HtmlParser htmlParser)
    {
        string startHostname = getHostname(startUrl);

        // graph could have cycle
        queue<string> q;
        q.push(startUrl);
        unordered_set<string> visited{startUrl};
        string startHostname = getHostname(startUrl);

        // space complexity: queue: n nodes * l (url lengh)

        // O(m*n)
        // O(m)
        while (!q.empty())
        {
            string url = q.front();
            q.pop();
            // O(n)
            for (const auto& neighbor : htmlParser.getUrls(url))
            {
                if (getHostname(neighbor) == startHostname && !visited.count(nextUrl))
                {
                    q.push(nextUrl);
                    visited.insert(nextUrl);
                }
            }
        }
        return vector<string>(visited.begin(), visited.end());
    }

private:
    // care about the node, not the path-->dfs
    void dfs(HtmlParser &htmlParser, string curr, string targetHostName, unordered_set<string> &visited)
    {
        visited.insert(curr);
        for (const string &neighbor : htmlParser.getUrls(curr))
        {
            if (getHostname(neighbor) == targetHostName && !visited.count(neighbor))
            {
                dfs(htmlParser, neighbor, targetHostName, visited);
            }
        }
    }

    string getHostname(const string &url)
    {
        // after position 7
        // http://news.google.com
        // http://
        // example.org/foo/bar
        int pos = min(url.size(), url.find('/', 7));
        // return the substring that starts after "http://" and ends
        // before the next slash of at the end of the string
        return url.substr(7, pos - 7);
    };
};