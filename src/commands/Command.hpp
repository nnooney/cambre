////////////////////////////////////////////////////////////////////////////////
/// @file Command.hpp
/// @brief A base class to implement the Command Pattern for dispatching events.
///
/// This class represents a generic command.
////////////////////////////////////////////////////////////////////////////////

#ifndef _CAMBRE_COMMAND_H_
#define _CAMBRE_COMMAND_H_

class Command
{
public:
    virtual ~Command(void);
    virtual void execute(void) = 0;
};

#endif
