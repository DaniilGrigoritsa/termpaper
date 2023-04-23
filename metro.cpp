#include <iostream>
#include <iomanip>
#define STATIONS 300
using namespace std;

struct St {
    string arrival;
    string departure;
};

St input(string *stations, int length) {
    St st = St{ "", "" };
    bool flag = true;
    cout << "Введите станцию отправления: \n";
    while (flag) {
        cin >> st.departure;
        if (includes(st.departure, stations, length)) flag = false;
        else cout << "Станция введена неверно \n";
    }
    flag = true;
    while (flag) {
        cin >> st.arrival;
        if (includes(st.arrival, stations, length)) {
            if (st.arrival != st.departure) flag = false;
            else cout << "Введены одинаковые станции отправления и прибытия\n";
        }
        else cout << "Станция введена неверно \n";
    }
    return st;
}

bool includes(string station, string* stations, int length) {
    for (int i = 0; i < length; i++) {
        if (station == stations[i]) return true;
    }
    return false;
}

int main() {
    int big_num(10000);
    int matrix[STATIONS][STATIONS] = { }; // матрица смежности расстояний между станциями
    string* stations = { };
    string arrival, departure;
    St st = input(stations, STATIONS);

    int pos[STATIONS], node[STATIONS], min(0), index_min(0);
    for (int i = 0;i < STATIONS;++i) {     // заполняем путь к вершине большими числами, желательно взять биг_нам ещё больше, но и так ок.
        pos[i] = big_num;       // а все вершины помечаем как "непройденные"
        node[i] = 0;
    }

    for (int i = 0;i < STATIONS;++i) {     // вывод матрицы
        for (int j = 0;j < STATIONS;++j) {
            cout << setw(STATIONS - 1) << matrix[i][j];
        }
        cout << "\n";
    }
    pos[2] = 0;                // назначаем какую-то вершину началом алгоритма, узлом ( или так не говорят, хз)
    for (int i = 0;i < STATIONS - 1;++i) {    // основной цикл
        min = big_num;
        for (int j = 0;j < STATIONS;++j) {     // находим вершину с минимальным к ней расстоянием, на первом шаге это будет узел
            if (!node[j] && pos[j] < min) {
                min = pos[j];
                index_min = j;
            }
        }
        node[index_min] = true;   // помечаем выбранную вершину как пройденную
        for (int j = 0;j < STATIONS;++j) {   // цикл, в котором мы даем всем вершинам, смежным с выбранной вес пути к ней
            if (!node[j] && matrix[index_min][j] > 0 && pos[index_min] != big_num && pos[index_min] + matrix[index_min][j] < pos[j]) {
                pos[j] = pos[index_min] + matrix[index_min][j];
            } // условие такое, если эта вершина не пройденная и она смежна с выбранной и если сумма веса выбранной вершины и ребра к текущей будет меньше, чем
        }     // вес текущей на данный момент, то  - меняем значение веса текущей вершины.
    }
    cout << pos[0] << "\n"; // теперь у нас в pos минимальные расстояния от выбранного узла к любой другой вершине

    cout << endl;
    return 0;
}