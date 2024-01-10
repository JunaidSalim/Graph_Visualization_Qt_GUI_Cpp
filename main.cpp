#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>
#include<conio.h>
using namespace std;

class Graph
{
    int numNodes;
    double density;
    int edges;
    vector<vector<int>> adjacencyMatrix;

public:
    Graph(int num, double d)
    {
        numNodes = num;
        density = d;
        adjacencyMatrix.resize(num, vector<int>(num, 0));
        calculateNumberOfEdges();
        PopulateMatrix();
    }

    void calculateNumberOfEdges()
    {
        int maxEdges = (numNodes * (numNodes - 1)) / 2;
        double temp = density * maxEdges;
        edges = round(temp);
    }

    void display()
    {
        cout << endl
             << "Number of Nodes: " << numNodes;
        cout << endl
             << "Density: " << density;
        cout << endl
             << "Edges: " << edges;
        cout << endl;
        for (int i = 0; i < numNodes; i++)
        {
            for (int j = 0; j < numNodes; j++)
            {
                cout << adjacencyMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void PopulateMatrix()
    {
        int count = edges;
        while(count>0)
        {
            srand(time(NULL));
            int i = rand()%numNodes;
            int j = rand()%numNodes;
            if (i!=j && adjacencyMatrix[i][j]!=1)
            {
                adjacencyMatrix[i][j]=1;
                adjacencyMatrix[j][i]=1;
                count--;
            }
        }
    }

    int findDegree(int node)
    {
        int degree=0;
        for(int i=0;i<numNodes;i++)
        {
            if(adjacencyMatrix[node-1][i]==1)
            {
                degree++;
            }
        }
        return degree;
    }

    int findMaxDegree()
    {
        int max=0,temp=0;
        int maxDegree=0;
        for(int i=0;i<numNodes;i++)
        {
            temp = findDegree(i+1);
            if (temp>max)
            {
                max=temp;
                maxDegree = i+1;
            }
            
        }
        return maxDegree;
    }

    int findMinDegree()
    {
        int min=numNodes;
        int temp=0;
        int minDegree=0;
        for(int i=0;i<numNodes;i++)
        {
            temp = findDegree(i+1);
            if (temp<min)
            {
                min=temp;
                minDegree = i+1;
            }
        }
        return minDegree;
    }

    void displayRawAdjacencyMatrix()
    {
        cout<<endl<<"Raw Adjacency Matrix:\n";
        for (int i = 0; i < numNodes; i++)
        {
            for (int j = 0; j < numNodes; j++)
            {
                cout<<adjacencyMatrix[i][j]<<"\t";
            }
            cout<<endl;
        }
    }

    vector<int> findNeighbours(int node)
    {
        vector<int>neighbours;
        for (int i = 0; i < numNodes; i++)
        {
            if (adjacencyMatrix[node-1][i]==1)
            {
                neighbours.push_back(i+1);
            }
        }
        return neighbours;
    }

};

int main()
{
    int num,input;
    double density;
    char choice;
    cout<<"\nEnter Number of Nodes: ";
    cin>>num;
    cout<<"\nEnter Density: ";
    cin>>density;
    Graph graph(num,density);
    system("cls");
    while (true)
    {
        cout<<"\n\n\nPress a)Show Degree of a node\nb)Find Node with Maximum Degree\nc)Find Node with Minimum Degree\nd)Display the raw adjacency matrix\ne)Find Neighbours of given Node\nAny other to break\n";
        choice=getch();
        system("cls");
        if (choice == 'a')
        {
            cout<<"\nEnter Node: ";
            cin>>input;
            cout<<"\nDegree of Node "<<input<<" is "<<graph.findDegree(input); 
        }
        else if (choice =='b')
        {
            cout<<"\nThe Node with Maximum Degree is Node "<<graph.findMaxDegree();
        }
        else if (choice=='c')
        {
            cout<<"\nThe Node with Minimum Degree is Node "<<graph.findMinDegree();
        }
        else if (choice=='d')
        {
            graph.displayRawAdjacencyMatrix();
        }
        else if (choice=='e')
        {
            cout<<"\nEnter Node: ";
            cin>>input;
            vector<int> neighbours =  graph.findNeighbours(input);
            int size = neighbours.size();
            if (size>=1)
            {
                cout<<"\nNeighbours of Node "<<input<<" is/are: ";
                for (int i = 0; i < size; i++)
                {
                    cout<<neighbours[i]<<" ";
                }
            }
            else
            {
                cout<<"\nNo Neighbours found for Node "<<input;
            }
        }
        else
        {
            break;
        }
    }
    
    return 0;
}