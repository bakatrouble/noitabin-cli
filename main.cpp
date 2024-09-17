#include <noita.h>
#include <filesystem>
#include <print>
#include <args.hxx>

namespace fs = std::filesystem;

int main(int argc, char **argv) {
    args::ArgumentParser parser("A Noita entities search utility");
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
    args::ValueFlag<std::string> savedir(parser, "savedir", "Specify the save location", {'d', "save-dir"}, args::Options::Global);
    args::CompletionFlag completion(parser, {"complete"});

    try {
        parser.ParseCLI(argc, argv);
    } catch (const args::Completion &e) {
        std::cout << e.what();
        return 0;
    } catch (const args::Help&) {
        std::cout << parser;
        return 0;
    } catch (const args::ParseError &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }

    std::vector<noita::types::Entity> entities;
    fs::path savePath;
    if (savedir) {
        savePath = savedir.Get();
    } else {
#ifdef _WIN32
        savePath = getenv("APPDATA");
        savePath /= "../LocalLow/Nolla_Games_Noita/save00";
#else
        savePath = getenv("HOME");
        savePath /= ".local/share/steam/steamapps/compatdata/881100/pfx/drive_c/users/steamuser/AppData/LocalLow/Nolla_Games_Noita/save00";
#endif
    }
    fs::path worldPath = savePath / "world";
    uint32_t fileCnt = 0;
    for (auto &entry : fs::directory_iterator(worldPath)) {
        if (
                entry.is_regular_file() &&
                entry.path().filename().string().starts_with("entities_") &&
                entry.path().filename().extension() == ".bin"
        ) {
            fileCnt++;
            noita::read_compressed_entities(entry.path(), entities);
        }
    }
    std::print("Read {} files, found {} entities\n", fileCnt, (uint32_t)entities.size());
    if (entities.empty()) {
        std::print("No entities found \n");
        return 0;
    }

    uint32_t wandsCnt = 0, cardActionCnt = 0;
    for (auto &entity : entities) {
        if (entity.tags.contains(std::string("wand"))) {
            wandsCnt++;
        }
        if (entity.tags.contains(std::string("card_action"))) {
            cardActionCnt++;
        }
    }
    std::print("{} wands, {} card actions\n", wandsCnt, cardActionCnt);

    return 0;
}
