#include <iostream>
#include <memory>
#include <vector>
#include <string>

class Company;

class Department {
public:
    std::string name;
    std::weak_ptr<Company> company;

    Department(std::string departmentName) : name(departmentName) {}

    void setCompany(std::shared_ptr<Company> comp) {
        company = comp;
    }

    void displayInfo() const;
};

class Company : public std::enable_shared_from_this<Company> {
public:
    std::string name;
    std::vector<std::shared_ptr<Department>> departments;

    Company(std::string companyName) : name(companyName) {}

    void addDepartment(std::shared_ptr<Department> department) {
        departments.push_back(department);
        department->setCompany(shared_from_this());
    }

    void displayInfo() const {
        std::cout << "Company: " << name << "\nDepartments:\n";
        for (const auto& department : departments) {
            department->displayInfo();
        }
    }
};

void Department::displayInfo() const {
    auto companyPtr = company.lock();
    std::cout << "  Department: " << name << " (Company: "
              << (companyPtr ? companyPtr->name : "Unknown") << ")\n";
}

int main() {
    auto company1 = std::make_shared<Company>("TechCorp");

    auto dept1 = std::make_shared<Department>("Research");
    company1->addDepartment(dept1);

    auto dept2 = std::make_shared<Department>("Development");
    company1->addDepartment(dept2);

    company1->displayInfo();

    return 0;
}
