// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#ifndef __libol__Value__
#define __libol__Value__

#include <string>
#include <map>
#include <vector>
#include <cstdint>

namespace libol {
    class Object;
    class Array;

    class Value {
    public:
        enum {
            UNDEFINED,
            OBJECT, // Object
            ARRAY, // Array
            STRING, // std::string
            INTEGER, // int32_t
            LARGE_INTEGER, // int64_t
            FLOAT, // float
            BOOL // bool
        } type;
        void *value;

        Value() : type(UNDEFINED), value(nullptr) {
        }

        void destroy();

        template<class T>
        T &as() {
            return *reinterpret_cast<T *>(value);
        }

        std::string toString(size_t indent = 0);

        static Value create(Object &val);

        static Value create(Array &val);

        static Value create(std::string &val);

        static Value create(const char *&val);

        static Value create(uint64_t &val);

        static Value create(uint32_t &val);

        static Value create(uint16_t &val);

        static Value create(uint8_t &val);

        static Value create(int64_t &val);

        static Value create(int32_t &val);

        static Value create(int16_t &val);

        static Value create(int8_t &val);

        static Value create(float &val);

        static Value create(bool &val);
    };

    class Object {
        std::map<std::string, Value> map;
    public:
        template<class T>
        void setv(std::string name, T value) {
            set(name, Value::create(value));
        }

        void set(std::string name, Value value);

        Value get(std::string name);

        size_t size();

        std::map<std::string, Value>::iterator begin() {
            return map.begin();
        }

        std::map<std::string, Value>::iterator end() {
            return map.end();
        }
    };

    class Array {
        std::vector<Value> vector;
    public:
        template<class T>
        void pushv(T value) {
            push(Value::create(value));
        }

        void push(Value value);

        size_t size();

        Value at(size_t index);
    };
}

#endif /* defined(__libol__Value__) */
