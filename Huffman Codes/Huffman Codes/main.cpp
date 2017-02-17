#include<iostream>
#include <string>
using namespace std;
#define MaxNum 64

struct TreeNode//树的结点
{
    int Weight=0;
    TreeNode *Left=nullptr;
    TreeNode *Right=nullptr;
};

struct HeapNode//堆
{
    TreeNode Data[MaxNum];
    int Size=0;
};

HeapNode *CreateHeap(int N)//创建一个新的小根堆
{
    HeapNode *H=new(HeapNode);
    H->Data[0].Weight=-1;
    return H;
}

TreeNode *DeleteMin(HeapNode *H)//从堆中删除一个结点
{
    int Parent=0,Child=0;
    TreeNode temp;
    TreeNode *MinItem=new(TreeNode);
    *MinItem=H->Data[1];
    
    temp=(H->Data[(H->Size)--]);
    
    for (Parent = 1; Parent*2 <= H->Size ; Parent=Child)//寻找删除结点前堆中最后一个结点在新堆中的插入位置
    {
        Child=Parent*2;
        if ((Child!=H->Size)&&((H->Data[Child].Weight)>(H->Data[Child+1].Weight)))
        {
            Child++;
        }
        if ((temp.Weight)<=(H->Data[Child].Weight))
        {
            break;
        }else
        {
            H->Data[Parent]=H->Data[Child];
        }
        
    }
    H->Data[Parent]=temp;
    return MinItem;
    
}

void Insert(HeapNode *H,TreeNode *item)//插入新结点到堆中
{
    int i=0;
    i=++(H->Size);
    for (;H->Data[i/2].Weight>item->Weight; i/=2)
    {
        H->Data[i]=H->Data[i/2];
        
    }
    H->Data[i]=*item;
    
}

HeapNode *ReadData(int N,HeapNode *H,int A[])//读取各个节点的权值输入数据
{
    char s='\0';
    int value=0;
    for (int i=0; i<N; ++i)
    {
        cin>>s;
        cin>>value;
        A[i]=value;
        TreeNode *T=new(TreeNode);
        T->Weight=value;
        Insert(H, T);
    }
    return H;
}

TreeNode *Huffman(HeapNode *H)//构建Huffman树
{
    TreeNode *T=nullptr;
    int num=H->Size;
    for (int i=0; i<num-1; ++i)
    {
        T=new(TreeNode);
        T->Left=DeleteMin(H);
        
        T->Right=DeleteMin(H);
        
        T->Weight=T->Left->Weight+T->Right->Weight;
        Insert(H, T);
        
    }
    T=DeleteMin(H);
    return T;
}

int WPL(TreeNode *T,int Depth)//计算Huffman树的编码长度
{
    if ((T->Left==nullptr)&&(T->Right==nullptr))
    {
        return Depth*(T->Weight);
    }else
    {
        return (WPL(T->Left,Depth+1)+WPL(T->Right,Depth+1));
    }
}
struct JNode
{
    int Flag=0;
    JNode *Left=nullptr;
    JNode *Right=nullptr;
    
};
bool Judge(string S,JNode *J)//判断该次编码能否符合前缀编码的要求
{
    int i=0;
    for (; i<S.length(); ++i)
    {
        if (S[i]=='0')
        {
            if (J->Left==nullptr)
            {
                JNode *J_1=new(JNode);
                J->Left=J_1;
            }else
            {
                if (J->Left->Flag==1)
                {
                    return false;
                }
            }
            J=J->Left;
        }else
        {
            if (J->Right==nullptr)
            {
                JNode *J_1=new(JNode);
                J->Right=J_1;
            }else
            {
                if (J->Right->Flag==1)
                {
                    return false;
                }
            }
            J=J->Right;
        }
    }
    J->Flag=1;
    if (J->Left==nullptr&&J->Right==nullptr)
    {
        return true;
    }else
    {
        return false;
    }
}

int main(int argc, char const *argv[])
{
    int N=0,n=0;
    cin>>N;
    HeapNode *H=CreateHeap(N);
    int Value[MaxNum]={};
    H=ReadData(N,H,Value);
    
    TreeNode *T=Huffman(H);
    
    int CodeLen=WPL(T,0);
    
    cin>>n;
    string temp="\0";
    char c='\0';
    bool result=false;
    
    
    for (int i=0; i<n; ++i)
    {
        int count=0,flag=0;
        JNode *J=new(JNode);
        for (int k=0; k<N; ++k)
        {
            cin>>c>>temp;
            count+=temp.length()*Value[k];
            if (!flag)
            {
                result=Judge(temp,J);
                if (!result)
                {
                    flag=1;
                }
            }
            
            
        }
        delete J;
        if (result&&(count==CodeLen))//前缀编码且编码长度之和与Huffman编码相同
        {
            cout<<"Yes"<<endl;
        }else{
            cout<<"No"<<endl;
        }
    }
    
    return 0;
}