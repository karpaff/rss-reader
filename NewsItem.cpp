//
// Created by Андрей Борисов on 12.12.2022.
//

#include "NewsItem.h"
#include <fstream>

void Channel::show() {
    if (!chanName.empty())
        cout << "Название источника: " << chanName << endl;
    if (!chanDesc.empty())
        cout << "Описание источника: " << chanDesc << endl;
    if (!chanLink.empty())
        cout << "Ссылка на источник: " << chanLink << endl;
}

void NewsItem::show() {
    if (!title.empty())
        cout << "Заголовок: " << title << endl;
    if (!description.empty())
        cout << "Описание: " << description << endl;
    if (!link.empty())
        cout << "Ссылка: " << link << endl;
    if (!pubDate.empty())
        cout << "Дата: " << pubDate << endl;
    if (!author.empty())
        cout << "Автор: " << author << endl;
    if (!tags.empty()) {
        int i = 0;
        for(auto tag : tags) {
            if (i <= 5)
            {
                cout << "Категория: " << tag << endl;
                i++;
            }
            else break;
        }
    }
    cout << "Источник: " << chanName << endl;
    cout << endl;
}

bool NewsItem::addToFile(ofstream &outFile) {
    if (!title.empty())
        outFile << "Название: " << title << endl;
    if (!description.empty())
        outFile << "Описание: " << description << endl;
    if (!link.empty())
        outFile << "Ссылка: " << link << endl;
    if (!pubDate.empty())
        outFile << "Дата: " << pubDate << endl;
    if (!author.empty())
        outFile << "Автор: " << author << endl;
    if (!tags.empty()) {
        int i = 0;
        for(const auto& tag : tags) {
            if (i <= 5)
            {
                outFile << "Категория: " << tag << endl;
                i++;
            }
            else break;
        }
    }
    outFile << "Источник: " << chanName << endl;
    outFile << endl;
}

Channel::Channel(short dfltMode) {
    switch (dfltMode) {
        case 1:
        {
            chanName = "BBC News Europe";
            chanDesc = "BBC News - Europe";
            chanRSSLink = "http://feeds.bbci.co.uk/news/rss.xml";
            chanLink = "https://www.bbc.com/news/world/europe";
            break;
        }
        case 2:
        {
            chanName = "The Guardian";
            chanDesc = "Latest news, sport, business, comment, analysis and reviews from the Guardian, the world's leading liberal voice";
            chanRSSLink = "https://www.theguardian.com/uk/rss";
            chanLink = "https://www.theguardian.com/uk";
            break;
        }
        case 3:
        {
            chanName = "Reuters";
            chanRSSLink = "https://cdn.feedcontrol.net/8/1114-wioSIX3uu8MEj.xml";
            chanDesc = "Business and financial news, U.S. and international breaking news.";
            chanLink = "https://www.reuters.com";
            break;
        }
        case 4:
        {
            chanName = "Yahoo News";
            chanDesc = "The latest news and headlines from Yahoo! News. Get breaking news stories and in-depth coverage with videos and photos.";
            chanRSSLink = "https://www.yahoo.com/news/rss";
            chanLink = "https://www.yahoo.com/";
            break;
        }
        default:
            break;
    }
}
