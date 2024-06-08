/* The knows API is defined for you.
      bool knows(int a, int b); */

class Solution {
public:
    int findCelebrity(int n) {
        // id: 0, n-1
        // cannot use indegree, outdegree, the adj list is not constructable

        // random select a starting point
        int candidate = 0;
        for (int i = 0; i < n; ++i) {
            // condition for candidate is celebiry
            // knows(i, candidate) && !knows(candidate, i)
            if (!(knows(i, candidate) && !knows(candidate, i))) {
                // candidate is not celebrity
                candidate = i;
            }
        }

        for (int i = 0; i < n; ++i) {
            // know(i, i) = 1
            if (candidate == i)
                continue;
            if (!knows(i, candidate) || knows(candidate, i)) {
                return -1;
            }
        }
        return candidate;
    }
};