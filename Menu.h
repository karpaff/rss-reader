#ifndef RSS_READER_MENU_H
#define RSS_READER_MENU_H
#include "NewsItem.h"
#include "UserRequest.h"
void printDefaultChannels();
void printMenu();
bool subscribe(short mode, set<Channel>& channel);
void printRequestOptions(UserRequest& request);
#endif //RSS_READER_MENU_H
