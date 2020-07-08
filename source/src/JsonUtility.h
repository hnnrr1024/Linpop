#pragma once

#include <string>
#include <iostream>

using namespace std;

#include "json/json.h"

#pragma comment (lib, "jsoncpp.lib")

int parse(const string& msg, Json::Value& root);
