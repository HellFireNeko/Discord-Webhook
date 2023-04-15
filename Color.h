#include <string>

using namespace std;

class Color {
public:
    static const int Default = 0;
    static const int Aqua = 1752220;
    static const int DarkAqua = 1146986;
    static const int Green = 5763719;
    static const int DarkGreen = 2067276;
    static const int Blue = 3447003;
    static const int DarkBlue = 2123412;
    static const int Purple = 10181046;
    static const int DarkPurple = 7419530;
    static const int Pink = 15277667;
    static const int DarkPink = 11342935;
    static const int Gold = 15844367;
    static const int DarkGold = 12745742;
    static const int Orange = 15105570;
    static const int DarkOrange = 11027200;
    static const int Red = 15548997;
    static const int DarkRed = 10038562;
    static const int Grey = 9807270;
    static const int DarkGrey = 9936031;
    static const int DarkerGrey = 8359053;
    static const int LightGrey = 12370112;
    static const int Navy = 3426654;
    static const int DarkNavy = 2899536;
    static const int Yellow = 16776960;

    static int from_hex(string hexVal)
    {
        int len = hexVal.size();

        int base = 1;

        int dec_val = 0;

        for (int i = len - 1; i >= 0; i--) {
            if (hexVal[i] >= '0' && hexVal[i] <= '9') {
                dec_val += (int(hexVal[i]) - 48) * base;

                base = base * 16;
            }

            else if (hexVal[i] >= 'A' && hexVal[i] <= 'F') {
                dec_val += (int(hexVal[i]) - 55) * base;

                base = base * 16;
            }
        }
        return dec_val;
    }
};