#ifndef RSS_READER_USERREQUEST_H
#define RSS_READER_USERREQUEST_H

#include <iostream>
#include <vector>
#include <set>
#include <curl/curl.h>
#include "NewsItem.h"
using namespace std;

//объявляем буфер для хранения возможной ошибки, размер определяется в самой библиотеке
static char errorBuffer[CURL_ERROR_SIZE];

//объялвяем буфер принимаемых данных
static string buffer;

static int writer(char *data, size_t size, size_t nmemb, string *buffer);

class UserRequest {
    set<Channel> channels;
    set<string> tags;
    set<NewsItem> res;
    bool parseChannel(string buffer, Channel channel);
    void filterTags(set<string> &tags, NewsItem &news, int &i, ofstream &out);
    void filterTags(set<string> &tags, NewsItem &news, int &i);
public:
    bool showChannels();
    bool showTags();
    void sendRequest();
    bool showRes();
    bool saveResToFile(string outputPath);

    set<NewsItem> getRes() { return res; }

    bool addChannel(Channel channel);
    bool addChannels(set<Channel> &channels);
    bool addTags(vector<string> tags);
    bool addTag(string tags);
};
#endif //RSS_READER_USERREQUEST_H
