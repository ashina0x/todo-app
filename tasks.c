#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"

#define SIZE 100
#define TASKFILE "TaskList.txt"

void clearScreen()
{
#ifdef _WIN32
  system("cls"); // Windows
#else
  system("clear"); // Linux/MacOS
#endif
}

void welcomeMsg() // Main Menu
{
  printf("%s==========================================%s\n", CYAN, RESET);
  printf("         %sWelcome to To-Do Manager%s         \n", BLUE, RESET);
  printf("%s==========================================%s\n", CYAN, RESET);
  printf("A simple console-based To-Do application.\n");
  printf("Manage your tasks efficiently and easily!\n");
  printf("       - Made by github.com/peaceful-wolf\n");
  printf("------------------------------------------\n");
  printf("%sFeatures:%s\n", GREEN, RESET);
  printf("1. Add new tasks.\n");
  printf("2. View all tasks.\n");
  printf("3. Mark tasks as complete.\n");
  printf("4. Delete tasks.\n");
  printf("5. Exit.\n");
}

int choice()
{
  int choice;
  printf("%sChoose an option:%s ", GREEN, RESET);
  scanf("%d", &choice);
  return choice;
}

void backToMainMenu()
{
  while (getchar() != '\n')
    ;
  printf("Press Enter to return to the Main Menu...");
  getchar(); // wait for Enter
  clearScreen();
  welcomeMsg();
}

void addTasks()
{
  FILE *file;
  file = fopen(TASKFILE, "a");
  if (file == NULL)
  {
    printf("Error opening file.\n");
    return;
  }

  getchar();

  char title[SIZE];
  char description[SIZE];
  int priority;
  char priorityLevel[10];
  int day, month, year;

  printf("01. Enter the Title: ");
  fgets(title, 100, stdin);
  title[strcspn(title, "\n")] = '\0';

  printf("02. Enter the Description: ");
  fgets(description, 100, stdin);
  description[strcspn(description, "\n")] = '\0';

  printf("03. Enter the Priority Level(1-High,2-Medium,3-Low): ");
  scanf("%d", &priority);
  if (priority == 1)
    strcpy(priorityLevel, "High");
  else if (priority == 2)
    strcpy(priorityLevel, "Medium");
  else if (priority == 3)
    strcpy(priorityLevel, "Low");
  else
    strcpy(priorityLevel, "N/A");

  while (getchar() != '\n')
    ;

  printf("04. Enter the Deadline Date[(DD/MM/YY)- without '/']: ");
  scanf("%2d%2d%2d", &day, &month, &year);

  fprintf(file, "%s | %s | Priority: %s | Deadline: %02d/%02d/%02d\n", title, description, priorityLevel, day, month, year);
  fclose(file);
  printf("%sTask added successfully.%s\n", GREEN, RESET);
}

void viewTasks()
{
  FILE *file;
  file = fopen(TASKFILE, "r");
  if (file == NULL)
    printf("%sNo tasks found.%s\n", YELLOW, RESET);

  char line[SIZE * 3];
  char count = 0;

  printf("%s<------------ Tasks List ------------>%s\n\n", YELLOW, RESET);

  while (fgets(line, sizeof(line), file))
  {
    printf("%d. %s", count + 1, line);
    count++;
  }

  if (count == 0)
    printf("No tasks available at this moment.\n");

  printf("\n");
  fclose(file);
  backToMainMenu();
}

void completeTasks()
{
  FILE *file;
  file = fopen(TASKFILE, "r");

  char tasks[SIZE][SIZE * 3];
  int count = 0;

  printf("%s<------------ Mark Task as Complete ------------>%s\n\n", CYAN, RESET);
  while (fgets(tasks[count], sizeof(tasks), file))
  {
    printf("%d. %s", count + 1, tasks[count]);
    count++;
  }

  if (count == 0)
  {
    printf("%sNo active tasks available.%s\n\n", YELLOW, RESET);
    backToMainMenu();
  }
  printf("\n");
  fclose(file);

  int choice;
  do
  {
    printf("Select the task number that you want to add as complete: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > count)
      printf("%sInvalid task number. %s\n\n", RED, RESET);
  } while (choice < 1 || choice > count);

  if (strstr(tasks[choice - 1], "[COMPLETED]") == NULL)
  {
    tasks[choice - 1][strcspn(tasks[choice - 1], "\n")] = '\0';
    strcat(tasks[choice - 1], " [COMPLETED]\n");
  }

  file = fopen(TASKFILE, "w");
  for (int i = 0; i < count; i++)
  {
    fputs(tasks[i], file);
  }
  fclose(file);

  printf("%sTask marked as completed successfully.%s\n", GREEN, RESET);
  backToMainMenu();
}

int deleteTasks()
{
  FILE *file;
  file = fopen(TASKFILE, "r");

  char tasks[SIZE][SIZE * 3];
  int count = 0;

  printf("%s<------------ Tasks List ------------>%s\n\n", CYAN, RESET);
  while (fgets(tasks[count], sizeof(tasks), file))
  {
    printf("%d. %s", count + 1, tasks[count]);
    count++;
  }

  if (count == 0)
  {
    printf("%sNo active tasks available.%s\n\n", YELLOW, RESET);
    backToMainMenu();
    return 0;
  }
  printf("\n");
  fclose(file);

  int choice;
  do
  {
    printf("Select the task number that you want to delete: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > count)
      printf("%sInvalid task number. %s\n\n", RED, RESET);
  } while (choice < 1 || choice > count);

  file = fopen(TASKFILE, "w");
  for (int i = 0; i < count; i++)
  {
    if (i != (choice - 1))
      fputs(tasks[i], file);
  }
  fclose(file);

  printf("%sTask deleted successfully.%s\n", GREEN, RESET);
  return 1;
}