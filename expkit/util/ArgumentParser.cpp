#pragma once

#include <string>
#include <vector>
#include <map>
#include <optional>
#include <sstream>

using namespace std;

class ArgumentParser {
public:
    ArgumentParser(int argc, const char* argv[]) {
        vector<string> args(argv, argv + argc);

        for (size_t i = 1; i < args.size(); ++i) {
            auto arg = args[i];

            size_t hyphenCount = 0;
            while (hyphenCount < arg.size() && arg[hyphenCount] == '-')
                hyphenCount++;

            if (hyphenCount == 0) {
                positionalArgs_.push_back(arg);
            } else {
                arg = arg.substr(hyphenCount);

                string value = "";
                if (i + 1 < args.size() && !args[i + 1].empty() && args[i + 1][0] != '-') {
                    value = args[i + 1];
                    i++;
                }

                if (options_.count(arg) > 0)
                    options_[arg] += "," + value;
                else
                    options_[arg] = value;
            }
        }
    }

    const map<string, string>& getOptions() const {
        return options_;
    }

    optional<string> getOption(const string& name) const {
        auto it = options_.find(name);
        return it != options_.end() ? optional(it->second) : nullopt;
    }

    optional<long> getInt(const string& name) const {
        auto it = options_.find(name);
        return it != options_.end() ? optional(stoi(it->second)) : nullopt;
    }

    optional<vector<string>> getListOption(const string& name) const {
        auto it = options_.find(name);
        if (it == options_.end())
            return nullopt;

        vector<string> result;
        stringstream ss(it->second);
        string item;
        while (getline(ss, item, ','))
            result.push_back(item);
        return result;
    }

    const vector<string>& getPositionalArgs() const {
        return positionalArgs_;
    }

private:
    map<string, string> options_;
    vector<string> positionalArgs_;
};