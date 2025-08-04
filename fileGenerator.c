#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

// Days in each month (non-leap year)
const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// Function to check if a year is a leap year
bool isLeapYear(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Function to get days in a specific month accounting for leap years
int getDaysInMonth(int year, int month) {
	if (month == 2 && isLeapYear(year))
		return 29;
	return daysInMonth[month];
}

// Structure to represent a date
typedef struct {
	int year;
	int month;
	int day;
} Date;

// Function to convert date to days since epoch (for date difference calculation)
int dateToDays(Date date) {
	int days = date.day;

	// Add days for months in current year
	for (int m = 1; m < date.month; m++) {
		days += getDaysInMonth(date.year, m);
	}

	// Add days for all previous years
	for (int y = 2009; y < date.year; y++) {
		days += isLeapYear(y) ? 366 : 365;
	}

	return days;
}

// Function to calculate days between two dates
int daysBetween(Date start, Date end) {
	return dateToDays(end) - dateToDays(start);
}

// Function to advance a date by a specific number of days
Date advanceDate(Date date, int days) {
	date.day += days;

	while (true) {
		int daysInCurrentMonth = getDaysInMonth(date.year, date.month);

		if (date.day <= daysInCurrentMonth)
			break;

		date.day -= daysInCurrentMonth;
		date.month++;

		if (date.month > 12) {
			date.month = 1;
			date.year++;
		}
	}

	return date;
}

// Function to generate a random date error
Date generateDateError() {
	Date date;
	int errorType = rand() % 4;

	switch (errorType) {
		case 0: // Month > 12
			date.year = 2000 + (rand() % 25);
			date.month = 13 + (rand() % 20);
			date.day = 1 + (rand() % 28);
			break;

		case 1: // Day > days in month
			date.year = 2000 + (rand() % 25);
			date.month = 1 + (rand() % 12);
			date.day = 32 + (rand() % 20);
			break;

		case 2: // Negative month or day
			date.year = 2000 + (rand() % 25);
			if (rand() % 2 == 0) {
					date.month = -(1 + (rand() % 12));
					date.day = 1 + (rand() % 28);
			} else {
					date.month = 1 + (rand() % 12);
					date.day = -(1 + (rand() % 28));
			}
			break;

		case 3: // Future date
			date.year = 2026 + (rand() % 10);
			date.month = 1 + (rand() % 12);
			date.day = 1 + (rand() % 28);
			break;
	}

	return date;
}

int main(int ac, char **av) {
	if (ac != 3){
		perror("Wrong number of arguments");
		return 1;
	}
	int num = (int)strtol(av[1], NULL, 10);
	FILE *file = fopen(av[2], "w");
	if (!file) {
		perror("Error opening file");
		return 1;
	}

	srand(time(NULL));

	// First line is the header
	fprintf(file, "date | value\n");

	// Start date (Bitcoin's launch date)
	Date startDate = {2009, 1, 3};
	Date endDate = {2025, 8, 8};

	// Calculate total days available
	int totalDays = daysBetween(startDate, endDate);

	// Calculate maximum advancement to ensure we don't run out of dates
	int maxAdvancement = totalDays / (num - 1);
	if (maxAdvancement < 1) maxAdvancement = 1;
	if (maxAdvancement > 30) maxAdvancement = 30;  // Cap at 30 as per original spec

	Date currentDate = startDate;

	// Generate N more lines (total N+1 including header)
	for (int i = 1; i < num; i++) {
		// Decide if we generate errors
		bool DateError = (rand() % 50 == 0);  // 1 in 50 chance
		bool generateValueError = (rand() % 50 == 0); // 1 in 50 chance
		bool skipValue = (DateError && rand() % 3 == 0);

		maxAdvancement = totalDays / (num - i);
		// Generate date
		if (DateError) {
			Date errorDate = generateDateError();
			if (skipValue) {
					// Just output the date without value
					fprintf(file, "%d-%02d-%02d\n", errorDate.year, errorDate.month, errorDate.day);
					continue;
			} else {
					fprintf(file, "%d-%02d-%02d", errorDate.year, errorDate.month, errorDate.day);
			}
		} else {
			fprintf(file, "%d-%02d-%02d", currentDate.year, currentDate.month, currentDate.day);

			// Calculate remaining entries and days
			int remainingEntries = num - i;
			int remainingDays = daysBetween(currentDate, endDate);

			// Adjust advancement based on remaining days and entries
			int maxAdvanceForRemaining = remainingDays / (remainingEntries > 0 ? remainingEntries : 1);
			if (maxAdvanceForRemaining < 1) maxAdvanceForRemaining = 1;
			if (maxAdvanceForRemaining > maxAdvancement) maxAdvanceForRemaining = maxAdvancement;

			// Advance date by 1 to maxAdvanceForRemaining days
			int daysToAdd = rand() % maxAdvanceForRemaining + 1;
			currentDate = advanceDate(currentDate, daysToAdd);

			// Ensure we don't exceed end date
			if (daysBetween(startDate, currentDate) > totalDays) {
					currentDate = endDate;
			}
		}

		// Generate value
		if (generateValueError) {
			int errorType = rand() % 2;
			if (errorType == 0) {
					// Negative value
					fprintf(file, " | %d\n", -(rand() % 1000 + 1));
			} else {
					// Value over max int
					fprintf(file, " | %lld\n", (long long)2147483648 + (rand() % 1000));
			}
		} else {
			// Normal value between 1-1000
			double value;
			int x = rand() % 10;
			if (x == 1)
					value = 1.0 + (rand() % 1000);
			else
					value = 1.0 + (rand() % 10);
			// 50% chance of having a decimal
			if (rand() % 2 == 0) {
					fprintf(file, " | %.1f\n", value);
			} else {
					fprintf(file, " | %d\n", (int)value);
			}
		}
	}

	fclose(file);
	printf("File 'input.txt' generated with %d lines.\n", num);

	return 0;
}