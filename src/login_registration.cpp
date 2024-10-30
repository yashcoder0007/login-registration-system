#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class User {
public:
    std::string username;
    std::string password;

    User(std::string u, std::string p) : username(u), password(p) {}
};

class UserManager {
private:
    std::vector<User> users;

    void loadUsers() {
        std::ifstream infile("users.txt");
        std::string u, p;
        while (infile >> u >> p) {
            users.push_back(User(u, p));
        }
        infile.close();
    }

    void saveUser(const User &user) {
        std::ofstream outfile("users.txt", std::ios::app);
        outfile << user.username << " " << user.password << std::endl;
        outfile.close();
    }

public:
    UserManager() {
        loadUsers();
    }

    void registerUser() {
        std::string username, password;
        std::cout << "Enter username: ";
        std::cin >> username;
        
        // Check if the username already exists
        for (const auto &user : users) {
            if (user.username == username) {
                std::cout << "Username already exists. Try again.\n";
                return;
            }
        }

        std::cout << "Enter password: ";
        std::cin >> password;

        User newUser(username, password);
        users.push_back(newUser);
        saveUser(newUser);
        std::cout << "Registration successful!\n";
    }

    void loginUser() {
        std::string username, password;
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;

        for (const auto &user : users) {
            if (user.username == username && user.password == password) {
                std::cout << "Login successful! Welcome, " << username << "!\n";
                return;
            }
        }
        std::cout << "Invalid credentials. Please try again.\n";
    }
};

int main() {
    UserManager userManager;
    int choice;

    do {
        std::cout << "1. Register\n2. Login\n3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                userManager.registerUser();
                break;
            case 2:
                userManager.loginUser();
                break;
            case 3:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please choose again.\n";
        }
    } while (choice != 3);

    return 0;
}
