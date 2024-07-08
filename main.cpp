#include <iostream>
#include <string>
#include <curl/curl.h>
#include <json/json.h>

// Function to fetch data from a URL
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string fetchData(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

void getWeather(const std::string& apiKey) {
    std::string url = "http://api.openweathermap.org/data/2.5/weather?q=London&appid=" + apiKey;
    std::string response = fetchData(url);

    // Parse JSON response
    Json::Value jsonData;
    Json::Reader jsonReader;
    if (jsonReader.parse(response, jsonData)) {
        std::string weather = jsonData["weather"][0]["description"].asString();
        std::cout << "Weather: " << weather << std::endl;
    }
}

void getNews(const std::string& apiKey) {
    std::string url = "http://newsapi.org/v2/top-headlines?country=us&apiKey=" + apiKey;
    std::string response = fetchData(url);

    // Parse JSON response
    Json::Value jsonData;
    Json::Reader jsonReader;
    if (jsonReader.parse(response, jsonData)) {
        std::string headline = jsonData["articles"][0]["title"].asString();
        std::cout << "News: " << headline << std::endl;
    }
}

void getMotto() {
    // Example static motto
    std::string motto = "Stay positive, work hard, make it happen.";
    std::cout << "Motto of the day: " << motto << std::endl;
}

int main() {
    std::string weatherApiKey = "your_weather_api_key";
    std::string newsApiKey = "your_news_api_key";

    std::cout << "Good Morning!" << std::endl;

    getWeather(weatherApiKey);
    getNews(newsApiKey);
    getMotto();

    return 0;
}
