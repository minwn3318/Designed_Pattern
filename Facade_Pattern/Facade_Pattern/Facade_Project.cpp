#include <iostream>
#include <vector>
#include <map>
using namespace std;

static unsigned int hour = 0;
static bool ring = false;

class SetTime {
public :
	void upTime()
	{
		hour++;
		cout << "시간을 1시간 올렸습니다. : " << hour << endl;
	}
	void downTime()
	{
		hour--;
		cout << "시간을 1시간 내렸습니다. : " << hour << endl;
	}
};

class SetAlarm {
public:
	void turingUPAlarm()
	{
		ring = !ring;
		switch (ring)
		{
		case true :
			cout << "알람을 켰습니다. : " << ring << endl;
			break;
		case false :
			cout << "알람을 껐습니다. : " << ring << endl;
			break;
		default:
			break;
		}
	}
};

class FacadeAlarm {
	SetTime* setTime;
	SetAlarm* setAlarm;
public :
	FacadeAlarm() : setTime(), setAlarm() 
	{
		cout << "알람이 생성되었습니다." << endl << endl;
	}
	void uppingTime()
	{
		setTime->upTime();
	}
	void downdingTime()
	{
		setTime->downTime();
	}
	void turnAlarm()
	{
		setAlarm->turingUPAlarm();
	}
};

int main()
{
	FacadeAlarm* alamr = new FacadeAlarm();
	
	alamr->turnAlarm();
	alamr->turnAlarm();
	alamr->turnAlarm();

	return 0;
}