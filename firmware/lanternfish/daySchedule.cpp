#include <stddef.h>
#include "daySchedule.h"
#include <EEPROM.h>

DaySchedule::DaySchedule(unsigned char dow){
  nbPts = 0;
  dow = MONDAY;
}

unsigned char DaySchedule::getSize() const{
  return nbPts;
}

point DaySchedule::getPoint(unsigned char pos) const{
    if(pos >= getSize()){
        return point{0, 0, 0};
    }else{
        return point{ptHour[pos], ptMin[pos], ptDC[pos]};    
    }
}

/*
 * Adds a point to the schedule. 
 * Automatically sorts the point at the correct position according to it's time.
 * If a point already exists for that time, the duty cycle is simply updated.
 *
 * In:
 *  pt: a point containing hour, minute, duty cycle
 * Out:
 *  bool: true if the point was successfully added. 
 *        false otherwise (error or schedule full)
 */
bool DaySchedule::addPoint(point pt){
    //If the list is full we return false
    if(getSize() == NB_PTS_MAX){
        return false;
    }
    
    //Search for the correct position
    unsigned char i = 0;
    while( (pt.h < ptHour[i]) && (i < getSize()) ){
        i++;
    }
    while( (pt.m < ptMin[i]) && (i < getSize()) ){
        i++;
    }
    
    //Add the point
    if(pt.m == ptMin[i]){
        ptDC[i] = pt.dc;
    }else{
        unsigned char tmp1 = 0, tmp2 = 0;
        
        //Hours
        tmp1 = ptHour[i];
        ptHour[i] = pt.h;
        for(unsigned char j = i; j < getSize()-1; j++){
            tmp2 = ptHour[j+1];
            ptHour[j+1] = tmp1;
            tmp1 = tmp2;
        }
        
        //Minutes
        tmp1 = ptMin[i];
        ptMin[i] = pt.m;
        for(unsigned char j = i; j < getSize()-1; j++){
            tmp2 = ptMin[j+1];
            ptMin[j+1] = tmp1;
            tmp1 = tmp2;
        }
        
        //Duty Cycles
        tmp1 = ptDC[i];
        ptDC[i] = pt.dc;
        for(unsigned char j = i; j < getSize()-1; j++){
            tmp2 = ptDC[j+1];
            ptDC[j+1] = tmp1;
            tmp1 = tmp2;
        }
        
        setSize(getSize()+1);
    }
    return save();
}

/*
 * Deletes a point from the schedule given it's position.
 * 
 * In:
 *  pos : unsigned char containing the position [0; size[
 * Out:
 *  bool: true if point was successfully found and deleted
 *        false otherwise
 */
bool DaySchedule::delPoint(unsigned char pos){
    if( pos >= getSize() ){
        return false;
    }
    
    // Shifts the remaining points
    for(unsigned char i = pos; i < getSize()-1; i++){
        ptHour[i] = ptHour[i+1];
        ptMin[i] = ptMin[i+1];
        ptDC[i] = ptDC[i+1];
    }
    
    //Sets the last point to zeros
    ptHour[getSize()-1] = 0;
    ptMin[getSize()-1] = 0;
    ptDC[getSize()-1] = 0;
    
    //Update size
    setSize(getSize()-1);
    
    return save();
}

/*
 * Update the schedule to another day of the week. The data will come from
 * the internal EEPROM of the device.
 *
 * In: 
 *  unsigned char day: number of the day of the week [0;6]. 0 is monday.
 * Out:
 *  bool: true if successful
 *        false otherwise
 */
bool DaySchedule::changeDay(unsigned char day){
    if( day >= 7 ){
        return false;
    }
    size_t offset = day*BYTES_PER_DAY;
    unsigned char n = EEPROM.read(offset);
    
    // If the size we read is higher than NB_PTS_MAX we consider the memory
    // as unitialized
    if( n>NB_PTS_MAX ){
        setSize(0);
    }else{
        setSize(n);    
    }
    
    // Read memory
    for(unsigned char i = 0; i < getSize(); i++){
        ptHour[i] = EEPROM.read(offset + 3*i);
        ptMin[i] = EEPROM.read(offset + 3*i + 1);
        ptDC[i] = EEPROM.read(offset + 3*i + 2);
    }
    for(unsigned char i = getSize(); i < NB_PTS_MAX; i++){
        ptHour[i] = 0;
        ptMin[i] = 0;
        ptDC[i] = 0;
    }
    dow = day;
    return true;
}

/*
 * Saves the schedule for the current day in the EEPROM of the device
 * In:
 *  /
 * Out:
 *  bool: true if successfully saved
 *        false otherwise
 */
bool DaySchedule::save(){
    size_t offset = dow*BYTES_PER_DAY;
    EEPROM.update(offset, getSize());
    for(unsigned char i = 0; i < NB_PTS_MAX; i++){
        EEPROM.update(offset + 3*i, ptHour[i]);
        EEPROM.update(offset + 3*i + 1, ptMin[i]);
        EEPROM.update(offset + 3*i + 2, ptDC[i]);
    }
    
}

void DaySchedule::setSize(unsigned char n){
    nbPts = n;
}

void DaySchedule::reset(){
  for(unsigned char i = 0; i < getSize(); i++){
    ptHour[i] = 0;
    ptMin[i] = 0;
    ptDC[i] = 0;
  }
  setSize(0);
}
