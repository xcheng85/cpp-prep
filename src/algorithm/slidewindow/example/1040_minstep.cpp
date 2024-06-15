class Solution {
public:
    vector<int> numMovesStonesII(vector<int>& stones) {
        int n = stones.size();
        vector<int> result;
        
		// sorting the stones array
        sort(stones.begin(), stones.end());
        
		// window size, stones count in a window
        int i = 0, j = 0, wsize, scount, minMoves = INT_MAX;
        
        while (j < n) {

            wsize = stones[j] - stones[i] + 1;
            scount = j - i + 1;
            cout << "window: [" << stones[i]<< "," << stones[j] << "]" << endl;
            cout << "window size: " << wsize << endl;
            cout << "stone count: " << scount << endl;
            
			// if window size becomes greater than number of stones
            if (wsize > n) {
                cout << "move left" << endl;
                i++;
                continue;
            }
            
			/* To handle some corner cases
			   Example - _ _ 3 4 5 6 _ _ 10
			   Here, putting, stone at 10th position, next to stone at 6th position is an invalid move.
			*/
            if (wsize == n - 1 && scount == n - 1){
                cout << "edge case " << endl;
                minMoves = min(minMoves, 2);
                cout << "update minimum move: " << minMoves << endl;
            }
            else {
                cout << "no edge case " << endl;
                cout << "update minimum move: " << n - scount << endl;
                minMoves = min(minMoves, n - scount);
            }                
            j++;
        }
        
        result.push_back(minMoves);
        
        int maxMoves;
		
		// consecutive stones at the beginning or consecutive stones at the end or both
        if (stones[1] == stones[0] + 1 || stones[n - 1] == stones[n - 2] + 1)
            maxMoves = stones[n - 1] - stones[0] + 1 - n;
        
		// non-consecutive stones at both the beginning and the end
        else 
            maxMoves = max(((stones[n - 1] - stones[1]) - (n - 1) + 1), ((stones[n - 2] - stones[0]) - (n - 1) + 1));
        
        result.push_back(maxMoves);
        
        return result;
    }
};