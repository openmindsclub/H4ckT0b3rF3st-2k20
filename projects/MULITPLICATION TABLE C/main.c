#include <stdio.h>
#include <stdlib.h>
/* THE CODE WAS REVIEWED BY CHOUAKI TAREK */
int main()

{
    int nombre, i = 1;
    printf("ENTER A NUMBER BETWEEN 1 and 10\n");
    scanf("%d", &nombre);
        while (nombre < 1 || nombre >  10)
    {
        printf("ENTER A NUMBER BETWEEN 1 and 10\n");
        scanf("%d", &nombre);
    }
    /* NOMBRE LOOP IS FINISHED */
        while (i <= 10)
    {
        printf("%d * %d = %d\n", nombre, i, nombre*i);
        i++;
    }
    return 0;
}
