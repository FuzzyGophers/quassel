# SPDX-FileCopyrightText: 2018-2025 Quassel Project <devel@quassel-irc.org>
# SPDX-License-Identifier: GPL-2.0-or-later

# The compile(r) features required to build the Quassel source.
# This list is used by CMake to determine if the compiler can build the code.
set(QUASSEL_COMPILE_FEATURES
    cxx_aggregate_default_initializers
    cxx_alias_templates
    cxx_constexpr
    cxx_decltype
    cxx_default_function_template_args
    cxx_defaulted_functions
    cxx_defaulted_move_initializers
    cxx_delegating_constructors
    cxx_deleted_functions
    cxx_enum_forward_declarations
    cxx_explicit_conversions
    cxx_final
    cxx_generalized_initializers
    cxx_generic_lambdas
    cxx_inheriting_constructors
    cxx_lambdas
    cxx_lambda_init_captures
    cxx_noexcept
    cxx_nonstatic_member_init
    cxx_nullptr
    cxx_override
    cxx_range_for
    cxx_raw_string_literals
    cxx_return_type_deduction
    cxx_right_angle_brackets
    cxx_rvalue_references
    cxx_static_assert
    cxx_strong_enums
    cxx_thread_local
    cxx_trailing_return_types
    cxx_uniform_initialization
    cxx_user_literals
    cxx_variadic_macros
    cxx_variadic_templates
    cxx_template_template_parameters
)
