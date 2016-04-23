/* devsCPP - a DEVS C++ library
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
#ifndef DEVS_CPP_SIMULATOR__
#define DEVS_CPP_SIMULATOR__

#include "OutputMessage.h"
#include "ExternalMessage.h"
#include "Time.h"

namespace DEVS {

/*
 * Simulator es la interfaz basica de todo simulador y el principio que permite
   abstraer del lugar donde se ejecuta el modelo.
 */

class Simulator
{
public:
    Simulator() : error_(false)
    {}

    virtual ~Simulator() 
    {}

    virtual void externalTransition(TIME t, ExternalMessage* message)=0;
    virtual OutputMessage* internalTransition(TIME t)=0;
    virtual TIME nextTN() const =0;

    virtual std::string model_name() const = 0;

    bool error() { return error_; }

protected:
    void error( bool e ) { error_ = e; }

private:
    bool error_;

}; // Simulator

}; // DEVS

#endif


