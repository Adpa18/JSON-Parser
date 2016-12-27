//
// Created by wery_a on 18/12/16.
//

#include "Object.hpp"

namespace JSON {
    Object::Object() {

    }

    Object::~Object() {
        for (ValueMap::const_iterator it = m_values.begin(); it != m_values.end(); ++it) {
            delete it->second;
        }
    }

    Object::ValueMap    const &Object::getValues() const {
        return m_values;
    };

    ValueMap    const& Object::operator*() const {
        return m_values;
    }

    Value*& Object::operator[](std::string const &key) {
        return m_values[key];
    }

    Value* const & Object::operator[](std::string const &key) const {
        return m_values.find(key)->second;
    }

    Value *Object::get(std::string const &key) const {
        ValueMap::const_iterator it = m_values.find(key);
        if (it == m_values.end() || it->second->type != CHAR) {
            throw std::runtime_error("Bad key " + it->first);
        }
        return it->second;
    }

    char Object::get(std::string const &key, char &rvalue) const {
        rvalue = getChar(key);
        return rvalue;
    }

    int Object::get(std::string const &key, int &rvalue) const {
        rvalue = getInt(key);
        return rvalue;
    }

    float Object::get(std::string const &key, float &rvalue) const {
        rvalue = getFloat(key);
        return rvalue;
    }

    double Object::get(std::string const &key, double &rvalue) const {
        rvalue = getDouble(key);
        return rvalue;
    }

    std::string Object::get(std::string const &key, std::string &rvalue) const {
        rvalue = getString(key);
        return rvalue;
    }

    Array *Object::get(std::string const &key, Array *&rvalue) const {
        rvalue = getArray(key);
        return rvalue;
    }

    Object *Object::get(std::string const &key, Object *&rvalue) const {
        rvalue = getObject(key);
        return rvalue;
    }

    char Object::getChar(std::string const &key) const {
        ValueMap::const_iterator it = m_values.find(key);
        if (it == m_values.end() || it->second->type != CHAR) {
            return 0;
        }
        return it->second->value.c;
    }

    int Object::getInt(std::string const &key) const {
        ValueMap::const_iterator it = m_values.find(key);
        if (it == m_values.end() || it->second->type != INT) {
            return 0;
        }
        return it->second->value.i;
    }

    float Object::getFloat(std::string const &key) const {
        ValueMap::const_iterator it = m_values.find(key);
        if (it == m_values.end() || it->second->type != FLOAT) {
            return 0;
        }
        return it->second->value.f;
    }

    double Object::getDouble(std::string const &key) const {
        ValueMap::const_iterator it = m_values.find(key);
        if (it == m_values.end() || it->second->type != DOUBLE) {
            return 0;
        }
        return it->second->value.d;
    }

    std::string Object::getString(std::string const &key) const {
        ValueMap::const_iterator it = m_values.find(key);
        if (it == m_values.end() || it->second->type != STRING) {
            return 0;
        }
        return *it->second->value.s;
    }

    Array *Object::getArray(std::string const &key) const {
        ValueMap::const_iterator it = m_values.find(key);
        if (it == m_values.end() || it->second->type != ARRAY) {
            return 0;
        }
        return it->second->value.array;
    }

    Object *Object::getObject(std::string const &key) const {
        ValueMap::const_iterator it = m_values.find(key);
        if (it == m_values.end() || it->second->type != OBJECT) {
            return 0;
        }
        return it->second->value.object;
    }

    void Object::push(std::string const &key, Value *value) {
        m_values[key] = value;
    }

    void Object::push(std::string const &key, char value) {
        m_values[key] = new Value(value);
    }

    void Object::push(std::string const &key, int value) {
        m_values[key] = new Value(value);
    }

    void Object::push(std::string const &key, float value) {
        m_values[key] = new Value(value);
    }

    void Object::push(std::string const &key, double value) {
        m_values[key] = new Value(value);
    }

    void Object::push(std::string const &key, std::string const &value) {
        m_values[key] = new Value(value);
    }

    void Object::push(std::string const &key, Array *value) {
        m_values[key] = new Value(value);
    }

    void Object::push(std::string const &key, Object *value) {
        m_values[key] = new Value(value);
    }

    std::string const Object::toString() const {
        std::stringstream   ss;
        ss << "{";
        Object::ValueMap::const_iterator last_it = --m_values.end();
        for (Object::ValueMap::const_iterator it = m_values.begin(); it != m_values.end(); ++it) {
            ss << "\"" << it->first << "\"" << ":" << *(it->second);
            if (it != last_it) {
                ss << ",";
            }
        }
        ss << "}";
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Object &object) {
        return os << object.toString();
    }

    std::ostream &operator<<(std::ostream &os, const Object *object) {
        return operator<<(os, *object);
    }
}

