#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>
#include <string>
using namespace std;

class Graph
{
public:
    int G[11][11], vertices = 11;
    vector<string> places = {
        "MIT_ADTU", "Shewalewadi", "Hadapsar", "Magarpatta",
        "Fatima_Nagar", "Mundhwa", "Kharadi", "Viman_Nagar",
        "Kondhwa", "Kalyaninagar", "Wagholi"};

    Graph()
    {
        // Initialize the graph with infinite distances
        for (int i = 0; i < 11; i++)
        {
            for (int j = 0; j < 11; j++)
            {
                G[i][j] = INT_MAX;
            }
        }

        // Add edges according to the image
        // Format: G[source][destination] = weight

        // MIT_ADTU connections
        G[0][1] = G[1][0] = 11; // MIT_ADTU - Shewalewadi

        // Shewalewadi connections
        G[1][2] = G[2][1] = 6; // Shewalewadi - Hadapsar

        // Hadapsar connections
        G[2][3] = G[3][2] = 2;   // Hadapsar - Magarpatta
        G[2][4] = G[4][2] = 5.2; // Hadapsar - Fatima_Nagar

        // Magarpatta connections
        G[3][6] = G[6][3] = 6;   // Magarpatta - Kharadi
        G[3][5] = G[5][3] = 2.6; // Magarpatta - Mundhwa

        // Fatima_Nagar connections
        G[4][8] = G[8][4] = 5.1; // Fatima_Nagar - Kondhwa

        // Mundhwa connections
        G[5][6] = G[6][5] = 3.4; // Mundhwa - Kharadi

        // Kharadi connections
        G[6][7] = G[7][6] = 5.4;   // Kharadi - Viman_Nagar
        G[6][10] = G[10][6] = 5.5; // Kharadi - Wagholi

        // Viman_Nagar connections

        G[7][9] = G[9][7] = 3.6; // Viman_Nagar - Kalyaninagar

        // Kondhwa connections
        G[8][9] = G[9][8] = 12; // Kondhwa - Kalyaninagar

        // Kalyaninagar connections
        G[9][7] = G[7][9] = 4.6; // Kalyaninagar - Viman_Nagar
        // mundhwa connections
        G[5][9] = G[9][5] = 4.6;
    }

    void display()
    {
        cout << "Available places (vertices):\n";
        for (int i = 0; i < vertices; i++)
        {
            cout << (i + 1) << ". " << places[i] << "\n";
        }
    }

    void dijkstra(int start, int destination)
    {
        start--;       // Convert to 0-based index
        destination--; // Convert to 0-based index

        vector<double> dist(vertices, INT_MAX);
        vector<bool> visited(vertices, false);
        vector<int> parent(vertices, -1);

        dist[start] = 0;

        for (int count = 0; count < vertices - 1; count++)
        {
            double minDist = INT_MAX;
            int u = -1;

            for (int v = 0; v < vertices; v++)
            {
                if (!visited[v] && dist[v] < minDist)
                {
                    minDist = dist[v];
                    u = v;
                }
            }

            if (u == -1)
                break;

            visited[u] = true;

            for (int v = 0; v < vertices; v++)
            {
                if (!visited[v] && G[u][v] != INT_MAX && dist[u] != INT_MAX &&
                    dist[u] + G[u][v] < dist[v])
                {
                    dist[v] = dist[u] + G[u][v];
                    parent[v] = u;
                }
            }
        }

        cout << "\nShortest path from " << places[start] << " to " << places[destination] << ":\n";

        if (dist[destination] == INT_MAX)
        {
            cout << "No path exists\n";
        }
        else
        {
            cout << "Distance = " << dist[destination] << " km, Path = ";
            vector<int> path;
            for (int v = destination; v != -1; v = parent[v])
            {
                path.push_back(v);
            }
            for (int i = path.size() - 1; i >= 0; i--)
            {
                cout << places[path[i]];
                if (i > 0)
                    cout << " -> ";
            }
            cout << endl;
        }
    }
};

int main()
{
    Graph g;
    g.display();

    int source, destination;
    cout << "\nChoose the source (by number): ";
    cin >> source;

    cout << "Choose the destination (by number): ";
    cin >> destination;

    if (source > 0 && source <= g.vertices && destination > 0 && destination <= g.vertices)
    {
        g.dijkstra(source, destination);
    }
    else
    {
        cout << "Invalid source or destination.\n";
    }

    return 0;
}