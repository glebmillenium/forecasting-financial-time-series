#include "datescaledraw.h"

DateScaleDraw::DateScaleDraw( const QTime &base ):
    baseTime( base )
{
    setLabelRotation( -20.0 );
}
QwtText DateScaleDraw::label( double v ) const
{
    int year = v / 100;
    double path = (int) ((v - year * 100.0));
    int month = round(path / (366.00001/30.4));
    int day = round(fmod(path * 366.0001 / 100, 30.04));
    if(day == 0) day++;
    month++;
    char* result = new char[256];
    char* nameMonth = new char[20];
    switch(month){
        case 1:
        sprintf(nameMonth, "%s", "янв");
        break;
    case 2:
        sprintf(nameMonth, "%s", "фев");
        break;
    case 3:
        sprintf(nameMonth, "%s", "март");
        break;
    case 4:
        sprintf(nameMonth, "%s", "апр");
        break;
    case 5:
        sprintf(nameMonth, "%s", "май");
        break;
    case 6:
        sprintf(nameMonth, "%s", "июнь");
        break;
    case 7:
        sprintf(nameMonth, "%s", "июль");
        break;
    case 8:
        sprintf(nameMonth, "%s", "авг");
        break;
    case 9:
        sprintf(nameMonth, "%s", "сен");
        break;
    case 10:
        sprintf(nameMonth, "%s", "окт");
        break;
    case 11:
        sprintf(nameMonth, "%s", "ноя");
        break;
    case 12:
        sprintf(nameMonth, "%s", "дек");
        break;
    }

    sprintf(result, "%d.%s.%d", day, nameMonth,  year);
    return (QwtText) result;
}
