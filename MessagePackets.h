#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "Embed.h"

using namespace std;
using json = nlohmann::json;

class SendMessagePacket {
public:
	string Content;
	string Username;
	string AvatarUrl;
	bool TTS = false;
	vector<Embed> Embeds;

	bool IsValidPacket() {
		if (Content.empty() && Embeds.empty())
			return false;
		return true;
	}

	string SerializePacket() {
		json j;
		if (Content.empty() == false)
			j["content"] = Content;
		if (Username.empty() == false)
			j["username"] = Username;
		if (AvatarUrl.empty() == false)
			j["avatar_url"] = AvatarUrl;
		j["tts"] = TTS;
		if (Embeds.empty() == false) {
			for (int i = 0; i < Embeds.size(); i++) {
				json e;
				Embeds[i].to_json(e);
				j["embeds"][i] = e;
			}
		}
		return j.dump();
	}
};

class EditMessagePacket {
public:
	string Content;
	vector<Embed> Embeds;

	bool IsValidPacket() {
		if (Content.empty() && Embeds.empty())
			return false;
		return true;
	}

	string SerializePacket() {
		json j;
		if (Content.empty() == false)
			j["content"] = Content;
		if (Embeds.empty() == false) {
			for (int i = 0; i < Embeds.size(); i++) {
				json e;
				Embeds[i].to_json(e);
				j["embeds"][i] = e;
			}
		}
		return j.dump();
	}
};