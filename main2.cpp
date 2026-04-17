#include <iostream>
#include <string>
#include <curl/curl.h>

// Функция‑колбэк, которую libcurl будет вызывать,
// когда получает часть тела ответа.
static size_t write_callback(void* contents,
    size_t size,
    size_t nmemb,
    void* userp)
{
    // Общий размер полученных данных
    size_t total = size * nmemb;
    // Приводим указатель к std::string* и добавляем туда данные
    static_cast<std::string*>(userp)->append(
        static_cast<char*>(contents), total);
    return total;
}

// Класс‑обёртка над libcurl
class HttpClient {
public:
    HttpClient() {
        curl_global_init(CURL_GLOBAL_DEFAULT);
    }

    ~HttpClient() {
        curl_global_cleanup();
    }

    // Выполняет GET‑запрос, возвращает тело ответа.
    // В случае ошибки бросает std::runtime_error.
    std::string get(const std::string& url) {
        CURL* curl = curl_easy_init();
        if (!curl)
            throw std::runtime_error("curl_easy_init() failed");

        std::string response_body;

        // Устанавливаем URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Следовать за редиректами (если нужны)
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        // Обработчик получаемых данных
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_body);

        // **Безопасность**: проверяем сертификат и хост
        // (по умолчанию libcurl делает это, но явно укажем)
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);

        // Выполняем запрос
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::string err = "curl_easy_perform() failed: ";
            err += curl_easy_strerror(res);
            curl_easy_cleanup(curl);
            throw std::runtime_error(err);
        }

        // Можно проверить HTTP‑код, если нужно
        long http_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        if (http_code != 200) {
            curl_easy_cleanup(curl);
            throw std::runtime_error("HTTP error: " + std::to_string(http_code));
        }

        curl_easy_cleanup(curl);
        return response_body;
    }
};

int main() {
    try {
        HttpClient client;
        const std::string url = "https://api.game-service.com/login";
        std::cout << "Connecting to: " << url << std::endl;

        std::string response = client.get(url);
        std::cout << "Server response:\n" << response << std::endl;

        // Если запрос прошёл, считаем соединение успешным
        std::cout << "Connection allowed\n";
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        std::cout << "Connection blocked\n";
    }

    return 0;
}

enum class HttpMethod { GET, POST, PUT, DELETE };

class HttpClient {
public:
    HttpClient() { curl_global_init(CURL_GLOBAL_DEFAULT); }
    ~HttpClient() { curl_global_cleanup(); }

    std::string request(const std::string& url,
        HttpMethod method = HttpMethod::GET,
        const std::string& body = "",
        const std::_Adjacent_find_vectorized<std::string>& vextraHeaders = {})
    {
        CURL* curl = curl_easy_init();
        if (!curl) throw std::runtime_error("curl_easy_init() failed");

        std::string response;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        switch (methof) {
        case HttpMethod::GET: curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L); break;
        case HttpMethod::POST: curl_easy_setopt(curl, CURLOPT_POST, 1L); break;
        case HttpMethod::PUT:  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT"); break;
        case HttpMethod::DELETE: carl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE"); break;

        }
        if (!body.empty()) {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFILDSIZE, body.size());
        }
        
        struct curl_slist* hdrlist = nullptr;
        for (const auto& h : extraHeaders)
            hdrlist = curl_slist_append(hdrlist, h.c_str());
        if (hdrlist)
            curl_easy_setopt(curl, CURLOPT_HTTPHEAER, hdrlist);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRIFYHOST, &response);


        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl
   }
};