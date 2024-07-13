/**
 * @file base.hpp
 * @brief 包含字符串编码转换、字符串检查和基类定义的头文件。
 *
 * 此文件定义了两个主要的字符串编码转换函数(utf8_to_gbk, gbk_to_utf8)，
 * 一个字符串检查函数(IsPureNumber)以及一个用于演示虚函数概念的基类(Base)。
 */

#pragma once
#include <iconv.h>
#include <filesystem>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>
#include <conio.h>

using namespace std;

/**
 * 将UTF-8编码的字符串转换为GBK编码。
 *
 * @param utf8_str UTF-8编码的字符串。
 * @return 转换后的GBK编码字符串。如果转换失败，返回空字符串。
 */
string utf8_to_gbk(const string &utf8_str)
{
    iconv_t cd = iconv_open("GBK", "UTF-8");
    if (cd == (iconv_t)-1)
        return "";
    size_t in_bytes_left = utf8_str.size();
    size_t out_bytes_left = in_bytes_left * 2;
    char *in_buf = const_cast<char *>(utf8_str.c_str());
    char out_buf[out_bytes_left];
    char *out_buf_start = out_buf;
    size_t ret = iconv(cd, &in_buf, &in_bytes_left, &out_buf_start, &out_bytes_left);
    if (ret == (size_t)-1)
    {
        iconv_close(cd);
        return "";
    }
    *out_buf_start = '\0';
    iconv_close(cd);
    return string(out_buf);
}

/**
 * 将GBK编码的字符串转换为UTF-8编码。
 *
 * @param gbk_str GBK编码的字符串。
 * @return 转换后的UTF-8编码字符串。如果转换失败，返回空字符串。
 */
string gbk_to_utf8(const string &gbk_str)
{
    iconv_t cd = iconv_open("UTF-8", "GBK");
    if (cd == (iconv_t)-1)
        return "";
    size_t in_bytes_left = gbk_str.size();
    size_t out_bytes_left = in_bytes_left * 2;
    char *in_buf = const_cast<char *>(gbk_str.c_str());
    char out_buf[out_bytes_left];
    char *out_buf_start = out_buf;
    size_t ret = iconv(cd, &in_buf, &in_bytes_left, &out_buf_start, &out_bytes_left);
    if (ret == (size_t)-1)
    {
        iconv_close(cd);
        return "";
    }
    *out_buf_start = '\0';
    iconv_close(cd);
    return string(out_buf);
}

/**
 * 检查字符串是否全部由数字组成。
 *
 * @param input 待检查的字符串。
 * @return 如果字符串全部由数字组成，则返回true；否则返回false。
 */
bool IsPureNumber(const string &input)
{
    return all_of(input.begin(), input.end(), ::isdigit);
}

/**
 * 基类，定义了一组接口，用于演示虚函数的概念。
 */
class Base
{
public:
    /**
     * 纯虚函数，要求派生类实现加法操作。
     *
     * @return 加法操作的结果。
     */
    virtual int Add() const = 0;

    /**
     * 纯虚函数，要求派生类实现保存操作。
     */
    virtual void Save() const = 0;

    /**
     * 纯虚函数，要求派生类实现删除操作。
     *
     * @return 删除操作的结果。
     */
    virtual int Delete() const = 0;

    /**
     * 纯虚函数，要求派生类实现编辑操作。
     *
     * @return 编辑操作的结果。
     */
    virtual int Edit() const = 0;
};