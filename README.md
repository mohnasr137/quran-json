# Quran JSON Processor (C++)

A fast, modern C++ tool for processing, combining, and restructuring Quranic datasets into clean, hierarchical JSON representations.

The program integrates Quran metadata (Surah names in Arabic/English, Surah numbers, and Juz information) with full Uthmanic verse texts into an ordered, structured JSON dataset.

---

## 📁 Project Structure

```text
.
├── CMakeLists.txt              # CMake build configuration
├── .gitignore                  # Git ignore rules for build artifacts and IDEs
├── README.md                   # Project documentation
├── include/                    # Header files
│   ├── json.hpp                # Top-level header wrapper
│   └── nlohmann/               # nlohmann/json library headers
│       ├── json.hpp
│       └── json_fwd.hpp
├── main.cpp                    # Core processing and JSON conversion logic
├── json-files/                 # Active dataset directory
│   ├── me.json                 # Input: Quran metadata by Surah
│   ├── data.json               # Input: Verse texts in Uthmanic script
│   └── per.json                # Output: Merged and structured JSON dataset
└── important/                  # Reference and backup datasets
    ├── data.json
    ├── me.json
    ├── re.json
    └── try.json
```

---

## 🚀 Features

- **Modern C++17**: Uses `std::filesystem` and `nlohmann::ordered_json` to preserve key order across all 114 Surahs.
- **Smart Path Resolution**: Automatically detects dataset paths whether executed from the project root directory or the `build/` folder.
- **CLI Options**: Supports custom input/output file paths as command-line arguments, as well as `-h` / `--help`.
- **Robust Error Handling**: Validates file existence and reports JSON parsing errors with line/column diagnostics.
- **Cross-Platform**: Builds seamlessly on Linux, macOS, and Windows.

---

## 🛠️ Prerequisites

- **C++ Compiler**: Supporting C++17 (e.g. GCC 9+, Clang 10+, or MSVC 2019+)
- **CMake**: Version 3.16 or higher *(optional, can also be compiled directly)*

---

## 🔨 Building the Project

### Option 1: Using CMake (Recommended)

```bash
# 1. Configure the build
cmake -B build -S .

# 2. Compile the executable
cmake --build build
```

The compiled binary will be placed at `build/json_c__`.

### Option 2: Direct Compilation with GCC / Clang

```bash
mkdir -p build
g++ -std=c++17 -O2 -Iinclude main.cpp -o build/json_c__
```

---

## ▶️ Running the Application

### Default Run
Runs with default datasets (`json-files/me.json` and `json-files/data.json`), writing output to `json-files/per.json`:

```bash
# From the project root:
./build/json_c__

# Or from inside the build directory:
cd build
./json_c__
```

### Custom File Paths
You can specify custom input and output file paths via positional arguments:

```bash
./build/json_c__ <path/to/metadata.json> <path/to/text.json> <path/to/output.json>
```

### Help Option
```bash
./build/json_c__ --help
```

Output:
```text
Usage: ./build/json_c__ [OPTIONS] [ME_JSON] [DATA_JSON] [OUTPUT_JSON]

Restructures and combines Quran JSON datasets with verse text.

Arguments:
  ME_JSON       Path to metadata JSON file    (default: json-files/me.json)
  DATA_JSON     Path to verse text JSON file   (default: json-files/data.json)
  OUTPUT_JSON   Path to destination JSON file  (default: json-files/per.json)

Options:
  -h, --help    Show this help message and exit
```

---

## 📊 Output Data Schema

The generated `per.json` is organized by Surah name as keys, containing metadata and a list of verses:

```json
{
  "Al-Fatihah": {
    "sura_no": 1,
    "sura_name_en": "Al-Fātiḥah",
    "sura_name_ar": "الفَاتِحة",
    "verses": [
      {
        "id": 1,
        "aya_no": 1,
        "aya_text": "بِسۡمِ ٱللَّهِ ٱلرَّحۡمَٰنِ ٱلرَّحِيمِ"
      },
      ...
    ]
  },
  "Al-Baqarah": {
    "jozz": 1,
    "sura_no": 2,
    "sura_name_en": "Al-Baqarah",
    "sura_name_ar": "البَقَرَة",
    "verses": [ ... ]
  }
}
```

---

## 📦 Dependencies

- [nlohmann/json](https://github.com/nlohmann/json) - JSON for Modern C++ (bundled in `include/nlohmann/`).
