#include <iostream>
#include <vector>
#include <iomanip>

struct Graph
{
    unsigned int verticesCount, edgesCount;
    std::vector<std::vector<bool>> matrix;
    std::vector<std::vector<unsigned int>> adjacent;
    std::vector<bool> visited;

};

void readGraph(Graph& g)
{
    std::cin >> g.verticesCount;

    g.matrix.resize(g.verticesCount);
    g.adjacent.resize(g.verticesCount);

    for(int i = 0; i < g.verticesCount; ++i)
    {   
        g.visited.push_back(false);
        g.matrix[i].resize(g.verticesCount);
    }

    for(int i = 0; i < g.verticesCount; ++i)
        for(int j = 0; j < g.matrix[i].size(); ++j)
            g.matrix[i][j] = false;

    for(int i = 0; i < g.verticesCount; ++i)
    {
        unsigned int degree;
        std::cin >> degree;

        for(int j = 0; j < degree; ++j)
        {
            unsigned int neighbor;
            std::cin >> neighbor;
            g.adjacent[i].push_back(neighbor-1);
        }
    }
}

void printGraph(const Graph& g)
{
    for(int i = 0; i < g.verticesCount; ++i)
    {
        std::cout << std::endl << i << ": ";
        for(int j = 0; j < g.adjacent[i].size(); ++j)
        {
            std::cout << g.adjacent[i][j] << " ";
        }
    }
}

void printMatrix(const Graph& g)
{   
    std::cout << "    ";
    for(int i = 0; i < g.verticesCount; ++i)
        std::cout  << std::setw(3) << i;

    for(int i = 0; i < g.verticesCount; ++i)
    {
        std::cout << std::endl << std::setw(3) << i << "  ";
        for(int j = 0; j < g.matrix[i].size(); ++j)
        {
            std::cout << " " << g.matrix[i][j] << " ";
        }
    }
}
void convertAdjToMatrix(Graph& g)
{
    for(int i = 0; i < g.matrix.size(); ++i)
    {
        for(int j = 0; j < g.adjacent[i].size(); ++j)
        {
            g.matrix[i][g.adjacent[i][j]] = true;
            g.matrix[g.adjacent[i][j]][i] = true;
        }
    }
}

unsigned int countEdges(Graph& g)
{
    unsigned int count = 0;

    for(int i = 0; i < g.matrix.size(); ++i)
        for(int j = 0; j < g.matrix[i].size(); ++j)
            if(g.matrix[i][j] == true)
                count++;

    g.edgesCount = count/2;
    return count/2;
}

void convertMatrixToAdjacencyList(Graph & g)
{
    for(int i = 0; i < g.verticesCount; ++i)
    {
        for(int j = 0; j < g.verticesCount; ++j)
            if(g.matrix[i][j] == true)
            {    
                g.adjacent[i].push_back(j);
            }
    }
}

void printAdjList(std::vector<std::vector<unsigned int>> adjlist)
{
    for(int i = 0; i < adjlist.size(); ++i)
    {
        std::cout << i << ": ";
        
        for(int j = 0; j < adjlist[i].size(); ++j)
        {
            std::cout << adjlist[i][j] << " ";
        }
        std::cout << std::endl;  
    }
}

void DFS(Graph &g, int startVertex)
{
    g.visited[startVertex] = true;
    std::cout << startVertex+1 << " ";
    for (std::vector<unsigned int>::const_iterator it = g.adjacent[startVertex].begin(); it < g.adjacent[startVertex].end(); ++it)
        if (!g.visited[*it])
            DFS(g, *it);
}

void printEdges(Graph &g)
{
    for(int i = 0; i < g.matrix.size(); ++i)
        for(int j = i; j < g.matrix[i].size(); ++j)
            if(g.matrix[i][j] == true)
                std::cout << i+1 << " " << j+1 << std::endl;    
}
        

int main()
{
    Graph g;
    readGraph(g);

    convertAdjToMatrix(g);

    std::cout << std::endl;

    printMatrix(g);

    std::cout << std::endl << std::endl << countEdges(g) << std::endl << std::endl;

    convertAdjToMatrix(g);

    printEdges(g);
    //printAdjList(g.adjacent);

    //DFS(g, 0);
}