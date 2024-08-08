#include "UserRequest.h"
#include <curl/curl.h>
#include "pugi/pugixml.hpp"
#include <fstream>

static int writer(char *data, size_t size, size_t nmemb, string *buffer) {
    int result = 0;
    if (buffer != nullptr) {
        // строки из data в количестве nmemb
        buffer->append(data, size * nmemb);
        //объем принятых данных
        result = size * nmemb;
    }
    return result;
}

bool UserRequest::addChannels(set<Channel> &channels) {
    try {
        UserRequest::channels.insert(channels.begin(), channels.end());
        return true;
    }
    catch(exception) {
        return false;
    }
}

void UserRequest::sendRequest() {
    //необходимые CURL объекты
    CURL *curl;
    CURLcode result;
    //инициализируем curl
    curl = curl_easy_init();
    //проверяем результат инициализации
    if (curl) {
        //задаем все необходимые опции
        //определяем, куда выводить ошибки
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
        //задаем опцию отображение заголовка страницы
        curl_easy_setopt(curl, CURLOPT_HEADER, 1);
        //указываем функцию обратного вызова для записи получаемых данных
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
        //указываем куда записывать принимаемые данные
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        for(auto channel : UserRequest::channels){
            curl_easy_setopt(curl, CURLOPT_URL, channel.getRSSLink().c_str());
            //запускаем выполнение задачи
            result = curl_easy_perform(curl);
            //проверяем успешность выполнения операции
            if (result == CURLE_OK) {
                parseChannel(buffer, channel);
            } else
                //выводим сообщение об ошибке
                cout << "Ошибка: " << errorBuffer << endl;
        }
    }
    //завершаем сессию
    curl_easy_cleanup(curl);
}

bool UserRequest::showRes() {
    int i = 0;
    for(auto news : res) {
        this->filterTags(tags, news, i);
    }
    return true;
}

bool UserRequest::saveResToFile(string outputPath) {
    int i = 0;
    try {
        if (filesystem::exists(outputPath)) remove(outputPath.c_str());
        ofstream out(outputPath);
        for (auto news: res) {
            this->filterTags(tags, news, i, out);
        }
        return true;
    }
    catch(exception) { return false; }
}

bool UserRequest::parseChannel(string buffer, Channel initChannel) {
        using namespace pugi;
        xml_document doc;
        xml_parse_result res = doc.load_string(buffer.c_str(), 100);
        try {
            if (!res) {
                std::cout << "ERROR: " << res.description() << endl;
            } else {

                pugi::xml_node channel = doc.child("rss").child("channel");

                for (pugi::xml_node field = channel.first_child(); field; field = field.next_sibling()) {

                    if (strcmp(field.name(), "item") == 0) {
                        NewsItem news(initChannel);
                        bool tagsSet = false;
                        for (pugi::xml_node child: field.children()) {
                            string value = field.child(child.name()).text().as_string();
                            if (value != "") {
                                if (strcmp(child.name(), "title") == 0)
                                    news.setTitle(value);
                                if (strcmp(child.name(), "description") == 0)
                                    news.setDesc(value);
                                if (strcmp(child.name(), "link") == 0)
                                    news.setLink(value);
                                if (strcmp(child.name(), "pubDate") == 0)
                                    news.setPubDate(value);
                                if (strcmp(child.name(), "author") == 0)
                                    news.setAuthor(value);
                                if (strcmp(child.name(), "category") == 0 && !tagsSet) {
                                    transform(value.begin(), value.end(), value.begin(),
                                              [](unsigned char c) { return tolower(c); });
                                    news.addTag(value);
                                    tagsSet = true;
                                }
                            }
                        }
                        this->res.insert(news);
                    }
                }
            }
            return true;
        }
        catch(exception) { return false; }
}

bool UserRequest::addTag(string tag) {
    try { this->tags.insert(tag); return true; }
    catch(exception) { return false; }
}

bool UserRequest::showChannels() {
    if (channels.empty()) return false;
    for (auto channel : channels) {
        cout << "— " << channel.getName() << endl;
    }
    return true;
}

bool UserRequest::showTags() {
    if (tags.empty()) return false;
    else
        for (auto tag : tags) {
            cout << "— " << tag << endl;
        }
        return true;
}

void UserRequest::filterTags(set<string> &tags, NewsItem &news, int &i, ofstream &out) {
    if (!tags.empty()) {
        for (auto tag: this->tags) {
            for (auto newsTag: news.getTags()) {
                if (strcmp(newsTag.c_str(), tag.c_str()) == 0) {
                    out << i + 1 << ". ";
                    news.addToFile(out);
                    i++;
                }
            }
        }
    } else {
        out << i + 1 << ". ";
        news.addToFile(out);
        i++;
    }
}

void UserRequest::filterTags(set<string> &tags, NewsItem &news, int &i) {
    if (!tags.empty()) {
        for (auto tag: this->tags) {
            for (auto newsTag: news.getTags()) {
                if (strcmp(newsTag.c_str(), tag.c_str()) == 0) {
                    cout << i + 1 << ". ";
                    news.show();
                    i++;
                }
            }
        }
    } else {
        cout << i + 1 << ". ";
        news.show();
        i++;
    }
}



