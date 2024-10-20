#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_DISHES 10
#define MAX_ORDERS 5

// 1. Класс Dish (Блюдо)
class Dish {
private:
    char name[50];
    float price;
    int quantity;

public:
    // Конструктор
    Dish(const char* dish_name, float dish_price, int dish_quantity) {
        strcpy_s(name, dish_name);
        price = dish_price;
        quantity = dish_quantity;
    }

    // Метод для вывода информации о блюде
    void print() const {
        printf("Блюдо: %s, Цена: %.2f, Количество порций: %d\n", name, price, quantity);
    }

    // Доступ к приватным данным, если нужно
    float getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    const char* getName() const { return name; }
};

// 2. Класс Menu (Меню)
class Menu {
private:
    Dish* dishes[MAX_DISHES];
    int dish_count;

public:
    // Конструктор
    Menu() {
        dish_count = 0;
    }

    // Метод для добавления блюда в меню
    void addDish(Dish* dish) {
        if (dish_count < MAX_DISHES) {
            dishes[dish_count] = dish;
            dish_count++;
        }
        else {
            printf("Меню переполнено!\n");
        }
    }

    // Метод для вывода меню
    void print() const {
        printf("Меню:\n");
        for (int i = 0; i < dish_count; i++) {
            dishes[i]->print();
        }
        printf("\n");
    }

    // Получение блюда по индексу
    Dish* getDish(int index) const {
        if (index >= 0 && index < dish_count) {
            return dishes[index];
        }
        return NULL;
    }
};


// 3. Класс Client (Клиент)
class Client {
private:
    char name[50];
    char phone[15];

public:
    // Конструктор
    Client(const char* client_name, const char* client_phone) {
        strcpy_s(name, client_name);
        strcpy_s(phone, client_phone);
    }

    // Метод для вывода информации о клиенте
    void print() const {
        printf("Клиент: %s, Телефон: %s\n", name, phone);
    }

    const char* getName() const { return name; }
};


// 4. Класс Employee (Сотрудник)
class Employee {
private:
    char name[50];
    int id;

public:
    // Конструктор
    Employee(const char* employee_name, int employee_id) {
        strcpy_s(name, employee_name);
        id = employee_id;
    }

    // Метод для вывода информации о сотруднике
    void print() const {
        printf("Официант: %s, ID: %d\n", name, id);
    }

    const char* getName() const { return name; }
};


// 5. Класс Order (Заказ)
class Order {
private:
    Client client;
    Employee employee;
    Dish* ordered_dishes[MAX_ORDERS];
    int order_count;
    float total_price;

public:
    // Конструктор
    Order(const Client& c, const Employee& e) : client(c), employee(e), order_count(0), total_price(0.0) {}

    // Метод для добавления блюда в заказ
    void addDish(Dish* dish) {
        if (order_count < MAX_ORDERS) {
            ordered_dishes[order_count] = dish;
            total_price += dish->getPrice() * dish->getQuantity();
            order_count++;
        }
        else {
            printf("Заказ переполнен!\n");
        }
    }

    // Метод для вывода заказа
    void print() const {
        printf("Заказ клиента: %s\n", client.getName());
        printf("Обслуживает официант: %s\n", employee.getName());
        printf("Блюда в заказе:\n");
        for (int i = 0; i < order_count; i++) {
            ordered_dishes[i]->print();
        }
        printf("Общая стоимость заказа: %.2f\n\n", total_price);
    }
};

int main() {

    setlocale(LC_ALL, "Russian");

    // Инициализируем меню
    Menu menu;
    Dish* borsh = new Dish("Борщ", 250.0, 1);
    Dish* pelmeni = new Dish("Пельмени", 300.0, 1);
    menu.addDish(borsh);
    menu.addDish(pelmeni);
    menu.print();

    // Создание клиента и официанта
    Client client("Иван Иванов", "89005555555");
    Employee employee("Сергей Петров", 101);

    // Инициализация заказа
    Order order(client, employee);
    order.addDish(menu.getDish(0));  // Борщ
    order.addDish(menu.getDish(1));  // Пельмени
    order.print();

    // Работа с динамическим массивом заказов
    Order* dynamic_order = new Order(client, employee);
    dynamic_order->addDish(menu.getDish(0));  // Борщ
    dynamic_order->print();

    // Удаление динамических объектов
    delete dynamic_order;
    delete borsh;
    delete pelmeni;

    return 0;
}

