/*
 Password Manager in C
 Uses basic XOR encryption and file handling
 Note: This is a learning project, not production security
*/

#include <stdio.h>
#include <string.h>

int main() {
    char site[50], password[100], encrypted[100], decrypted[100];
    char master[100], stored_master[100];
    char key = 'K';
    FILE *fp;
    int i;
    char choice = 'y';


    fp = fopen("master.txt", "r");
    if (fp == NULL) {

        printf("No master password found. Set a master password: ");
        scanf("%s", master);

  
        for (i = 0; master[i] != '\0'; i++)
            master[i] = master[i] ^ key;
        master[i] = '\0';

        
        fp = fopen("master.txt", "w");
        fprintf(fp, "%s", master);
        fclose(fp);
        printf("Master password set successfully!\n");
    } else {
       
        fscanf(fp, "%s", stored_master);
        fclose(fp);

        printf("Enter master password to access: ");
        scanf("%s", master);

        
        for (i = 0; master[i] != '\0'; i++)
            master[i] = master[i] ^ key;
        master[i] = '\0';

        if (strcmp(master, stored_master) != 0) {
            printf("Incorrect master password! Exiting...\n");
            return 0;
        }
        printf("Access granted!\n");
    }

    while (choice == 'y' || choice == 'Y') {
        printf("\nEnter website/app name: ");
        scanf("%s", site);
        printf("Enter password: ");
        scanf("%s", password);

        for (i = 0; password[i] != '\0'; i++)
            encrypted[i] = password[i] ^ key;
        encrypted[i] = '\0';

        fp = fopen("passwords.txt", "a");
        if (fp == NULL) {
            printf("Error opening passwords.txt!\n");
            return 1;
        }
        fprintf(fp, "%s:%s\n", site, encrypted);
        fclose(fp);
        printf("Password stored securely!\n");

        printf("Add another password? (y/n): ");
        scanf(" %c", &choice);
    }

    printf("\nStored passwords (after decryption):\n");
    fp = fopen("passwords.txt", "r");
    if (fp == NULL) {
        printf("Error opening passwords.txt!\n");
        return 1;
    }

    while (fscanf(fp, "%[^:]:%s\n", site, encrypted) != EOF) {
        for (i = 0; encrypted[i] != '\0'; i++)
            decrypted[i] = encrypted[i] ^ key;
        decrypted[i] = '\0';

        printf("Site: %s | Password: %s\n", site, decrypted);
    }

    fclose(fp);
    return 0;
}
