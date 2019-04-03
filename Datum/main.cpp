//
//  main.cpp
//  Datum
//
//  Created by florian Herrmann on 02.04.19.
//  Copyright © 2019 florian Herrmann. All rights reserved.
//

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;
int lookupTabelMonthLengthNormal[] = {31,28,31,30,31,30,31,31,30,31,30,31};
int lookupTabelMonthLengthSchift[] = {31,29,31,30,31,30,31,31,30,31,30,31};
class date{
private:
    string dateString;
    int day;
    int month;
    int year;
    bool shiftYear;
public:

    bool get_shiftYear(){
        return shiftYear;
    }
   void getdate(){
       cout << "Inteface for Date input"  << endl;
       char buffer[256];
       while (true) {
           cout << "Enter the Day:" << endl;
           cin >> buffer;
           if (atoi(buffer) <= 31 && atoi(buffer) >= 1) {
               day = atoi(buffer);
               break;
           }
           cout << "Ther is a maximum of 31 days in a month" << endl;
       }
       while (true) {
           cout << "Enter the Month:" << endl;
           cin >> buffer;
           if (atoi(buffer) <= 12 && atoi(buffer) >= 1) {
               month = atoi(buffer);
               break;
           }
           cout << "Ther is a maximum of 12 month in a year" << endl;
       }
       cout << "Enter the Year:" << endl;
       cin >> buffer;
       year = atoi(buffer);
       cout << "The date you entered:" << day << "." << month << "." << year << endl;
    }
    void schiftYear(){
        if (year%4 == 0 && (year%100 != 0 || year%400 == 0)) {
            shiftYear = 1;
        }
        else{
            shiftYear = 0;
        }
        
    }
    int dayOfTheYear(){
        int count1 = 0;
        int days = 0;
        if (shiftYear == 0) {
            for (count1; count1 <= (month-2); count1++) {
                days += lookupTabelMonthLengthNormal[count1];
            }
        }
        else if (shiftYear == 1) {
            for (count1; count1 <= (month-2); count1++) {
                days += lookupTabelMonthLengthSchift[count1];
            }
        }
        days += day;
        return days;
    }
};

date array[10];
int main(int argc, const char * argv[]) {
    date test1;
    test1.getdate();
    test1.schiftYear();
    cout << test1.get_shiftYear() << endl;
    cout << test1.dayOfTheYear() << endl;
   
    return 0;
}
