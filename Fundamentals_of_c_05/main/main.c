#include <stdio.h>
#include <string.h>

struct Person
{
  char firstName[20];
  char lastName[20];
  int age;
};

void app_main(void)
{
  struct Person person;
  strcpy(person.firstName, "Dev");
  strcpy(person.lastName, "Kumar");
  person.age = 37;
  printf("Person %s %s is %d years old.\n", person.firstName, person.lastName, person.age);
}
