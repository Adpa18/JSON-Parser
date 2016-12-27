//
// Created by wery_a on 18/12/16.
//

#ifndef JSONPARSER_VALUE_HPP
#define JSONPARSER_VALUE_HPP

#include <iostream>
#include <ostream>
#include <string>
#include <sstream>

namespace JSON {
    class Object;
    class Array;
    enum ValueType {
        UNKNOWN = 0,
        CHAR,
        INT,
        FLOAT,
        DOUBLE,
        STRING,
        ARRAY,
        OBJECT
    };
    union ValueValue {
        char    c;
        int     i;
        float   f;
        double  d;
        std::string *s;
        Array       *array;
        Object      *object;
    };

    struct Value {
        Value(char value);
        Value(int value);
        Value(float value);
        Value(double value);
        Value(std::string value);
        Value(Array *value);
        Value(Object *value);
        ~Value();
        ValueType   type;
        ValueValue  value;
        std::string const   toString() const;
        friend std::ostream& operator<<(std::ostream& os, const Value &value);
        friend std::ostream& operator<<(std::ostream& os, const Value *value);
    };
}


#endif //JSONPARSER_VALUE_HPP
