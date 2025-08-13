#include <stdio.h>
#include <string.h>
#include "colors.h"
#include "tasks.h"

int main()
{
  welcomeMsg();

  while (1)
  {
    int result = choice();
    switch (result)
    {
    case 1:
      clearScreen();
      char repeat_case1;
      do
      {
        addTasks();
        printf("\nAdd another Task(y/n): ");
        getchar();
        repeat_case1 = getchar();
      } while (repeat_case1 == 'y' || repeat_case1 == 'Y');
      clearScreen();
      welcomeMsg();
      break;
    case 2:
      clearScreen();
      viewTasks();
      break;
    case 3:
      clearScreen();
      completeTasks();
      break;
    case 4:
      clearScreen();
      char repeat_case2;
      int success;
      do
      {
        success = deleteTasks();
        if (!success)
          break;
        printf("\nDelete another Task (y/n): ");
        getchar();
        repeat_case2 = getchar();
      } while (repeat_case2 == 'y' || repeat_case2 == 'Y');
      clearScreen();
      welcomeMsg();
      break;
    case 5:
      return 0;
    default:
      printf("%sInvalid option. Please try again.\n%s", RED, RESET);
      break;
    }
  }
}