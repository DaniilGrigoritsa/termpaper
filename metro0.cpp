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
    wcout << L"\nВведите станцию отправления: \n";
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
            else wcout << L"Введены одинаковые станции отправления и прибытия \n";
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

// Вывод списка линий для выбора станции
vector<int> output_lines(vector<int> ind) {
    wcout << L"Пожалуйста, уточните линию из представленных ниже: \n";  
    vector<int> _lines;
    for(int i = 0; i < ind.size(); i++) {
        wcout << lines[stations_lines[ind.at(i)] - 1] << "\n";
        _lines.push_back(stations_lines[ind.at(i)] - 1);
    }
    return _lines;
}

// Получаем индекс станции прибытия и отправления по ее названию
int get_station_index(wstring station) {
    vector<int> ind;
    for (int i = 0; i < STATIONS; i++) {
        if (stations[i] == station) {
            ind.push_back(i);
        }
    }
    if (ind.size() == 1) return ind.at(0);
    else if (ind.size() > 1) {
        bool flag = true;
        wstring inputed_line;
        vector<int> _lines = output_lines(ind); 
        while (flag) {
            getline(wcin, inputed_line);
            for(int i = 0; i < _lines.size(); i++) {
                if (lines[_lines[i]] == inputed_line) {
                    flag = false;
                    return ind.at(i);
                }
            }  
            output_lines(ind); 
        }
    }
    return 0;
}

// Восстанавливаем кратчайший путь после отработки алгоритма дейкстры
vector<int> find_shortest_path(int parent[], int dest) {
    vector<int> path;
    int current = dest;

    while (current != -1) {
        path.insert(path.begin(), current);
        current = parent[current];
    }

    return path;
}

// Вывод списка всех поддерживаемых станций
void output() {
    wcout << L"Список станций, доступных для выбора: \n";
    for(int i = 0; i < STATIONS; i+=3) {
        wcout << stations[i] << ", " << stations[i + 1] << ", " << stations[i + 2] << "\n";
    }
}

// Алгоритм дейкстры для поиска кратчайшего пути во взвешенном графе
void dijkstra(int graph[STATIONS][STATIONS], int src, int dest) {
    int dist[STATIONS];
    bool visited[STATIONS];
    int parent[STATIONS];
    // Процесс инициализации: 
    // Устанавливаем расстояния до всех станций равными большому числу, указываем все станции 
    // как не посещенные, а так же указываем предыдущие станции для каждой как -1
    for (int i = 0; i < STATIONS; ++i) {
        dist[i] = INF;
        visited[i] = false;
        parent[i] = -1;
    }

    // Расстояние до начальной вершины равно 0
    dist[src] = 0;

    for (int count = 0; count < STATIONS - 1; ++count) {
        // Получаем индекс ближайшей непосещенной станции
        int u = find_min_distance(dist, visited);
        // Указываем станцию как посещенную
        visited[u] = true;

        for (int i = 0; i < STATIONS; ++i) {
            // Обновляем расстояние до станции только если она не посещена, если существует перегон 
            // между станциями i и u и путь между исходной станцией (src) до i через u 
            // меньше, чем текущее значение дистанции dist[i]
            if (!visited[i] && graph[u][i] && dist[u] != INF && dist[u] + graph[u][i] < dist[i]) {
                dist[i] = dist[u] + graph[u][i];
                parent[i] = u;
            }
        }
    }

    wcout << L"Кратчайший путь между станциями равен " << dist[dest] << L" секундам" <<"\n";
    // Восстанавливаем кратчайший путь из конечной станции в начальную
    vector<int> shortestPath = find_shortest_path(parent, dest);
    wcout << L"Кратчайший путь: ";

    // Вывод полученного пути
    for (int i = 0; i < shortestPath.size() - 1; i++) {
        wcout << stations[shortestPath[i]] << " -> ";
    }

    wcout << stations[shortestPath[shortestPath.size() - 1]] << "\n";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "");

    output();

    wstring arrival, departure;
    St st = input();

    int source = get_station_index(st.departure);
    int destination = get_station_index(st.arrival);

    cout << destination << " " << source;

    dijkstra(time_graph, source, destination);

    return 0;
}