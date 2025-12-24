#include "db.h"
#include <mysql.h>
#include <iostream>

std::vector<Video> getAllVideos() {
    std::vector<Video> videos;

    MYSQL* conn = mysql_init(nullptr);
    if (!mysql_real_connect(conn, "localhost", "root", "root", "videoplatform", 3306, NULL, 0)) {
        std::cout << "DB connection failed\n";
        return videos;
    }

    mysql_query(conn, "SELECT id, title, teacher FROM videos");
    MYSQL_RES* res = mysql_store_result(conn);

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        Video v;
        v.id = atoi(row[0]);
        v.title = row[1];
        v.teacher = row[2];
        videos.push_back(v);
    }

    mysql_free_result(res);
    mysql_close(conn);
    return videos;
}
void insertVideo(const std::string& title,
    const std::string& teacher,
    const std::string& filename)
{
    MYSQL* conn = mysql_init(nullptr);
    mysql_real_connect(conn, "localhost", "root", "1234",
        "videoplatform", 3306, NULL, 0);

    std::string query =
        "INSERT INTO videos (title, teacher, filename) VALUES ('" +
        title + "','" + teacher + "','" + filename + "')";

    mysql_query(conn, query.c_str());
    mysql_close(conn);
}
