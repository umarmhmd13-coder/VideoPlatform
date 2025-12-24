#pragma once
#include <vector>
#include <string>

struct Video {
    int id;
    std::string title;
    std::string teacher;
};

std::vector<Video> getAllVideos();
void insertVideo(const std::string& title,
    const std::string& teacher,
    const std::string& filename);
