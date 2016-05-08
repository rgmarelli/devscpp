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
 *
 * -----------------
 * This program is an example of use of Time class
 */

#include "../include/Time.h"
#include <iostream>

int main(int argc, char *argv[])
{
    DEVS::Time t1(1000*DEVS::Time::mili_to_nano_sec);
    std::cout << "t1 = " + t1.to_string() << std::endl;
    DEVS::Time t2 = t1*0.5;
    std::cout << "t2 = t1*0.5 =" + t2.to_string() << std::endl;
    DEVS::Time t3 = t2 - t1; // This is bad, don't!
    std::cout << "t3 = t2-t1 =" + t3.to_string() << std::endl;
    DEVS::Time t4 = t1 - t2;
    std::cout << "t4 = t1-t2 =" + t4.to_string() << std::endl;
    DEVS::Time t5 = (t1+t2)*-1; // This is bad, don't!
    std::cout << "t5 = (t1+t2)*-1 =" + t5.to_string() << std::endl;
    return 0;
}

