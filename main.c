#include<stdio.h>
#include<inttypes.h>

void text_printing(char** text, uint8_t row) //просто виводжу текст користувача
{
    for (uint8_t i = 0; i < row; i++) {
        if (text[i] != NULL) {
            printf("Your current text: %s", text[i]);
        }
    }
}
int main() 
{
    uint8_t row = 1;//бо вже маю активни й рядок з індексом 0.
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
            //fgets - зчитування цілих рядків із пробілами(до того як ентер натиснули)
            //scanf - зчитування окремих слів( до першого пробілу) або чисел(char,int, float)
        case 1: printf("Enter text to append: ");
            char buffer[256];
            //strcpy - ф-ція для копіювання рядків (посимвольно переносить у цільовий буфер)
            getchar(); //для того, щоб прибрати залишковий символ \n, щоб він не впливав на результат fgets (не пропустить введення)
            // ця ф-ція бере 1 символ із потоку stdin
            if (row > capacity) {
                uint8_t old_capacity = capacity;
                if (capacity == 0) { capacity = 2; }
                else { capacity *= 2; }
                text = realloc(text, capacity * sizeof(char*));// помножила на 2, щоб менше викликати realloc 
                for (uint8_t i = old_capacity; i < capacity; i++)//занулює нові комірки, в яких поки що лежить сміття 
                {
                    text[i] = NULL;
                }
                if (text == NULL) {
                    printf("Memory extension failed!\n");
                    break;
                }
            }
            if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                printf("Your text is: %s", buffer);
                size_t len = strlen(buffer);
                if (text[row - 1] == NULL) {
                    text[row - 1] = malloc((len + 1) * sizeof(char));
                    strcpy_s(text[row - 1],len+1, buffer);//більш захищена, ніж strcpy
                }
                else
                {

                    size_t old_len = strlen(text[row - 1]); // розширюю текст, який вже є
                    text[row - 1] = realloc(text[row - 1], (old_len + len + 1) * sizeof(char));
                    strcat_s(text[row - 1], old_len+len+1, buffer);//strcat - для об'єднання двох рядків
                }
               
                //Append text symbols to the end 
            }
            break;
        case 2:
            printf("New line is started ");
            row++;
            if (row > capacity) {
                uint8_t old_capacity = capacity;
                if (capacity == 0) { capacity = 2; }
                else { capacity *= 2; }
                text = realloc(text, capacity * sizeof(char*));// помножила на 2, щоб менше викликати realloc 
                if (text == NULL) {
                    printf("Memory extension failed!\n");
                    break;
                }
                for (uint8_t i = old_capacity; i < capacity; i++)//занулює нові комірки, в яких поки що лежить сміття 
                {
                    text[i] = NULL;
                }
            }
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
            text_printing(text, row);break;
        case 6:printf("Choose line and index: ");
            printf("The command is not implemented!!\n");break;
        case 7: printf("Choose line and index: ");
            printf("The command is not implemented\n");break;

        }
    }
        return 0;
}