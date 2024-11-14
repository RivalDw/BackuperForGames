// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;


void copySaveFolder(const fs::path& source, const fs::path& destination) {
    try {
        // Проверяем, существует ли папка-источник
        if (fs::exists(source) && fs::is_directory(source)) {
            // Создаем папку назначения, если ее еще нет
            if (!fs::exists(destination)) {
                fs::create_directories(destination);
            }
            // Копируем все содержимое из source в destination
            fs::copy(source, destination, fs::copy_options::recursive);
            std::cout << "Backup completed for: " << source << " -> " << destination << std::endl;
        }
        else {
           // std::cout << "Folder not found: " << source << std::endl;
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Copy error: " << e.what() << std::endl;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    std::cout << "Hello World!\n";

    std::vector<std::string> usersBan = { "Public", "Default", "desktop.ini", "All Users", "Default User","Все пользователи"};
    std::vector<std::string> result;
    const auto dirUsers = std::string("C:\\Users\\");

    // Перебор файлов в директории
    for (const auto& f : fs::directory_iterator(dirUsers)) {
        bool isBanned = false;

        // Проверяем, не является ли файл одним из запрещённых
        for (size_t i = 0; i < usersBan.size(); i++) {
            if (f.path().filename() == usersBan[i]) {
                isBanned = true;
                break;  // Прерываем цикл, если нашли запрещённый файл
            }
        }

        // Если файл не запрещён, добавляем его в результат
        if (!isBanned) {
            result.push_back(f.path().string());
        }

    }

    // Выводим результаты
    std::cout << "\nFiltered files:\n";
    for (const auto& file : result) {
        std::cout << file << std::endl;
    }


    // Пути базовых папок
    std::vector<std::string> dirDocuments = { "OneDrive\\Documents", "OneDrive\\Documents\\My Games", "Documents" };
    std::vector<std::string> dirAnother = { "C:\\GOG Games\\", result.at(0)+"AppData\\Local\\", "C:\\Program Files (x86)\\Steam\\steamapps\\common" };

    // Пути папок с сохранениями
    std::vector<std::string> dirSaves = {
        "GTA San Andreas User Files",
        "18 WoS Convoy\\save",
        "Call Of Duty Black Ops Cold War\\player",
        "Electronic Arts\\The Sims 4\\saves",
        "Ghost of Tsushima DIRECTOR'S CUT",
        "Skyrim Special Edition\\Saves",
        "SpaceRangersHD\\Save",
        "The Witcher 3\\gamesaves",
        "Timberborn\\Saves",
        "NFS SHIFT",
        "NFS Carbon",
        "Test Drive Unlimited\\savegame"
        "Kenshi\\save",
        "Death to Spies",
        "KingsBounty2\\Saved\\SaveGames",
        "StateOfDecay2\\Saved"
    };

    // Папка назначения для резервных копий
    fs::path backupDestination = "Z:\\BACKUPS\\";  // Замените на путь для резервного копирования

    // Процесс резервного копирования
    for (const auto& dirDoc : dirDocuments) {
        for (const auto& save : dirSaves) {
            fs::path sourcePath = fs::path(result[0]) / dirDoc / save;  // Путь из Documents
            fs::path destinationPath = backupDestination / "DocumentsBackup" / save;  // Путь для сохранения в резервной копии
            copySaveFolder(sourcePath, destinationPath);
        }
    }

    for (const auto& dirOther : dirAnother) {
        for (const auto& save : dirSaves) {
            fs::path sourcePath = fs::path(dirOther) / save;  // Путь для папок вне Documents
            fs::path destinationPath = backupDestination / "OtherBackup" / save;  // Путь для резервного копирования
            copySaveFolder(sourcePath, destinationPath);
        }
    }

    std::cout << "Резервное копирование завершено!" << std::endl;
    return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
