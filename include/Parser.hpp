//
// Created by wery_a on 22/12/16.
//

#ifndef JSONPARSER_PARSER_HPP
#define JSONPARSER_PARSER_HPP

#include <stack>
#include "Config/Object.hpp"
#include "Config/Array.hpp"

namespace JSON {
    class Parser {
        enum ParsingType {
            ObjectType,
            ArrayType,
            KeyType,
            ValueType
        };

    public:
        Parser(std::string const &filename);

        ~Parser();

        Config::Object &Parse();

    private:
        std::ifstream *m_file;
        Config::Object *m_json;
        std::stack<ParsingType> m_type;

        std::string m_key;
        std::string m_value;
        std::stack<std::string> m_keys;

        std::stack<Config::AObject *> m_parents;

        bool gettingString;
        bool isValueIsString;

    private:
        void act(char c);

        void openObject();

        void closeObject();

        void openArray();

        void closeArray();

        void gettingKey(char c);

        void gettingValue(char c);

        void savingKeyValue();

        void pushChar(char value);

        void pushInt(int value);

        void pushFloat(float value);

        void pushDouble(double value);

        void pushString();
    };
}

#endif //JSONPARSER_PARSER_HPP
