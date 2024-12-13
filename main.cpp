#include <iostream>
#include <memory>
#include <vector>
#include <string>

class Employee {
public:
    std::string name;
    int id;

    Employee(std::string n, int i) : name(n), id(i) {}

    void display() const {
        std::cout << "Name: " << name << ", ID: " << id << std::endl;
    }
};

void transferOwnership(std::unique_ptr<Employee>& from, std::unique_ptr<Employee>& to) {
    to = std::move(from);
}

int main() {
    std::vector<std::unique_ptr<Employee>> employees;
    employees.push_back(std::unique_ptr<Employee>(new Employee("Alice", 1)));
    employees.push_back(std::unique_ptr<Employee>(new Employee("Bob", 2)));
    employees.push_back(std::unique_ptr<Employee>(new Employee("Charlie", 3)));

    std::cout << "Original list of employees:\n";
    for (const auto& employee : employees) {
        employee->display();
    }

    std::vector<std::unique_ptr<Employee>> newEmployees;

    std::cout << "\nTransferring ownership of Alice and Bob:\n";
    transferOwnership(employees[0], newEmployees[0]);
    transferOwnership(employees[1], newEmployees[1]);

    std::cout << "\nEmployees after transfer:\n";
    std::cout << "Original list:\n";
    for (const auto& employee : employees) {
        if (employee) {
            employee->display();
        } else {
            std::cout << "Empty\n";
        }
    }

    std::cout << "\nNew list of employees:\n";
    for (const auto& employee : newEmployees) {
        employee->display();
    }

    return 0;
}
