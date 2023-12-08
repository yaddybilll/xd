#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

// Enum class для представления пола
enum class Gender {
    Male,
    Female
};

// Структура данных
struct Person {
    std::string name;
    int age;
    Gender gender;
};

// Функция для сериализации строки в поток
void serializeString(std::ostream& stream, const std::string& value) {
    stream << value << ",";
}

// Функция для сериализации целочисленного значения в поток
void serializeInt(std::ostream& stream, int value) {
    stream << value << ",";
}

// Функция для сериализации enum в поток
void serializeGender(std::ostream& stream, Gender value) {
    switch (value) {
        case Gender::Male:
            stream << "M,";
            break;
        case Gender::Female:
            stream << "F,";
            break;
    }
}

// Функция для сериализации объекта Person в поток
void serializePerson(std::ostream& stream, const Person& person) {
    serializeString(stream, person.name);
    serializeInt(stream, person.age);
    serializeGender(stream, person.gender);
    stream << "\n";  // Разделитель строки
}

// Функция для десериализации строки из потока в объект Person
bool deserializePerson(std::istream& stream, Person& person) {
    std::string line;
    if (!std::getline(stream, line)) {
        return false;  // Не удалось считать строку
    }

    std::istringstream iss(line);
    // Разбиваем строку по запятым и считываем поля
    if (!(std::getline(iss, person.name, ',') &&
          (iss >> person.age) &&
          (iss.ignore(), deserializeGender(iss, person.gender)))) {
        return false;  // Не удалось десериализовать поля
    }

    return true;
}

// Функция для десериализации enum из потока
bool deserializeGender(std::istream& stream, Gender& value) {
    std::string genderStr;
    if (!(stream >> genderStr)) {
        return false;
    }

    if (genderStr == "M") {
        value = Gender::Male;
    } else if (genderStr == "F") {
        value = Gender::Female;
    } else {
        return false;  // Некорректное значение для enum
    }

    return true;
}

// Функция для сериализации вектора объектов Person в поток
void serializePeople(std::ostream& stream, const std::vector<Person>& people) {
    for (const auto& person : people) {
        serializePerson(stream, person);
    }
}

// Функция для десериализации вектора объектов Person из потока
std::vector<Person> deserializePeople(std::istream& stream) {
    std::vector<Person> people;
    Person person;

    while (deserializePerson(stream, person)) {
        people.push_back(person);
    }

    return people;
}

int main() {
    // Создаем вектор объектов Person для тестирования
    std::vector<Person> people = {
        {"Alice", 25, Gender::Female},
        {"Bob", 30, Gender::Male},
        {"Charlie", 22, Gender::Male}
    };

    // Сериализуем объекты Person в файл "people.csv"
    std::ofstream outFile("people.csv");
    if (outFile.is_open()) {
        serializePeople(outFile, people);
        outFile.close();
    } else {
        std::cerr << "Error: Unable to open output file." << std::endl;
        return 1;
    }

    // Десериализуем объекты Person из файла "people.csv"
    std::ifstream inFile("people.csv");
    if (inFile.is_open()) {
        std::vector<Person> deserializedPeople = deserializePeople(inFile);

        // Модифицируем первый объект
        if (!deserializedPeople.empty()) {
            deserializedPeople[0].age += 5;
            deserializedPeople[0].gender = Gender::Male;
        }

        // Добавляем новый объект
        deserializedPeople.push_back({"Eva", 28, Gender::Female});

        // Сериализуем обновленные объекты в файл "updated_people.csv"
        std::ofstream updatedOutFile("updated_people.csv");
        if (updatedOutFile.is_open()) {
            serializePeople(updatedOutFile, deserializedPeople);
            updatedOutFile.close();
        } else {
            std::cerr << "Error: Unable to open updated output file." << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }

    std::cout << "Serialization and deserialization successful." << std::endl;

    return 0;
}
