#include <stddef.h>
#include "daySchedule.h"
#include <EEPROM.h>

DaySchedule::DaySchedule(unsigned char dayOfWeek){
  nbPts = 0;
  dow = MONDAY;
  changeDay(dow);
}

/*
 * Returns the number of points in the selected schedule
 *
 */
unsigned char DaySchedule::getSize() const{
  return nbPts;
}

point DaySchedule::getPoint(const unsigned char pos) const{
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
bool DaySchedule::addPoint(const point pt){
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
bool DaySchedule::delPoint(const unsigned char pos){
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
bool DaySchedule::changeDay(const unsigned char day){
    if( day >= 7 ){
        return false;
    }
    size_t offset = day*BYTES_PER_DAY;
    unsigned char n = EEPROM.read(offset);
    
    // If the size we read is higher than NB_PTS_MAX we consider the memory
    // as unitialized
    if(n > NB_PTS_MAX){
        setSize(0);
    }else{
        setSize(n);    
    }
    
    // Read memory
    for(unsigned char i = 0; i < getSize(); i++){
        ptHour[i] = EEPROM.read(offset + 3*i + 1);
        ptMin[i] = EEPROM.read(offset + 3*i + 2);
        ptDC[i] = EEPROM.read(offset + 3*i + 3);
    }
    for(unsigned char i = getSize(); i < NB_PTS_MAX; i++){
        ptHour[i] = 0;
        ptMin[i] = 0;
        ptDC[i] = 0;
    }
    dow = day;
    
    // Loads last point of previous day with > 0 points
    unsigned int counter = 0, i = dow-1;
    while(EEPROM.read(i*BYTES_PER_DAY) == 0 || counter <= 7){
        i--;
        counter++;
        if(i > 6){       // if we underflow
            i = 6
        }
    } // i now contains the previous DOW with at least 1 point (if counter <= 6)
    
    if(counter > 7){ // There is no point in the schedule
        prevD = prevH = prevM = prevDC = 0;
        nextD = nextH = nextM = nextDC = 0;
        return true;
    }
    
    // Load value of prev point
    prevD = i;
    unsigned char n = EEPROM.read(i*BYTES_PER_DAY);
    prevH = EEPROM.read(i*BYTES_PER_DAY + 3*(n-1) + 1);
    prevM = EEPROM.read(i*BYTES_PER_DAY + 3*(n-1) + 2);
    prevDC = EEPROM.read(i*BYTES_PER_DAY + 3*(n-1) + 3);
    
    // Load first point of next day with > 0 points
    i = dow+1;
    while(EEPROM.read(i*BYTES_PER_DAY) == 0){
        i = (i+1)%7;
    } 
    
    // Load value of next point
    nextD = i;
    nextH = EEPROM.read(i*BYTES_PER_DAY + 1);
    nextM = EEPROM.read(i*BYTES_PER_DAY + 2);
    nextDC = EEPROM.read(i*BYTES_PER_DAY + 3);
    
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
        EEPROM.update(offset + 3*i + 1, ptHour[i]);
        EEPROM.update(offset + 3*i + 2, ptMin[i]);
        EEPROM.update(offset + 3*i + 3, ptDC[i]);
    }
    
}

void DaySchedule::setSize(const unsigned char n){
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

unsigned char DaySchedule::getPower(const unsigned char hh, const unsigned char mm, const unsigned char ss) const{
    
    unsigned char pt1D = 0, pt1H = 0, pt1M = 0, pt1DC = 0
    unsigned char pt2D = 0, pt2H = 0, pt2M = 0, pt2DC = 0;
    
    if(nbPts > 0){
        //Determine point before
        int i = 0;
        while(ptHour[i] < hh && i < LENGTH){
            i++;
        }
        while(ptHour[i] == hh && ptMin[i] < mm && i < LENGTH){
            i++;
        }
        i--;
        
        if(i < 0){
            pt1D = prevD;
            pt1H = prevH;
            pt1M = prevM;
            pt1DC = prevDC;
        }else{
            pt1D = dow;
            pt1H = ptHour[i];
            pt1M = ptMin[i];
            pt1DC = ptDC[i];
        }
        
        //i+1 is the next point. If >= nbPts we take the one of the next day
        i++;
        if(i >= nbPts ){
            pt2D = nextD;
            pt2H = nextH;
            pt2M = nextM;
            pt2DC = nextDC;
        }else{
            pt2D = dow;
            pt2H = ptHour[i];
            pt2M = ptMin[i];
            pt2DC = ptDC[i];
        }
    }else{
        pt1D = prevD;
        pt1H = prevH;
        pt1M = prevM;
        pt1DC = prevDC;
        pt2D = nextD;
        pt2H = nextH;
        pt2M = nextM;
        pt2DC = nextDC;
    }
    
    //Compute adequate power
    //Compute time from pt1 to pt2
    unsigned int nbHours = (24 + pt2H - pt1H)%24;
    if((pt1D == pt2D) && (pt1H <= pt2H && pt1M <= pt2M)){
        nbHours += 6*24;
    }else{
        nbHours += 24*(7 + pt2D - pt1D)%7;
    }
    int nbMin = pt2M - pt1M;
    
    unsigned long int length_12 = 60*(nbHours*60+nbMin); // length in seconds
    
    //compute time from pt1 to hh:mm:ss
    nbHours = (24 + hh - pt1H)%24;
    if((pt1D == dow) && (pt1H <= hh && pt1M <= mm)){
        nbHours += 6*24;
    }else{
        nbHours += 24*(7 + dow - pt1D)%7;
    }
    nbMin = mm - pt1M;
    unsigned long int length_1t = 60*(nbHours*60+nbMin)+ss; // length in seconds
    
    return pt1DC + (pt2DC-pt1DC)*length_1t/length_12;
    
}
