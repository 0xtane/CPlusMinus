#pragma once
class Date
{
private:
	int Day;
	char Month[4];
	int Year; // anno Domini
	int iMonth; // 1...12
	time_t Now; // in Visual Studio 64-bit integer, the number of seconds since January 1, 1970, 0:00 UTC
	const char MonthNames[12][4] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	char *pText = nullptr;
public:
	Date();
	Date(int d, int m, int y);
	Date(const Date &);
	virtual ~Date();
	char *ToString() const;
	void SetYear(int y);
	int GetYear() const { return Year; }
	void SetMonth(int);
	int GetMonth(char * = nullptr, int = 0) const;
	void SetDay(int);
	int GetDay() const  { return Day; }
	void SetDate(int, int, int);
	bool operator==(const Date &) const;
	bool operator<(const Date &) const;
	Date &operator=(const Date &);
	static Date CreateRandomDate(Date, Date);
private:
	bool IsLeap(int);
};

