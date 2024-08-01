#include <iostream>
#include <random>

int main() {
 std::cout << "Введите команду: ";
 char command;
 std::cin >> command;

 if (command == '+') { // Если выбрана команда '+'
 // Заполняем банкомат случайными купюрами
 std::random_device rd;
 std::mt19937 gen(rd());
 std::uniform_int_distribution<> dis(100, 5000);

 int total_amount = 0;
 for (int i = 0; i < 1000; ++i) {
 int bill = dis(gen);
 std::cout << "В банкомат добавлена купюра номиналом " << bill << "\n";
 total_amount += bill;
 }
 std::cout << "Всего добавлено " << total_amount << " рублей.\n";
 } else {
 std::cout << "Неизвестная команда.\n";
 }

 return 0;
}
//Этот код запрашивает у пользователя ввести команду + для заполнения банкомата случайными купюрами от 100 до 5000 рублей. В случае выбора команды +, программа заполняет банкомат 1000 купюрами, выводя информацию о каждой добавленной купюре и общей сумме добавленных денег.