/**
* ############################################################
* # THIS IS A TEST FILE - IT DOES NOT DEMONSTRATE FULL USAGE #
* # OF THE ENGINE. IT ONLY DEMONSTRATES NEW ITEMS THAT ARE   #
* # BEING TESTED BY THE CR TEAM.                             #
* #                                                          #
* #          MAY THE CODING GODS BLESS THIS CODE!            #
* ############################################################
*/

#include <assert.h>
#include <stddef.h>
#include <new>
#include <iostream>

#include "CRCore.hpp"
#include "DNDDApp.hpp"

int main(int argc, char* argv[])
{
    // Default exit code
    int exitCode = CRE::STATUS_OK;

    // Create our app
    CRE::App * dndapp = new(std::nothrow) TestApp("DDND", 800, 600);
    assert(NULL != dndapp and "main() can't create application");

    //dndapp->set_max_updates(1);

    // Execute the application
    exitCode = testApp->run();

    delete dndapp;

    dndapp = NULL;

    return exitCode;
}
