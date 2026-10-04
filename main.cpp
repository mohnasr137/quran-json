#include <iostream>
#include <fstream>
#include <iomanip>
#include "json.hpp"
#include <vector>

using namespace std;
using json = nlohmann::ordered_json;
typedef long long ll;

int main() {
    string s[] = {"Al-Fatihah", "Al-Baqarah","Al-Imran", "An-Nisa", "Al-Maidah", "Al-Anam", "Al-Araf", "Al-Anfal", "At-Taubah", "Yunus", "Hud", "Yusuf", "Ar-Rad", "Ibrahim", "Al-Hijr", "An-Nahl", "Al-Isra", "Al-Kahf", "Maryam", "Ṭa-Ha", "Al-Anbiya", "Al-Hajj", "Al-Muminun", "An-Nur", "Al-Furqan", "Ash-Shuara", "An-Naml", "Al-Qasas", "Al-Ankabut", "Ar-Rum", "Luqman", "As-Sajdah", "Al-Ahzab", "Saba", "Fatir", "Ya-Sin", "As-Saffat", "Sad", "Az-Zumar", "Ghafir", "Fussilat", "Ash-Shura", "Az-Zukhruf", "Ad-Dukhan", "Al-Jathiyah", "Al-Ahqaf", "Muhammad", "Al-Fath", "Al-Hujurat", "Qaf", "Adh-Dhariyat", "At-Tur", "An-Najm", "Al-Qamar", "Ar-Rahman", "Al-Waqiah", "Al-Hadid", "Al-Mujadilah", "Al-Hashr", "Al-Mumtahanah", "As-Saff", "Al-Jumuah", "Al-Munafiqun", "At-Taghabun", "At-Ṭalaq", "At-Tahrim", "Al-Mulk", "Al-Qalam", "Al-Haqqah", "Al-Maarij", "Nuh", "Al-Jinn", "Al-Muzzammil", "Al-Muddaththir", "Al-Qiyamah", "Al-Insan", "Al-Mursalat", "An-Naba", "An-Naziat", "Abasa", "At-Takwir", "Al-Infitar", "Al-Mutaffifin", "Al-Inshiqaq", "Al-Buruj", "At-Tariq", "Al-Ala", "Al-Ghashiyah", "Al-Fajr", "Al-Balad", "Ash-Shams", "Al-Lail", "Ad-Duha", "Ash-Sharh", "At-Tin", "Al-Alaq", "Al-Qadr", "Al-Bayyinah", "Az-Zalzalah", "Al-Adiyat", "Al-Qariah", "At-Takathur", "Al-Asr", "Al-Humazah", "Al-Fil", "Quraish", "Al-Maun", "Al-Kauthar", "Al-Kafirun", "An-Nasr", "Al-Masad", "Al-Ikhlas", "Al-Falaq", "An-Nas"};
    ll size_of_s = sizeof(s) / sizeof(s[0]);
    // Read the JSON file
    ifstream file("C:\\Users\\MohNasr\\Desktop\\json-c++\\json-files\\me.json");
    if (!file.is_open()) {
        cerr << "Failed open file!" << endl;
        return 1;
    }

    ifstream file3("C:\\Users\\MohNasr\\Desktop\\json-c++\\json-files\\data.json");
    if (!file3.is_open()) {
        cerr << "Failed open file!" << endl;
        return 1;
    }

    json data;
    file >> data;
    file.close();

    json data3;
    file3 >> data3;
    file3.close();

    vector<json> myVector1;
    vector<json> myVector2;
    json data2;

    for (ll j = 0; j < size_of_s; j++) {
        for (ll i = 0; i < data[s[j]].size(); i++) {
//            myVector1.push_back({
//                                        {"id",              data[s[j]][i]["id"]},
//                                        {"page",            data[s[j]][i]["page"]},
//                                        {"line_start",      data[s[j]][i]["line_start"]},
//                                        {"line_end",        data[s[j]][i]["line_end"]},
//                                        {"aya_no",          data[s[j]][i]["aya_no"]},
//                                        {"aya_text",        data3[j]["verses"][i]["text"]},
//                                        {"aya_text_emlaey", data[s[j]][i]["aya_text_emlaey"]}});
//        }
            myVector1.push_back({
                                        {"id",              data[s[j]][i]["id"]},
                                        {"aya_no",          data[s[j]][i]["aya_no"]},
                                        {"aya_text",        data3[j]["verses"][i]["text"]}});
        }
        if(j == 0){
//            data2 = {{s[0], {
//                    {"jozz", data[s[0]][0]["jozz"]},
//                    {"sura_no", data[s[0]][0]["sura_no"]},
//                    {"sura_name_en", data[s[0]][0]["sura_name_en"]},
//                    {"sura_name_ar", data[s[0]][0]["sura_name_ar"]},
//                    {"verses", myVector1}
//            }}};
            data2 = {{s[0], {
                    {"sura_no", data[s[0]][0]["sura_no"]},
                    {"sura_name_en", data[s[0]][0]["sura_name_en"]},
                    {"sura_name_ar", data[s[0]][0]["sura_name_ar"]},
                    {"verses", myVector1}
            }}};
        }else{
            data2.push_back({s[j], {
                    {"jozz", data[s[j]][0]["jozz"]},
                    {"sura_no", data[s[j]][0]["sura_no"]},
                    {"sura_name_en", data[s[j]][0]["sura_name_en"]},
                    {"sura_name_ar", data[s[j]][0]["sura_name_ar"]},
                    {"verses", myVector1}
            }});
        }
        myVector1 = {};
    }

    ofstream file2("C:\\Users\\MohNasr\\Desktop\\json-c++\\json-files\\per.json");
    file2 << setw(2) << data2 << endl;
    file2.close();

    return 0;
}