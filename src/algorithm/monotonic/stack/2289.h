class Solution {
public:
    int totalSteps(vector<int>& nums) 
    {
        int n=nums.size(),i,ans=0,cnt,prev;
        stack <pair<int,int>> st;
        st.push({nums[n-1],0});
        for(i=n-2;i>=0;i--)
        {
            cnt=0;
            //given:   In one step, remove all elements nums[i] where nums[i - 1] > nums[i]

            // 5,3,4,4: three steps
            // 7,3,6,: 2 steps
            // 11,8,5: 1 step 
            while(!st.empty() && nums[i]>st.top().first)
            {
                cnt=max(cnt+1,st.top().second);
                cout << "pop: " << st.top().first << ", cnt: " << st.top().second  << endl;

                st.pop();
            }
            ans=max(ans,cnt);
            st.push({nums[i],cnt});

            cout << "push: " << nums[i] << ", cnt: " << cnt << endl;
        }
        return ans;
    }
};