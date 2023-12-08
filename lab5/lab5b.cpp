#include <iostream>
#include <cassert>

// Структура для представления узла списка
struct Node {
    int data;
    Node* prev;
    Node* next;

    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

// Структура для представления двусвязного списка
struct LinkedList {
    Node* first;
    Node* last;

    LinkedList() : first(nullptr), last(nullptr) {}

    // Метод для вставки нового узла после указанного узла
    Node* insertAfter(Node* node, int value) {
        Node* newNode = new Node(value);

        if (!node) {
            // Если node == nullptr, добавляем в начало списка
            newNode->next = first;
            if (first) {
                first->prev = newNode;
            }
            first = newNode;

            if (!last) {
                // Если список был пуст, обновляем last
                last = newNode;
            }
        } else {
            // Вставляем после указанного узла
            newNode->next = node->next;
            newNode->prev = node;
            if (node->next) {
                node->next->prev = newNode;
            }
            node->next = newNode;

            if (node == last) {
                // Если вставляется после последнего узла, обновляем last
                last = newNode;
            }
        }

        return newNode;
    }

    // Метод для вставки нового узла перед указанным узлом
    Node* insertBefore(Node* node, int value) {
        Node* newNode = new Node(value);

        if (!node) {
            // Если node == nullptr, добавляем в конец списка
            newNode->prev = last;
            if (last) {
                last->next = newNode;
            }
            last = newNode;

            if (!first) {
                // Если список был пуст, обновляем first
                first = newNode;
            }
        } else {
            // Вставляем перед указанным узлом
            newNode->prev = node->prev;
            newNode->next = node;
            if (node->prev) {
                node->prev->next = newNode;
            }
            node->prev = newNode;

            if (node == first) {
                // Если вставляется перед первым узлом, обновляем first
                first = newNode;
            }
        }

        return newNode;
    }

    // Метод для поиска узла с заданным значением
    Node* find(int value) {
        Node* current = first;

        while (current && current->data != value) {
            current = current->next;
        }

        return current;
    }

    // Метод для удаления указанного узла
    void remove(Node* node) {
        if (!node) {
            return;
        }

        if (node->prev) {
            node->prev->next = node->next;
        } else {
            // Если удаляется первый узел, обновляем first
            first = node->next;
        }

        if (node->next) {
            node->next->prev = node->prev;
        } else {
            // Если удаляется последний узел, обновляем last
            last = node->prev;
        }

        delete node;
    }

    // Метод для проверки отсутствия циклов в списке
    void assertNoCycles() {
        Node* current = first;

        while (current) {
            assert(current->prev != current); // Проверка наличия цикла в узлах
            current = current->next;
        }

        assert(first ? first->prev == nullptr : true); // Проверка начала списка
        assert(last ? last->next == nullptr : true);   // Проверка конца списка
    }
};

int main() {
    LinkedList list;

    // Пример использования методов
    Node* node1 = list.insertAfter(nullptr, 1);
    Node* node2 = list.insertBefore(node1, 2);
    Node* node3 = list.insertAfter(node2, 3);

    list.assertNoCycles();

    Node* foundNode = list.find(2);
    if (foundNode) {
        std::cout << "Found node with value 2." << std::endl;
        list.remove(foundNode);
    }

    list.assertNoCycles();

    return 0;
}
