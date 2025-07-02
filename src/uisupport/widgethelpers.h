// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <algorithm>
#include <initializer_list>
#include <tuple>
#include <utility>

#include <QAbstractButton>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QObject>
#include <QSpinBox>
#include <QTextEdit>

#include "colorbutton.h"
#include "fontselector.h"
#include "funchelpers.h"
#include "util.h"

namespace detail {

/**
 * Contains all supported widget changed signals.
 */
static const auto supportedWidgetChangedSignals = std::make_tuple(
        &ColorButton::colorChanged,
        &FontSelector::fontChanged,
        &QAbstractButton::toggled,
        selectOverload<int>(&QComboBox::currentIndexChanged),
        selectOverload<double>(&QDoubleSpinBox::valueChanged),
        &QGroupBox::toggled,
        &QLineEdit::textChanged,
        selectOverload<int>(&QSpinBox::valueChanged),
        &QTextEdit::textChanged
);

/**
 * Tries to find a changed signal that matches the given widget type, and connects that to the given receiver/slot.
 */
template<typename Receiver, typename Slot, std::size_t... Is>
bool tryConnectChangedSignal(const QObject* widget, const Receiver* receiver, Slot slot, std::index_sequence<Is...>)
{
    // Tries to cast the given QObject to the given signal's class type, and connects to receiver/slot if successful.
    // If *alreadyConnected is true, just returns false to prevent multiple connections.
    static const auto tryConnect = [](const QObject* object, auto sig, auto receiver, auto slot, bool* alreadyConnected) {
        if (!*alreadyConnected) {
            auto widget = qobject_cast<const typename FunctionTraits<decltype(sig)>::ClassType*>(object);
            if (widget) {
                *alreadyConnected = QObject::connect(widget, sig, receiver, slot);
                return *alreadyConnected;
            }
        }
        return false;
    };

    // Unpack the tuple and try to connect to each contained signal in order
    bool alreadyConnected{false};
    auto results = {tryConnect(widget, std::get<Is>(supportedWidgetChangedSignals), receiver, slot, &alreadyConnected)...};
    return std::any_of(results.begin(), results.end(), [](bool result) { return result; });
}

}  // namespace detail

/**
 * Connects the given widget's changed signal to the given receiver/context and slot.
 *
 * Changed signals for supported widgets are listed in detail::supportedWidgetChangedSignals.
 *
 * @note The slot must not take any arguments.
 *
 * @param widget   Pointer to the widget
 * @param receiver Receiver of the signal (or context for the connection)
 * @param slot     Receiving slot (or functor, or whatever)
 * @returns true if the widget type is supported, false otherwise
 */
template<typename Receiver, typename Slot>
bool connectToWidgetChangedSignal(const QObject* widget, const Receiver* receiver, Slot slot)
{
    return detail::tryConnectChangedSignal(widget,
                                           receiver,
                                           slot,
                                           std::make_index_sequence<std::tuple_size<decltype(detail::supportedWidgetChangedSignals)>::value>{});
}

/**
 * Connects the given widgets' changed signals to the given receiver/context and slot.
 *
 * Changed signals for supported widgets are listed in detail::supportedWidgetChangedSignals.
 *
 * @note The slot must not take any arguments.
 *
 * @param widget   Pointer to the widget
 * @param receiver Receiver of the signal (or context for the connection)
 * @param slot     Receiving slot (or functor, or whatever)
 * @returns true if all given widget types are supported, false otherwise
 */
template<typename Container, typename Receiver, typename Slot>
bool connectToWidgetsChangedSignals(const Container& widgets, const Receiver* receiver, Slot slot)
{
    bool success = true;
    for (auto&& widget : widgets) {
        success &= detail::tryConnectChangedSignal(widget,
                                                   receiver,
                                                   slot,
                                                   std::make_index_sequence<
                                                       std::tuple_size<decltype(detail::supportedWidgetChangedSignals)>::value>{});
    }
    return success;
}

/**
 * @overload
 * Convenience overload that allows brace-initializing the list of widgets.
 */
template<typename Receiver, typename Slot>
bool connectToWidgetsChangedSignals(const std::initializer_list<const QObject*>& widgets, const Receiver* receiver, Slot slot)
{
    return connectToWidgetsChangedSignals(std::vector<const QObject*>{widgets}, receiver, slot);
}
