/*AVR SOURCE FILES FOR GSM,SERIAL FUNCTIONALITY                         *
*                     Copyright (C) 2010  Justin Downs of GRounND LAB	*
*                     www.GroundLab.cc     1%                          	*
*                                                                 	*
* This program is free software: you can redistribute it and/or modify 	*
* it under the terms of the GNU General Public License as published by 	*
* the Free Software Foundation, either version 3 of the License, or    	*
* at your option) any later version.                                   	*
*                                                                      	*
* This program is distributed in the hope that it will be useful,      	*
* but WITHOUT ANY WARRANTY; without even the implied warranty of       	*
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        	*
* GNU General Public License for more details.                         	*
*                                                                      	*
* You should have received a copy of the GNU General Public License    	*
* with this program.  If not, see <http://www.gnu.org/licenses/>.      	* 
************************************************************************/

#include "gsmMaster.h"

gsmMASTER::gsmMASTER(Serial& _telit, uint32_t (*_millis)(), Serial* _debug)
:GSMbase(_telit, _millis, _debug), gsmSMS(_telit ,_millis, _debug), 
gsmGPRS(_telit, _millis, _debug)
{}

bool gsmMASTER::init(uint16_t band){
	if(GSMbase::init( band) && gsmSMS::smsInit()) return 1;
return 0;	
}
