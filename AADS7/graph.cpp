#include "graph.h"

Graph::Graph(size_t size) : size(size) {
    matrix = new int*[capacity];
    for (size_t i = 0; i < capacity; ++i) {
        matrix[i] = new int[capacity]{};
    }
}

Graph::~Graph() {
    for (size_t i = 0; i < capacity; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void Graph::addEdge(char U, char V) {
    if (hasEdge(U, V)) throw std::logic_error("Ошибка: Данное ребро уже существует!");

    size_t U_num = verticeNum(U);
    size_t V_num = verticeNum(V);

    if (U_num > capacity || V_num > capacity)
        throw std::out_of_range("Ошибка: Нельзя добавить ребро с вершиной больше Z!");

    size_t sizenew = (U_num > V_num ? U_num : V_num) + 1;
    size = (sizenew > size) ? sizenew : size;
    // size = (U_num > V_num) ? U_num : V_num;
    // size += 1;

    matrix[U_num][V_num] = 1;
    matrix[V_num][U_num] = 1;
}

void Graph::removeEdge(char U, char V) {
    if (!hasEdge(U, V)) throw std::out_of_range("Ошибка: Заданное ребро не существует!");

    size_t U_num = verticeNum(U);
    size_t V_num = verticeNum(V);

    matrix[U_num][V_num] = 0;
    matrix[V_num][U_num] = 0;
}

bool Graph::hasEdge(char U, char V) const {
    size_t U_num = verticeNum(U);
    size_t V_num = verticeNum(V);

    if (U_num < size && V_num < size) {
        return matrix[U_num][V_num] == 1;
    }
    return false;
}

size_t Graph::getDegree(char U) const {
    size_t U_num = verticeNum(U);

    if (U_num > capacity) throw std::out_of_range("Ошибка: Не существует вершины больше Z!");

    int degreeCount = 0;
    for (size_t V_num = 0; V_num < size; V_num++) {
        degreeCount += matrix[U_num][V_num];
    }
    return degreeCount;
}

void Graph::show() const {
    cout << "    ";
    for (size_t V_num = 0; V_num < size; V_num++) cout << std::setw(3) << verticeLetter(V_num) << " ";
    cout << endl;
    for (size_t U_num = 0; U_num < size; U_num++) {
        cout << std::setw(3) << verticeLetter(U_num) << " ";
        for (size_t V_num = 0; V_num < size; V_num++) {
            cout << std::setw(3) << matrix[U_num][V_num] << " ";
        }
        cout << endl;
    }
}

void Graph::dfs(size_t V_num, bool visited[]) const {
    visited[V_num] = true;
    for (size_t U_num = 0; U_num < size; U_num++) {
        if (matrix[V_num][U_num] == 1 && !visited[U_num]) {
            dfs(U_num, visited);
        }
    }
}

bool Graph::isConnected() const {
    bool visited[capacity] = {false};

    size_t V_start = 0;
    while (V_start < size && getDegree(verticeLetter(V_start)) == 0) {
        V_start++;
    }

    if (V_start < size) {
        dfs(V_start, visited);
    }

    // Проверяем, все ли вершины с ненулевой степенью были посещены
    for (size_t i = 0; i < size; i++) {
        if (getDegree(verticeLetter(i)) > 0 && visited[i] == 0) {
            return false;
        }
    }

    return true;
}

bool Graph::hasEulerianCycle() const {
    if (!isConnected()) {
        return false;
    }

    // Проверяем, все ли вершины имеют четную степень
    for (size_t i = 0; i < size; i++) {
        if (getDegree(verticeLetter(i)) % 2 != 0) {
            return false;
        }
    }

    return true;
}

void Graph::EulerianCycleCalc(size_t start, std::deque<char>& cycle, int** tempMatrix) const {
    for (size_t V_num = 0; V_num < size; V_num++) {
        while (tempMatrix[start][V_num] > 0) {
            tempMatrix[start][V_num] = 0;
            tempMatrix[V_num][start] = 0;
            EulerianCycleCalc(V_num, cycle, tempMatrix);
        }
    }
    cycle.push_front(verticeLetter(start));
}

void Graph::printEulerianCycle(char start) const {
    if (!hasEulerianCycle()) {
        cout << "Граф не имеет Эйлерова цикла." << endl;
        return;
    }

    std::deque<char> cycle;
    int** tempMatrix = new int*[capacity];

    for (size_t i = 0; i < capacity; ++i) {
        tempMatrix[i] = new int[capacity];
        for (size_t j = 0; j < capacity; ++j) {
            tempMatrix[i][j] = matrix[i][j];
        }
    }

    EulerianCycleCalc(verticeNum(start), cycle, tempMatrix);

    for (size_t i = 0; i < capacity; ++i) {
        delete[] tempMatrix[i];
    }
    delete[] tempMatrix;

    cout << "Эйлеров цикл: ";
    for (const char& vertex : cycle) {
        cout << vertex << " ";
    }
    cout << endl;
}

// int main() {
//     setlocale(LC_ALL, "Russian");

//     Graph GR(6);

//     GR.addEdge('A', 'B');
//     GR.addEdge('A', 'C');
//     GR.addEdge('A', 'D');
//     GR.addEdge('A', 'E');
//     GR.addEdge('B', 'C');
//     GR.addEdge('B', 'D');
//     GR.addEdge('B', 'E');
//     GR.addEdge('C', 'D');
//     GR.addEdge('C', 'E');
//     GR.addEdge('D', 'E');

//     GR.show();

//     GR.printEulerianCycle('A');

//     GR.show();

//     GR.printEulerianCycle('D');

//     return 0;
// }
