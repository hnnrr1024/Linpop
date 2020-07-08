#include "JsonUtility.h"

int parse(const string& msg, Json::Value& root)
{
    bool res;
    std::string errs;
    Json::CharReaderBuilder readerBuilder;

    const std::unique_ptr<Json::CharReader> jsonReader(readerBuilder.newCharReader());
    res = jsonReader->parse(msg.c_str(), msg.c_str() + msg.length(), &root, &errs);
    if (!res || !errs.empty()) {
        std::cout << "parseJson err. " << errs << std::endl;
        return -1;
    }
    return 0;
}
