#include<stdio.h>
#include<inttypes.h>
#include<stdlib.h>
#include<string.h>

void text_printing(char** text, uint8_t row) //просто виводжу текст користувача
{
    if (text == NULL) return;

    for (size_t i = 0; i < row; i++) {
        if (text[i] != NULL) {
            printf("Your current text: %s", text[i]);
        }
    }
}
//ф-ця для case1
void append_text(char*** text, size_t* capacity,size_t current_row, const char* buffer) {
    size_t len = strlen(buffer);
    if (current_row >= *capacity) {
        size_t old_capacity = *capacity;
        if (*capacity == 0) { *capacity = 2; }
        else { *capacity *= 2; }

        char** temp = realloc(*text, (*capacity) * sizeof(char*));

        if (temp == NULL) {
            printf("Memory extension failed!\n");
            return;
        }
        *text = temp;
        for (size_t i = old_capacity; i < *capacity; i++)//занулює нові комірки, в яких поки що лежить сміття 
        {
            (*text)[i] = NULL;
        }
    }

    if ((*text)[current_row] == NULL)
    {
        (*text)[current_row] = malloc(len + 1);
        if ((*text)[current_row] == NULL) {
            printf("Malloc failed!\n");
            return;
        }
        strcpy_s((*text)[current_row], len + 1, buffer);
    }
        else {
        //текст є - додаю в кінець
        size_t old_len = strlen((*text)[current_row]);
        char* temp_line = realloc((*text)[current_row], old_len + len + 1);
        if (temp_line == NULL) {
            printf("Realloc failed;(\n");return;
        }
        (*text)[current_row] = temp_line;
        strcat_s((*text)[current_row], old_len + len + 1, buffer);
        }
}
int main()
{
    size_t row = 1;//бо вже маю активни й рядок з індексом 0.
    size_t current_row = 0;
    size_t column = 0;
    size_t capacity = 0;
    char** text = NULL;
    // malloc(row * sizeof(int*));
    while (1) // створила нескінчений цикл, щоб програма не завершувалась після першого введення
    {
        uint8_t choice;
        printf("Choose the command:\n");
        printf("1. Append text symbols to the end\n");
        printf("2. Start the new line\n");
        printf("3. Use files to load/save the information\n");
        printf("4. Print the current text to console\n");
        printf("5. Insert the text by line and symbol index\n");
        printf("6. Search (please note that the text can be found more than once)\n");
        printf("7. (Optional) Clearing the console\n");
        scanf_s(" %hhu", &choice);// однобайтове ціле число
        switch (choice)
        {
            //fgets - зчитування цілих рядків із пробілами(до того як ентер натиснули)
            //scanf - зчитування окремих слів( до першого пробілу) або чисел(char,int, float)
        case 1: printf("Enter text to append: ");
            char buffer[256];
            //strcpy - ф-ція для копіювання рядків (посимвольно переносить у цільовий буфер)
            getchar(); //для того, щоб прибрати залишковий символ \n, щоб він не впливав на результат fgets (не пропустить введення)
            // ця ф-ція бере 1 символ із потоку stdin

            if (fgets(buffer, sizeof(buffer), stdin) != NULL)
            {
                append_text(&text, &capacity, current_row, buffer);
            }
            break;
        case 2:
            printf("New line is started ");
            if (current_row + 1 >= capacity)
            {
                size_t old_capacity = capacity;
                if (capacity == 0) { capacity = 2; }
                else { capacity *= 2; }
                char** temp = realloc(text, capacity * sizeof(char*));
                if (!temp) {
                    printf("Memory extension failed!\n");
                    return;
                }
                text = temp;
                // printf("%p\n", (void*)text); - для перевірки чи створилась комірка

                for (size_t i = old_capacity; i < capacity; i++)//занулює нові комірки, в яких поки що лежить сміття 
                {
                    text[i] = NULL;
                }
            }
            current_row++;
            text[current_row] = NULL;
            break;
            //Start the new line 
        case 3:
            printf("Enter the file name for saving:");
            printf("The command is not implemented\n");break;
            //Use files to load/save the information
        case 4: printf("Enter the file name for loading:");
            printf("The command is not implemented\n");
            break;
        case 5:// printf("Hello, text editor!");
            //printf("The command is not implemented\n");
            text_printing(text, current_row + 1);break;
        case 6:printf("Choose line and index: ");
            printf("The command is not implemented!!\n");break;
        case 7: printf("Choose line and index: ");
            printf("The command is not implemented\n");break;

        }
    }
        //тут звільняю пам'ять
        for (size_t i = 0; i < capacity; i++)//занулює нові комірки, в яких поки що лежить сміття 
        {
            free(text[i]);
        }
        free(text);

        return 0;
}
