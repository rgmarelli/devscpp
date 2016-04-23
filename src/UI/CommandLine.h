/*
 * Copyright (c) 2013-2014 Ricardo Guido Marelli
 * All rights reserved.
 *
 */
#ifndef DEVS_CPP_UI_COMMAND_LINE__
#define DEVS_CPP_UI_COMMAND_LINE__

#include "AbstractUI.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string>
#include <vector>

namespace DEVS {
namespace UI {

class CommandLine : public AbstractUI
{
public:
    CommandLine( Controller* controller ) : AbstractUI(controller)
    {
        std::vector<std::string> c;
        this->commands( controller->commands( &c ) );
    }

protected:

    static std::vector<std::string> &commands( std::vector<std::string> *v=NULL ) {
        static std::vector<std::string> c; 
        if( v != NULL ) {
            c.clear();
            for( unsigned int i=0;i<v->size();i++ ) {
                c.push_back( (*v)[i] );
            }
        }
        return c;
    }

    static char** cmd_completion (const char* text, int start, int end) {

        rl_attempted_completion_over = 1;
        char **matches = NULL;

        if (start == 0) {
            matches = rl_completion_matches (text, CommandLine::cmd_generator);
        }

        return (matches);
    }

    static char* cmd_generator (const char *text, int state) {
        /* 
           El código para este método esta basado en el ejemplo provisto en: GNU Readline Library documentation
           http://cnswww.cns.cwru.edu/php/chet/readline/readline.html
           Accedido: 18/08/2014
        */

        static int list_index=0, len=0;
        const char *name=NULL;

        if (!state) {
            list_index = 0;
            len = strlen (text);
        }

        while ( list_index < commands().size() ) {
            name = commands()[list_index].c_str();
            list_index++;
            if (strncmp (name, text, len) == 0) {
                char *s = (char*)malloc( strlen(name) + 1 );
                strcpy(s, name );
                return s;
            }
        }

        /* If no names matched, then return NULL. */
        return ((char *)NULL);
    }

    virtual void do_run() {

        char* input = NULL;

        rl_attempted_completion_function = CommandLine::cmd_completion;
        rl_bind_key('\t', rl_complete );

        bool do_exit = false;
        while( !do_exit) {

            // Display prompt and read input (n.b. input must be freed after use)...
            input = readline("DEVS> ");
     
            // Check for EOF.
            if (input) {

                // Add input to history.
                add_history(input);

                std::string command(input);
                command.erase(0, command.find_first_not_of(' ')); 
                command.erase(command.find_last_not_of(' ')+1); 
         
                if( command.size() > 0 ) {
                    Optional<std::string> result = this->send_command( command );
                    if( result ) {
                        std::cout << result.value() << std::endl;
                    }
                } 

                if( command == command_exit() ) {
                    do_exit = true;
                }

                // Free input.
                free(input);
            }
            else {
                std::cout << std::endl;
            }
        }
    }
};

} //namespace UI
} //namespace DEVS

#endif //DEVS_CPP_UI_COMMAND_LINE__
