#include <vector>
#include <queue>
#include <string>
#include <map>
#include <iterator>
#include <functional>
class Node
{
    private:
    unsigned int frequence;
    char sym;
    Node* right;
    Node* left;
    public:
    Node (char sym, int frequence)
    {
        this -> frequence = frequence;
        this -> sym = sym; 
        right = nullptr;
        left = nullptr;
    }
    Node ()
    {
        frequence = 0;
        sym = '-';
        right = nullptr;
        left = nullptr;
    }
    void newChild(Node* child)
    {
        if(this -> left == nullptr )
            left = child;
        else
        {
            if( left -> frequence < child -> frequence)
                right = child;
                else
                {
                    right = left;
                    left = child;     
                }
        }
        frequence += child -> frequence;    
    }
    unsigned int getFreq ()
    {
        return frequence;
    }
    Node* rightCh()
    {
        return right;
    }
    Node* leftCh()
    {
        return left;
    }
    char getSym()
    {
        return sym;
    }
};

class Tree
{
    private:
    Node* root;
    public:
    Tree ()
    {
        root = new Node();
    }
    Tree (Node* root)
    {
        this -> root = root;
    }
    unsigned int getFreq() const
    {
        return root -> getFreq();
    }
    Node* getRoot() 
    {
        return root;
    }
};
bool Compare(Tree* t1, Tree* t2)
{
    return (t1 -> getFreq() > t2 -> getFreq());
}

class HufmanTree
{
    private:
    std::string mes;
    Tree hufmantree;
    std::map <char, unsigned int> freqtable;
    std::map <char, std::string> codetable;
    public:
    HufmanTree(std::string encoding)
    {
        this -> mes = encoding;
        fillFreqTable();
        createHuffman();
        std::string temp = "";
        fillCodeTable(temp, hufmantree.getRoot());
        int a =2+2;
    } 
    void fillFreqTable()
    {
        for(size_t i = 0; i < mes.size(); i++)
        {
            freqtable[mes[i]]++;
        }
    }
    Tree createHuffman()
    {
        //std:EEE:priority_queue<Tree*> pq;
        std::priority_queue<Tree*, std::vector<Tree*>, std::function<bool(Tree*, Tree*)>> pq(Compare);
        std::map <char, unsigned int>::iterator it;
        for(it = freqtable.begin(); it != freqtable.end();++it)
        {
            char b = it -> first;

            Node* temp = new Node(it -> first, it -> second);
            Tree* obj = new Tree(temp);
           pq.emplace(obj);
        }
        while(pq.size() > 1)
        {
            Tree* temp1 = pq.top();
            pq.pop();
            Tree* temp2 = pq.top();
            pq.pop();
            Tree* res = new Tree();
            (res -> getRoot()) -> newChild(temp1 -> getRoot());
            (res -> getRoot()) -> newChild(temp2 -> getRoot());
          //  delete temp1;
           // delete temp2;
            //(*(temp2 -> getRoot())).newChild(temp1 -> getRoot());
           // pq.push(res);
            pq.emplace(res);
        }
        hufmantree = *(pq.top());
    }

    void fillCodeTable(std::string code, Node* root)
    {
        if(root -> leftCh() != nullptr)
        {
           // code.push_back('0');
            fillCodeTable(code+'0', root -> leftCh());
        }
        if(root -> rightCh() != nullptr)
        {
           // code.push_back('1');
            fillCodeTable(code + '1', root -> rightCh());
        }
         if(root -> leftCh() == nullptr && root -> rightCh() == nullptr)
        {
            codetable[root -> getSym()] = code;
        }
    }
};

int main()
{
    HufmanTree a("beep boop beer!");
    a.createHuffman();
}