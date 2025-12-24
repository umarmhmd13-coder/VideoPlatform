#include "crow.h"
#include <mysql.h>
#include <fstream>

MYSQL* conn;

int main() {
    crow::SimpleApp app;

    // MySQL
    conn = mysql_init(nullptr);
    mysql_real_connect(
        conn,
        "localhost",
        "root",
        "root",
        "videoplatform",
        0, NULL, 0
    );

    // health
    CROW_ROUTE(app, "/health")([]() {
        return "SERVER OK";
        });

    // =======================
    // GET videos
    // =======================
    CROW_ROUTE(app, "/videos")([]() {
        crow::json::wvalue res;
        MYSQL_RES* result;
        MYSQL_ROW row;

        mysql_query(conn, "SELECT id,title,teacher,filename FROM videos");
        result = mysql_store_result(conn);

        int i = 0;
        while ((row = mysql_fetch_row(result))) {
            res["videos"][i]["id"] = atoi(row[0]);
            res["videos"][i]["title"] = row[1];
            res["videos"][i]["teacher"] = row[2];
            res["videos"][i]["filename"] = row[3];
            i++;
        }
        return res;
        });

    // =======================
    // UPLOAD
    // =======================
    CROW_ROUTE(app, "/upload").methods("POST"_method)
        ([](const crow::request& req) {

        crow::multipart::message msg(req);

        std::string title, teacher, filename;

        for (auto& part : msg.parts) {
            if (part.name == "title")
                title = part.body;
            else if (part.name == "teacher")
                teacher = part.body;
            else if (part.name == "file") {
                filename = part.filename;
                std::ofstream out("uploads/" + filename, std::ios::binary);
                out.write(part.body.c_str(), part.body.size());
                out.close();
            }
        }

        std::string q =
            "INSERT INTO videos(title,teacher,filename) VALUES('" +
            title + "','" + teacher + "','" + filename + "')";

        mysql_query(conn, q.c_str());

        return crow::response("OK");
            });

    // =======================
    // Serve uploaded videos
    // =======================
    CROW_ROUTE(app, "/uploads/<string>")
        ([](const std::string& name) {
        std::ifstream in("uploads/" + name, std::ios::binary);
        if (!in) return crow::response(404);

        std::ostringstream contents;
        contents << in.rdbuf();

        crow::response res;
        res.body = contents.str();
        res.set_header("Content-Type", "video/mp4");
        return res;
            });

    app.port(18080).run();
}
