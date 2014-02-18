/*
 * Macros.h
 */
#ifndef __MACROS_H__
#define __MACROS_H__

#define WIN_WIDTH CCDirector::sharedDirector()->getWinSize().width
#define WIN_HEIGHT CCDirector::sharedDirector()->getWinSize().height

inline std::string appendIntToString(int _number, std::string _str)
{
    std::stringstream ss;
    ss << _str << _number;
    return std::string(ss.str());
}

#endif