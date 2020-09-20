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
  unsigned char h; //Hour
  unsigned char m; //Minutes
  unsigned char dc; //Duty cycle
} point;

class DaySchedule{
  private:
    static const unsigned char BYTES_PER_DAY = 1+(3*NB_PTS_MAX);
    unsigned char nbPts = 0;
    unsigned char dow = 0;
    unsigned char ptHour[NB_PTS_MAX] = {0};
    unsigned char ptMin[NB_PTS_MAX] = {0};
    unsigned char ptDC[NB_PTS_MAX] = {0};
    unsigned char prevD = 0, prevH = 0, prevM = 0, prevDC = 0;
    unsigned char nextD = 0, nextH = 0, nextM = 0, nextDC = 0;
    void setSize(const unsigned char n);

  public:
    DaySchedule(const unsigned char dayOfWeek);
    unsigned char getSize() const;
    point getPoint(const unsigned char pos) const;
    bool addPoint(const point pt);
    bool delPoint(const unsigned char pos);
    bool changeDay(const unsigned char day);
    bool save();
    void reset();
    unsigned char getPower(const unsigned char hh, const unsigned char mm,
        const unsigned char ss) const;
};

#endif
