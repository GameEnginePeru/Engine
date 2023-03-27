#include "Utils/Time/Time.h"
#include <iomanip>

namespace ENGINE_NAMESPACE
{
    CString Time::IGetTime(const char* format)
    {
        if (!format)
        {
            format = m_TimeFormat.c_str();
        }

        auto t = std::time(nullptr);
        auto* tm = std::localtime(&t);

        std::ostringstream stream;
        stream << std::put_time(tm, format);

        return stream.str();
    }
}
