/**
 * Interval: make interval checks pretier
 * 
 * Copyright (C) 2014 Mauricio Jabur
 * 
 * 
 * Version 20140528
 *  * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INTERVAL_H
#define INTERVAL_H

//#include "application.h"
#if defined(WIRING) && WIRING >= 100
#include <Wiring.h>
#elif defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <string.h>
#include <Stream.h>

class Interval {
    public:
        long t;
        long dt;
        
        Interval(long timeout);
        bool check();
        void reset();
};

//////////////////////////////////////////////////////////
// Interval.cpp
//////////////////////////////////////////////////////////

//#include "Interval.h"

Interval::Interval(long timeout){
    dt = timeout;
    reset();
}

bool Interval::check() {
    if (millis()-t > dt){
        t += dt;
        return true;
    }
    return false;
}

void Interval::reset() {
    t = millis();
}
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
#endif //INTERVAL_H

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
