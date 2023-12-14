#include <iostream>
#include <fstream>
#include <string>
#include <array>

// Enum class for Gender
//https://www.geeksforgeeks.org/enumeration-in-cpp/
enum class Gender {
    Male,
    Female
};

// Struct for Person
struct Person {
    std::array<char, 256> name;  // C-string with a maximum length of 255 characters
    int age;
    Gender gender;
};

// https://stackoverflow.com/questions/7046244/serializing-a-class-which-contains-a-stdstring
void serializeString(std::ostream& os, const std::array<char, 256>& str) {
    os << str.data();
}

void serializeInt(std::ostream& os, int value) {
    os << value; 
}

void serializeEnum(std::ostream& os, Gender gender) {
    os << (gender == Gender::Male ? "Male" : "Female");
}

// functia pentru serializarea intregului obiect
void serializePerson(std::ostream& os, const Person& person) {
    //serializarea fiecaroi valori aparte
    serializeString(os, person.name);
    os << ",";
    serializeInt(os, person.age);
    os << ",";
    serializeEnum(os, person.gender);
}

int main() {
    // crearea documentului
    //http://cppstudio.com/post/446/
    std::ofstream outFile("data.csv");
    if (outFile.is_open()) {
        Person person1 = { "John", 30, Gender::Male };
        Person person2 = { "Alice", 25, Gender::Female };

        serializePerson(outFile, person1);
        outFile << "\n";
        serializePerson(outFile, person2);
    }
    outFile.close();
    //update la document
    if (updateData("data.csv", "updated_data.csv")) {
        std::cout << "Data updated successfully.\n";
    } else {
        std::cerr << "Error updating data.\n";
    }

    return 0;
}
