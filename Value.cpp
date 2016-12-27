//
// Created by wery_a on 23/12/16.
//

#include "Value.hpp"
#include "Array.hpp"
#include "Object.hpp"

namespace JSON {
    Value::~Value() {
        switch (type) {
            case STRING:
                delete value.s;
                break;
            case ARRAY:
                delete value.array;
                break;
            case OBJECT:
                delete value.object;
                break;
            default:
                break;
        }
    }

    Value::Value(char value) {
        type = CHAR;
        this->value.c = value;
    }

    Value::Value(int value) {
        type = INT;
        this->value.i = value;
    }

    Value::Value(float value) {
        type = FLOAT;
        this->value.f = value;
    }

    Value::Value(double value) {
        type = DOUBLE;
        this->value.d = value;
    }

    Value::Value(std::string value) {
        type = STRING;
        this->value.s = new std::string(value);
    }

    Value::Value(Array *value) {
        type = ARRAY;
        this->value.array = value;
    }

    Value::Value(Object *value) {
        type = OBJECT;
        this->value.object = value;
    }

    std::string const Value::toString() const {
        std::stringstream ss;

        switch (type) {
            case CHAR:
                ss << value.c;
                break;
            case INT:
                ss << value.i;
                break;
            case FLOAT:
                ss << value.f;
                break;
            case DOUBLE:
                ss << value.d;
                break;
            case STRING:
                ss << "\"" << *(value.s) << "\"";
                break;
            case ARRAY:
                ss << *(value.array);
                break;
            case OBJECT:
                ss << *(value.object);
                break;
            default:
                throw std::runtime_error("Bad Type");
        }
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Value &value) {
        return os << value.toString();
    }
    std::ostream &operator<<(std::ostream &os, const Value *value) {
        return operator<<(os, *value);
    }

}