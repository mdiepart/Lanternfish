#ifndef DAY_SCHEDULE_H
#define DAY_SCHEDULE_H

#define NB_PTS_MAX 30

#define MONDAY 0
#define TUESDAY 1
#define WEDNESDAY 2
#define THURSDAY 3
#define FRIDAY 4
#define SATURDAY 5
#define SUNDAY 6

typedef struct s_point{
  unsigned char h;
  unsigned char m;
  unsigned char dc;
} point;

class DaySchedule{
  private:
    static const unsigned char BYTES_PER_DAY = 1+(3*NB_PTS_MAX);
    unsigned char nbPts = 0;
    unsigned char dow = 0;
    unsigned char ptHour[NB_PTS_MAX] = {0};
    unsigned char ptMin[NB_PTS_MAX] = {0};
    unsigned char ptDC[NB_PTS_MAX] = {0};
    void setSize(unsigned char n);

  public:
    DaySchedule(unsigned char dow);
    unsigned char getSize() const;
    point getPoint(unsigned char pos) const;
    bool addPoint(point pt);
    bool delPoint(unsigned char pos);
    bool changeDay(unsigned char day);
    bool save();
    
};

#endif
