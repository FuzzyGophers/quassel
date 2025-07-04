// SPDX-FileCopyrightText: 2005-2025 Quassel Project <devel@quassel-irc.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <array>
#include <functional>
#include <tuple>
#include <type_traits>
#include <utility>

#include <QDebug>
#include <QVariant>
#include <QVariantList>

#include <boost/optional.hpp>

// ---- Function traits --------------------------------------------------------------------------------------------------------------------

namespace detail {

/// @cond DOXYGEN_CANNOT_PARSE_THIS

// Primary template
template<typename Func>
struct FuncHelper : public FuncHelper<decltype(&Func::operator())>
{};

// Overload for free function
template<typename R, typename... Args>
struct FuncHelper<R (*)(Args...)>
{
    using FunctionType = std::function<R(Args...)>;
    using ReturnType = R;
    using ArgsTuple = std::tuple<Args...>;
};

// Overload for member function with non-const call operator
template<typename C, typename R, typename... Args>
struct FuncHelper<R (C::*)(Args...)> : public FuncHelper<R (*)(Args...)>
{
    using ClassType = C;
};

// Overload for member function with const call operator
template<typename C, typename R, typename... Args>
struct FuncHelper<R (C::*)(Args...) const> : public FuncHelper<R (C::*)(Args...)>
{};

/// @endcond

}  // namespace detail

/**
 * Provides traits for the given callable.
 */
template<typename Callable>
using FunctionTraits = detail::FuncHelper<Callable>;

// ---- Invoke function with argument list -------------------------------------------------------------------------------------------------

namespace detail {

// Helper for invoking the callable, wrapping its return value in a QVariant (default-constructed if callable returns void).
// The correct overload is selected via SFINAE.
template<typename Callable, typename... Args>
auto invokeWithArgs(const Callable& c, Args&&... args)
    -> std::enable_if_t<std::is_void<typename FunctionTraits<Callable>::ReturnType>::value, QVariant>
{
    c(std::forward<Args>(args)...);
    return QVariant{};
}

template<typename Callable, typename... Args>
auto invokeWithArgs(const Callable& c, Args&&... args)
    -> std::enable_if_t<!std::is_void<typename FunctionTraits<Callable>::ReturnType>::value, QVariant>
{
    return QVariant::fromValue(c(std::forward<Args>(args)...));
}

// Helper for unpacking the argument list via an index sequence
template<typename Callable, std::size_t... Is, typename ArgsTuple = typename FunctionTraits<Callable>::ArgsTuple>
boost::optional<QVariant> invokeWithArgsList(const Callable& c, const QVariantList& args, std::index_sequence<Is...>)
{
    // Sanity check that all types can be converted
    std::array<bool, std::tuple_size<ArgsTuple>::value> convertible{
        {args[Is].canConvert<std::decay_t<std::tuple_element_t<Is, ArgsTuple>>>()...}};
    for (size_t i = 0; i < convertible.size(); ++i) {
        if (!convertible[i]) {
            qWarning() << "Cannot convert parameter" << i << "from type" << args[static_cast<int>(i)].typeName()
                       << "to expected argument type";
            return boost::none;
        }
    }

    // Invoke callable with unmarshalled arguments
    return invokeWithArgs(c, args[Is].value<std::decay_t<std::tuple_element_t<Is, ArgsTuple>>>()...);
}

}  // namespace detail

/**
 * Invokes the given callable with the arguments contained in the given variant list.
 *
 * The types contained in the given QVariantList are converted to the types expected by the callable.
 * If the invocation is successful, the returned optional contains a QVariant with the return value,
 * or an invalid QVariant if the callable returns void.
 * If the conversion fails, or if the argument count does not match, this function returns boost::none
 * and the callable is not invoked.
 *
 * @param c    Callable
 * @param args Arguments to be given to the callable
 * @returns An optional containing a QVariant with the return value if the callable could be invoked with
 *          the given list of arguments; otherwise boost::none
 */
template<typename Callable>
boost::optional<QVariant> invokeWithArgsList(const Callable& c, const QVariantList& args)
{
    using ArgsTuple = typename FunctionTraits<Callable>::ArgsTuple;
    constexpr auto tupleSize = std::tuple_size<ArgsTuple>::value;

    if (tupleSize != args.size()) {
        qWarning().nospace() << "Argument count mismatch! Expected: " << tupleSize << ", actual: " << args.size();
        return boost::none;
    }
    return detail::invokeWithArgsList(c, args, std::make_index_sequence<tupleSize>{});
}

/**
 * Invokes the given member function pointer on the given object with the arguments contained in the given variant list.
 *
 * The types contained in the given QVariantList are converted to the types expected by the member function.
 * If the invocation is successful, the returned optional contains a QVariant with the return value,
 * or an invalid QVariant if the member function returns void.
 * If the conversion fails, or if the argument count does not match, this function returns boost::none
 * and the member function is not invoked.
 *
 * @param c    Callable
 * @param args Arguments to be given to the member function
 * @returns An optional containing a QVariant with the return value if the member function could be invoked with
 *          the given list of arguments; otherwise boost::none
 */
template<typename R, typename C, typename... Args>
boost::optional<QVariant> invokeWithArgsList(C* object, R (C::*func)(Args...), const QVariantList& args)
{
    if (sizeof...(Args) != args.size()) {
        qWarning().nospace() << "Argument count mismatch! Expected: " << sizeof...(Args) << ", actual: " << args.size();
        return boost::none;
    }
    return detail::invokeWithArgsList([object, func](Args&&... args) { return (object->*func)(std::forward<decltype(args)>(args)...); },
                                      args,
                                      std::make_index_sequence<sizeof...(Args)>{});
}
