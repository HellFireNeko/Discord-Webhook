#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class ZenQuote {
public:
	static string GetQuote() {
		CURL* curl;
		CURLcode res;
		string url = "https://zenquotes.io/api/random";

		string response_data;

		curl_global_init(CURL_GLOBAL_ALL);

		curl = curl_easy_init();

		struct curl_slist* headers = NULL;

		if (!curl) {
			cout << "ERROR : Curl initialization" << endl;
			Cleanup(curl, headers);
			return "0";
		}

		headers = curl_slist_append(headers, "User-Agent: libcurl-agent/1.0");
		headers = curl_slist_append(headers, "Content-Type: application/json");
		headers = curl_slist_append(headers, "Cache-Control: no-cache");

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

		res = curl_easy_perform(curl);

		if (res != 0) {
			cout << "Error: Request failed on URL : " << url << endl;
			cout << "Error Code: " << res << " Error Detail : " << curl_easy_strerror(res) << endl;
			Cleanup(curl, headers);
			return "0";
		}

		curl_easy_cleanup(curl);
		curl_slist_free_all(headers);
		curl_global_cleanup();

		json j = json::parse(response_data);

		return "\"" + j[0]["q"].get<string>() + "\" - " + j[0]["a"].get<string>();
	}
private:
	static void Cleanup(CURL* curl, curl_slist* headers)
	{
		if (curl)
			curl_easy_cleanup(curl);
		if (headers)
			curl_slist_free_all(headers);
		curl_global_cleanup();
	}

	static size_t curl_callback(void* ptr, size_t size, size_t nmemb, std::string* data) {
		data->append((char*)ptr, size * nmemb);
		return size * nmemb;
	}
};