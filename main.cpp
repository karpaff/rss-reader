#include <iostream>
#include "UserRequest.h"
#include "Menu.h"
#include <set>
using namespace std;

int main() {
    UserRequest request;
    set<Channel> channels;
    set<string> tags;
    vector<string> validButtons = {"s", "m", "w", "p", "r", "c"};
    bool channelsSelected = false;
    string mode;
    while (mode != "c") {
        while (true) {
            printMenu();
            getline(cin >> ws, mode);
            if (mode.size() != 1 || find(validButtons.begin(), validButtons.end(), mode) == validButtons.end())
                cout << "Такой команды нет. Попробуйте ещё раз." << endl;
            else break;
        }
        switch (mode[0]) {
            case 's':
            {
                cout << "Выберите, какие источники хотите выбрать. Для этого введите через пробел номера источников." << endl;
                string mode2;
                while (true) {
                    printDefaultChannels();
                    getline(cin >> ws, mode2);

                    try {
                        if (stoi(mode2) == 0) break;
                        else if (!subscribe(stoi(mode2), channels)) cout << "Этот источник уже добавлен или команда не распознана. Попробуйте ещё раз" << endl;
                    }
                    catch(exception)
                    {
                        cout << "Такой команды нет. Попробуйте ещё раз" << endl;
                        break;
                    }
                }
                channelsSelected = true;
                break;
            }
            case 'm':
            {
                string tag;
                while (true) {
                    cout << "Введите ключевое слово, по которому нужно найти новости." << endl;
                    cout << "Введите 0, чтобы выйти." << endl;
                    getline(cin >> ws, tag);
                    if (strcmp(tag.c_str(), "0") == 0) { cout << "Выбор ключевых слов завершён." << endl << endl; break; }
                    else request.addTag(tag);
                }
                break;
            }
            case 'w':
            {
                cout << "Выбранные источники:" << endl;
                int i = 0;
                if (!channels.empty()) {
                    for (auto channel: channels) {
                        cout << i + 1 << ". ";
                        channel.show();
                        i++;
                    }
                }
                else cout << "Не выбран ни один источник." << endl;

                break;
            }
            case 'p':
            {
                if (!channelsSelected)
                    cout << "Ещё не выбран ни один источник. Нажмите s, чтобы выбрать источники." << endl;
                else {
                    request.addChannels(channels);
                    printRequestOptions(request);
                    cout << "Выполняем запрос..." << endl;
                    request.sendRequest();
                    if (!request.getRes().empty()) {
                        cout << "Выводим на экран..." << endl;
                        request.showRes();
                    } else cout << "Новостей по таком запросу нет." << endl;
                }
                break;
            }
            case 'r': {
                if (!channelsSelected)
                    cout << "Вы ещё не выбрали ни один источник. Нажмите s, чтобы выбрать источники." << endl;
                else {
                    request.addChannels(channels);
                    printRequestOptions(request);

                    cout << "Выполняем запрос..." << endl;
                    request.sendRequest();

                    if (!request.getRes().empty()) {
                        cout << "Формируем файл..." << endl;
                        if (request.saveResToFile("../news/news.txt")) cout << "Файл сохранен news/news.txt" << endl;
                        else cout << "Произошла ошибка при сохранении. Попробуйте ещё раз."<< endl;
                    } else cout << "Новостей по таком запросу нет." << endl;
                }
                break;
            }
            case 'c':
            {
                cout << "Выход из программы..." << endl;
                break;
            }
        }
    }
    return 0;
}

