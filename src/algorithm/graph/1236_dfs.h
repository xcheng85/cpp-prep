#include <vector>
#include <string>
#include <unordered_set>

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
    // startUrl: start node
    vector<string> crawl(string startUrl, HtmlParser htmlParser)
    {
        string startHostname = getHostname(startUrl);

        // graph could have cycle
        unordered_set<string> visited;
        dfs(htmlParser, startUrl, startHostname, visited);
        return vector<string>(visited.begin(), visited.end());
    }

private:
    // care about the node, not the path-->dfs
    void dfs(HtmlParser& htmlParser, string curr, string targetHostName, unordered_set<string> &visited)
    {
        visited.insert(curr);
        for (const string& neighbor : htmlParser.getUrls(curr))
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