// Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <ctime>
#include <thread>
#include <future>

using std::string;

void func(std::promise<int>&& p) {
    p.set_value(1);
}

int generateBit() {
    long r = rand();
    if (r % 2 == 0)return 0;
    return 1;
}

long generateRandRange(long min, long max) {
    long r = rand();
    while (r<min || r>max) {
        r = rand();
        if (r > min && r < max) {
            return r;
        }
    }
}

long generateUnsignedRandRange(long min, long max)
{
    return min + rand() % (max - min + 1);
}

string getRandSymbol() {
    const char* ds[7] = { "AUDCAD", "AUDCHF", "AUDJPY", "AUDNZD", "AUDUSD", "CADCHF", "CADJPY" };
    int index = 0 + (rand() % static_cast<int>(7 - 0 + 1));
    return ds[index];
}

float getRandDec(float min, float max) {
    float fl = min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
    return fl;
}

string GetTodayDate() {
    time_t curr_time;
    tm* curr_tm;
    char date_string[100];
    char time_string[100];

    time(&curr_time);
    curr_tm = localtime(&curr_time);
    strftime(date_string, 50, "%B %d, %Y", curr_tm);
    return date_string;
}

string buildTradeStr(
    string username,
    string login,
    string deal,
    string active,
    string time,
    string symbol,
    string price,
    string profit,
    string volume) {
    return "{\"username\":\"" + username + "\", \"login\": \"" + login + "\", \"deal\":\"" + deal + "\", \"active\":\"" + active + "\", \"time\": \""+ time +"\", \"symbol\":\""+ symbol +"\", \"price\":\""+ price +"\", \"profit\":\""+ profit +"\", \"volume\":\""+ volume +"\"}";
}

string getTrade(string username) {
    
    std::ostringstream strLogin;
    auto login = generateRandRange(1000, 2000);
    strLogin << login;

    std::ostringstream strDeal;
    auto deal = generateRandRange(10000, 50000);
    strDeal << deal;

    std::ostringstream strActive;
    auto active = generateBit();
    strActive << active;

    auto strTime = GetTodayDate();

    std::ostringstream strSymbol;
    auto symbol = getRandSymbol();
    strSymbol << symbol;

    std::ostringstream strPrice;
    auto price = getRandDec(1.2030, 100.50);
    strPrice << price;

    std::ostringstream strProfit;
    auto profit = generateUnsignedRandRange(-5000, 10000);
    strProfit << profit;

    std::ostringstream strVolume;
    auto volume = getRandDec(0.01, 100);
    strVolume << volume;

    return buildTradeStr(username, strLogin.str(), strDeal.str(), strActive.str(), strTime, strSymbol.str(), strPrice.str(), strProfit.str(), strVolume.str());
}

int main()
{
    int count = 1000;
    int i;
    for (i = 0; i < count; i++) {
        std::thread t(getTrade, "Username");
        t.join();
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
