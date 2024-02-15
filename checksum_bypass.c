#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE 128

int Manifest() {
	const char *rabbit = "\
 _   _               _      _    _            ______        _      _      _  _   \n\
| | | |             | |    | |  | |           | ___ \\      | |    | |    (_)| |  \n\
| |_| |  __ _   ___ | | __ | |_ | |__    ___  | |_/ / __ _ | |__  | |__   _ | |_ \n\
|  _  | / _` | / __|| |/ / | __|| '_ \\  / _ \\ |    / / _` || '_ \\ | '_ \\ | || __|\n\
| | | || (_| || (__ |   <  | |_ | | | ||  __/ | |\\ \\| (_| || |_) || |_) || || |_ \n\
\\_| |_/ \\__,_| \\___||_|\\_\\  \\__||_| |_| \\___| \\_| \\_|\\__,_||_.__/ |_.__/ |_| \\__|\n\
((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((\n\
((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((\n\
((((((((((((((((((((((((((( ,,*(((((((((((((((((((((((((((((((((((((((((((((((((\n\
((((((((((((((((((((((((((,,,,,((((((((((*((((((((((((((((((((((((((((((((((((((\n\
(((((((((((((((((((((((((,,,,,,(((((( ......((((((((((((((((((((((((((((((((((((\n\
(((((((((((((((////(////.,,,,,,(/// .......#((((((((((((((((((((((((((((((((((((\n\
((((((((((((/(((/(//////.,,,,,.(//........((/(((/(((((((((((((((((((((((((((((((\n\
((((((((((((/(//////////.,,,,,#(........#(/////(((((((((((((((((((((((((((((((((\n\
((((((((/(//////////////.,,,..(.......#(///////////(/(((((((((((((((((((((((((((\n\
((((////////////////////.,,.........((/////////////////(/(((((((((((((((((((((((\n\
((((/(//////////////,,,,,,,......*(//////////////////////(((((((((((((((((((((((\n\
/(((/////////////(,,,,,(),,......(////////////////////////(/(/((((((((((((((((((\n\
((//////////////,,,,,,,,,,........////////////////////////((/(((((((((((((((((((\n\
///////////////,,,,,,,,,..............                 ////////(((((((((((((((((\n\
///////////////,,,,,,,,,...............                   .//(((((((((((((((((((\n\
/////////////////,,,,,...............                        (((((((((((((((((((\n\
///////////////////////.............                          ((((((((((((((((((\n\
///////////////////////...........                             (/(((((((((((((((\n\
////////////////////////...........                            (/(((((((((((((((\n\
/////////////////////////.........                             (/(((((((((((((((\n\
///////////////////////////,....                               ( (((((((((((((((\n\
///////////////////////////////(                                 .((((((((((((((\n\
////////////////////////////////     (((/                        (((((((((((((((\n\
/(////////////////////////....     ((//////.                 (((((((((((((((((((\n\
/(((/////////////////////////////////////////////////////(((/(((((((((((((((((((\n\
((((/////////////////////////////////////////////////////(/(((((((((((((((((((((\n\n\n";
	printf("%s", rabbit);
}

struct choice_ext{
    int pointer;
    char* registry;
} __attribute__ ((packed));

struct choice_base{
    int pointer;
    char* registry;
} __attribute__ ((packed));

struct shw_sfp_header{
    uint8_t id;
    uint8_t ext_id;
    uint8_t connector;
    uint8_t transciever[8];
    uint8_t encoding;
    uint8_t br_nom;
    uint8_t reserved1;
    uint8_t length1;
    uint8_t length2;
    uint8_t length3;
    uint8_t length4;
    uint8_t length5;
    uint8_t length6;
    uint8_t vendor_name[16];
    uint8_t reserved3;
    uint8_t vendor_oui[3];
    uint8_t vendor_pn[16];
    uint8_t vendor_rev[4];
    uint8_t tx_wavelength[2];
    uint8_t reserved4;
    uint8_t cc_base;
    uint8_t options[2];
    uint8_t br_max;
    uint8_t br_min;
    uint8_t vendor_serial[16];
    uint8_t date_code[8];
    uint8_t diagnostic_monitoring_type;
    uint8_t enhanced_options;
    uint8_t sff_8472_compliance;
    uint8_t cc_ext;
} __attribute__ ((packed));

int cc_ext_alteratives(char opt, struct choice_ext *point) {
    int pointer;
    char* registry;
    switch (opt) {
        case '1':
            pointer = 67;
            registry = "br_min";
            break;
        case '2':
            pointer = 94;
            registry = "sff_8472_compliance";
            break;
    }
    point->pointer = pointer;
    point->registry = registry;
    return 1;
}

int cc_base_alteratives(char opt, struct choice_base *point) {
    int pointer;
    char* registry;
    switch (opt) {
        case '1':
            pointer = 11;
            registry = "encoding";
            break;
        case '2':
            pointer = 13;
            registry = "reserved1";
            break;
        case '3':
            pointer = 16;
            registry = "length3";
            break;
        case '4':
            pointer = 17;
            registry = "length4";
            break;
        case '5':
            pointer = 18;
            registry = "length5";
            break;
        case '6':
            pointer = 19;
            registry = "length6";
            break;
        case '7':
            pointer = 36;
            registry = "reserved3";
            break;
        case '8':
            pointer = 62;
            registry = "reserved4";
            break;
    }
    point->pointer = pointer;
    point->registry = registry;
    return 1;
}

uint32_t Sum(int offset, int limit, struct shw_sfp_header *head) {
    uint32_t sum = 0;
    for (int i = offset; i < limit; i++)
        sum += ((uint8_t*)head)[i];
    sum &= 0xff;
    return (uint8_t)sum;
}

int Generate_header(struct shw_sfp_header *head) {
    int ret;
    FILE *fp;
    fp = fopen("./header_ok", "wb");
    if (fp == NULL) {
        perror("Error opening file");
        return -1;
    }
    ret = fwrite(head, 1, sizeof(struct shw_sfp_header), fp);
    if (ret != sizeof(struct shw_sfp_header)) {
        perror("Error writing to file");
        fclose(fp);
        return -1;
    }
    fclose(fp);

    printf("The new header is in a file called header_ok in this directory, load it with /wr/bin/wrs_sfp_dump -I -a WRITE -f header_ok -p <sfp>. This is the new structure - > \n");
    return 1;
}

int Cheat_ext(uint8_t wrong_sum, struct shw_sfp_header *head, int pointer, char* registry) {
    uint8_t *field = (uint8_t*)head + pointer;
    printf("CC_EXT to hack -> %X\n", head->cc_ext);
    uint8_t hack = head->cc_ext - wrong_sum + *field;
    *field = hack;
    uint32_t sum = 0;
    for (int i = 64; i < 95; i++) {
        sum += ((uint8_t*)head)[i];
    }
    sum &= 0xff;
    printf("I changed the %s value in header to cheat it with -> %02X\n", registry, *field);
    printf("CC_EXT checksum result is %X, CC_EXT in EEPROM is %X\n\n", sum, head->cc_ext);
    return 1;
}

int Cheat_base(uint8_t wrong_sum, struct shw_sfp_header *head, int pointer, char* registry) {
    uint8_t *field = (uint8_t*)head + pointer;
    printf("CC_BASE to hack -> %X\n", head->cc_base);
    uint8_t hack = head->cc_base - wrong_sum + *field;
    *field = hack;
    uint32_t sum = 0;
    for (int i = 0; i < 63; i++) {
        sum += ((uint8_t*)head)[i];
    }
    sum &= 0xff;
    printf("I changed the %s value in header to cheat it with -> %02X\n", registry, *field);
    printf("CC_BASE checksum result is %X, CC_BASE in EEPROM is %X\n\n", sum, head->cc_base);
    return 1;
}

void To_hex(const char *conv_me, uint8_t inhex[]) {
    int i = 0; 
    while (conv_me[i] != '\0') {
        char hex_str[3];
        sprintf(hex_str, "%02X", conv_me[i]);
        int value;
        sscanf(hex_str, "%02X", &value);
        inhex[i] = (uint8_t)value;
        i++;
    }
}

//check content of array
int check_hex(uint8_t check[], size_t size, char *whois) {
    printf("Check if the conversion of %s is right => ", whois);
    for (size_t i = 0; i < size; i++) {
         printf("%02X ", check[i]);
    }
    printf("\n");
    return 1;
}


int Read_file(struct shw_sfp_header *head) {
    char filename[256];
    printf("Give me the file path to read (ex. ./file_header). Remember I just need 12 rows of 8 bytes separated by a space, \
like the output of this command \"/wr/bin/wrs_sfp_dump -I -x -p <sfp> | tail -12 > name_of_file\", \
so just run this command and give me the file path -> ");
    scanf("%s", filename);
    printf("\n");

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open the file. Loaded a default configuration with some empty fields");
        return 0;
    }

    size_t index = 0;
    int value;

    while (fscanf(file, "%02X", &value) == 1) {
        ((uint8_t *)head)[index++] = (uint8_t)value;

        fseek(file, 1, SEEK_CUR); // step +1 to avoid blank
    }

    fclose(file);
    return 1;
}

int Print_struct(struct shw_sfp_header *head) {
    int c = 0;
    for (int i = 0; i < 96; i++) {
        printf("%02X ", ((uint8_t*)head)[i]);
        c++;
        if (c == 8) {
            c = 0;
            printf("\n");
        }
    }
    return 1;
}

char* exec(char* cmd) {
    #define MAX_PATH_LENGTH 256
    #define MAX_RESULT_LENGTH 1024

    int lun = MAX_PATH_LENGTH;
    FILE *fp;
    int status;
    char path[MAX_PATH_LENGTH];
    char *res = (char *)malloc(MAX_RESULT_LENGTH * sizeof(char));
    res[0] = '\0'; // Inizializza la stringa risultato

    fp = popen(cmd, "r");

    while (fgets(path, lun, fp) != NULL) 
        if (strlen(res) + strlen(path) < MAX_RESULT_LENGTH) 
            strcat(res, path);
        
    //printf("%s", res);

    status = pclose(fp);

    return res;
}

int Kill_em_Hall() {
    char kill_command[256];
    printf("Make sure that Hal is not running!\n");
    printf("I'm stopping the Hal monit /etc/init.d/monit.sh stop\n");
    char* monit = exec("ls c*");
    free(monit);
    sleep(2);

    printf("Now grepping the Hal pid, if exist, and kill him\n");
    char* result = exec("ps aux | grep -E /usr/lib/libreoffice/program/soffice.bin | grep -v grep | head -n 1 |awk '{print $2}'");
    sprintf(kill_command, "kill %s", result);
    char* kill = exec(kill_command);
    free(kill);
    printf("I Kill'em Hal, check with ps aux | grep hal if still exist\n");

    return 1;
}

int main() {
    struct shw_sfp_header head;
    struct choice_base pointB;
    struct choice_ext pointE;

    Manifest();
    Kill_em_Hall();

    Read_file(&head);
    Print_struct(&head);

    const char *heart = "\xE2\x9D\xA4\xEF\xB8\x8F";
    uint8_t filler_serial[10] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20};
    uint8_t vendor_serial[16];
    uint8_t hex_serial[6];

    uint8_t filler_date_code[2] = {0x00, 0x00};
    uint8_t date_code[8];
    uint8_t hex_date_code[6];

	char serial[6];
	char date_code_str[6];

    char rew;
    int cc_base_flag = 1; //is rewritable
    int cc_ext_flag = 1; //is rewritable

    printf("Insert the serial (ex. 001111) => ");
    scanf("%s", serial);

    printf("Insert the serial (usually 210421) => ");
    scanf("%s", date_code_str);

    printf("Is the CC_BASE still rewritable? (y , n) => ");
    scanf(" %c", &rew);
    if (rew == 'n') {
        cc_base_flag = 0;
    }

    printf("Is the CC_EXT still rewritable? (y , n) => ");
    scanf(" %c", &rew);
    if (rew == 'n') {
        cc_ext_flag = 0;
    }

    printf("For the CC_BASE checksum, is the field ext_id (2° byte of 96) still rewritable? type y to confirm or select another registry:\n\
    type 1 for registry encoding, byte position 12\n\
    type 2 for registry reserved1, byte position 14\n\
    type 3 for registry length3, byte position 17\n\
    type 4 for registry length4, byte position 18\n\
    type 5 for registry length5, byte position 19\n\
    type 6 for registry length6, byte position 20\n\
    type 7 for registry reserved3, byte position 37\n\
    type 8 for registry reserved4, byte position 63\n");
    scanf(" %c", &rew);

    if (rew != 'y') {
        cc_base_alteratives(rew, &pointB);
    }
    else {
        pointB.pointer = 1;
        pointB.registry = "ext_id";
    }

    printf("For the CC_EXT checksum, is the field br_max (67° byte of 96) still rewritable? type y to confirm or select another registry:\n\
    type 1 for registry br_min, byte position 68\n\
    type 2 for registry sff_8472_compliance, byte position 95\n");
    scanf(" %c", &rew);

    if (rew != 'y') {
        cc_ext_alteratives(rew, &pointE);
    }
    else {
        pointE.pointer = 66;
        pointE.registry = "br_max";
    }

    To_hex(serial, hex_serial);
    To_hex(date_code_str, hex_date_code);

    //join 2 arrays
    memcpy(vendor_serial, hex_serial, sizeof(hex_serial));
    memcpy(vendor_serial + sizeof(hex_serial), filler_serial, sizeof(filler_serial));

    //join 2 arrays
    memcpy(date_code, hex_date_code, sizeof(hex_date_code));
    memcpy(date_code + sizeof(hex_date_code), filler_date_code, sizeof(filler_date_code));

    printf("\n");
    check_hex(date_code, sizeof(date_code) / sizeof(date_code[0]), "Date_Code ");
    check_hex(vendor_serial, sizeof(vendor_serial) / sizeof(vendor_serial[0]), "Vendor_Serial ");
    printf("\n");

    //write to the header struct the variables
    memcpy(head.vendor_serial, vendor_serial, sizeof(vendor_serial));
    memcpy(head.date_code, date_code, sizeof(date_code));

    uint8_t sum = Sum(0, 63, &head); //calc cc_base
    if (cc_base_flag == 1)
        head.cc_base = sum;

    //head.cc_base = static_cast<uint8_t>(0x30); //test against a corrupted header
    printf("CC_BASE checksum result is %x CC_BASE in EEPROM is %x\n", sum, head.cc_base);
    if (sum != head.cc_base) {
        printf("I'll resolve with a fake header for you %s\n", heart);
        Cheat_base(sum, &head, pointB.pointer, pointB.registry);
    }

    sum = Sum(64, 95, &head); //calc cc_ext
    if (cc_ext_flag == 1)
        head.cc_ext = sum;

    //head.cc_ext = static_cast<uint8_t>(0xd3); //test against a corrupted header
    printf("CC_EXT checksum result is %x CC_EXT in EEPROM is %x\n", sum, head.cc_ext);
    if (sum != head.cc_ext) {
        printf("I'll resolve with a fake header for you %s\n", heart);
        Cheat_ext(sum, &head, pointE.pointer, pointE.registry);
    }

    Generate_header(&head);
    Print_struct(&head);

    printf("\n");

    return 0;
}
