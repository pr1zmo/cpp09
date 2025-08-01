#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

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

int main() {
	FILE *file = fopen("input.txt", "w");
	if (!file) {
		perror("Error opening file");
		return 1;
	}
	
	srand(time(NULL));
	
	// First line is the header
	fprintf(file, "date | value\n");
	
	// Start date (Bitcoin's launch date)
	Date currentDate = {2009, 1, 3};
	
	// Generate 1611 more lines (total 1612 including header)
	for (int i = 1; i < 1612; i++) {
		// Decide if we generate errors
		bool DateError = (rand() % 50 == 0);  // 1 in 50 chance
		bool generateValueError = (rand() % 50 == 0); // 1 in 50 chance
		bool skipValue = (DateError && rand() % 3 == 0);
		
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
			// Advance date by 1-30 days for next entry
			int daysToAdd = rand() % 30 + 1;
			currentDate = advanceDate(currentDate, daysToAdd);
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
	printf("File 'input.txt' generated with 1612 lines.\n");
	
	return 0;
}