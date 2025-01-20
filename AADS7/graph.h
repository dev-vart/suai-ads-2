#include <deque>
#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::size_t;

class Graph {
   private:
    size_t size;
    const size_t capacity = 26;
    int** matrix;
    char verticeLetter(int verticeNum) const { return static_cast<char>(65 + (verticeNum % 26)); }
    size_t verticeNum(char verticeLetter) const { return (static_cast<int>(verticeLetter) - 65) % 26; }
    void dfs(size_t v, bool visited[]) const;
    bool isConnected() const; 
    bool hasEulerianCycle() const;
    void EulerianCycleCalc(size_t start, std::deque<char>& cycle, int** tempMatrix) const;

   public:
    explicit Graph(size_t size);
    ~Graph();
    void addEdge(char U, char V);
    void removeEdge(char U, char V);
    bool hasEdge(char U, char V) const;
    size_t getDegree(char V) const;
    void show() const;
    void printEulerianCycle(char start) const;
};
