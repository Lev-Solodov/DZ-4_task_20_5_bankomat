/*DZ-4_task_20_5_bankomat_v0_1_UTF-8.cpp
Задание 4. Симуляция работы банкомата
Что нужно сделать
Реализуйте упрощённую симуляцию работы банкомата.

Учтите следующее:

В банкомате могут храниться только бумажные купюры номиналом 100, 200, 500, 1 000, 2 000 и 5 000 рублей.
Максимально в банкомате может храниться только 1 000 купюр. Все они записываются в отдельный файл.
У банкомата, как у устройства, две основных операции — снятие денег пользователем и наполнение деньгами инкассаторами банка.
Состояние банкомата должно храниться в отдельном бинарном файле, автономно. Хранение в бинарном виде улучшает производительность программы и уменьшает размер данных.
Банкомат работает следующим образом:

При старте программа проверяет наличие файла .bin. Если он есть (данные по банкомату были сохранены), данные загружаются и на экран выводится информация о текущем состоянии банкомата: сколько сейчас купюр каждого номинала и общая сумма. Если файла нет — банкомат «пустой».
При вводе «+» заполняются недостающие купюры и выводится информация о текущем состоянии банкомата: сколько сейчас купюр каждого номинала и общая сумма. Количество купюр рассчитывается так, чтобы банкомат был заполнен полностью. Все купюры при этом выбираются случайным образом.
При вводе «−» симулируется снятие пользователем денег. Пользователь указывает сумму с точностью до 100 рублей. Считайте, что каждый клиент обладает неограниченным балансом в системе и теоретически может снять любую сумму. Выдача происходит начиная с купюр большего номинала. Если запрошенная сумма не может быть снята из-за отсутствия подходящих купюр в машине, показывается сообщение, что эта операция невозможна. После выдачи денег на экран выдаётся информация о текущем состоянии банкомата: сколько сейчас купюр каждого номинала и общая сумма.
При выходе из программы сохраняем состояние банкомата в файл.
Рекомендации
Вы можете хранить массив купюр целиком, помечая отсутствующие позиции нулями.
Выход из программы рекомендуется сделать по отдельной команде, а команды «+» и «−» получать в цикле.


Что оценивается
Соблюдены все условия заданий.
Программы работают корректно.
*/

#include <iostream>
#include <fstream>
#include <random>
#include <cstring> // для memset
//#include <numeric> // для std::accumulate
#include <cstdlib> // библиотека для работы с памятью, преобразования текста в числа, генерации случайных чисел и другие утилиты std::rand()
#include <ctime>   // включает заголовочный файл ctime, содержащий функции для работы с датой и временем std::time()
//#include <locale> //помощь для отображения кириличесских символов, т.е. русского языка
//#include <filesystem> //для работы с файлами
//#include <memory> //для работы с std::unique_ptr
#include <algorithm> // для std::sort
const int MAX_BILLS = 1000;
const int BANKNOTES[] = { 100, 200, 500, 1000, 2000, 5000 };
const int NUM_DENOMINATIONS = sizeof(BANKNOTES) / sizeof(BANKNOTES[0]);
std::vector<int> bank;
// Структура для хранения информации о купюрах
struct ATMState {
    int bills[NUM_DENOMINATIONS];
    int totalAmount;
};
//инициализация банкомата
/*При старте программа проверяет наличие файла .bin. Если он есть (данные по банкомату были сохранены), данные загружаются и на экран выводится информация о текущем состоянии банкомата: сколько сейчас купюр каждого номинала и общая сумма. Если файла нет — банкомат «пустой».*/
void loadAtmState(ATMState& state) {
    std::ifstream file("atm_state.bin", std::ios::binary);
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(&state), sizeof(state));
        file.close();
        std::cout << "ATM state loaded from file.\n";
        // Загружаю купюры из файла moneyFill.txt
        std::ifstream moneyFillFile("moneyFill.txt");
        if (moneyFillFile.is_open()) {
            int denomination; //наименования номинала купюр 100, 200, 500, 1000, 2000, 5000
            while (moneyFillFile >> denomination ) {
                bank.emplace_back(denomination); //было bank.push_back(denomination);
            }
            moneyFillFile.close();
        }
        else {
            std::cerr << "Не удалось открыть файл moneyFill.txt для чтения..\n";
        }
        // Сортирую купюры по убыванию
        std::sort(bank.begin(), bank.end(), std::greater<int>());
        // Вывожу информацию о текущем состоянии банкомата
        std::cout << "Current ATM state:\n";
        for (int i = 0; i < NUM_DENOMINATIONS; i++){
            std::cout << BANKNOTES[i] << ": " << state.bills[i] << "\n";
        }
        std::cout << "Total amount: " << state.totalAmount << " rubles." << std::endl;
    }
    else {
        std::memset(&state, 0, sizeof(state));
        std::cout << "ATM is empty." << std::endl;
    }
}
//показать состояние банкомата
void displayAtmState(const ATMState& state, std::vector<int>& bank) {
    // Отображаю информацию о состоянии банкомата на экране
    //показываю сколько купюр в банкомате
    for (int i = 0; i < bank.size(); ++i) {
        bank[i];
    }
    std::cout << "\nВ банкомате имеются следующие купюры:\n";
    for (int i = 0; i < NUM_DENOMINATIONS; ++i) {
        int count = 0;
        for (int denomination : bank) {
            if (denomination == BANKNOTES[i]) {
                count++;
            }
        }
        std::cout << "Номинал " << BANKNOTES[i] << ": " << count << " купюр.\n";
    }
    std::cout << "Купюр: " << bank.size() << " на общую сумму: " << state.totalAmount << " рублей.\n";
    // Запись оставшихся купюр в файл
    //std::ofstream moneyFile("moneyFill.txt", std::ios::app);
    std::ofstream moneyFile("moneyFill.txt");
    if (!moneyFile.is_open()) {
        std::cerr << "Не удалось открыть файл для записи\n";
        return;
    }
    for (int denomination : bank) {
        moneyFile << denomination << std::endl;
    }
    moneyFile.close();
}
/*При вводе «+» заполняются недостающие купюры и выводится информация о текущем состоянии банкомата: сколько сейчас купюр каждого номинала и общая сумма.
Количество купюр рассчитывается так, чтобы банкомат был заполнен полностью.
Все купюры при этом выбираются случайным образом.*/
// Функция для заполнения банкомата
void fillAtm(ATMState& state) {
    if (bank.empty()) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        for (int i = 0; i < MAX_BILLS; ++i) {
            int random_index = std::rand() % NUM_DENOMINATIONS;
            bank.push_back(BANKNOTES[random_index]);
        }
        std::cout << "Банкомат заполнен!\n";
    }
    else {
        std::cout << "Банкомат уже не пуст!\n";
    }
    // Записываю данные в файл
    std::ofstream moneyFile("moneyFill.txt");
    if (!moneyFile.is_open()) {
        std::cerr << "Не удалось открыть файл для записи\n";
        return;
    }
    // Выполняю итерацию по вектору банка и записываю каждый элемент в файл
    for (int BANKNOTES : bank) {
        moneyFile << BANKNOTES << std::endl;
    }
    moneyFile.close(); // Close the file
    displayAtmState(state, bank);
}
//снятие денег
/*При вводе «−» симулируется снятие пользователем денег.
Пользователь указывает сумму с точностью до 100 рублей. Считайте, что каждый клиент обладает неограниченным балансом в системе и теоретически может снять любую сумму. Выдача происходит начиная с купюр большего номинала. Если запрошенная сумма не может быть снята из-за отсутствия подходящих купюр в машине, показывается сообщение, что эта операция невозможна. После выдачи денег на экран выдаётся информация о текущем состоянии банкомата: сколько сейчас купюр каждого номинала и общая сумма.*/
bool withdrawMoney(ATMState& state, int amount, std::vector<int>& bank) {
    if (amount % 100 != 0) {
        std::cout << "Сумма должна быть кратна 100.\n";
        return false;
    }
    if (amount < 0 || amount > state.totalAmount) {
        std::cout << "Недостаточно средств в банкомате.\n";
        return false;
    }
    state.totalAmount -= amount;
    // Выдача денег
    std::cout << "Выдано " << amount << " рублей.\n";
    std::cout << "Выдача произведена успешно.";
    for (int i = NUM_DENOMINATIONS - 1; i >= 0 && amount > 0; --i) {
        while (amount >= BANKNOTES[i] && bank.size() > 0) {
            if (bank.back() == BANKNOTES[i]) {
                bank.pop_back();
                amount -= BANKNOTES[i];
            }
            else {
                break; // переходим к следующей купюре
            }
        }
    }
    displayAtmState(state, bank);
    return true;
}

/*При выходе из программы сохраняем состояние банкомата в файл.*/
void saveAtmState(ATMState& state) {
    std::ofstream file("atm_state.bin", std::ios::binary); //дописываю файл atm_state.bin в бинарном виде
    if (file.is_open()) {
        // Подсчитываем количество купюр каждого номинала
        for (int i = 0; i < NUM_DENOMINATIONS; ++i) {
            state.bills[i] = 0;
            for (int denomination : bank) {
                if (denomination == BANKNOTES[i]) {
                    state.bills[i]++;
                }
            }
        }
        // Записываем состояние в файл
        file.write(reinterpret_cast<const char*>(&state), sizeof(state));
        file.close();
        std::cout << "ATM state saved to file." << std::endl;
    }
    else {
        std::cerr << "Error saving ATM state to file." << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, ""); //setlocale(LC_ALL, "Rus");
    std::cout << "Задание 4. Симуляция работы банкомата v0_1 UTF-8\n"; //Инициализирую строку как широкие символы, используя префикс L перед строками.
    ATMState atmState;
    loadAtmState(atmState);

    char command;
    do {
        std::cout << "Enter command (+, -, or q to quit): ";
        std::cin >> command;

        switch (command) {
        case '+':
            fillAtm(atmState);
            break;
        case '-':
            int amount;
            std::cout << "Enter the amount to withdraw (in 100 ruble increments): ";
            std::cin >> amount;
            withdrawMoney(atmState, amount, bank);
            break;
        case 'q':
            saveAtmState(atmState);
            std::cout << "Exiting program.\n";
            break;
        default:
            std::cout << "Invalid command.\n";
            break;
        }
    } while (command != 'q');

    std::cout << "Возвращайтесь скорее. Пока :-) !\n";
    return 0;
}