#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_DISHES 10
#define MAX_ORDERS 5

// 1. Структура Dish (Блюдо)
typedef struct {
    char name[50];
    float price;
    int quantity;
} Dish;

// 2. Структура Menu (Меню)
typedef struct {
    Dish dishes[MAX_DISHES];
    int dish_count;
} Menu;

// 3. Структура Client (Клиент)
typedef struct {
    char name[50];
    char phone[15];
} Client;

// 4. Структура Employee (Сотрудник)
typedef struct {
    char name[50];
    int id;
} Employee;

// 5. Структура Order (Заказ)
typedef struct {
    Client client;
    Employee employee;
    Dish ordered_dishes[MAX_DISHES];
    int order_count;
    float total_price;
} Order;

void init_menu(Menu* menu) {
    menu->dish_count = 0; // Начальное количество блюд 0
}

void add_dish_to_menu(Menu* menu, const char* name, float price, int quantity) {
    if (menu->dish_count < MAX_DISHES) {
        strcpy_s(menu->dishes[menu->dish_count].name, name);
        menu->dishes[menu->dish_count].price = price;
        menu->dishes[menu->dish_count].quantity = quantity;
        menu->dish_count++;
    }
    else {
        printf("Меню переполнено!\n");
    }
}

void print_menu(Menu* menu) {
    printf("Меню:\n");
    for (int i = 0; i < menu->dish_count; i++) {
        printf("Блюдо: %s, Цена: %.2f, Количество порций: %d\n",
            menu->dishes[i].name, menu->dishes[i].price, menu->dishes[i].quantity);
    }
    printf("\n");
}

void init_order(Order* order, Client client, Employee employee) {
    order->client = client;
    order->employee = employee;
    order->order_count = 0;
    order->total_price = 0.0;
}

void add_dish_to_order(Order* order, Dish dish) {
    if (order->order_count < MAX_DISHES) {
        order->ordered_dishes[order->order_count] = dish;
        order->total_price += dish.price * dish.quantity;
        order->order_count++;
    }
    else {
        printf("Заказ переполнен!\n");
    }
}

void print_order(Order* order) {
    printf("Заказ клиента: %s\n", order->client.name);
    printf("Обслуживает официант: %s\n", order->employee.name);
    printf("Блюда в заказе:\n");
    for (int i = 0; i < order->order_count; i++) {
        printf("Блюдо: %s, Количество: %d, Цена: %.2f\n",
            order->ordered_dishes[i].name,
            order->ordered_dishes[i].quantity,
            order->ordered_dishes[i].price);
    }
    printf("Общая стоимость заказа: %.2f\n\n", order->total_price);
}

Order* create_dynamic_order(Client client, Employee employee) {
    Order* order = (Order*)malloc(sizeof(Order));
    if (order != NULL) {
        init_order(order, client, employee);
    }
    return order;
}

void free_order(Order* order) {
    free(order);  // Освобождаем память
}

int main() {

    setlocale(LC_ALL, "Russian");

    // Инициализируем меню
    Menu menu;
    init_menu(&menu);
    add_dish_to_menu(&menu, "Борщ", 250.0, 1);
    add_dish_to_menu(&menu, "Пельмени", 300.0, 1);
    print_menu(&menu);

    // Создание клиента и официанта
    Client client = { "Иван Иванов", "89005555555" };
    Employee employee = { "Сергей Петров", 101 };

    // Инициализация заказа
    Order order;
    init_order(&order, client, employee);
    add_dish_to_order(&order, menu.dishes[0]);  // Борщ
    add_dish_to_order(&order, menu.dishes[1]);  // Пельмени

    // Печать заказа
    print_order(&order);

    // Работа с динамической памятью
    Order* dyn_order = create_dynamic_order(client, employee);
    add_dish_to_order(dyn_order, menu.dishes[0]);  // Борщ
    print_order(dyn_order);

    // Освобождаем память
    free_order(dyn_order);

    return 0;
}

