#pragma once
#include <string>

enum class eCommandTypes
{
    INVALID = 0,
    QuitCommand,
    Count
};


inline eCommandTypes StringToCommand(const std::string& string)
{
    if (string == "QuitCommand")				    return eCommandTypes::QuitCommand;
    return eCommandTypes::INVALID;
}

inline std::string CommandToString(eCommandTypes type)
{
    if (type == eCommandTypes::QuitCommand)				        return "QuitCommand";

    return "Invalid";
}