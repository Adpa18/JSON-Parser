//
// Created by wery_a on 22/12/16.
//

#include "Array.hpp"

namespace JSON {
    Array::Array() {

    }

    Array::~Array() {
        for (ValueList::const_iterator it = m_array.begin(); it != m_array.end(); ++it) {
            delete *it;
        }
    }

    Array::ValueList   const& Array::getValues() const {
        return m_array;
    }

//    Value& Array::operator[](unsigned int i) {
//        return m_array[i];
//    }
//
//    const Value& Array::operator[](unsigned int i) const {
//        return m_array[i];
//    }

    void Array::push(Value *value) {
        m_array.push_back(value);
    }

    void Array::push(char value) {
        m_array.push_back(new Value(value));
    }

    void Array::push(int value) {
        m_array.push_back(new Value(value));
    }

    void Array::push(float value) {
        m_array.push_back(new Value(value));
    }

    void Array::push(double value) {
        m_array.push_back(new Value(value));
    }

    void Array::push(std::string const &value) {
        m_array.push_back(new Value(value));
    }

    void Array::push(Array *value) {
        m_array.push_back(new Value(value));
    }

    void Array::push(Object *value) {
        m_array.push_back(new Value(value));
    }

    std::string const Array::toString() const {
        std::stringstream   ss;

        ss << "[";
        Array::ValueList::const_iterator last_it = --m_array.end();
        for (Array::ValueList::const_iterator it = m_array.begin(); it != m_array.end(); ++it) {
            ss << *(*it);
            if (it != last_it) {
                ss << ",";
            }
        }
        ss << "]";
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Array &array) {
        return os << array.toString();
    }

    std::ostream &operator<<(std::ostream &os, const Array *array) {
        return operator<<(os, *array);
    }
}