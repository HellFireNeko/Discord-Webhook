#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class EmbedFooter {
public:
	string Text;
	string IconUrl;

	bool Include() {
		if (Text.empty() == false || IconUrl.empty() == false)
			return true;
		return false;
	}

	void to_json(json& j) const {
		if (Text.empty() == false)
			j["text"] = Text;
		if (IconUrl.empty() == false)
			j["icon_url"] = IconUrl;
	}
};

class EmbedMultimedia {
public:
	string Url;
	int Height;
	int Width;

	bool Include() {
		if (Url.empty() == false)
			return true;
		return false;
	}

	void to_json(json& j) const {
		if (Url.empty() == false)
			j["url"] = Url;
		if (Height > 0)
			j["height"] = Height;
		if (Width > 0)
			j["width"] = Width;
	}
};

class EmbedProvider {
public:
	string Name;
	string Url;

	bool Include() {
		if (Name.empty() == false || Url.empty() == false)
			return true;
		return false;
	}

	void to_json(json& j) const {
		if (Name.empty() == false)
			j["name"] = Name;
		if (Url.empty() == false)
			j["url"] = Url;
	}
};

class EmbedAuthor {
public:
	string Name;
	string Url;
	string IconUrl;

	bool Include() {
		if (Name.empty() == false || Url.empty() == false || IconUrl.empty() == false)
			return true;
		return false;
	}

	void to_json(json& j) const {
		if (Name.empty() == false)
			j["name"] = Name;
		if (Url.empty() == false)
			j["url"] = Url;
		if (IconUrl.empty() == false)
			j["icon_url"] = IconUrl;
	}
};

class EmbedField {
public:
	string Name;
	string Value;
	bool Inline;

	EmbedField(string name, string value, bool il) {
		Name = name;
		Value = value;
		Inline = il;
	}

	void to_json(json& j) const {
		j["name"] = Name;
		j["value"] = Value;
		j["inline"] = Inline;
	}
};

class Embed {
public:
	string Title;
	string Type = "rich";
	string Description;
	string Url;
	int Color = 0;
	EmbedFooter Footer;
	EmbedMultimedia Image;
	EmbedMultimedia Thumbnail;
	EmbedMultimedia Video;
	EmbedProvider Provider;
	EmbedAuthor Author;
	vector<EmbedField> Fields;

	void add_field(string Name, string Value, bool Inline = false) {
		if (Fields.size() < 25)
			Fields.push_back(EmbedField(Name, Value, Inline));
	}

	void to_json(json& j) {
		if (Title.empty() == false)
			j["title"] = Title;
		j["type"] = Type;
		if (Description.empty() == false)
			j["description"] = Description;
		if (Url.empty() == false)
			j["url"] = Url;
		j["color"] = Color;
		if (Footer.Include()) {
			json e;
			Footer.to_json(e);
			j["footer"] = e;
		}
		if (Image.Include()) {
			json e;
			Image.to_json(e);
			j["image"] = e;
		}
		if (Thumbnail.Include()) {
			json e;
			Thumbnail.to_json(e);
			j["thumbnail"] = e;
		}
		if (Video.Include()) {
			json e;
			Video.to_json(e);
			j["video"] = e;
		}
		if (Provider.Include()) {
			json e;
			Provider.to_json(e);
			j["provider"] = e;
		}
		if (Fields.empty() == false) {
			for (int i = 0; i < Fields.size(); i++) {
				json e;
				Fields[i].to_json(e);
				j["fields"][i] = e;
			}
		}
	}
};