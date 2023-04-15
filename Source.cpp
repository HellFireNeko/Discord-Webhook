#include <iostream>
#include <thread>
#include <chrono>
#include "Color.h"
#include "Webhook.h"
#include "ZenQuote.h"

using namespace std; using namespace std::chrono; using namespace std::this_thread;

const string WEBHOOK_URL = "YOUR_WEBHOOK_GOES_HERE";

string FixContent(string original) {
	replace(original.begin(), original.end(), ';', ',');
	return original;
}

int main() {
	Webhook wh(WEBHOOK_URL);

	SendMessagePacket packet;

	packet.Username = "Suck it";

	while (true) {

		packet.Content = FixContent(ZenQuote::GetQuote());

		wh.SendMessagePacket(packet);

		sleep_for(seconds(5));
	}
}