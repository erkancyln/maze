
#include <stdio.h>
#include <stdlib.h>   
#include <time.h>

struct YiginStruct
{
    int x_pozisyonu;
    int y_pozisyonu;
    struct YiginStruct* sonraki;
};

struct YiginStruct* yeniYiginElemaniYarat(int pos_x, int pos_y)
{
    struct YiginStruct* _yigin =
    (struct YiginStruct*) malloc(sizeof(struct YiginStruct));
    _yigin->y_pozisyonu = pos_y;
    _yigin->x_pozisyonu = pos_x;
    _yigin->sonraki = NULL;
    return _yigin;
}

int yiginBosMu(struct YiginStruct *root)
{
    return !root;
}

void yiginElemanEkle(struct YiginStruct** root, int pos_x, int pos_y)
{
    struct YiginStruct* _yigin = yeniYiginElemaniYarat(pos_x,pos_y);
    _yigin->sonraki = *root;
    *root = _yigin;
    printf("\n%d,%d pushed to stack", pos_x,pos_y);
}

int* yiginElemanCikar(struct YiginStruct** root)
{
    if (yiginBosMu(*root))
        return NULL;
    struct YiginStruct* temp = *root;
    *root = (*root)->sonraki;
    // x ve y noktlarini array halinde gonder
    int cikarilan[2] = {temp->x_pozisyonu, temp->y_pozisyonu};
    
    //printf("\n%d,%d popped from stack", temp->x_pozisyonu,temp->y_pozisyonu);
    //free(temp);
    
    return cikarilan;
}
//////////////////// LINKED LIST FUNCTIONS

struct LinkedList {
    struct LinkedList* onceki;
    struct LinkedList* sonraki;
    int x_pozisyonu;
    int y_pozisyonu;
    int deger;
};

int MATRIX_SIZE = 0;

// This function prints contents of linked list starting from the given node
void listeyiYazdir(struct LinkedList *list)
{
    struct LinkedList *temp;
    printf("\n * Random Uretilen matrix ; \n");
    while (list != NULL)
    {
        if (list->y_pozisyonu == 0){
        
            printf("\n");
        }
        
        printf("%d ", list->deger);
        temp = list;
        list = list->sonraki;
    }
    printf("\n\n");
}


int degeriGetir (struct LinkedList** liste, int x, int y) {
    
    if ((x < 0 || x >= MATRIX_SIZE) || (y < 0 || y >= MATRIX_SIZE)) {
        return -1;
    }
    
    struct LinkedList *temp = *liste;  /* used in step 5*/
    
    if (temp->x_pozisyonu == x && temp->y_pozisyonu == y){
        return temp->deger;
    }
    
    while (temp != NULL && (temp->x_pozisyonu != x || temp->y_pozisyonu != y)) {
        temp = temp->sonraki;
    }
    
    return temp->deger;
}


void listeyeEkle(struct LinkedList** liste, int deger, int x, int y)
{
    /* yer ayir */
    struct LinkedList* yeni_eleman = (struct LinkedList*) malloc(sizeof(struct LinkedList));
    
    struct LinkedList *temp = *liste;
    
    /* datayi ekle  */
    yeni_eleman->deger  = deger;
    yeni_eleman->x_pozisyonu = x;
    yeni_eleman->y_pozisyonu = y;
    
    yeni_eleman->sonraki = NULL;
    
    /* liste bossa ilk eleman olarak ata */
    if (*liste == NULL)
    {
        yeni_eleman->onceki = NULL;
        *liste = yeni_eleman;
        return;
    }
    
    /*liste doluysa sonuna kadar git */
    while (temp->sonraki != NULL)
        temp = temp->sonraki;
    
    /*yeni elemani sonraki olarak ata*/
    temp->sonraki = yeni_eleman;
    
    /*kalan listeyi onceki linke ata */
    yeni_eleman->onceki = temp;
    
    return;
}

void listeyiGuncelle(struct LinkedList** liste, int deger, int x, int y) {
    struct LinkedList *temp = *liste;
    
    while (temp != NULL && (temp->y_pozisyonu != y || temp->x_pozisyonu != x)){
        
        temp = temp->sonraki;
    }
    
    if (temp == NULL) {
        // listede yok, yeni ekle
        listeyeEkle(liste, deger, x, y);
    }
    else {
        // degeri guncelle
        temp->deger = deger;
    }
    
}
////////////////////


struct LinkedList* matrisYarat (int matrix_size) {
    
    
    srand(time(NULL));
    
    int x = 0;
    int y = 0;
    int sayac = 0;
    
    /* Start with the empty list */
    struct LinkedList* liste = NULL;
    
    while (sayac < (matrix_size * matrix_size)) { // 3x3 luk matris için 9 kez
        
        int deger = rand() % 2;
        listeyeEkle(&liste, deger, x, y);
        
        y++;
        if (y >= matrix_size) { // yeni satira geç
            y = 0;
            x++;
        }
        sayac++;
    }
    
    
    return liste;
}


/* A utility function to print solution matrix sol[N][N] */
void sonucuYazdir(struct YiginStruct* sonucYigini)
{
    printf("\n\nSonuc yazdiriliyor!\n\n");
    
    struct LinkedList* sonucListesi = NULL;
    
    // boþ matris oluþtur
    int i,j;
    for (i = 0; i < MATRIX_SIZE; i++)
    {
        for (j = 0; j < MATRIX_SIZE; j++)
        {
            int val = 0;
            listeyeEkle(&sonucListesi, val, i, j);
        }
    }
    
    // stack'den deðerleri al ve boþ matrisi güncelle
    int* koordinatlar = yiginElemanCikar(&sonucYigini);
    while (koordinatlar != NULL) {
        int pos_x = *koordinatlar;
        int pos_y = *(koordinatlar + 1);
        int val = 1;
        
        // stack'deki deðeri sonuç listesine ekle
        listeyiGuncelle(&sonucListesi, val, pos_x, pos_y);
        
        // sýradaki koordinat deðeri al
        koordinatlar = yiginElemanCikar(&sonucYigini);
    }
    
    // path'i ekrana yazdýr
    for (i = 0; i < MATRIX_SIZE; i++)
    {
        for (j = 0; j < MATRIX_SIZE; j++)
        {
            int val = degeriGetir(&sonucListesi, i, j);
            printf("%d ",val);
        }
        printf("\n");
    }

    printf("\n");
}

int yigindaVarMi(struct YiginStruct** yigin, int x,int y){
    struct YiginStruct* tempYigin = *yigin;
    int pos_x,pos_y;
    
    while (tempYigin != NULL) {
        
        pos_x = tempYigin->x_pozisyonu;
        pos_y = tempYigin->y_pozisyonu;
        
        if (pos_x == x && pos_y == y) {
            return 0;
        }
        
        
        tempYigin = tempYigin->sonraki;
    }
    return 1;
}


int degeriKontrolEt(struct LinkedList** list,struct YiginStruct** yigin ,int x, int y)
{
    // if (x,y outside maze) return false
    int deger = degeriGetir(list, x, y);
    if(x >= 0 && x < MATRIX_SIZE && y >= 0 && y < MATRIX_SIZE && deger == 1 &&
       yigindaVarMi(yigin,x,y))
        return 1;
    
    return 0;
}



int matrisdeGez(struct LinkedList** list,struct YiginStruct** sonucyigin , int x, int y, int finalPozisyon_x,int finalPozisyon_y)
{
    
    if(degeriKontrolEt(list, sonucyigin, x, y) == 1)
    {
        
        yiginElemanEkle(sonucyigin, x, y);
        
        // Final noktasý
        if (x == finalPozisyon_x && y == finalPozisyon_y) {
            return 1;
        }
        
        
        /* x + 1 */
        if (matrisdeGez(list, sonucyigin, x + 1, y, finalPozisyon_x, finalPozisyon_y) == 1)
            return 1;
        
        /* y + 1 */
        if (matrisdeGez(list, sonucyigin, x, y + 1, finalPozisyon_x, finalPozisyon_y) == 1)
            return 1;
        
        /* x - 1 */
        if (matrisdeGez(list, sonucyigin, x - 1, y, finalPozisyon_x, finalPozisyon_y) == 1)
            return 1;
        
        /* y - 1 */
        if (matrisdeGez(list, sonucyigin, x, y - 1, finalPozisyon_x, finalPozisyon_y) == 1)
            return 1;
        
        yiginElemanCikar(sonucyigin);
        return 0;
    }
    
    return 0;
}

int matrisiDegerlendir(struct LinkedList** list, struct YiginStruct** sonucyigin,int x_basla,int y_basla,int x_bitis, int y_bitis)
{
    if(matrisdeGez(list, sonucyigin, x_basla, y_basla, x_bitis, y_bitis) == 0)
    {
        // baðlantý bulunamadý
        return 0;
    }
    
    sonucuYazdir(*sonucyigin);
    return 1;
}

int yoluBul(struct LinkedList** list, struct YiginStruct** sonucyigin ,int x_basla, int y_basla, int x_bitis, int y_bitis ) {
    
    return matrisiDegerlendir(list, sonucyigin, x_basla, y_basla,x_bitis,y_bitis);
}

int main(int argc, const char * argv[]) {
    
    struct YiginStruct* sonucyigin = NULL;
    int exit = 0;
    do {
        
        printf("\nMatrix boyutunu girin : ");
        scanf("%d", &MATRIX_SIZE);
        
        
        struct LinkedList* list = matrisYarat(MATRIX_SIZE);
        listeyiYazdir(list);
        
        int x_basla, y_basla, x_bitis,y_bitis, degerlerDogruMu;
        do {
            degerlerDogruMu = 1;
            printf("Baslangic noktasi x koordinati(0'dan baslayarak) : ");
            scanf("%d", &x_basla);
            printf("Baslangic noktasi y koordinatý(0'dan baslayarak) : ");
            scanf("%d", &y_basla);
            printf("Bitis noktasi x koordinati(0'dan baslayarak) : ");
            scanf("%d", &x_bitis);
            printf("Bitis noktasi y koordinati(0'dan baslayarak) : ");
            scanf("%d", &y_bitis);
            
            // girilen koordinatlar doðru mu kontrol et
            if ((x_basla >= MATRIX_SIZE || x_basla < 0)||
                (y_basla >= MATRIX_SIZE || y_basla < 0)||
                (x_bitis >= MATRIX_SIZE || x_bitis < 0)||
                (y_bitis >= MATRIX_SIZE || y_bitis < 0)) {
                printf("\n\nGirilen koordinatlarda gecersiz deger var, tekrar deneyin!!!\n\n");
                degerlerDogruMu = 0;
            }
        } while (degerlerDogruMu == 0);// girilen koordinatlar doðru deðilse tekrar iste
        
        
        printf("\n\n * Matrix isleniyor...\n\n");
        
        int bulunanYol = yoluBul(&list,&sonucyigin,x_basla,y_basla,x_bitis,y_bitis);
        
        if (bulunanYol == 0) {
            printf("\n\nBelirtilen noktalar arasi baglanti bulunamadi!\n\n");
        }
        
        printf("\nCikis yapmak icin 1 girin, tekrar baslamak icin 0 girin! : ");
        scanf("%d", &exit);
    } while (exit != 1);
    
    return 0;
}
