#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <thread>
#include <future>
#include <cstdlib>  // for system()
#include <mutex>

namespace fs = std::filesystem;
std::mutex print_mutex;

void convert_avi_to_mkv(const std::string& input_path) {
    std::string output_path = input_path.substr(0, input_path.find_last_of(".")) + ".mkv";

    if (fs::exists(output_path)) {
        std::lock_guard<std::mutex> lock(print_mutex);
        std::cout << "File already exists, skipped: " << output_path << "\n";
        return;
    }

    // Construct FFmpeg command
    std::string cmd = "ffmpeg -i \"" + input_path + "\" -c:v libx264 \"" + output_path + "\" -y";

    int result = std::system(cmd.c_str());
    if (result == 0) {
        std::lock_guard<std::mutex> lock(print_mutex);
        std::cout << "Conversion complete: " << output_path << "\n";

        // Delete original file
        fs::remove(input_path);
        std::cout << "Deleted original: " << input_path << "\n";
    } else {
        std::lock_guard<std::mutex> lock(print_mutex);
        std::cerr << "Error converting file: " << input_path << "\n";
    }
}

void find_and_convert_avi(const std::string& root_folder) {
    std::vector<std::string> avi_files;

    // Find .avi files recursively
    for (const auto& entry : fs::recursive_directory_iterator(root_folder)) {
        if (entry.path().extension() == ".avi") {
            avi_files.push_back(entry.path().string());
        }
    }

    // Run conversions in parallel
    std::vector<std::future<void>> futures;
    for (const auto& file : avi_files) {
        futures.emplace_back(std::async(std::launch::async, convert_avi_to_mkv, file));
    }

    for (auto& f : futures) {
        f.get();
    }

    std::cout << "✅ All AVI files have been processed!\n";
}

int main() {
    std::string path;
    std::cout << "Enter the path to the external drive: ";
    std::getline(std::cin, path);

    if (fs::exists(path)) {
        find_and_convert_avi(path);
    } else {
        std::cerr << "❌ Error: Path does not exist!\n";
    }

    return 0;
}