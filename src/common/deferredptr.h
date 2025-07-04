// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "common-export.h"

#include <memory>
#include <type_traits>

#include <QObject>

namespace detail {

/**
 * Deleter for storing QObjects in STL containers and smart pointers
 *
 * QObject should always be deleted by calling deleteLater() on them, so the event loop can
 * perform necessary cleanups.
 */
struct DeferredDeleter
{
    /// Deletes the given QObject
    void operator()(QObject* object) const
    {
        if (object)
            object->deleteLater();
    }
};

}  // namespace detail

/**
 * Unique pointer for QObjects with deferred deletion
 *
 * @tparam T Type derived from QObject
 */
template<typename T>
using DeferredUniquePtr = std::unique_ptr<T, detail::DeferredDeleter>;

/**
 * Helper function for creating a DeferredUniquePtr
 *
 * An instance of T is created and returned in a DeferredUniquePtr, such that it will be deleted via
 * QObject::deleteLater().
 *
 * @tparam T       The type to create
 * @tparam Args    Constructor argument types
 * @param[in] args Constructor arguments
 * @returns A DeferredUniquePtr holding a new instance of T
 */
template<typename T, typename... Args>
DeferredUniquePtr<T> makeDeferredUnique(Args... args)
{
    static_assert(std::is_base_of<QObject, T>::value, "Type must inherit from QObject");
    return DeferredUniquePtr<T>(new T(std::forward<Args>(args)...));
}

/**
 * Shared pointer for QObjects with deferred deletion
 *
 * @tparam T Type derived from QObject
 */
template<typename T>
using DeferredSharedPtr = std::shared_ptr<T>;

/**
 * Helper function for creating a DeferredSharedPtr
 *
 * An instance of T is created and returned in a DeferredSharedPtr, such that it will be deleted via
 * QObject::deleteLater().
 *
 * @tparam T       The type to create
 * @tparam Args    Constructor argument types
 * @param[in] args Constructor arguments
 * @returns A DeferredSharedPtr holding a new instance of T
 */
template<typename T, typename... Args>
DeferredSharedPtr<T> makeDeferredShared(Args... args)
{
    static_assert(std::is_base_of<QObject, T>::value, "Type must inherit from QObject");
    return DeferredSharedPtr<T>(new T(std::forward<Args>(args)...), detail::DeferredDeleter{});
}
