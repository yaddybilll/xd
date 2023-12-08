#include <iostream>
#include <cassert>

// Структура для представления узла списка
struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

// Структура для представления результата поиска узла
struct FindNodeResult {
    Node* current;  // Узел с заданным значением
    Node* previous; // Узел перед ним

    FindNodeResult(Node* cur, Node* prev) : current(cur), previous(prev) {}
};

// Структура для представления связного списка
struct LinkedList {
    Node* first;
    Node* last;
    int size;

    LinkedList() : first(nullptr), last(nullptr), size(0) {}

    // Метод для вставки нового узла после указанного узла
    Node* insertAfter(Node* node, int value) {
        Node* newNode = new Node(value);

        if (!node) {
            // Если node == nullptr, добавляем в начало списка
            newNode->next = first;
            first = newNode;

            if (!last) {
                // Если список был пуст, обновляем last
                last = newNode;
            }
        }
        else {
            // Вставляем после указанного узла
            newNode->next = node->next;
            node->next = newNode;

            if (node == last) {
                // Если вставляется после последнего узла, обновляем last
                last = newNode;
            }
        }

        size++;
        return newNode;
    }

    // Метод для поиска узла с заданным значением
    FindNodeResult find(int value) {
        Node* current = first;
        Node* previous = nullptr;

        while (current && current->data != value) {
            previous = current;
            current = current->next;
        }

        return FindNodeResult(current, previous);
    }

    // Метод для удаления узла после указанного узла
    void removeAfter(Node* node) {
        if (!node) {
            // Удаляем первый узел
            if (first) {
                Node* temp = first;
                first = first->next;
                delete temp;

                if (!first) {
                    // Если удалили последний узел, обновляем last
                    last = nullptr;
                }

                size--;
            }
        }
        else if (node->next) {
            // Удаляем узел после указанного узла
            Node* temp = node->next;
            node->next = temp->next;
            delete temp;

            if (temp == last) {
                // Если удалили последний узел, обновляем last
                last = node;
            }

            size--;
        }
    }

    // Метод для проверки отсутствия циклов в списке
    void assertNoCycles() {
        int count = 0;
        Node* slow = first;
        Node* fast = first;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            count++;

            assert(count <= size * 2); // Защита от бесконечного цикла
        }

        assert(count == size);
    }
};

int main() {
    LinkedList list;

    // Пример использования методов
    Node* node1 = list.insertAfter(nullptr, 1);
    Node* node2 = list.insertAfter(node1, 2);
    Node* node3 = list.insertAfter(node2, 3);

    list.assertNoCycles();

    FindNodeResult result = list.find(2);
    if (result.current) {
        std::cout << "Found node with value 2." << std::endl;
        list.removeAfter(result.previous);
    }

    list.assertNoCycles();

    return 0;
}
