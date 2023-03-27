#pragma once
#include "Core/CoreSTD.h"

namespace ENGINE_NAMESPACE
{
    enum class JSONType 
    {
        NULL_TYPE,
        BOOL_TYPE,
        NUMBER_TYPE,
        STRING_TYPE,
        ARRAY_TYPE,
        OBJECT_TYPE
    };

    class JSON 
    {
    public:
        JSON() : m_Type(JSONType::NULL_TYPE), m_Value("") {}
        JSON(bool b) : m_Type(JSONType::BOOL_TYPE), m_Value(b ? "true" : "false") {}
        JSON(double n) : m_Type(JSONType::NUMBER_TYPE), m_Value(std::to_string(n)) {}
        JSON(const CString& s) : m_Type(JSONType::STRING_TYPE), m_Value(s) {}
        JSON(CVector<JSON> v) : m_Type(JSONType::ARRAY_TYPE), m_Array(v) {}
        JSON(CUnorderedMap<CString, JSON> m) : m_Type(JSONType::OBJECT_TYPE), m_Object(m) {}

        JSONType GetType() const { return m_Type; }
        bool IsNull() const { return m_Type == JSONType::NULL_TYPE; }
        bool IsBool() const { return m_Type == JSONType::BOOL_TYPE; }
        bool IsNumber() const { return m_Type == JSONType::NUMBER_TYPE; }
        bool IsString() const { return m_Type == JSONType::STRING_TYPE; }
        bool IsArray() const { return m_Type == JSONType::ARRAY_TYPE; }
        bool IsObject() const { return m_Type == JSONType::OBJECT_TYPE; }

        bool AsBool() const { return m_Value == "true"; }
        double AsNumber() const { return std::stod(m_Value); }
        CString AsString() const { return m_Value; }
        CVector<JSON> AsArray() const { return m_Array; }
        CUnorderedMap<CString, JSON> AsObject() const { return m_Object; }

        CString EscapeString(const CString& input) const;

        static JSON Parse(const CString& json);
        void Print(std::ostream& os) const;

        JSON& operator[](const CString& key) 
        {
            if (m_Type == JSONType::OBJECT_TYPE) return m_Object[key];
            else throw std::runtime_error("Not an Object");
        }

        const JSON& operator[](const CString& key) const 
        {
            if (m_Type == JSONType::OBJECT_TYPE) {
                auto it = m_Object.find(key);
                if (it != m_Object.end()) {
                    return it->second;
                }
                else {
                    throw std::runtime_error("Key not found");
                }
            }
            else {
                throw std::runtime_error("Not an object");
            }
        }
    private:
        JSONType m_Type;
        CString m_Value;
        CVector<JSON> m_Array;
        CUnorderedMap<CString, JSON> m_Object;
    };
}