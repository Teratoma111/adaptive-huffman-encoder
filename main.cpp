#include <vector>
#include <queue>
#include <string>
#include <map>
#include <iterator>
#include <functional>
#include <iostream>
#include <stdio.h>
#include <fstream>
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

char bin_2_int(const std::string &str )
{
unsigned int number = 0;
int lshift = 0;
int L = str.size();
for ( int i = L - 1; i >= 0; --i)
{
if ( str[i] == '1' ) number += ( 1 << lshift );
else if ( str[i] != '0')
{
std::cout << "wrong string ";
return 0;
}
++lshift;
}
return number;
}
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
    ~Tree()
    {
        delete root;
    }
    void deleteTree(Node* trueRoot)
    {
        if(trueRoot -> leftCh() != nullptr)
        {
           deleteTree(trueRoot -> leftCh());
        }
        if(trueRoot -> rightCh() != nullptr)
        {
           deleteTree(trueRoot -> rightCh());
        }
         if(trueRoot -> leftCh() == nullptr && trueRoot -> rightCh() == nullptr)
        {
            delete trueRoot;
        }
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
    //std::map <char, unsigned int> freqtable;
    std::map <char, std::string> codetable;
    public:
    HufmanTree(std::string a)
    {
        mes = a;
        hufmantree = new Tree();
      //  temp2 = temp -> rightCh();
        //temp2 =  new Node('\eof', 1);
    }
    ~HufmanTree()
    {
        delete hufmantree;
    }
    HufmanTree()
    {
        mes = "";
        hufmantree = new Tree();
      //  temp2 = temp -> rightCh();
        //temp2 =  new Node('\eof', 1);
    }
    std::string binString()
    {
        std::string bins = "";
        for(size_t i = 0; i < mes.size(); i++)
        {
            bins+=(int_2_bin(mes[i]));
        }
        return bins;
    }
    void putNewWord(std::string word)
    {
        mes+=word;
    }
    std::string decode()
    {
        std::string a;
        for(unsigned int k = 0; k < 8; k++)
        {
            a.push_back(mes[k]);
        }
        char firstsym = bin_2_int(a);
        insertSym(hufmantree -> getRoot(),firstsym);
        res+=firstsym;
        updateTree(&(hufmantree -> root));
        std::string temps = "";
        fillCodeTable(temps, hufmantree -> getRoot());
       for(size_t i = 9; i < mes.size(); i++)
        {
            i--;
            std::string code = "";
            Node* temp = hufmantree -> getRoot();
            while(temp -> rightCh() != nullptr && temp -> leftCh() != nullptr)
            {
                if(mes[i] == '0')
                {
                    temp = temp -> leftCh();
                    i++;
                    code.push_back('0');
                    //continue;
                }
                else
                {
                    temp = temp -> rightCh();
                    i++;
                    code.push_back('1');
                }
            }
            char token = temp -> getSym();
            if(token == '=')
            {
            std::string aS;
            for(unsigned int j = 0; j < 8; j++)
            {
            aS.push_back(mes[i]);
            i++;
            }
            char NewSym = bin_2_int(aS);
            insertSym(hufmantree -> getRoot(),NewSym);
            res += NewSym;
            updateTree(&(hufmantree -> root));
            std::string temps = "";
            fillCodeTable(temps, hufmantree -> getRoot());
            }
            else
            {
                res += token;
                Node* temproot = hufmantree -> getRoot();
                for(size_t p = 0; p < code.size(); p++)
                {
                    temproot -> incFreq();
                    if(code[p] == '0')
                    {
                        temproot = temproot -> leftCh();
                    }
                    if(code[p] == '1')
                    {
                        temproot = temproot -> rightCh();
                    }
                }
                //temproot -> incFreq();
                updateTree(&(hufmantree -> root));
                std::string temp = "";
                fillCodeTable(temp, hufmantree -> getRoot());
            }

        }
        hufmantree -> deleteTree(hufmantree -> getRoot());
        //delete hufmantree;
        return res;
    }
    std::string handleData()
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
                    else
                    {
                        temproot = temproot -> rightCh();
                    }
                }
                //temproot -> incFreq();
                updateTree(&(hufmantree -> root));
                std::string temp = "";
                fillCodeTable(temp, hufmantree -> getRoot());
            }
        }
        hufmantree -> deleteTree(hufmantree -> getRoot());
        //delete hufmantree;
        return res;
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
            fillCodeTable(code + '0', root -> leftCh());
        }
        if(root -> rightCh() != nullptr)
        {
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
    std::string a = "", con = "";
    std::ifstream fin("gamlet.txt"); 
    std::string buff;
    while(fin >> buff)
    {
        a +=buff;
        a +=' ';
    }
    HufmanTree b(a);
    std::string data = b.binString();
    double size1 = data.size();
    //std::cout << b.binString() << std::endl;
    con = b.handleData();
    size1 /= con.size();
    std::cout << size1 << std:: endl;
    //std::cout << con << std::endl;
    HufmanTree decode(con);
    std::cout << decode.decode() << std::endl;
    fin.close();
}