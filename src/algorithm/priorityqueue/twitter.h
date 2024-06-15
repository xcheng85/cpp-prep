#pragma once
#include <vector>
#include <set>
#include <unordered_map>
#include <queue>

// OOD
using namespace std;

class Twitter
{
public:
    static int s_timestamp;

    void postTweet(int userId, int tweetId)
    {
        if (_userMap.find(userId) == _userMap.end())
        {
            // std::pair
            _userMap.insert({userId, User(userId)});
        }
        // non const operator[]
        User &u = _userMap[userId];
        u.post(tweetId);
    }

    // 返回该 user 关注的人（包括他自己）最近的动态 id，
    // 最多 10 条，而且这些动态必须按从新到旧的时间线顺序排列
    vector<int> getNewsFeed(int userId)
    {
        // merge k lists alogrithm
        // min-heap

        vector<int> res;
        if (!_userMap.count(userId))
            return res;

        // 关注列表的用户 Id
        set<int> &users = _userMap[userId]._followed;

        // 自动通过 time 属性从大到小排序，容量为 users 的大小
        // default is max ? std::less<Tweet *>
        priority_queue<Tweet *, vector<Tweet *>> pq;

        // 先将所有链表头节点插入优先级队列
        for (auto id : users)
        {
            Tweet *twt = _userMap[id]._head;
            if (twt == nullptr)
                continue;
            pq.push(twt);
        }

        while (!pq.empty())
        {
            // 最多返回 10 条就够了
            if (res.size() == 10)
                break;
            // 弹出 time 值最大的（最近发表的）
            Tweet *twt = pq.top();
            pq.pop();
            res.push_back(twt->_id);
            // 将下一篇 Tweet 插入进行排序
            if (twt->_next != nullptr)
                pq.push(twt->_next);
        }
        return res;
    }

    // follower 关注 followee，如果 Id 不存在则新建
    void follow(int followerId, int followeeId)
    {
        // create followerId
        if (_userMap.find(followerId) == _userMap.end())
        {
            _userMap.insert({followerId, User(followerId)});
        }
        if (_userMap.find(followeeId) == _userMap.end())
        {
            _userMap.insert({followeeId, User(followeeId)});
        }
        _userMap[followerId].follow(followeeId);
    }

    // follower 取关 followee，如果 Id 不存在则什么都不做
    void unfollow(int followerId, int followeeId)
    {
        if (_userMap.find(followerId) != _userMap.end())
        {
            _userMap[followerId].unfollow(followeeId);
        }
    }

private:
    class User;
    unordered_map<int, User> _userMap;

    class Tweet
    {
    public:
        Tweet() = delete;
        explicit Tweet(int id, int timestamp)
            : _id{id},
              _timestamp{timestamp}
        {
        }

        bool operator<(const Tweet *t2) const {
            return this->_timestamp < t2->_timestamp;
        };

        friend class Twitter;
        friend class User;

    private:
        int _id;
        int _timestamp;
        Tweet *_next{nullptr};
    };

    class User
    {
    public:
        User() = delete;
        explicit User(int uid)
            : _uid{uid}
        {
            follow(uid);
        }

        void follow(int uid)
        {
            _followed.insert(uid);
        }

        void unfollow(int uid)
        {
            // 不可以取关自己
            if (uid != this->_uid)
                _followed.erase(uid);
        }

        void post(int tweetId)
        {
            Tweet *twt = new Tweet(tweetId, s_timestamp++);
            // 将新建的推文插入链表头
            // 越靠前的推文 time 值越大
            twt->_next = _head;
            _head = twt;
        }

        friend class Twitter;

    private:
        int _uid;
        set<int> _followed;
        Tweet *_head;
    };
};