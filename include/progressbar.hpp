#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace colors {
    const std::string RESET   = "\033[0m";
    const std::string BOLD    = "\033[1m";
    const std::string RED     = "\033[31m";
    const std::string GREEN   = "\033[32m";
    const std::string YELLOW  = "\033[33m";
    const std::string BLUE    = "\033[34m";
    const std::string CYAN    = "\033[36m";
}

class ProgressBar {
public:
    explicit ProgressBar(size_t total, size_t bar_width = 30, char fill = '=', char head = '>', char empty = ' ')
        : total_(total), bar_width_(bar_width), fill_char_(fill), head_char_(head), empty_char_(empty) {
        start_time_ = std::chrono::steady_clock::now();
    }

    void set(size_t current) {
        current_ = std::min(current, total_);
        render();
    }

    ProgressBar& operator++() {
        if (current_ < total_) ++current_;
        render();
        return *this;
    }

    void finish() {
        set(total_);
        std::cout << "\n";
    }

private:
    static std::string format_time(double seconds) {
        int sec = static_cast<int>(seconds);
        int mins = sec / 60;
        sec %= 60;
        int hours = mins / 60;
        mins %= 60;

        std::ostringstream oss;
        if (hours > 0) {
            oss << hours << "h ";
        }
        oss << std::setfill('0') << std::setw(2) << mins << "m:" 
            << std::setfill('0') << std::setw(2) << sec << "s";
        return oss.str();
    }

    void render() const {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = now - start_time_;
        double elapsed_sec = elapsed.count();

        // Speed (it/s) and ETA calculation
        double speed = (elapsed_sec > 0.001) ? (static_cast<double>(current_) / elapsed_sec) : 0.0;
        double eta_sec = (speed > 0.0 && current_ < total_) ? (static_cast<double>(total_ - current_) / speed) : 0.0;

        float progress = (total_ == 0) ? 1.0f : static_cast<float>(current_) / total_;
        size_t filled_len = static_cast<size_t>(std::round(bar_width_ * progress));

        std::cout << "\r" << colors::BOLD << "[";

        // Render colored progress bar
        for (size_t i = 0; i < bar_width_; ++i) {
            if (i < filled_len) {
                std::cout << colors::GREEN << fill_char_ << colors::RESET;
            } else if (i == filled_len && filled_len > 0 && current_ < total_) {
                std::cout << colors::YELLOW << head_char_ << colors::RESET;
            } else {
                std::cout << empty_char_;
            }
        }

        int percent = static_cast<int>(progress * 100.0f);
        
        // Formatted line: [====>   ] 45% | 45/100 | 12.3 it/s | Elapsed: 00m:03s | ETA: 00m:04s
        std::cout << colors::BOLD << "] " << std::setw(3) << percent << "% | "
                  << current_ << "/" << total_ << " | " << colors::RESET
                  << colors::CYAN << std::fixed << std::setprecision(1) << speed << " it/s" << colors::RESET << " | "
                  << "Elapsed: " << colors::GREEN << format_time(elapsed_sec) << colors::RESET << " | "
                  << "ETA: " << colors::YELLOW << format_time(eta_sec) << colors::RESET
                  << "   " << std::flush;
    }

    size_t current_ = 0;
    size_t total_ = 100;
    size_t bar_width_ = 30;
    char fill_char_;
    char head_char_;
    char empty_char_;
    std::chrono::time_point<std::chrono::steady_clock> start_time_;
};