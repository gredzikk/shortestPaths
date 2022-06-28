/*
Dany jest graf nieskierowany G z wagami dodatnimi. 
Napisz program, który znajdzie długości najkrótszych dróg do wszystkich pozostałych z wierzchołka o numerze 0. 
W pierwszym wierszu podane są dwie liczby: n (liczba wierzchołków) i m (liczba krawędzi). 
Następnie podanych jest m linijek składających się z trzech liczb - dwie pierwsze liczby to końce krawędzi w grafie, 
zaś trzecia liczba oznacza wagę tej krawędzi.

Przykład

5 5
0 1 1
1 3 1
0 3 3
3 4 2
2 3 2
Graf taki można zapisać w macierzy sąsiedztwa A z wagami:

A	0	1	2	3	4
0	0	1	0	3	0
1	1	0	0	1	0
2	0	0	0	2	0
3	3	1	2	0	2
4	0	0	0	2	0
Wynik

Odleglosc od 0 do 0 wynosi 0
Odleglosc od 0 do 1 wynosi 1
Odleglosc od 0 do 2 wynosi 4
Odleglosc od 0 do 3 wynosi 2
Odleglosc od 0 do 4 wynosi 4

*/


#include <iostream>
#include <vector>
#include <iomanip>

struct Graph
{
    unsigned int edgesCount, verticesCount;
    std::vector<std::vector<unsigned int> > matrix;
    std::vector<double> distances;
    std::vector<bool> visited;
};

void readGraph(Graph& graph)
{
    std::cout << "podaj ilosc punktow i krawedzi grafu: ";
    std::cin >> graph.verticesCount >> graph.edgesCount;

    graph.matrix.resize(graph.verticesCount);
    for(int i = 0; i < graph.verticesCount; ++i)
        graph.matrix[i].resize(graph.verticesCount);

    graph.distances.resize(graph.verticesCount);
    graph.visited.resize(graph.verticesCount);

    for(int i = 0; i < graph.verticesCount; ++i)
        graph.distances[i] = INT_MAX, graph.visited[i] = false;  //ustaw odleglosci na nieskonczonosc i wszystkie wierzcholki na nieodwiedzone

    for(int i = 0; i < graph.edgesCount; ++i)
    {
        int u, v, w;
        std::cout << "podaj dwa punkty bedace koncami krawedzi (" << i+1 << "/" << graph.edgesCount << ") i wage tej krawedzi: ";
        std::cin >> u >> v >> w;
        graph.matrix[u-1][v-1] = w;
        graph.matrix[v-1][u-1] = w;
    }
}

void printGraph(Graph graph)
{
    std::cout << std::endl << "A   ";
    for(int i = 0; i < graph.verticesCount; ++i)
        std::cout << i << " ";

    std::cout << std::endl << std::endl;


    for(int i = 0; i < graph.verticesCount; ++i)
    {
        std::cout << i << "   ";
        for(int j = 0; j < graph.verticesCount; ++j)
        {
            std::cout << graph.matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int minDistance(Graph& graph)
{
    int min = INT_MAX, minIndex;
 
    for (int i = 0; i < graph.verticesCount; ++i)
        if (graph.visited[i] == false && graph.distances[i] < min)
            min = graph.distances[i], minIndex = i;
 
    return minIndex;  //zwroc indeks pod ktorym jest nieodwiedzony element o najkrotszym dystansie
}

void printDistances(Graph graph, unsigned int start)
{
    std::cout << std::endl;

    for(int i = 0; i < graph.verticesCount; ++i)
    std::cout << "Odleglosc od " << start << " do " << i << " wynosi " << std::setprecision(3) << std::fixed << graph.distances[i]/1000 << std::endl;
}

void dijkstra(Graph & graph, unsigned int start)
{
    graph.distances[start] = 0; //dystans z 0 do 0 jest rowny 0

    for (int i = 0; i < graph.verticesCount - 1; ++i) 
    {
        int minIndex = minDistance(graph);
        graph.visited[minIndex] = true;
 
        for (int j = 0; j < graph.verticesCount; ++j)
            if (!graph.visited[j] && graph.matrix[minIndex][j] && graph.distances[minIndex] < INT_MAX && graph.distances[minIndex] + graph.matrix[minIndex][j] < graph.distances[j])
                graph.distances[j] = graph.distances[minIndex] + graph.matrix[minIndex][j];
    }
}

int main()
{
    Graph graph;
    readGraph(graph);
    //printGraph(graph);
 
    std::cout <<"Podaj wierzcholek startowy: ";
    unsigned int start;
    std::cin >> start;

    dijkstra(graph, start);

    printDistances(graph, start);
}