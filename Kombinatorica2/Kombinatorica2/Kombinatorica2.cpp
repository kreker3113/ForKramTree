#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Constants
const double INITIAL_INVESTMENT = 200000; // Начальный капитал
const double SERVER_COST = 150000; // Стоимость сервера
const double SERVER_YEARLY_COST = 20000; // Ежегодные затраты на сервер
const double FIRM_YEARLY_COST = 140000; // Ежегодные затраты на содержание фирмы
const double HIGH_DEMAND_PROBABILITY_YEAR1 = 0.6; // Вероятность высокого спроса в Year 1
const double HIGH_DEMAND_PROBABILITY_YEAR2 = 0.8; // Вероятность высокого спроса в Year 2
const double LOW_DEMAND_PROBABILITY_YEAR2 = 0.4; // Вероятность низкого спроса в Year 2
const double BANK_INTEREST_RATE = 0.2; // Процентная ставка банка
const double SERVER_RENTAL_RATE = 0.3; // Ставка аренды сервера
const double FIRM_SALE_PRICE = 350000; // Цена продажи фирмы

struct Node {
    string revenueName; // Название дохода
    double revenue; // Доход
    double probability; // Вероятность
    Node* highDemandChild; // Узел для высокого спроса
    Node* lowDemandChild; // Узел для низкого спроса
    int year; // Год
};

double calculateExpectedRevenue(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->revenue * node->probability + calculateExpectedRevenue(node->highDemandChild) + calculateExpectedRevenue(node->lowDemandChild);
}

Node* createDecisionTree(int years) {
    Node* root = new Node();
    root->revenueName = "Открытие фирмы";
    root->revenue = 0;
    root->probability = 1;
    root->year = 0;

    Node* current = root;
    for (int i = 1; i <= years; i++) {
        Node* highDemandChild = new Node();
        highDemandChild->revenueName = (i == 1) ? "Высокий спрос в текущем году" : "Высокий спрос в следующем году";
        highDemandChild->revenue = (i == 1) ? 500000 - FIRM_YEARLY_COST - SERVER_YEARLY_COST : 500000 - FIRM_YEARLY_COST - SERVER_YEARLY_COST;
        highDemandChild->probability = (i == 1) ? HIGH_DEMAND_PROBABILITY_YEAR1 : HIGH_DEMAND_PROBABILITY_YEAR2;
        highDemandChild->year = i;

        Node* lowDemandChild = new Node();
        lowDemandChild->revenueName = (i == 1) ? "Низкий спрос в текущем году" : "Низкий спрос в следующем году";
        lowDemandChild->revenue = (i == 1) ? 300000 - FIRM_YEARLY_COST - SERVER_YEARLY_COST : 300000 - FIRM_YEARLY_COST - SERVER_YEARLY_COST;
        lowDemandChild->probability = (i == 1) ? 1 - HIGH_DEMAND_PROBABILITY_YEAR1 : 1 - HIGH_DEMAND_PROBABILITY_YEAR2;
        lowDemandChild->year = i;

        current->highDemandChild = highDemandChild;
        current->lowDemandChild = lowDemandChild;

        current = (i % 2 == 0) ? highDemandChild : lowDemandChild;
    }

    return root;
}

void printDecisionTree(Node* node, int indent = 0) {
    if (node == nullptr) {
        return;
    }

    for (int i = 0; i < indent; i++) {
        cout << "  ";
    }
    cout << "+---------------+" << endl;
    cout << "|  " << node->revenueName << " (" << node->revenue << ", " << node->probability * 100 << "%) - " << node->year << " год" << endl;
    cout << "+---------------+" << endl;

    if (node->highDemandChild != nullptr) {
        cout << "                  |" << endl;
        cout << "                  v" << endl;
        printDecisionTree(node->highDemandChild, indent + 1);
    }

    if (node->lowDemandChild != nullptr) {
        cout << "                  |";
        cout << "                  |" << endl;
        cout << "                  v" << endl;
        printDecisionTree(node->lowDemandChild, indent + 1);
    }
}
int main() {
    setlocale(0, "");
    int years;
    cout << "Введите количество лет: ";
    cin >> years;

    Node* root = createDecisionTree(years);

    cout << "Дерево решений:" << endl;
    printDecisionTree(root);
    // Рассчитываем ожидаемый доход для каждого варианта
    double expectedRevenueOpenFirm = calculateExpectedRevenue(root);
    double expectedRevenueBank = INITIAL_INVESTMENT * pow(1 + BANK_INTEREST_RATE, years);

    // Рассчитываем ожидаемый доход для каждого варианта сервера
    double expectedRevenueBuyServer = expectedRevenueOpenFirm - SERVER_COST;

    cout << "Ожидаемый доход от банковского депозита: " << expectedRevenueBank << endl;
    cout << "Ожидаемый доход от открытия фирмы с арендой: " << expectedRevenueOpenFirm << endl;
    cout << "Ожидаемый доход от открытия фирмы с покупкой сервера: " << expectedRevenueBuyServer << endl;

    return 0;
}