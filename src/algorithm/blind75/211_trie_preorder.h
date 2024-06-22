struct TrieNode {
    bool isLeaf{false};
    unordered_map<int, TrieNode*> nodes;
};

class WordDictionary {
public:
    WordDictionary() {
        
    }
    
    void addWord(string word) {
        TrieNode* curr = &_root;
        for(const auto& c : word) {
            int offset = c - 'a';
            if(!curr->nodes.count(offset)) {
                TrieNode* tmp = new TrieNode;
                _memoryPool.push_back(tmp);
                curr->nodes[offset] = tmp;
            }
            curr = curr->nodes[offset];
        }
        curr->isLeaf = true;
    }
    
    bool search(string word) {
        TrieNode* curr = &_root;
        return preOrder(curr, word, 0);
    }

private: 
    bool preOrder(TrieNode* curr, string word, int charIndex) {
        // key is here, ==
        if(charIndex == word.size() ) {
             auto c = word[charIndex];
             if(c == '.' ) {
                return true;
             } else {
                return curr->isLeaf;
             }
        }

        auto c = word[charIndex];
        if(c == '.' ){
            for(const auto&[k, node] : curr->nodes) {
               bool isFound = preOrder(node, word, charIndex + 1);
               if(isFound) {
                    return true;
               }
            }
            return false;
        } else {
            int offset = c - 'a';
            if(!curr->nodes.count(offset)) {
                return false;
            }
            return preOrder(curr->nodes[offset], word, charIndex + 1);
        }
    }


    TrieNode _root;
    vector<TrieNode*> _memoryPool;
    bool _found {false};
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */