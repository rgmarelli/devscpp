/* 
 * devsCPP - a DEVS C++ library
 * Copyright (c) 2013 Ricardo Guido Marelli
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef DEVS_CPP_EVENT__
#define DEVS_CPP_EVENT__

#include "Simulator.h"
#include "Message.h"
#include "Time.h"

namespace DEVS {

class Event
{
public:
    bool external() const { return internal_==false; }
    bool internal() const { return internal_==true; }
    TIME TN() const { return TN_; }
    ExternalMessage* message() const { return message_; }
    Simulator* simulator() const { return simulator_; }

    static Event createExternalEvent(TIME TN,Simulator* simulator,ExternalMessage* message) {
        return Event(TN,simulator,message,false);
    }

    static Event createInternalEvent(TIME TN,Simulator* simulator) {
        return Event(TN,simulator,NULL,true);
    }
private:
    Event(TIME TN,Simulator* simulator,ExternalMessage* message, bool internal) :
                 TN_(TN),simulator_(simulator),message_(message), internal_(internal)
    {} 
    TIME TN_;
    Simulator* simulator_;
    ExternalMessage *message_;    
    bool internal_;
}; // Event

}; // DEVS

#endif


