#include <vector>
#include <queue>
#include <string>
#include <map>
#include <iterator>
#include <functional>
#include <iostream>
class Node
{
    private:
    friend class Tree;
    friend class HufmanTree;
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
    void swapChildren()
    {
        Node* temp = this -> right;
        this -> right = this -> left;
        this -> left = temp;
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
    void newNode(Node* child)
    {
        if(this -> left != nullptr)
        {
        Node* temp = this -> left;
        this -> left = new Node('-', temp -> getFreq() + 1);
        this -> left -> left = temp;
        this -> left -> right = child;
        }
        else
        {
        this -> left = new Node('=',0);
        this -> right = child;
        this -> sym = '-';
        this -> frequence = 1;
        }
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
    void incFreq()
    {
        frequence++;
    }
};

std::string int_2_bin( const char &n )
{
std::string bin_str = "";
int L = 8*sizeof(n);

for (int r = L - 1; r >= 0;--r)
{
if ( ( n & ( 1 << r ) ) >> r ) 
bin_str += '1';
else 
bin_str += '0';
}
return bin_str;
}

class Tree
{
    private:
    Node* root;
    friend class HufmanTree;
    public:
    Tree ()
    {
        root = new Node('=', 0);
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
    std::string res;
    Tree* hufmantree;
    std::map <char, unsigned int> freqtable;
    std::map <char, std::string> codetable;
    public:
    HufmanTree(std::string a)
    {
        mes = a;
        hufmantree = new Tree();
      //  temp2 = temp -> rightCh();
        //temp2 =  new Node('\eof', 1);
    }

    void handleData()
    {
        for(size_t i = 0; i < mes.size(); i++)
        {
            char token = mes[i];
            if(codetable[token] == "")
            {
                if(i != 0)
                res += codetable['='];
                unsigned int sym = token;
                res += int_2_bin(sym);
                insertSym(hufmantree -> getRoot(), token);
                updateTree(&(hufmantree -> root));
                std::string temp = "";
                fillCodeTable(temp, hufmantree -> getRoot());
            }
            else
            {
                std::string code = codetable[token];
                res += codetable[token];
                Node* temproot = hufmantree -> getRoot();
                for(size_t i = 0; i < code.size(); i++)
                {
                    temproot -> incFreq();
                    if(code[i] == '0')
                    {
                        temproot = temproot -> leftCh();
                    }
                    if(code[i] == '1')
                    {
                        temproot = temproot -> rightCh();
                    }
                }
                temproot -> incFreq();
                updateTree(&(hufmantree -> root));
                std::string temp = "";
                fillCodeTable(temp, hufmantree -> getRoot());
            }
            int a = 2*2;
        }
        std::cout << res;
    }
    void updateTree(Node** root)
    {
        if((*root) -> leftCh() != nullptr)
        {
            updateTree(&((*root)-> left));
        }

        if((*root) -> rightCh() != nullptr)
        {
            updateTree(&((*root)-> right));
        }

        if((*root) -> leftCh() != nullptr && (*root) -> rightCh() != nullptr)
        {
            if((*root) -> leftCh() -> getFreq() > (*root) -> rightCh() -> getFreq())
            {
                (*root) -> swapChildren();
            }
        }
    }

    void insertSym(Node* root, char token)
    {
        while(root -> leftCh() != nullptr && root -> leftCh() -> getFreq() > 1)
        {
            root -> incFreq();
            root = root -> leftCh();
        }
        root -> incFreq();
        Node* temp = new Node(token, 1);
        root -> newNode(temp);
    }

       void fillCodeTable(std::string code, Node* root)
    {
        if(root -> leftCh() != nullptr)
        {
           // code.push_back('0');
            fillCodeTable(code + '0', root -> leftCh());
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
    std::string a = "aardvark";
    HufmanTree b(a);
    b.handleData();
    int c = 2*2;
}