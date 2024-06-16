class Solution {
public:
     int findMin(vector<int> &num) {
        int start=0,end=num.size()-1;
        
        while (start<end) {
            // increasing range: clear path
            cout << "[" << num[start] << ", " << num[end] << "]" <<  endl;
            if (num[start]<num[end])
                return num[start];
            
            int mid = (start+end)/2;
            cout << "mid: " << num[mid] << endl;
            
            // in the end you will run into 
            // [7,0]
            // or [0, 7]

            // because start >= end and then mid >= start
            // that means mid >= end, the vally is in the right side
            if (num[mid]>=num[start]) {
                start = mid+1;
            } else {
                end = mid;
            }
        }
        
        return num[start];
    }
};