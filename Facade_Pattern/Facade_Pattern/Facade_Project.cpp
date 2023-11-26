#include <iostream>
#include <vector>
#include <map>
using namespace std;

class SetTime {
public :
	void upTime()
	{
		cout << "시간을 1시간 올렸습니다." << endl;
	}
	void downTime()
	{
		cout << "시간을 1시간 내렸습니다." << endl;
	}
};

class SetAlarm {
public:
	void onAlarm()
	{
		cout << "알람을 켰습니다." << endl;
	}
	void offAlarm()
	{
		cout << "알람을 껐습니다." << endl;
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
	void turnOnAlarm()
	{
		setAlarm->onAlarm();
	}
	void turnOffAlarm()
	{
		setAlarm->offAlarm();
	}
};

int main()
{
	FacadeAlarm* alamr = new FacadeAlarm();
	
	alamr->uppingTime();
	alamr->downdingTime();
	alamr->turnOnAlarm();
	alamr->turnOffAlarm();

	return 0;
}