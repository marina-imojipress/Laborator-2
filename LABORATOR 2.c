#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct profile
{
    char name[20];
    int age;
    int height;
    char sign[10];
    char hobby[20];

    struct profile *next;
};

struct profile *head = NULL;

int create_list(int n)
{
    struct profile *current, *previous = NULL;
    int i;

    for (i = 0; i < n; i++)
    {
        current = (struct profile *)calloc(1, sizeof(*current));
        if (current == NULL)
        {
            head = NULL;
            return 0;
        }
        if (previous == NULL)
        {
            head = current;
        }
        else
        {
            previous->next = current;
        }
        previous = current;
    }
    current->next = NULL;
    return 1;
}

void read_profile()
{
    struct profile *current = head;
    int i = 0;

    printf("Enter information for profiles:\n");
    while (current)
    {
        printf("Profile %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", current->name);
        printf("Age: ");
        scanf("%d", &current->age);
        printf("Height: ");
        scanf("%d", &current->height);
        printf("Zodiac Sign: ");
        scanf("%s", current->sign);
        printf("Hobby: ");
        scanf("%s", current->hobby);
        i++;
        current = current->next;
    }
}

void display_profiles()
{
    struct profile *current = head;
    int i = 1;

    printf("Information about profiles:\n");
    while (current)
    {
        printf("Profile %d:\n", i);
        printf("Name: %s, Age: %d, Height: %d, Zodiac Sign: %s, Hobby: %s\n",
               current->name, current->age, current->height, current->sign, current->hobby);
        i++;
        current = current->next;
    }
}

struct profile *search_profile(char *name)
{
    struct profile *current = head;
    int index = 1;

    while (current)
    {
        if (strcmp(current->name, name) == 0)
        {
            printf("Profile found at position: %d\n", index);
            return current;
        }
        current = current->next;
        index++;
    }
    printf("Profile not found.\n");
    return NULL;
}

int list_size()
{
    struct profile *current = head;
    int count = 0;

    while (current)
    {
        count++;
        current = current->next;
    }
    return count;
}

void sort_list() {
    int n = list_size();
    struct profile *temp, *current, *next, *prev = NULL;

    for (int i = 0; i < n - 1; i++) {
        current = head;
        next = head->next;

        for (int j = 0; j < n - 1 - i; j++) {
            if (current->age > next->age) {
                if (prev != NULL) {
                    prev->next = next;
                } else {
                    head = next;
                }
                current->next = next->next;
                next->next = current;

                temp = current;
                current = next;
                next = temp;
            }
            prev = current;
            current = current->next;
            next = next->next;
        }
    }
}



int introduce_profile_in_last_position(struct profile *new_profile)
{
    struct profile *last = head;

    if (last == NULL)
    {
        head = new_profile;
    }
    else
    {
        while (last->next != NULL)
        {
            last = last->next;
        }
        last->next = new_profile;
    }
    new_profile->next = NULL;
    return 1;
}

int introduce_profile_in_first_position(struct profile *new_profile)
{
    new_profile->next = head;
    head = new_profile;
    return 1;
}

void delete_a_profile_in_specified_position(int position)
{
    struct profile *current = head;
    struct profile *previous = NULL;
    int current_position = 1;

    while (current && current_position < position)
    {
        previous = current;
        current = current->next;
        current_position++;
    }

    if (current && current_position == position)
    {
        if (previous == NULL)
        {
            head = current->next;
        }
        else
        {
            previous->next = current->next;
        }
        free(current);
        printf("Profile deleted successfully from position: %d\n", position);
    }
    else
    {
        printf("Profile not found at position %d.\n", position);
    }
}

void reverse_list()
{
    struct profile *prev = NULL;
    struct profile *current = head;
    struct profile *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

void free_memory()
{
    struct profile *current = head;
    struct profile *next_profile;

    while (current)
    {
        next_profile = current->next;
        free(current);
        current = next_profile;
    }
    head = NULL;
}

int main()
{
    int choice, n;
    struct profile *new_profile, *found_profile;

    while (1)
    {
        printf("\n\t MENU:\n");
        printf("1. Create dynamic memory list.\n");
        printf("2. Enter profile information from keyboard.\n");
        printf("3. Display profile information.\n");
        printf("4. Search for a profile.\n");
        printf("5. Sort the list.\n");
        printf("6. Add a new profile to the end of the list.\n");
        printf("7. Add a new profile to the beginning of the list.\n");
        printf("8. Delete a profile.\n");
        printf("9. Reverse the list.\n");
        printf("10. Exit the program and free memory\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the number of profiles: ");
            scanf("%d", &n);
            if (!create_list(n))
            {
                printf("Memory allocation failed.\n");
                exit(1);
            }
            printf("Memory allocation successful.\n");
            break;

        case 2:
            read_profile();
            break;

        case 3:
            display_profiles();
            break;

        case 4:
            char search_name[20];
            printf("Enter the name of the profile to search: ");
            scanf("%s", search_name);
            found_profile = search_profile(search_name);
            break;

        case 5:
            sort_list();
            printf("List sorted successfully.\n");
            break;

        case 6:
            new_profile = (struct profile *)calloc(1, sizeof(*new_profile));
            if (new_profile == NULL)
            {
                printf("Memory allocation failed\n");
                exit(1);
            }
            printf("Enter information for the new profile:\n");
            printf("Name: ");
            scanf("%s", new_profile->name);
            printf("Age: ");
            scanf("%d", &new_profile->age);
            printf("Height: ");
            scanf("%d", &new_profile->height);
            printf("Zodiac Sign: ");
            scanf("%s", new_profile->sign);
            printf("Hobby: ");
            scanf("%s", new_profile->hobby);
            if (!introduce_profile_in_last_position(new_profile))
            {
                printf("Failed to add profile.\n");
                free(new_profile);
            }
            else
            {
                printf("Profile added successfully\n");
            }
            break;

        case 7:
            new_profile = (struct profile *)calloc(1, sizeof(*new_profile));
            if (new_profile == NULL)
            {
                printf("Memory allocation failed\n");
                exit(1);
            }
            printf("Enter information for the new profile:\n");
            printf("Name: ");
            scanf("%s", new_profile->name);
            printf("Age: ");
            scanf("%d", &new_profile->age);
            printf("Height: ");
            scanf("%d", &new_profile->height);
            printf("Zodiac Sign: ");
            scanf("%s", new_profile->sign);
            printf("Hobby: ");
            scanf("%s", new_profile->hobby);
            if (!introduce_profile_in_first_position(new_profile))
            {
                printf("Failed to add profile\n");
                free(new_profile);
            }
            else
            {
                printf("Profile added successfully\n");
            }
            break;

        case 8:
        int delete_profile;
        printf("Enter the position of the profile to delete: ");
        scanf("%d", &delete_profile);
        delete_a_profile_in_specified_position(delete_profile);
        break;


        case 9:
            reverse_list();
            printf("List reversed successfully.\n");
            break;

        case 10:
            printf("Do you want to exit the program? (1/0): ");
            scanf("%d", &choice);
            if (choice == 1)
            {
                free_memory();
            }
            return 0;

        default:
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
