//
// Created by wery_a on 22/12/16.
//
#include <iostream>
#include <fstream>
#include "../include/Parser.hpp"

//#define DEBUG_MODE

void Debug(std::string const &txt) {
#ifdef DEBUG_MODE
    std::cerr << txt << std::endl;
#endif
}

namespace JSON {

    Parser::Parser(std::string const &filename) :
            m_json(nullptr) {
        m_file = new std::ifstream(filename);
        gettingString = false;
        isValueIsString = false;
    }

    Parser::~Parser() {
        m_file->close();
        delete m_file;
    }

    void Parser::openObject() {
        Debug("Openning Object");
        m_parents.push(new Config::Object());
        if (m_json == nullptr) {
            m_json = dynamic_cast<Config::Object *>(m_parents.top());
        }
        m_type.push(ObjectType);
        m_type.push(KeyType);
    }

    void Parser::closeObject() {
        Debug("Closing Object");
        savingKeyValue();
        if (m_type.top() != ObjectType) {
            throw std::runtime_error("Bad type need ObjectType");
        }
        m_type.pop();
        Config::AObject *current = m_parents.top();
        m_parents.pop();
        if (m_parents.empty()) {
            Debug("Object end");
            return;
        }
        Config::AObject *parent = m_parents.top();
        Config::Array *parentArray = dynamic_cast<Config::Array *>(parent);
        if (parentArray) {
            parent->push(dynamic_cast<Config::Object *>(current));
        } else {
            parent->push(m_keys.top(), dynamic_cast<Config::Object *>(current));
            m_keys.pop();
        }
    }

    void Parser::openArray() {
        Debug("Openning Array");
        m_parents.push(new Config::Array());
        m_type.push(ArrayType);
        m_type.push(ValueType);
    }

    void Parser::closeArray() {
        Debug("Closing Array");
        savingKeyValue();
        if (m_type.top() != ArrayType) {
            throw std::runtime_error("Error during parsing bad ArrayType");
        }
        m_type.pop();

        Config::AObject *current = m_parents.top();
        m_parents.pop();
        if (m_parents.empty()) {
            Debug("Array end");
            return;
        }
        Config::AObject *parent = m_parents.top();
        Config::Array *parentArray = dynamic_cast<Config::Array *>(parent);
        if (parentArray) {
            parent->push(dynamic_cast<Config::Array *>(current));
        } else {
            parent->push(m_keys.top(), dynamic_cast<Config::Array *>(current));
            m_keys.pop();
        }
    }

    void Parser::gettingKey(char c) {
        if (c == '"') {
            gettingString = !gettingString;
            return;
        }
        if (gettingString) {
            m_key += c;
        }
    }

    void Parser::gettingValue(char c) {
        if (c == '"') {
            isValueIsString = true;
            gettingString = !gettingString;
            return;
        }
        if (gettingString || c != ' ') {
            m_value += c;
        }
    }

    void Parser::savingKeyValue() {
        if (m_type.top() != ValueType) {
            throw std::runtime_error("Bad type need ValueType");
        }
        m_type.pop();

        if (m_value.empty()) {
            Debug("Empty Value");
            return;
        }
        if (!isValueIsString) {
            size_t pos = m_value.find_last_of(".");
            if (pos == std::string::npos) {
                int value = std::atoi(m_value.c_str());
                if (value > -255 && value < 255) {
                    pushChar(static_cast<char>(value));
                } else {
                    pushInt(value);
                }
            } else {
                double value = std::atof(m_value.c_str());
                if (pos + 15 < m_value.length()) {
                    pushDouble(value);
                } else {
                    pushFloat(static_cast<float>(value));
                }
            }
        } else {
            pushString();
        }

        m_value = "";
    }

    void Parser::pushChar(char value) {
        switch (m_type.top()) {
            case ObjectType:
                m_parents.top()->push(m_keys.top(), value);
                m_keys.pop();
                break;
            case ArrayType:
                m_parents.top()->push(value);
                break;
            default:
                throw std::runtime_error("Bad type need ObjectType or ArrayType");
        }
    }

    void Parser::pushInt(int value) {
        switch (m_type.top()) {
            case ObjectType:
                m_parents.top()->push(m_keys.top(), value);
                m_keys.pop();
                break;
            case ArrayType:
                m_parents.top()->push(value);
                break;
            default:
                throw std::runtime_error("Bad type need ObjectType or ArrayType");
        }
    }

    void Parser::pushFloat(float value) {
        switch (m_type.top()) {
            case ObjectType:
                m_parents.top()->push(m_keys.top(), value);
                m_keys.pop();
                break;
            case ArrayType:
                m_parents.top()->push(value);
                break;
            default:
                throw std::runtime_error("Bad type need ObjectType or ArrayType");
        }
    }

    void Parser::pushDouble(double value) {
        switch (m_type.top()) {
            case ObjectType:
                m_parents.top()->push(m_keys.top(), value);
                m_keys.pop();
                break;
            case ArrayType:
                m_parents.top()->push(value);
                break;
            default:
                throw std::runtime_error("Bad type need ObjectType or ArrayType");
        }
    }

    void Parser::pushString() {
        switch (m_type.top()) {
            case ObjectType:
                m_parents.top()->push(m_keys.top(), m_value);
                m_keys.pop();
                break;
            case ArrayType:
                m_parents.top()->push(m_value);
                break;
            default:
                throw std::runtime_error("Bad type need ObjectType or ArrayType");
        }
    }

    void Parser::act(char c) {
        switch (c) {
            case '{':
                openObject();
                break;
            case '}':
                closeObject();
                break;
            case '[':
                openArray();
                break;
            case ']':
                closeArray();
                break;
            case ':':
                if (m_type.top() != KeyType) {
                    throw std::runtime_error("Bad type need KeyType");
                }
                m_type.pop();
                if (m_key.empty()) {
                    throw std::runtime_error("Empty key not allowed");
                }
                m_keys.push(m_key);
                m_type.push(ValueType);
                m_key = "";
                break;
            case ',':
                savingKeyValue();
                switch (m_type.top()) {
                    case ObjectType:
                        m_type.push(KeyType);
                        break;
                    case ArrayType:
                        m_type.push(ValueType);
                        break;
                    default:
                        throw std::runtime_error("Bad type need ObjectType or ArrayType");
                }
                break;
            default:
                switch (m_type.top()) {
                    case KeyType:
                        gettingKey(c);
                        break;
                    case ValueType:
                        gettingValue(c);
                        break;
                    default:
                        std::cout << "Error bad type" << std::endl;
                        break;
                }
                break;
        }
    }

    Config::Object &Parser::Parse() {
        if (!m_file->is_open()) {
            throw std::runtime_error("Cannot open file");
        }
        std::string line;
        while (getline(*m_file, line)) {
            for (char c: line) {
                act(c);
            }
        }
        return *m_json;
    }
}