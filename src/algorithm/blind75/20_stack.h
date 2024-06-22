class Solution
{
public:
    bool isValid(string s)
    {
        stack<char> stk;
        unordered_map<char, char> lk = {{')', '('}, {']', '['}, {'}', '{'}};
        for (const auto &c : s)
        {
            if (c == '(' || c == '[' || c == '{')
            {
                stk.push(c);
            }
            else if (c == ')' || c == ']' || c == '}')
            {
                if (stk.empty())
                {
                    return false;
                }

                if (stk.top() != lk[c])
                {
                    return false;
                }

                stk.pop();
            }
            else
            {
                continue;
            }
        }
        return stk.empty();
    }
};