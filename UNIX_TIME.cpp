// C++ program for the above approach

// Unix time is in seconds and
// Humar Readable Format:
// DATE:MONTH:YEAR:HOUR:MINUTES:SECONDS,
// Start of unix time:01 Jan 1970, 00:00:00
#include <bits/stdc++.h>
using namespace std;

#include "mainwindow.h"
#include "ui_mainwindow.h"

 #define UNUSED(expr) do { (void)(expr); } while (0)

// Function to convert unix time to
// Human readable format
QString MainWindow::unixTimeToHumanReadable(long int seconds)
{

    // Save the time in Human
    // readable format
    QString ans = "";

    // Number of days in month
    // in normal year
    int daysOfMonth[] = { 31, 28, 31, 30, 31, 30,
                          31, 31, 30, 31, 30, 31 };

    long int currYear, daysTillNow, extraTime, extraDays,
        index, date, month, hours, minutes, secondss,
        flag = 0;

    UNUSED(date);


    // Calculate total days unix time T
    daysTillNow = seconds / (24 * 60 * 60);
    extraTime = seconds % (24 * 60 * 60);
    currYear = 1970;

    // Calculating current year
    while (true) {
        if (currYear % 400 == 0
            || (currYear % 4 == 0 && currYear % 100 != 0)) {
            if (daysTillNow < 366) {
                break;
            }
            daysTillNow -= 366;
        }
        else {
            if (daysTillNow < 365) {
                break;
            }
            daysTillNow -= 365;
        }
        currYear += 1;
    }
    // Updating extradays because it
    // will give days till previous day
    // and we have include current day
    extraDays = daysTillNow + 1;

    if (currYear % 400 == 0
        || (currYear % 4 == 0 && currYear % 100 != 0))
        flag = 1;

    // Calculating MONTH and DATE
    month = 0, index = 0;
    if (flag == 1) {
        while (true) {

            if (index == 1) {
                if (extraDays - 29 < 0)
                    break;
                month += 1;
                extraDays -= 29;
            }
            else {
                if (extraDays - daysOfMonth[index] < 0) {
                    break;
                }
                month += 1;
                extraDays -= daysOfMonth[index];
            }
            index += 1;
        }
    }
    else {
        while (true) {

            if (extraDays - daysOfMonth[index] < 0) {
                break;
            }
            month += 1;
            extraDays -= daysOfMonth[index];
            index += 1;
        }
    }

    // Current Month
    if (extraDays > 0) {
        month += 1;
        date = extraDays;
    }
    else {
        if (month == 2 && flag == 1)
            date = 29;
        else {
            date = daysOfMonth[month - 1];
        }
    }

    // Calculating HH:MM:YYYY
    hours = extraTime / 3600;
    minutes = (extraTime % 3600) / 60;
    secondss = (extraTime % 3600) % 60;

    h_u = hours;
    m_u = minutes;


//    ans.append(QString::number(date));
//    ans.append(".");
//    ans.append(QString::number(month));
//    ans.append(".");
//    ans.append(QString::number(currYear));
//    ans.append(" ");

    // winter UTC+2 / summer UNC+3
    int time_zone = 0;
    if(ui->radioButton->isChecked()) {
        time_zone = 2;
    }
    else{
        time_zone = 3;
    }

    h_u += time_zone;

    ans.append(QString::number(hours + time_zone));
    //ans.append(QString::number(hours));                       // UTC
    ans.append(":");

    if(minutes < 10){                                           // set 0
        ans.append("0");
    }

    ans.append(QString::number(minutes));                       // %3", 2

    ans.append(":");

    if(secondss < 10){                                           // set 0
        ans.append("0");
    }
    ans.append(QString::number(secondss));

    // Return the time
    return ans;
}

