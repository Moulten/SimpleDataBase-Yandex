#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

struct Day{
private:
	int value;

public:
	explicit Day(const int& new_value){
		if (new_value <=0 || new_value>31){
			string ss = "Day value is invalid: "+to_string(new_value);
			throw invalid_argument(ss);
		}
		value = new_value;
	}

	int get() const{
		return value;
	}
};

struct Month{
private:
	int value;

public:
	explicit Month(const int& new_value){
		if (new_value <=0 || new_value>12){

			string ss = "Month value is invalid: "+to_string(new_value);
			throw invalid_argument(ss);
		}
		value = new_value;
	}

	int get() const {
		return value;
	}
};

struct Year{
private:
	int value;

public:
	explicit Year(const int& new_value){
		value = new_value;
	}

	int get() const{
		return value;
	}
};

class Date {
public:
	Date(const Year& new_year, const Month& new_month, const Day& new_day){
		year = new_year.get();
		month = new_month.get();
		day = new_day.get();
	}

  int GetYear() const{
	  return year;
  }

  int GetMonth() const{
	  return month;
  }
  int GetDay() const{
	  return day;
  }
  string ForPrint() const
  {
	  stringstream buffer;
	  buffer << setfill('0');
	  buffer << setw(4) << year << '-' << setw(2) << month << '-' << setw(2) << day;
	  return buffer.str();
  }

private:
  int year;
  int month;
  int day;
};

bool operator<(const Date& lhs, const Date& rhs){
	if (lhs.GetYear()!= rhs.GetYear()){
		return lhs.GetYear()< rhs.GetYear();
	}
	else if(lhs.GetMonth()!= rhs.GetMonth() ){
		return lhs.GetMonth()< rhs.GetMonth();
	}
	else {
		return lhs.GetDay() < rhs.GetDay();
}
}
class Database {
public:
  void AddEvent(const Date& date, const string& event){
	  base[date].insert(event);
  }
  bool DeleteEvent(const Date& date, const string& event){
	  if (base.count(date) == 0){
		  return false;
	  }
	  if(base[date].count(event)>0){
		  base[date].erase(event);
		  return true;
	  }
	  else
		  return false;
  }
  int  DeleteDate(const Date& date){
	  int size = base[date].size();
	  base.erase(date);
	  return size;
  }

  string Find(const Date& date) const{
	  string ans;
	  if (base.count(date) > 0) {
	     for(auto x: base.at(date)){
	    	 ans +=x+"\n";
	     }
	  }
	  return ans;
  }

  void Print() const{
	  for (auto x: base){
		  for( auto y: x.second){
			  cout<<x.first.ForPrint()<<" "<<y<< endl;
		  }
	  }
  }

private:
  map<Date, set<string>> base;
};

Date transform(stringstream& ss){
	string check;
	ss>>check;
	stringstream buf(check);
	int y, m, d;
	char def1, def2;
	buf >> y >> def1 >> m >> def2 >> d;
	//������ ����� ��� �� �� ��� � ��������� ������, ����� �������� �� ����, ��� � �� �������� ����������
	if(buf.fail() == true || buf.peek() !=EOF){
		throw invalid_argument("Wrong date format: "+check);
	}
	return {Year(y),Month(m),Day(d)};
	}

void ADD(stringstream& ss, Database& db){
  Date input = transform(ss);
  string event;
  ss>>event;
  db.AddEvent(input,event);
}

void DEL(stringstream& ss, Database& db){
  Date input = transform(ss);
  string event;
  ss>>event;

	if(event != ""){
		  if(db.DeleteEvent(input,event)){
			  cout<<"Deleted successfully"<<endl;
		  }
		  else{
			  cout<<"Event not found"<<endl;
		  }
	}
	else{
		  cout<<"Deleted "<<db.DeleteDate(input)<<" events"<<endl;
	}
}

void FIND(stringstream& ss, Database& db){
	Date input = transform(ss);
	cout<<db.Find(input)<<endl;
}

int main() {
  Database db;

  string command;
  while (getline(cin, command)) {
    // �������� ������� � ������ ����� � ����������� ������
	  stringstream ss(command);
	  string command_1;
	  ss>>command_1;

	  if (command_1 == ""){
		  continue;
	  }
	  try{
	  if (command_1 == "Add"){
		  ADD(ss, db);
		  continue;
	  }
	  else if(command_1 == "Find"){
		  FIND(ss, db);
		  continue;
	  }
	  else if(command_1 == "Del"){
		  DEL(ss, db);
		  continue;
	  }
	  else if(command_1 == "Print"){
			  db.Print();
			  continue;
	  }
	  else{
		throw invalid_argument("Unknown command: "+ command_1);
	  }
	  }catch(invalid_argument& ex){
		  cout<<ex.what();
		  break;
	  }
  }

  return 0;
}