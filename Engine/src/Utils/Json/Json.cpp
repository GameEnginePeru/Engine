#include "Utils/Json/Json.h"

namespace ENGINE_NAMESPACE
{
    static void SkipWhiteSpace(const CString& json, size_t& i) 
    {
        while (i < json.size() && isspace(json[i])) 
        {
            ++i;
        }
    }

    static JSON ParseValue(const CString& json, size_t& i);

    static JSON ParseNull(const CString& json, size_t& i) 
    {
        if (json.substr(i, 4) == "null") 
        {
            i += 4;
            return JSON();
        }
        throw std::runtime_error("invalid JSON: expected 'null'");
    }

    static JSON ParseBool(const CString& json, size_t& i) 
    {
        if (json.substr(i, 4) == "true") 
        {
            i += 4;
            return JSON(true);
        }
        else if (json.substr(i, 5) == "false") 
        {
            i += 5;
            return JSON(false);
        }
        throw std::runtime_error("invalid JSON: expected 'true' or 'false'");
    }

    static JSON ParseNumber(const CString& json, size_t& i) 
    {
        size_t j = i;
        bool hasDecimal = false;
        while (j < json.size() && (isdigit(json[j]) || json[j] == '-' || json[j] == '+' || json[j] == '.')) 
        {
            if (json[j] == '.') 
            {
                hasDecimal = true;
            }
            ++j;
        }
        if (j == i) 
        {
            throw std::runtime_error("invalid JSON: expected a number");
        }
        double n = std::stod(json.substr(i, j - i));
        i = j;
        return JSON(n);
    }

    static JSON ParseString(const CString& json, size_t& i) 
    {
        if (json[i] != '\"') 
        {
            throw std::runtime_error("invalid JSON: expected '\"'");
        }
        ++i;
        CString s;
        while (i < json.size() && json[i] != '\"') 
        {
            if (json[i] == '\\') 
            {
                ++i;
                if (i == json.size()) 
                {
                    throw std::runtime_error("invalid JSON: incomplete escape sequence");
                }
                switch (json[i]) 
                {
                case '\"':
                case '\\':
                case '/':
                    s += json[i];
                    break;
                case 'b':
                    s += '\b';
                    break;
                case 'f':
                    s += '\f';
                    break;
                case 'n':
                    s += '\n';
                    break;
                case 'r':
                    s += '\r';
                    break;
                case 't':
                    s += '\t';
                    break;
                case 'u': 
                {
                    if (i + 4 >= json.size()) 
                    {
                        throw std::runtime_error("invalid JSON: incomplete unicode escape sequence");
                    }
                    CString hex(json.substr(i + 1, 4));
                    unsigned int codepoint = std::stoul(hex, nullptr, 16);
                    if (codepoint <= 0x7f) 
                    {
                        s += static_cast<char>(codepoint);
                    }
                    else if (codepoint <= 0x7ff) 
                    {
                        s += static_cast<char>(0xc0 | (codepoint >> 6));
                        s += static_cast<char>(0x80 | (codepoint & 0x3f));
                    }
                    else if (codepoint <= 0xffff) 
                    {
                        s += static_cast<char>(0xe0 | (codepoint >> 12));
                        s += static_cast<char>(0x80 | ((codepoint & 0xfc) >> 2));
                        s += static_cast<char>(0x80 | ((codepoint & 0x03) << 4)
                            | ((json[i + 5] & 0x3c) >> 2));
                        s += static_cast<char>(0x80 | (json[i + 5] & 0x03));
                    }
                    else 
                    {
                        throw std::runtime_error("invalid JSON: invalid unicode escape sequence");
                    }
                    i += 4;
                    break;
                }
                default:
                    throw std::runtime_error("invalid JSON: invalid escape sequence");
                }
            }
            else 
            {
                s += json[i];
            }
            ++i;
        }
        if (i == json.size()) 
        {
            throw std::runtime_error("invalid JSON: incomplete string");
        }
        ++i;
        return JSON(s);
    }

    static JSON ParseArray(const CString& json, size_t& i) 
    {
        if (json[i] != '[') 
        {
            throw std::runtime_error("invalid JSON: expected '['");
        }
        ++i;
        SkipWhiteSpace(json, i);
        CVector<JSON> a;
        if (i < json.size() && json[i] != ']') 
        {
            while (true) 
            {
                a.push_back(ParseValue(json, i));
                SkipWhiteSpace(json, i);
                if (i == json.size()) 
                {
                    throw std::runtime_error("invalid JSON: incomplete array");
                }
                if (json[i] == ']') 
                {
                    break;
                }
                if (json[i] != ',') 
                {
                    throw std::runtime_error("invalid JSON: expected ','");
                }
                ++i;
                SkipWhiteSpace(json, i);
            }
        }
        ++i;
        return JSON(a);
    }

    static JSON ParseObject(const CString& json, size_t& i) 
    {
        if (json[i] != '{') 
        {
            throw std::runtime_error("invalid JSON: expected '{'");
        }
        ++i;
        SkipWhiteSpace(json, i);
        CUnorderedMap<CString, JSON> o;
        if (i < json.size() && json[i] != '}') 
        {
            while (true) 
            {
                CString key = ParseString(json, i).AsString();
                SkipWhiteSpace(json, i);
                if (i == json.size() || json[i] != ':') 
                {
                    throw std::runtime_error("invalid JSON: expected ':'");
                }
                ++i;
                SkipWhiteSpace(json, i);
                o[key] = ParseValue(json, i);
                SkipWhiteSpace(json, i);
                if (i == json.size()) 
                {
                    throw std::runtime_error("invalid JSON: incomplete object");
                }
                if (json[i] == '}') 
                {
                    break;
                }
                if (json[i] != ',') 
                {
                    throw std::runtime_error("invalid JSON: expected ','");
                }
                ++i;
                SkipWhiteSpace(json, i);
            }
        }
        ++i;
        return JSON(o);
    }

    static JSON ParseValue(const CString& json, size_t& i) 
    {
        SkipWhiteSpace(json, i);
        if (i == json.size()) 
        {
            throw std::runtime_error("invalid JSON: incomplete value");
        }
        switch (json[i]) 
        {
        case 'n':
            return ParseNull(json, i);
        case 't':
        case 'f':
            return ParseBool(json, i);
        case '\"':
            return ParseString(json, i);
        case '[':
            return ParseArray(json, i);
        case '{':
            return ParseObject(json, i);
        default:
            return ParseNumber(json, i);
        }
    }

    JSON JSON::Parse(const CString& json) 
    {
        size_t i = 0;
        JSON val = ParseValue(json, i);
        SkipWhiteSpace(json, i);
        if (i < json.size()) 
        {
            throw std::runtime_error("invalid JSON: trailing characters");
        }
        return val;
    }

    CString JSON::EscapeString(const CString& input) const 
    {
        CString output;
        output.reserve(input.length() + 2);  // Add some extra space for escaped characters
        for (const auto& c : input) 
        {
            switch (c) 
            {
            case '\"':
                output += "\\\"";
                break;
            case '\\':
                output += "\\\\";
                break;
            case '\b':
                output += "\\b";
                break;
            case '\f':
                output += "\\f";
                break;
            case '\n':
                output += "\\n";
                break;
            case '\r':
                output += "\\r";
                break;
            case '\t':
                output += "\\t";
                break;
            default:
                output += c;
                break;
            }
        }
        return output;
    }

    void JSON::Print(std::ostream& os) const
    {
        switch (m_Type) 
        {
        case JSONType::NULL_TYPE:
        {
            os << "null";
            break;
        }
        case JSONType::BOOL_TYPE:
        {
            os << (m_Value == "true" ? "true" : "false");
            break;
        }
        case JSONType::NUMBER_TYPE:
        {
            std::stringstream ss(m_Value);
            double d;
            ss >> d;
            os << d;
            break;
        }
        case JSONType::STRING_TYPE:
        {
            os << "\"" << EscapeString(m_Value) << "\"";
            break;
        }
        case JSONType::ARRAY_TYPE:
        {
            os << "[ ";
            for (size_t i = 0; i < m_Array.size(); ++i) 
            {
                m_Array[i].Print(os);
                if (i != m_Array.size() - 1) 
                {
                    os << ", ";
                }
            }
            os << " ]";
            break;
        }
        case JSONType::OBJECT_TYPE:
        {
            os << "{ ";
            size_t i = 0;
            for (const auto& [key, value] : m_Object) 
            {
                os << "\"" << EscapeString(key) << "\": ";
                value.Print(os);
                if (i != m_Object.size() - 1) 
                {
                    os << ", ";
                }
                ++i;
            }
            os << " }";
            break;
        }
        default:
            break;
        }
        os << std::endl;
    }
}