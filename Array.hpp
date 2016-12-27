//
// Created by wery_a on 18/12/16.
//

#ifndef JSONPARSER_ARRAY_HPP
#define JSONPARSER_ARRAY_HPP

#include <vector>
#include "AObject.hpp"
#include "Value.hpp"

namespace JSON {
    class Array: public AObject {
    public:
        typedef std::vector<Value*>  ValueList;
        Array();
        virtual ~Array();
    private:
        ValueList   m_array;

    public:
        ValueList   const &getValues() const;

    public:
//        Value   &operator[](unsigned int i);
//        const Value &operator[](unsigned int i) const;

    public:
        void push(Value *value);
        void push(char value);
        void push(int value);
        void push(float value);
        void push(double value);
        void push(std::string const &value);
        void push(Array *value);
        void push(Object *value);

    public:
        std::string const   toString() const;
        friend std::ostream& operator<<(std::ostream& os, const Array &array);
        friend std::ostream& operator<<(std::ostream& os, const Array *array);
    };
}

#endif //JSONPARSER_ARRAY_HPP
