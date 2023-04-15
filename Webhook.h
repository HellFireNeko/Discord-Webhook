#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include "MessagePackets.h"

using namespace std;
using json = nlohmann::json;

class Webhook {
public:
	string Url;

	Webhook(string url) : Url(url) {}

	void SendMessagePacket(SendMessagePacket packet) {
		if (packet.IsValidPacket())
			SendPacket(Url, packet.SerializePacket());
		else
			cout << "ERROR : Invalid Packet" << endl;
	}

	void EditMessagePacket(string id, EditMessagePacket packet) {
		if (packet.IsValidPacket()) {
			SendPacket(Url + "/messages/" + id, packet.SerializePacket(), true);
		}
		else {
			cout << "ERROR : Invalid Packet" << endl;
		}
	}

private:
	static void SendPacket(string url, string packet, bool patch = false) {
		CURL* curl;
		CURLcode res;

		curl_global_init(CURL_GLOBAL_ALL);

		curl = curl_easy_init();
		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

			struct curl_slist* headers = NULL;
			headers = curl_slist_append(headers, "Content-Type: application/json");
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

			if (patch)
				curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");

			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, packet.c_str());

			res = curl_easy_perform(curl);

			curl_slist_free_all(headers);
			curl_easy_cleanup(curl);
		}

		curl_global_cleanup();
	}
};