#include<stdio.h>
#include<inttypes.h>

void text_printing(char** text, uint8_t row) //просто виводжу текст користувача
{
    for (uint8_t i = 0; i < row; i++) {
        printf("Your current text:  ");
        printf("%s\n", text[i]);
    }
}
int main() {
    uint8_t row = 0;
    uint8_t column = 0;
    uint8_t capacity = 0;
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
        case 1: printf("Enter text to append: ");
            char buffer[256];
            if (row==capacity) {
                if (capacity == 0) { capacity = 2; }
                else { capacity *= 2; }
                text = realloc(text, capacity * sizeof(char*));// помножила на 2, щоб менше викикати realloc 
                if (text == NULL) {
                    printf("Memory extension failed!\n");
                    break;
                }

            }            
            printf("The command is not implemented\n ");break;
            //Append text symbols to the end 
        case 2:
            printf("New line is started ");
            printf("The command is not implemented\n");break;
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
            text_printing(text, row);break;
        case 6:printf("Choose line and index: ");
            printf("The command is not implemented!!\n");break;
        case 7: printf("Choose line and index: ");
            printf("The command is not implemented\n");break;

        }
    }
    return 0;
}