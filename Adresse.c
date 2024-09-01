#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

char *remplir()
{
    char *ipMask = (char *)malloc(sizeof(char) * 35);
    printf("Enter the IP Adress and the netmask : ");
    scanf("%s", ipMask);
    return ipMask;
}

int bin(int n)
{
    int binary = 0;
    int base = 1;
    while (n > 0)
    {
        binary += (n % 2) * base;
        n /= 2;
        base *= 10;
    }
    return binary;
}

int dec(int n)
{
    int decimal = 0, base = 1;
    while (n > 0)
    {
        decimal += (n % 10) * base;
        n /= 10;
        base *= 2;
    }
    return decimal;
}

void determine_class(char **ip, int *mask, char *class)
{
    int a;
    int b;
    int c;
    int d;
    int k;
    int count = 0;
    while (sscanf(*ip, "%d.%d.%d.%d/%d", &a, &b, &c, &d, mask) != 5)
    {
        *ip = remplir();
    }
    if ((a >= 0 && a <= 127) && (b >= 0 && b <= 255) && (c >= 0 && c <= 255) && (d >= 0 && d <= 255))
    {
        *class = 'A';
        printf("Adresse Classe A\n");
    }
    else if ((a >= 128 && a <= 191) && (b >= 0 && b <= 255) && (c >= 0 && c <= 255) && (d >= 0 && d <= 255))
    {
        printf("Adresse Classe B\n");
        *class = 'B';
    }
    else if ((a >= 192 && a <= 223) && (b >= 0 && b <= 255) && (c >= 0 && c <= 255) && (d >= 0 && d <= 255))
    {
        printf("Adresse Classe C\n");
        *class = 'C';
    }
}

void adress_mask(int mask, char **IP_Mask)
{
    char ipBinary[33] = {0};
    int i;
    for (i = 0; i < mask; i++)
    {
        ipBinary[i] = '1';
    }
    for (; i < 32; i++)
    {
        ipBinary[i] = '0';
    }

    char bytesOne[9] = {0};
    char bytesTwo[9] = {0};
    char bytesThree[9] = {0};
    char bytesFour[9] = {0};

    strncpy(bytesOne, ipBinary, 8);
    strncpy(bytesTwo, ipBinary + 8, 8);
    strncpy(bytesThree, ipBinary + 16, 8);
    strncpy(bytesFour, ipBinary + 24, 8);

    int byte1 = (int)strtol(bytesOne, NULL, 2);
    int byte2 = (int)strtol(bytesTwo, NULL, 2);
    int byte3 = (int)strtol(bytesThree, NULL, 2);
    int byte4 = (int)strtol(bytesFour, NULL, 2);

    snprintf(*IP_Mask, 16, "%d.%d.%d.%d", byte1, byte2, byte3, byte4);
    printf("Adresse Masque : %s\n", *IP_Mask);
}

void calculate_subnet(char *mask_adress, char *ip, char **adress_net)
{
    int bytemask1;
    int bytemask2;
    int bytemask3;
    int bytemask4;

    int byteip1;
    int byteip2;
    int byteip3;
    int byteip4;

    int add1;
    int add2;
    int add3;
    int add4;

    sscanf(mask_adress, "%d.%d.%d.%d", &bytemask1, &bytemask2, &bytemask3, &bytemask4);
    sscanf(ip, "%d.%d.%d.%d", &byteip1, &byteip2, &byteip3, &byteip4);

    add1 = byteip1 & bytemask1;
    add2 = byteip2 & bytemask2;
    add3 = byteip3 & bytemask3;
    add4 = byteip4 & bytemask4;

    sprintf(*adress_net, "%d.%d.%d.%d", add1, add2, add3, add4);
    printf("Adresse du Réseau : %s\n", *adress_net);
}

int nbr_ip(int mask)
{
    return pow(2, (32 - mask) - 2);
}

void calculate_broadcast(char *adress_network, int mask, char **add_broad, char *ip_mask)
{
    int bytes1, bytes2, bytes3, bytes4;
    int bytesMask1, bytesMask2, bytesMask3, bytesMask4;
    sscanf(adress_network, "%d.%d.%d.%d", &bytes1, &bytes2, &bytes3, &bytes4);
    sscanf(ip_mask, "%d.%d.%d.%d", &bytesMask1, &bytesMask2, &bytesMask3, &bytesMask4);

    printf("%d %d %d %d \n", bytesMask1, bytesMask2, bytesMask3, bytesMask4);

    bytesMask1 = 255 - bytesMask1;
    bytesMask2 = 255 - bytesMask2;
    bytesMask3 = 255 - bytesMask3;
    bytesMask4 = 255 - bytesMask4;

    int bytesBrad1 = bytes1 | bytesMask1;
    int bytesBrad2 = bytes2 | bytesMask2;
    int bytesBrad3 = bytes3 | bytesMask3;
    int bytesBrad4 = bytes4 | bytesMask4;

    printf("%d.%d.%d.%d\n", (bytesBrad1), (bytesBrad2), (bytesBrad3), (bytesBrad4));
    sprintf(*add_broad, "%d.%d.%d.%d", (bytesBrad1), (bytesBrad2), (bytesBrad3), (bytesBrad4));
    printf("Adresse Broadcast : %s\n", *add_broad);
}

void number_div(int *n)
{
    printf("Give the division : ");
    scanf("%d", n);
}

void cut_IP(int netMask, char *IP_Mask, char *ip, int bit, char *adress_net, char *adress_broad, char class)
{
    int new_netMask = netMask + bit;
    char *new_IpMask = (char *)malloc(sizeof(char) * 16);
    adress_mask(new_netMask, &new_IpMask);
    int bit_hôte = (32 - new_netMask);
    int nombre_hotes = pow(2, bit_hôte) - 2;
    int bytes1, bytes2, bytes3, bytes4;
    sscanf(adress_net, "%d.%d.%d.%d", &bytes1, &bytes2, &bytes3, &bytes4);
    int subnet_size = pow(2, bit_hôte);
    int num_subnets = pow(2, bit);
    printf("    Sous réseau         |           \tbroadcast \n\n");
    for (int i = 0; i < num_subnets; i++)
    {
        int temp_bytes1 = bytes1;
        int temp_bytes2 = bytes2;
        int temp_bytes3 = bytes3;
        int temp_bytes4 = bytes4 + i * subnet_size;

        if (temp_bytes4 >= 256)
        {
            temp_bytes3 += temp_bytes4 / 256;
            temp_bytes4 %= 256;
        }

        if (temp_bytes3 >= 256)
        {
            temp_bytes2 += temp_bytes3 / 256;
            temp_bytes3 %= 256;
        }

        if (temp_bytes2 >= 256)
        {
            temp_bytes1 += temp_bytes2 / 256;
            temp_bytes2 %= 256;
        }

        int first_host = temp_bytes4 + 1;
        int last_host = temp_bytes4 + nombre_hotes;

        if (last_host >= 256)
        {
            temp_bytes3 += last_host / 256;
            last_host %= 256;
        }

        if (temp_bytes3 >= 256)
        {
            temp_bytes2 += temp_bytes3 / 256;
            temp_bytes3 %= 256;
        }

        if (temp_bytes2 >= 256)
        {
            temp_bytes1 += temp_bytes2 / 256;
            temp_bytes2 %= 256;
        }

        int broadcast = last_host + 1;
        printf("-----------------------------------------------------------------------------------------------\n");
            printf("|Sous réseau %d:%35d.%d.%d.%d\n", i + 1, temp_bytes1, temp_bytes2, temp_bytes3, temp_bytes4);
        printf("|Sous Adresse Broadcast %d:%24d.%d.%d.%d\n\n", i + 1, temp_bytes1, temp_bytes2, temp_bytes3, broadcast);
        printf("-----------------------------------------------------------------------------------------------\n");
    }
}
void exec()
{
    char class;
    char *ip = remplir();
    int mask;
    determine_class(&ip, &mask, &class);

    char *adress_net = (char *)malloc(sizeof(char) * 16);
    char *adress_broad = (char *)malloc(sizeof(char) * 16);
    char *IP_mask = (char *)malloc(sizeof(char) * 16);

    adress_mask(mask, &IP_mask);
    calculate_subnet(IP_mask, ip, &adress_net);
    calculate_broadcast(adress_net, mask, &adress_broad, IP_mask);
    int n;
    number_div(&n);
    cut_IP(mask, IP_mask, ip, n, adress_net, adress_broad, class);
}

int main()
{
    exec();
    return (0);
}
