//
// Created by wery_a on 18/12/16.
//

#ifndef JSONPARSER_OBJECT_HPP
#define JSONPARSER_OBJECT_HPP

#include <map>
#include <vector>
#include "AObject.hpp"
#include "Value.hpp"

namespace Config {
    class Object : public AObject {
    public:
        Object();

        virtual ~Object();

        typedef std::map<std::string, Value *> ValueMap;
    private:
        ValueMap m_values;

    public:
        ValueMap const &GetValues() const;

        std::vector<std::string> const GetKeys() const;

        ValueMap const &operator*() const;

        Value &operator[](std::string const &key);

        Value const &operator[](std::string const &key) const;

    public:
        Value &get(std::string const &key) const;

        char get(std::string const &key, char &rvalue) const;

        int get(std::string const &key, int &rvalue) const;

        float get(std::string const &key, float &rvalue) const;

        double get(std::string const &key, double &rvalue) const;

        std::string get(std::string const &key, std::string &rvalue) const;

        Array &get(std::string const &key, Array &rvalue) const;

        Object &get(std::string const &key, Object &rvalue) const;

    public:
        void push(std::string const &key, Value *value);

        void push(std::string const &key, char value);

        void push(std::string const &key, int value);

        void push(std::string const &key, float value);

        void push(std::string const &key, double value);

        void push(std::string const &key, std::string const &value);

        void push(std::string const &key, Array *value);

        void push(std::string const &key, Object *value);

    public:
        std::string const toString() const;

        friend std::ostream &operator<<(std::ostream &os, const Object &object);

        friend std::ostream &operator<<(std::ostream &os, const Object *object);
    };
}

#endif //JSONPARSER_OBJECT_HPP
