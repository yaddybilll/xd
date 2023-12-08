#include <iostream>
#include <vector>

// Структура для представления нода графа
struct GraphNode {
    int value;
    std::vector<GraphNode*> neighbors;

    GraphNode(int val) : value(val) {}
};

// Функция для вычисления суммы значений соседних нодов
int sumOfNeighbors(GraphNode* node) {
    int sum = 0;
    for (GraphNode* neighbor : node->neighbors) {
        sum += neighbor->value;
    }
    return sum;
}

int main() {
    // Создаем ноды графа
    GraphNode* nodeA = new GraphNode(1);
    GraphNode* nodeB = new GraphNode(2);
    GraphNode* nodeC = new GraphNode(3);
    GraphNode* nodeD = new GraphNode(4);

    // Устанавливаем связи между нодами
    nodeA->neighbors.push_back(nodeB);
    nodeA->neighbors.push_back(nodeC);
    nodeA->neighbors.push_back(nodeD);

    nodeB->neighbors.push_back(nodeC);
    nodeC->neighbors.push_back(nodeD);
    nodeD->neighbors.push_back(nodeA);

    // Вычисляем и выводим сумму значений соседних нодов для каждого нода
    std::cout << "Sum of neighbors for node A: " << sumOfNeighbors(nodeA) << std::endl;
    std::cout << "Sum of neighbors for node B: " << sumOfNeighbors(nodeB) << std::endl;
    std::cout << "Sum of neighbors for node C: " << sumOfNeighbors(nodeC) << std::endl;
    std::cout << "Sum of neighbors for node D: " << sumOfNeighbors(nodeD) << std::endl;

    // Очищаем выделенную память
    delete nodeA;
    delete nodeB;
    delete nodeC;
    delete nodeD;

    return 0;
}
