//
// Created by wery_a on 22/12/16.
//
#include <iostream>
#include <fstream>
#include "Parser.hpp"

//#define DEBUG_MODE

void    Debug(std::string const &txt) {
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
        m_parents.push(new Object());
        if (m_json == nullptr) {
            m_json = dynamic_cast<Object *>(m_parents.top());
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
        AObject *current = m_parents.top();
        m_parents.pop();
        if (m_parents.empty()) {
            Debug("Object end");
            return;
        }
        AObject *parent = m_parents.top();
        Array *parentArray = dynamic_cast<Array*>(parent);
        if (parentArray) {
            parent->push(dynamic_cast<Object *>(current));
        } else {
            parent->push(m_keys.top(), dynamic_cast<Object *>(current));
            m_keys.pop();
        }
    }

    void Parser::openArray() {
        Debug("Openning Array");
        m_parents.push(new Array());
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

        AObject *current = m_parents.top();
        m_parents.pop();
        if (m_parents.empty()) {
            Debug("Array end");
            return;
        }
        AObject *parent = m_parents.top();
        Array *parentArray = dynamic_cast<Array*>(parent);
        if (parentArray) {
            parent->push(dynamic_cast<Array *>(current));
        } else {
            parent->push(m_keys.top(), dynamic_cast<Array *>(current));
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
            //TODO get value type
        }
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
        m_value = "";
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

    Object *Parser::Parse() {
        if (!m_file->is_open()) {
            return nullptr;
        }
        std::string line;
        while (getline(*m_file, line)) {
            for (char c: line) {
                act(c);
            }
        }
        return m_json;
    }
}