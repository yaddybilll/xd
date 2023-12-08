#include <iostream>
#include <cassert>

// Структура для представления узла очереди
struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

// Структура для представления очереди
struct Queue {
    Node* front;
    Node* rear;

    Queue() : front(nullptr), rear(nullptr) {}

    // Метод для добавления элемента в конец очереди
    void enqueue(int value) {
        Node* newNode = new Node(value);

        if (!rear) {
            // Если очередь пуста, устанавливаем front и rear на новый узел
            front = rear = newNode;
        } else {
            // Иначе добавляем новый узел в конец и обновляем rear
            rear->next = newNode;
            rear = newNode;
        }
    }

    // Метод для удаления элемента из начала очереди и возвращения его значения
    int dequeue() {
        if (!front) {
            // Если очередь пуста, возвращаем -1 (предполагая, что -1 не может быть элементом очереди)
            std::cerr << "Error: Attempt to dequeue from an empty queue." << std::endl;
            return -1;
        }

        int value = front->data;
        Node* temp = front;

        if (front == rear) {
            // Если в очереди был один элемент, обнуляем front и rear
            front = rear = nullptr;
        } else {
            // Иначе обновляем front на следующий узел
            front = front->next;
        }

        delete temp;
        return value;
    }

    // Метод для проверки, является ли очередь пустой
    bool isEmpty() {
        return front == nullptr;
    }
};

// Функция тестирования для enqueue
void testEnqueue() {
    Queue queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    assert(queue.front->data == 1);
    assert(queue.rear->data == 3);
    assert(!queue.isEmpty());
}

// Функция тестирования для dequeue
void testDequeue() {
    Queue queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    int value1 = queue.dequeue();
    int value2 = queue.dequeue();
    int value3 = queue.dequeue();

    assert(value1 == 1);
    assert(value2 == 2);
    assert(value3 == 3);
    assert(queue.isEmpty());
}

// Функция тестирования для isEmpty
void testIsEmpty() {
    Queue queue;
    assert(queue.isEmpty());

    queue.enqueue(1);
    assert(!queue.isEmpty());

    queue.dequeue();
    assert(queue.isEmpty());
}

int main() {
    testEnqueue();
    testDequeue();
    testIsEmpty();

    std::cout << "All tests passed successfully." << std::endl;

    return 0;
}
