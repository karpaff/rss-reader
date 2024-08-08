//
// Created by Андрей Борисов on 12.12.2022.
//
#include <iostream>
#include <vector>
#include <set>
using namespace std;
#ifndef RSS_READER_NEWS_H
#define RSS_READER_NEWS_H

class Channel {
    string chanRSSLink;
protected:
    string chanName;
    string chanDesc;
    string chanLink;

public:
    virtual bool operator==(Channel other) {
        return strcmp(chanRSSLink.c_str(), other.chanRSSLink.c_str()) == 0;
    }
    virtual bool operator<(const Channel & other) const {
        return strcmp(chanRSSLink.c_str(), other.chanRSSLink.c_str()) != 0;
    }

    virtual void show();
    Channel() { };
    Channel(short dfltMode);

    string getName() {return chanName; }
    virtual string getLink() {return chanLink; }
    string getRSSLink() {return chanRSSLink; }
    virtual string getDesc() {return chanDesc; }

    void setName(string name) {chanName = name; }
    virtual void setDesc(string desc) {chanDesc = desc; }
    virtual void setLink(string link) {chanLink = link; }
    void setRSSLink(string link) {chanRSSLink = link; }
};

class NewsItem : public Channel {
protected:
    string title;
    string link;
    string description;
    vector<string> tags;
    string pubDate;
    string author;
public:
    NewsItem(Channel &parentChannel) {
        this->Channel::chanName = parentChannel.getName();
        this->Channel::chanDesc = parentChannel.getDesc();
        this->Channel::chanLink = parentChannel.getLink();
        this->Channel::setRSSLink(parentChannel.getName());
    };

    virtual bool operator==(NewsItem other) {
        return strcmp(link.c_str(), other.link.c_str()) == 0;
    }
    virtual bool operator<(const NewsItem & other) const {
        return strcmp(link.c_str(), other.link.c_str()) != 0;
    }

    void show();
    bool addToFile(ofstream &outFile);

    string getTitle() { return title; }
    string getLink() { return link; }
    string getDesc() { return description; }
    vector<string> getTags() { return tags; }
    string getPubDate() { return pubDate; }
    string getAuthor() { return author; }


    void setTitle(string text) { title = text;}
    void setDesc(string text) { description = text;}
    void setLink(string url) { link = url;}
    void setPubDate(string date) { pubDate = date; }
    void addTag(string tag) { tags.push_back(tag); }
    void setAuthor(string athr) {author = athr; }
};


#endif //RSS_READER_NEWS_H
