#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <filesystem>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;
using json = nlohmann::ordered_json;

// Resolves a relative path, checking the current directory and parent directory (for build/ folders)
fs::path resolve_path(const fs::path& requested) {
    if (fs::exists(requested)) {
        return requested;
    }
    fs::path parent_rel = fs::path("..") / requested;
    if (fs::exists(parent_rel)) {
        return parent_rel;
    }
    return requested;
}

void print_help(const char* prog_name) {
    std::cout << "Usage: " << prog_name << " [OPTIONS] [ME_JSON] [DATA_JSON] [OUTPUT_JSON]\n\n"
              << "Restructures and combines Quran JSON datasets with verse text.\n\n"
              << "Arguments:\n"
              << "  ME_JSON       Path to metadata JSON file    (default: json-files/me.json)\n"
              << "  DATA_JSON     Path to verse text JSON file   (default: json-files/data.json)\n"
              << "  OUTPUT_JSON   Path to destination JSON file  (default: json-files/per.json)\n\n"
              << "Options:\n"
              << "  -h, --help    Show this help message and exit\n";
}

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            print_help(argv[0]);
            return 0;
        }
    }

    const std::vector<std::string> surah_names = {
        "Al-Fatihah", "Al-Baqarah", "Al-Imran", "An-Nisa", "Al-Maidah", "Al-Anam",
        "Al-Araf", "Al-Anfal", "At-Taubah", "Yunus", "Hud", "Yusuf", "Ar-Rad",
        "Ibrahim", "Al-Hijr", "An-Nahl", "Al-Isra", "Al-Kahf", "Maryam", "Ṭa-Ha",
        "Al-Anbiya", "Al-Hajj", "Al-Muminun", "An-Nur", "Al-Furqan", "Ash-Shuara",
        "An-Naml", "Al-Qasas", "Al-Ankabut", "Ar-Rum", "Luqman", "As-Sajdah",
        "Al-Ahzab", "Saba", "Fatir", "Ya-Sin", "As-Saffat", "Sad", "Az-Zumar",
        "Ghafir", "Fussilat", "Ash-Shura", "Az-Zukhruf", "Ad-Dukhan", "Al-Jathiyah",
        "Al-Ahqaf", "Muhammad", "Al-Fath", "Al-Hujurat", "Qaf", "Adh-Dhariyat",
        "At-Tur", "An-Najm", "Al-Qamar", "Ar-Rahman", "Al-Waqiah", "Al-Hadid",
        "Al-Mujadilah", "Al-Hashr", "Al-Mumtahanah", "As-Saff", "Al-Jumuah",
        "Al-Munafiqun", "At-Taghabun", "At-Ṭalaq", "At-Tahrim", "Al-Mulk", "Al-Qalam",
        "Al-Haqqah", "Al-Maarij", "Nuh", "Al-Jinn", "Al-Muzzammil", "Al-Muddaththir",
        "Al-Qiyamah", "Al-Insan", "Al-Mursalat", "An-Naba", "An-Naziat", "Abasa",
        "At-Takwir", "Al-Infitar", "Al-Mutaffifin", "Al-Inshiqaq", "Al-Buruj",
        "At-Tariq", "Al-Ala", "Al-Ghashiyah", "Al-Fajr", "Al-Balad", "Ash-Shams",
        "Al-Lail", "Ad-Duha", "Ash-Sharh", "At-Tin", "Al-Alaq", "Al-Qadr",
        "Al-Bayyinah", "Az-Zalzalah", "Al-Adiyat", "Al-Qariah", "At-Takathur",
        "Al-Asr", "Al-Humazah", "Al-Fil", "Quraish", "Al-Maun", "Al-Kauthar",
        "Al-Kafirun", "An-Nasr", "Al-Masad", "Al-Ikhlas", "Al-Falaq", "An-Nas"
    };

    fs::path me_path = (argc > 1) ? fs::path(argv[1]) : resolve_path("json-files/me.json");
    fs::path data_path = (argc > 2) ? fs::path(argv[2]) : resolve_path("json-files/data.json");
    fs::path out_path = (argc > 3) ? fs::path(argv[3]) : resolve_path("json-files/per.json");

    std::cout << "[INFO] Loading metadata from:   " << me_path << std::endl;
    std::ifstream file(me_path);
    if (!file.is_open()) {
        std::cerr << "[ERROR] Failed to open metadata file: " << me_path << std::endl;
        return 1;
    }

    std::cout << "[INFO] Loading verse text from: " << data_path << std::endl;
    std::ifstream file3(data_path);
    if (!file3.is_open()) {
        std::cerr << "[ERROR] Failed to open verse text file: " << data_path << std::endl;
        return 1;
    }

    json data;
    try {
        file >> data;
    } catch (const json::parse_error& e) {
        std::cerr << "[ERROR] Failed to parse " << me_path << ": " << e.what() << std::endl;
        return 1;
    }
    file.close();

    json data3;
    try {
        file3 >> data3;
    } catch (const json::parse_error& e) {
        std::cerr << "[ERROR] Failed to parse " << data_path << ": " << e.what() << std::endl;
        return 1;
    }
    file3.close();

    std::cout << "[INFO] Processing " << surah_names.size() << " Surahs..." << std::endl;
    json data2 = json::object();

    for (size_t j = 0; j < surah_names.size(); ++j) {
        const std::string& surah = surah_names[j];
        if (!data.contains(surah)) {
            std::cerr << "[WARN] Surah '" << surah << "' not found in metadata file." << std::endl;
            continue;
        }

        json verses = json::array();
        for (size_t i = 0; i < data[surah].size(); ++i) {
            json verse_entry = {
                {"id",       data[surah][i]["id"]},
                {"aya_no",   data[surah][i]["aya_no"]},
                {"aya_text", data3[j]["verses"][i]["text"]}
            };
            verses.push_back(verse_entry);
        }

        json surah_obj = json::object();
        if (j > 0) {
            surah_obj["jozz"] = data[surah][0]["jozz"];
        }
        surah_obj["sura_no"]      = data[surah][0]["sura_no"];
        surah_obj["sura_name_en"] = data[surah][0]["sura_name_en"];
        surah_obj["sura_name_ar"] = data[surah][0]["sura_name_ar"];
        surah_obj["verses"]       = verses;

        data2[surah] = surah_obj;
    }

    if (out_path.has_parent_path() && !fs::exists(out_path.parent_path())) {
        fs::create_directories(out_path.parent_path());
    }

    std::cout << "[INFO] Writing formatted output to: " << out_path << std::endl;
    std::ofstream file2(out_path);
    if (!file2.is_open()) {
        std::cerr << "[ERROR] Failed to open output file: " << out_path << std::endl;
        return 1;
    }

    file2 << std::setw(2) << data2 << std::endl;
    file2.close();

    std::cout << "[SUCCESS] Done! Generated " << out_path << " successfully." << std::endl;
    return 0;
}