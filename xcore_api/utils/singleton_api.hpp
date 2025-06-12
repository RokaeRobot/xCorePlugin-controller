/**
 * Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 
 * All Rights Reserved.
 * 
 * Information in this file is the intellectual property of Rokae Technology Co., Ltd,
 * And may contains trade secrets that must be stored and viewed confidentially.
 * 
 * @file singleton_api.hpp
 * @brief 提供单例的实现模板 
 */

#pragma once
#include <utility>

namespace xcore_api {
namespace utils {

/**
 * @brief 单例基类
 *    1:继承该类模板
 *    2:类内部声明DECLARE_SINGLETON宏
 *    3:构造函数析构函数设置为私有的
 * @example
 * class object : public xcore_api::utils::SingletonBaseAPI<object> {
 *    DECLARE_SINGLETON(object);
 * private:
 *      object(){}
 *      ~object(){}
 *  };
 */
template <typename T>
class SingletonBaseAPI {
public:

    /**
     * @brief 删除拷贝构造函数
     */
    SingletonBaseAPI(const SingletonBaseAPI&) = delete;

    /**
     * @brief 删除赋值运算符
     */
    SingletonBaseAPI& operator=(const SingletonBaseAPI&) = delete;

    /**
     * @brief 获取单例实例的对象
     * @return T& 
     */
    static T& GetInstance() {
        static T instance;
        return instance;
    }

    /**
     * @brief 获取单例实例的指针
     * @return T* 
     */
    static T* GetInstancePtr() {
        return &GetInstance();
    }
protected:

    /**
     * @brief 构造函数声明为保护，禁止实例化
     */
    SingletonBaseAPI() = default;

    /**
     * @brief 析构函数声明为保护防止delete对象
     */
    virtual ~SingletonBaseAPI() = default;
};

}
}

/**
 * @brief 单例使用宏定义
 */
#define DECLARE_SINGLETON( type ) \
    friend class xcore_api::utils::SingletonBaseAPI< type >

#define SINGLETON_INSTANCE( type ) \
    type::GetInstancePtr()

#define INIT_SINGLETON( type ) \
    SINGLETON_INSTANCE(type)
    