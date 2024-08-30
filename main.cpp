/*DZ-4_task_20_5_bankomat_v0_1_UTF-8.cpp
Задание 4. Симуляция работы банкомата
Что нужно сделать
Реализуйте упрощённую симуляцию работы банкомата.

Учтите следующее:

В банкомате могут храниться только бумажные купюры номиналом 100, 200, 500, 1
000, 2 000 и 5 000 рублей. Максимально в банкомате может храниться только 1 000
купюр. Все они записываются в отдельный файл. У банкомата, как у устройства, две
основных операции — снятие денег пользователем и наполнение деньгами
инкассаторами банка. Состояние банкомата должно храниться в отдельном бинарном
файле, автономно. Хранение в бинарном виде улучшает производительность программы
и уменьшает размер данных. Банкомат работает следующим образом:

При старте программа проверяет наличие файла .bin. Если он есть (данные по
банкомату были сохранены), данные загружаются и на экран выводится информация о
текущем состоянии банкомата: сколько сейчас купюр каждого номинала и общая
сумма. Если файла нет — банкомат «пустой». При вводе «+» заполняются недостающие
купюры и выводится информация о текущем состоянии банкомата: сколько сейчас
купюр каждого номинала и общая сумма. Количество купюр рассчитывается так, чтобы
банкомат был заполнен полностью. Все купюры при этом выбираются случайным
образом. При вводе «−» симулируется снятие пользователем денег. Пользователь
указывает сумму с точностью до 100 рублей. Считайте, что каждый клиент обладает
неограниченным балансом в системе и теоретически может снять любую сумму. Выдача
происходит начиная с купюр большего номинала. Если запрошенная сумма не может
быть снята из-за отсутствия подходящих купюр в машине, показывается сообщение,
что эта операция невозможна. После выдачи денег на экран выдаётся информация о
текущем состоянии банкомата: сколько сейчас купюр каждого номинала и общая
сумма. При выходе из программы сохраняем состояние банкомата в файл.
Рекомендации
Вы можете хранить массив купюр целиком, помечая отсутствующие позиции нулями.
Выход из программы рекомендуется сделать по отдельной команде, а команды «+» и
«−» получать в цикле.


Что оценивается
Соблюдены все условия заданий.
Программы работают корректно.
*/

#include <cstring> // для memset
#include <fstream>
#include <iostream>
#include <random>
//#include <ctime>   // включает заголовочный файл ctime, содержащий функции для
//работы с датой и временем std::time()
#include <locale> //помощь для отображения кириличесских символов, т.е. русского языка
const int MAX_BILLS = 1000; //максимальное колличество купюр
const int BANKNOTES[] = { 100,  200,  500, 1000, 2000, 5000 }; //массив с номиналами купюр
const int NUM_DENOMINATIONS = sizeof(BANKNOTES) / sizeof(BANKNOTES[0]); //кол-во элементов в массиве BANKNOTES[], ктр. = 6 { //100, 200, 500, 1000, 2000, 5000 }
std::vector<int> bank(NUM_DENOMINATIONS, 0);
// Структура для хранения информации о купюрах
struct ATMState {
    int bills[NUM_DENOMINATIONS] = { 0 };
    int totalAmount = 0;
};
//Ф-ция отображает текущее состояние банкомата
void displayAtmState(ATMState& state) {
    std::cout << "\nВ банкомате имеются следующие купюры:\n";
    for (int i = 0; i < NUM_DENOMINATIONS; ++i) {
        std::cout << "Номинал " << BANKNOTES[i] << ": " << state.bills[i] << " купюр.\n";
    }
    // Вычисляю общее количество купюр
    int totalBills = 0;
    for (int i = 0; i < NUM_DENOMINATIONS; ++i) {
        totalBills += state.bills[i];
    }
    std::cout << "Купюр: " << totalBills << " на общую сумму: " << state.totalAmount << " рублей.\n";
}
//Ф-ция загружает ATMState из файла atm_state.bin, если он существует, в
//противном случае инициализирует пустой ATM.
void loadAtmState(ATMState& state) {
    std::ifstream file("atm_state.bin", std::ios::binary);
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(&state), sizeof(state));
        // Загружаю купюры/информацию из файлаatm_state.bin
        state.totalAmount = 0; //обнуляю общую сумму для подсчёта новой
        for (int i = 0; i < NUM_DENOMINATIONS; i++) {
            state.totalAmount += state.bills[i] * BANKNOTES[i];
        }
        // Вывожу информацию о текущем состоянии банкомата
        displayAtmState(state);
        file.close();
        std::cout << "ATM state loaded from file.\n";
    }
    else {
        std::memset(&state, 0, sizeof(state)); //см комментарий внизу кода
        std::cout << "ATM is empty." << "\n";
    }
}
// Функция для заполняет банкомат случайными купюрами до тех пор, пока он не заполнится
void fillAtm(ATMState& state) {
    // Ведём подсчёт всей суммы банкнот
    int totalBills = 0;
    for (int i = 0; i < NUM_DENOMINATIONS; ++i) {
        totalBills += state.bills[i];
    }
    if (totalBills < MAX_BILLS) { // Проверяем, сколько купюр уже есть
      //одсчитываем сколько осталось банкнот для полного заполнения
        int remainingBills = MAX_BILLS - totalBills;
        for (int i = 0; i < remainingBills; ++i) { // Заполняем до MAX_BILLS
            int random_index = std::rand() % NUM_DENOMINATIONS;
            state.bills[random_index]++; // Увеличиваем количество купюр в банкомате
            state.totalAmount += BANKNOTES[random_index]; // Обновляем общую сумму
        }
        std::cout << "\nБанкомат пополнен!\n";
    }
    else {
        std::cout << "\nБанкомат уже полон!\n";
    }
    displayAtmState(state); // Передаем bank по ссылке
}
//Ф-ция имитирует снятие денег
bool withdrawMoney(ATMState& state, int amount) {
    int remainingAmount = amount;
    if (amount % 100 != 0) {
        std::cout << "Сумма должна быть кратна 100.\n";
        return false;
    }
    if (amount < 0 || amount > state.totalAmount) {
        std::cout << "\nНедостаточно средств в банкомате.\n";
        displayAtmState(state);
        return false;
    }
    // Выдача денег
    std::cout << "Выдано " << amount << " рублей по:\n";
    for (int i = NUM_DENOMINATIONS - 1; i >= 0; --i) {
        int denomination = BANKNOTES[i];
        // int numBills = remainingAmount / denomination;
        int numBills = std::min(remainingAmount / denomination, state.bills[i]); //получаем минимальное кол-во купюр
        if (numBills > 0) {
            state.bills[i] -= numBills;
            remainingAmount -= numBills * denomination;
            std::cout << numBills << " купюр(-а) номиналом " << denomination << " рублей.\n";
        }
    }
    state.totalAmount -= amount;
    // Проверка, если выдача == 0
    if (remainingAmount == 0) {
        std::cout << "\nВыдача произведена успешно.\n";
        displayAtmState(state);
        return true;
    }
    return true;
}

//Ф-ция сохраняет текущее состояние банкомата в файл.
void saveAtmState(ATMState& state) {
    std::ofstream binFile("atm_state.bin", std::ios::binary); // открываю для записи файл atm_state.bin в бинарном виде
    if (binFile.is_open()) {
        // Записываем состояние в файл
        binFile.write(reinterpret_cast<const char*>(&state), sizeof(state));
        binFile.close();
        std::cout << "ATM state saved to file." << std::endl;
    }
    else {
        std::cerr << "Error saving ATM state to file." << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "Rus"); // setlocale(LC_ALL, "Rus");
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
            withdrawMoney(atmState, amount);
            break;
        case 'q':
            break;
        default:
            std::cout << "Invalid command.\n";
            break;
        }
    } while (command != 'q');
    saveAtmState(atmState);
    std::cout << "Exiting program.\n";
    std::cout << "Возвращайтесь скорее. Пока :-) !\n";
    return 0;
}
/*отличие что std::memset(&state, 0, sizeof(state)) от
for (int i = 0; i < MAX_BILLS; ++i) {
        state.bills[i] = 0;
}
Функция std::memset(&state, 0, sizeof(state)) устанавливает все байты в памяти, на которую указывает &state, в значение 0. Это означает, что она обнуляет всю память, выделенную под переменную state, независимо от её структуры или размера.
С другой стороны, цикл for выполняет итерацию по элементам массива state.bills и присваивает каждому элементу значение 0. Это значит, что он обнуляет только элементы массива state.bills, а не всю переменную state.
Таким образом, основное отличие заключается в том, что std::memset работает с памятью, на которую указывает указатель, и устанавливает все байты этой памяти в заданное значение, тогда как цикл for работает с элементами массива и устанавливает значения этих элементов индивидуально.
*/
