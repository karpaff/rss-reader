#include "Menu.h"
bool subscribe(short mode2, set<Channel>& channels) {
    if (mode2 > 4 || mode2 < 0) {
        return false;
    }
    Channel channel(mode2);
    try {
        channels.insert(channel);
        return true;
    }
    catch(exception) {
        return false;
    }
}

void printDefaultChannels() {
    cout << "1 — BBC News Europe" << endl;
    cout << "2 — The Guardian" << endl;
    cout << "3 — Reuters" << endl;
    cout << "4 — Yahoo News" << endl;
    cout << "Введите 0, чтобы закончить выбор." << endl;
}

void printMenu() {
    cout << "Выберите команду: " << endl;
    cout << "\ts — Выбрать источники для загрузки новостей" << endl;
    cout << "\tm — Добавить фильтр по ключевым словам" << endl;
    cout << "\tw — Вывести все выбранные источники" << endl;
    cout << "\tp — Вывести на экран новости из выбранных источников" << endl;
    cout << "\tr — Записать в файл новости из выбранных источников" << endl;
    cout << "\tc — Выйти" << endl;
    cout << endl;
}

void printRequestOptions(UserRequest& request) {
    cout << "Будет выполнен поиск новостей по следующим источникам:" << endl;
    request.showChannels();
    cout << "со следующими ключевыми словами:" << endl;
    if (!request.showTags()) cout << "(отсутствуют)" << endl;
    cout << endl;
}
