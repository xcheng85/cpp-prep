struct Node
{
    map<int, Node *> nodes;
    bool leaf{false};
};

class Trie
{
public:
    Trie() { _root = new Node(); }

    void insert(string word)
    {
        Node *curr = _root;
        for (const auto &c : word)
        {
            // does not exist
            if (!curr->nodes.count(c - 'a'))
            {
                Node *tmp = new Node();
                curr->nodes[c - 'a'] = tmp;
            }
            curr = curr->nodes[c - 'a'];
        }
        curr->leaf = true;
    }

    bool search(string word)
    {
        Node *curr = _root;
        for (const auto &c : word)
        {
            if (!curr->nodes.count(c - 'a'))
            {
                return false;
            }
            curr = curr->nodes[c - 'a'];
        }
        return curr->leaf;
    }

    bool startsWith(string prefix)
    {
        Node *curr = _root;
        for (const auto &c : prefix)
        {
            if (!curr->nodes.count(c - 'a'))
            {
                return false;
            }
            curr = curr->nodes[c - 'a'];
        }
        return true;
    }

private:
    Node *_root;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */