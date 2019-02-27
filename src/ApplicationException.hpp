////////////////////////////////////////////////////////////////////////////////
/// @file ApplicationException.hpp
/// @brief The application exceptions.
///
/// This class is an exception that handles application errors. The only time
/// this class is used is from the Application constructor, if any of the
/// resource initialization fails.
////////////////////////////////////////////////////////////////////////////////

#ifndef _CAMBRE_APPLICATION_EXCEPTION_H_
#define _CAMBRE_APPLICATION_EXCEPTION_H_

#include <exception>

/// @class ApplicationException
/// @brief The application exceptions.
///
/// This class is derived from std::runtime_error instead of std::exception so
/// that an error msg can be passed to the constructor.
class ApplicationException : public std::runtime_error
{
public:
    /// @brief The constructor.
    ///
    /// The constructor provides a method to pass a string into the exception so
    /// that a unique message can be displayed when an error occurs.
    ApplicationException(std::string const &error) : std::runtime_error(error)
    {};
};

#endif
