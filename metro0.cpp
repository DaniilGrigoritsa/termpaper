#include <iostream>
#include <vector>
#include <iomanip>
#include <windows.h>
#include "./headers/weight_time.h"
#include "./headers/stations.h"
#include <string>

#define INF 10000

struct St {
    wstring arrival;
    wstring departure;
};

bool includes(wstring station) {
    for (int i = 0; i < STATIONS; i++) {
        if (station == stations[i]) return true;
    }
    return false;
}

St input() {
    St st;
    bool flag = true;
    wcout << L"Введите станцию отправления: \n";
    while (flag) {
        getline(wcin, st.departure);
        if (includes(st.departure)) flag = false;
        else wcout << L"Станция введена неверно \n";
    }
    flag = true;
    wcout << L"Введите станцию прибытия: \n";
    while (flag) {
        getline(wcin, st.arrival);
        if (includes(st.arrival)) {
            if (st.arrival != st.departure) flag = false;
            else wcout << L"Введены одинаковые станции отправления и прибытия s\n";
        }
        else wcout << L"Станция введена неверно \n";
    }
    return st;
}

int find_min_distance(int dist[], bool visited[]) {
    int minDist = INF;
    int minIndex = -1;

    for (int i = 0; i < STATIONS; ++i) {
        if (!visited[i] && dist[i] <= minDist) {
            minDist = dist[i];
            minIndex = i;
        }
    }

    return minIndex;
}

int get_station_index(wstring station) {
    for (int i = 0; i < STATIONS; i++) {
        if (stations[i] == station) {
            return i;
        }
    }
    return 0;
}

vector<int> find_shortest_path(int parent[], int dest) {
    vector<int> path;
    int current = dest;

    while (current != -1) {
        path.insert(path.begin(), current);
        current = parent[current];
    }

    return path;
}

void dijkstra(int graph[STATIONS][STATIONS], int src, int dest) {
    int dist[STATIONS];
    bool visited[STATIONS];
    int parent[STATIONS];
    for (int i = 0; i < STATIONS; ++i) {
        dist[i] = INF;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < STATIONS - 1; ++count) {
        int u = find_min_distance(dist, visited);
        visited[u] = true;

        for (int i = 0; i < STATIONS; ++i) {
            if (!visited[i] && graph[u][i] && dist[u] != INF && dist[u] + graph[u][i] < dist[i]) {
                dist[i] = dist[u] + graph[u][i];
                parent[i] = u;
            }
        }
    }

    wcout << L"Кратчайший путь между станциями равен " << dist[dest] << L" секундам" <<"\n";
    vector<int> shortestPath = find_shortest_path(parent, dest);
    wcout << L"Кратчайший путь: ";

    for (int i = 0; i < shortestPath.size() - 1; i++) {
        wcout << stations[shortestPath[i]] << " -> ";
    }

    wcout << stations[shortestPath[shortestPath.size() - 1]] << "\n";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "");

    wstring arrival, departure;
    St st = input();

    int source = get_station_index(st.departure);
    int destination = get_station_index(st.arrival);

    dijkstra(time_graph, source, destination);

    return 0;
}