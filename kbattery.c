#include <stdio.h>
#include <errno.h>

#define BASE_PATH "/sys/class/power_supply/BAT0/energy_"
#define ARRAY_SIZE 50
#define STATUS_COUNT 3

/* display a progress bar */

char* print_bar(char bar[], double percent)
{
	percent *= 20;

	int j;
	for (j = 0; j < (int) percent; ++j)
	{
		bar[j] = '$';
	}
	bar[j+1] = '\0';
	return bar;
}

int main()
{
	long int battery_status[STATUS_COUNT]; /* info for now, full, full_design */
	char status_name[STATUS_COUNT][15] = {"now", "full", "full_design"};
	char battery_path[ARRAY_SIZE], buff[ARRAY_SIZE];

	int i;
	for (i = 0; i < STATUS_COUNT; ++i)
	{
		sprintf(battery_path, "%s%s", BASE_PATH, status_name[i]);
		/*printf("%s\n", battery_path);*/

		FILE *battery_fp = fopen(battery_path, "r");

		if (battery_fp == NULL)
		{
			perror("Can't open battery file. Error");
			return;
		}

		if (fgets(buff, ARRAY_SIZE, battery_fp) != NULL)
		{
			sscanf(buff, "%ld", &battery_status[i]);
		}

		/*printf("Now: %ld\n", battery_status[i]);*/

		if (battery_fp != NULL)
		{
			fclose(battery_fp);
		}
	}

	char bar[22] = {' '};
	double now_percent = ((double)battery_status[0]) / battery_status[1];
	printf("Now   %-20s %d%%\n", print_bar(bar, now_percent), (int)(now_percent * 100));
	printf("Full  %-20s %d%%\n", print_bar(bar, 1), 100);

	printf("\nkbattery: battery status. URL: github.com/XieConnect/kbattery \nAuthor: Wei Xie <XieConnect (at) gmail.com \n");

}
