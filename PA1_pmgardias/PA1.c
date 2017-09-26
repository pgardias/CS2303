// PA1.c -- Przemek Gardias

#include <stdio.h>

// Global variable init
int given_year, startingDay; // Explained further below. given_year saves the year provided by user and startingDay keeps track of the first day of the month
int known_year = 2017; // Known year to use to find what day the given year starts on (in 2017, January 1st is on a Sunday)

/**
  Prompts user for input of year.
 */
void input() {
  printf("MONTHLY CALENDAR\n");
  printf("Please enter year for this calendar:-  ");
  scanf("%d", &given_year);
} // void input();

/**
  Checks the year passed into the function to see if it is a leap year. The
  function returns 0 if the given year is a leap year, or a 1 if the given
  year is NOT a leap year.
 */
int isLeapYear(int year) {
  if(year%4 == 0 && year%100 == 0 && year%400 == 0) {
    return 0;
  } else if(year%4 == 0 && year%100 == 0) {
    return 1;
  } else if(year%4 == 0) {
    return 0;
  } else {
    return 1;
  }
} // isLeapYear(int year);

/**
  Prints the days of the week which are shown at the top of every month.
 */
void printWeekdays() {
  printf("Sun Mon Tue Wed Thu Fri Sat\n");
} // void printweekdays()

/**
  Takes int indicating month and prints the name of the month and year
  (January = 0 and December = 11).
 */
void printMonthName(int month) {
	switch(month) {
	case 0:
	    printf("January");
	    break;
	case 1:
 	    printf("February");
      break;
	case 2:
	    printf("March");
	    break;
	case 3:
	    printf("April");
	    break;
	case 4:
	    printf("May");
	    break;
	case 5:
	    printf("June");
	    break;
	case 6:
	    printf("July");
	    break;
	case 7:
	    printf("August");
	    break;
	case 8:
	    printf("September");
	    break;
	case 9:
	    printf("October");
	    break;
	case 10:
	    printf("November");
	    break;
	case 11:
	    printf("December");
	    break;
	}
	printf(" %d\n", given_year);
} // void printMonthName(int month);

/**
  Returns the number of days in the given month using a switch. If the month
  passed through is February (month = 1), then a special case occurs after
  the switch in which the function checks if the year given is a leap year.
 */
int getDaysInMonth(int month, int year) {
  switch(month) {
		case 0:
    case 2:
    case 4:
    case 6:
	  case 7:
    case 9:
    case 11:
			return 31;
		case 3:
    case 5:
    case 8:
    case 10:
			return 30;
    default: // Catches only case 1
      break;
	}

  // February exception on a leap year
	if(isLeapYear(year) == 0 && month == 1) {
    return 29;
  } else {
    return 28;
  }
} // int getDaysInMonth(int month, int year);

/**
  In order to find the starting day of the given year, compare known year
  to the given year, and either add or subtract onto the starting day of
  the year based upon whether the given year is bigger or smaller than the
  known year. Continuously increment the known year respective to whether
  it is bigger or smaller relative to the known year, while also changing
  the starting day until the given year is reached. The while loops will
  run from when they are started after firstDayOfMonth() is called until
  the given_year reaches the value of known_year. If the known year is a
  leap year, increase/decrease the starting day by two. Standard increment
  size is 1 because 365*7 = 1.
 */
int firstDayOfMonth() {
  int startingDay = 0; // Keeps track of the starting day of the month

  while(given_year < known_year) {
    // if statement checks if the known year is a leap year
    if (isLeapYear(known_year) == 0) { // isLeapYear(known_year) returning 0 indicates a leap year
      startingDay -= 2; // Add two days to startingDay if it is a leap year instead of the usual 1
    } else {
      startingDay -= 1;
    }
    known_year--; // Increment known_year towards given_year
    startingDay = (startingDay + 7)%7; // To ensure that startingDay stays below 7 and above 0, first add 7 then modulo by 7
  }

  while(given_year > known_year) {
    // if statement checks if the known year is a leap year
    if (isLeapYear(known_year) == 0) { // isLeapYear(known_year) returning 0 indicates a leap year
      startingDay += 2; // Add two days to startingDay if it is a leap year instead of the usual 1
    } else {
      startingDay += 1;
    }
    known_year++; // Increment known year towards given_year
    startingDay = (startingDay + 7)%7; // To ensure that startingDay stays below 7 and above 0, first add 7 then modulo by 7
  }

  return startingDay;
} // void firstDayOfMonth();

/**
  Returns the number of the day on which the next month starts and prints
  the month in a calendar format. The first for loop prints spaces leading
  up to the starting day of the month (e.g. if the month starts on Tuesday
  it will print blank spaces for Sunday and Monday). It will not loop more
  than 7 times.

  The second for loop iterates from one to the number of days in the month,
  printing the dates and starts a new line if startingDay has reached 7,
  which indicates the end of the week. startingDay keeps track of the number
  iterations the loop has made since it's last reset, which occurs when
  startingDay reaches 7.
 */
int printMonth(int year, int month, int startingDay) {
  for(int i = 0; i < startingDay; i++) {
    printf("   ");
    // Print extra spaces if the month has not started yet (for 0 < i < startingDay)
		if(i > 0) {
      printf(" ");
    }
	}

  int daysInMonth = getDaysInMonth(month, year); // Save the number of days in the month for loop
  for(int j = 1; j <= daysInMonth; j++) {
		if(startingDay > 0) {
      printf(" ");
    }
    printf("%3d", j);
    // Increment startingDay every iteration before checking for end of week
    startingDay++;
    // At the end of the week, setup conditions for printing the next week
    if(startingDay == 7) {
      printf("\n");
      startingDay = 0;
    }
  }
  // Print new lines following the end of a month
  printf("\n");
  printf("\n");

	return startingDay;
} // int printmonth(int year, int i, int startingDay);

/**
  Looping from 0 to 11 (0 = January, 11 = December), the for loop calls
  functions related to printing each piece of the monthly calendar in order.
  startingDay is calculated for the following month at the end of each
  iteration.
 */
void printCalendar(int year, int startingDay) {
  printf("***    CALENDAR for %d   ***\n", given_year);
  for(int i = 0; i <= 11; i++) {
	   printMonthName(i);
     printWeekdays();
	   startingDay = printMonth(year, i, startingDay);
  }
} // void printCalendar(int year, int startingDay);

int main(void) {
  input();
  startingDay = firstDayOfMonth();
  printCalendar(given_year, startingDay);
  return 0;
} // int main(void);
