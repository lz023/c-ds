#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

class node
{
public:
    long data;
    node* up;
    node* down;
    node* left;
    node* right;
    bool visited;
    node()
    {
        up = nullptr;
        down = nullptr;
        right = nullptr;
        left = nullptr;
        visited = 0;
    }
    node(int d)
    {
        data = d;
        up = nullptr;
        down = nullptr;
        left = nullptr;
        right = nullptr;
        visited = 0;
    }
    void printNode()
    {
        if (this)
        {
            cout << " | " << data << " | ";
        }
    }
};

class DoublyLinkedList
{

private:
    int col = 0;
    int row = 0;
    vector<long> arr;
public:
    node* head;

    DoublyLinkedList()
    {
        head = nullptr;
    }

    void Read(const string& filename)
    {
        ifstream file;
        file.open(filename);

        if (!file)
        {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        long a;
        char b = 'a';

        while (file >> a)
        {
            arr.push_back(a);
            node* newNode = new node(a);

            if (!head)
            {
                head = newNode;
            }

            file.get(b);

            if (b == ',')
            {
                col++;
            }
            else
            {
                row++;
                col = 0;
            }
        }
        row++;
        int k = 0;
        node* nn = new node(arr[k]);
        head = nn;
        node* temp = head;
        node* curr = temp;
        node* upper = nullptr;
        k++;
        for (int i = 0; i < row; i++)
        {
            for (int j = 1; j < col; j++)
            {
                nn = new node(arr[k]);
                temp->right = nn;
                nn->left = temp;
                temp = temp->right;
                k++;
                if (i > 0)
                {
                    upper = upper->right;
                    upper->down = nn;
                    nn->up = upper;
                }

            }
            if (i < row - 1)  //to prevent making extra row
            {
                temp = new node(arr[k]);
                temp->up = curr;
                curr->down = temp;
                k++;
                upper = curr;
                curr = temp;
            }
        }
    }

    void Print()
    {
        node* temp = head;
        node* start = temp;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (temp->right)
                {
                    cout << " | " << temp->data << " | -> ";
                }
                else
                {
                    cout << " | " << temp->data << " | ";
                }
                temp = temp->right;
            }
            if (start->down)
            {
                temp = start->down;
                start = temp;
            }
            cout << endl << endl;
        }
    }

    int ClueRow(int data)
    {
        int sum = 0;
        while (data > 0)
        {
            sum = sum + (data % 10);
            data = data / 10;
        }
        sum = sum % row;

        return (sum + 1);
    }

    int ClueColumn(int data)
    {
        if (data == 0)
        {
            return 1;
        }
        int count = 0;
        data = abs(data);

        while (data > 0)
        {
            data /= 10;
            count++;
        }

        return count;
    }

    bool EliteNode(node*& eliteNode)
    {
        node* temp = head;
        eliteNode = head;
        int r = 0;
        int c = 0;
        while (true)
        {
            eliteNode->printNode();
            cout << " -> ";
            eliteNode->visited = 1;
            r = ClueRow(eliteNode->data);
            c = ClueColumn(eliteNode->data);
            if (r > row || c > col)
            {
                cout << "Out of bound.\n";
                return 0;
            }
            for (int i = 1; i < r; i++)
            {
                temp = temp->down;
            }
            for (int j = 1; j < c; j++)
            {
                temp = temp->right;
            }
            if (temp == eliteNode)
            {
                return 1;
            }
            if (temp->visited)
            {
                cout << "Node already visted.\n";
                return 0;
            }
            eliteNode = temp;
            temp = head;
        }


    }

};

void main()
{
    DoublyLinkedList dll;
    dll.Read("data1.txt");
    dll.Print();
    node* ptr = nullptr;
    if (dll.EliteNode(ptr))
    {
        cout << "\nElite Node found!\n";
        ptr->printNode();
    }
    else
        cout << "\nElite Node does not exist!\n";

}