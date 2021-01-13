/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <string.h>
#define MAX 5000

/* Règles de gestion:
Un vol peut etre annulé
lorsqu'*/

/* A REVOIR 
Salaire: trouver le nombre d'heure de travail* taux horaire ou salaire de base * nombre de vol par mois (comme les journalistes)
Tarif différentes places
Différents choix à l'choix_utilisateur: acheter plusieurs places, formule confort, 
*/

typedef char string[80];

typedef struct
{
    int identifiant_avion;
    string designation_avion;
    string modele_avion;
    int capacite_premiere_classe;
    int capacite_second_classe;
    int nombre_vol_effectue;
    string date_acquisition;
    float prix_acquisition;
    
} avion;

typedef struct 
{
    int identifiant_vol;
    string jour_depart;
    string ville_depart;
    string heure_depart;
    string jour_arrivee;
    string ville_arrivee;
    string heure_arrivee;
    long matricule_pilote1;
    long matricule_pilote2;
    int nbre_places;
    int statut; // type booléen. 0 si le vol n'est pas encore confirmé et 1 s'il est confirmé. Un vol est confirmé si le nombre de places est supérieur ou égal à la moitié ou au quart de la capacité de l'avion
    float tarif_place;
    int identifiant_avion;
    
} vol;

typedef struct
{
    long matricule;
    string nom;
    string date_naissance;
    float salaire;
    float nbre_heure_travail;
    string type_contrat;
    string date_embauche;
    string telephone;
    string adresse;
    string email;
    
} pilote;

void ajout_avion (int *ne, avion t[], int identifiant, string designation, string modele, int place_max_1, int place_max_2, int nombre_utilisation, string date_achat, float prix_achat)
{
    t[*ne].identifiant_avion = identifiant;
    strcpy(t[*ne].designation_avion, designation);
    strcpy(t[*ne].modele_avion, modele);
    t[*ne].capacite_premiere_classe = place_max_1;
    t[*ne].capacite_second_classe = place_max_2;
    t[*ne].nombre_vol_effectue = nombre_utilisation;
    strcpy(t[*ne].date_acquisition, date_achat);
    t[*ne].prix_acquisition = prix_achat;
    
    *ne = *ne + 1;
    
    return;
}

void ajout_vol (int *ne, vol t[], int identifiant, int identifiant_plane, string jour_dep, string ville_dep, string heure_dep, string jour_arr, string ville_arr, string heure_arr, long identifiant_pilote1, long identifiant_pilote2, int nombre_place, int stat, float tarif)
{
    t[*ne].identifiant_vol = identifiant;
    t[*ne].identifiant_avion = identifiant_plane;
    strcpy(t[*ne].jour_depart, jour_dep);
    strcpy(t[*ne].ville_depart, ville_dep);
    strcpy(t[*ne].heure_depart, heure_dep);
    strcpy(t[*ne].jour_arrivee, jour_arr);
    strcpy(t[*ne].ville_arrivee, ville_arr);
    strcpy(t[*ne].heure_arrivee, heure_arr);
    t[*ne].matricule_pilote1 = identifiant_pilote1;
    t[*ne].matricule_pilote2 = identifiant_pilote2;
    t[*ne].nbre_places = nombre_place;
    t[*ne].statut = stat;
    t[*ne].tarif_place = tarif;

    *ne = *ne + 1;
    
    return;
}

void modifie_statut_vol (int nvol, vol t1[], int nav, avion t2[]) // Permet de changer le statut d'un vol si le nombre de place minimun est atteint
{
    int i;
    int j;
    int capacite_avion;
    int nbre_place_reserve;
    
    i = 0;
    while (i < nvol)
    {
        j = 0;
        while (j < nav)
        {
            if (t1[i].identifiant_avion == t2[i].identifiant_avion)
            {
               capacite_avion = t2[i].capacite_premiere_classe + t2[i].capacite_second_classe;
               nbre_place_reserve = t1[i].nbre_places;
               if (nbre_place_reserve >= (capacite_avion / 2))
               {
                   t1[i].statut = 1;
               }
            }
            j = j + 1;
        }
        
        i = i + 1;
    }
    return;
}

int verifie_jour(string d)
{
    int jour;
    
    jour = ((int)(d[0])-48)*10 + (int)(d[1])-48;
    if (1 <= jour && jour <= 31)
    {
        return 1;
    }
    else
    {
    return 0;
    }
}

int verifie_mois(string d)
{
    int mois;
    
    mois = ((int)(d[3])-48)*10 + (int)(d[4])-48;
    if (1 <= mois && mois <= 12)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int verifie_annee(string d)
{
    int annee;
    
    annee = ((int)(d[6])-48)*1000 + ((int)(d[7])-48)* 100 + ((int)(d[8])-48) * 10 + (int)(d[9])-48;
    if (1000 <= annee && annee <= 2020)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int pile_vide (int ne)
{
    int flag;
    
    flag = 0;
    if(ne == 0)
    {
        flag = 1;
    }
    return flag;
}

int pile_pleine (int ne, int max)
{
    int flag;
    
    flag = 0;
    if(ne == max)
    {
        flag = 1;
    }
    return flag;
}

void affiche_tab_avion(int n, avion t[])
{
    int i;
    
    printf("Liste des avions de la compagnie\n");
    i = 0;
    while (i < n)
    {
        printf("Avion n° %d\n", i + 1);
        printf("          Identifiant: %d\n", t[i].identifiant_avion);
        printf("          Désignation: %s\n", t[i].designation_avion);
        printf("          Modèle: %s\n", t[i].modele_avion);
        printf("          Capacité maximale: %d\n", t[i].capacite_second_classe + t[i].capacite_premiere_classe);
        printf("          Capacité première classe: %d\n",t[i].capacite_premiere_classe);
        printf("          Capacité classe économique: %d\n", t[i].capacite_second_classe);
        printf("          Nombre de vols effectués: %d\n", t[i].nombre_vol_effectue);
        printf("          Date d'acquisition: %s\n", t[i].date_acquisition);
        printf("          Prix d'acquisition: %.2f\n", t[i].prix_acquisition);
        i = i + 1;
    }
    return;
}

void affiche_tab_vol (int n, vol t[])
{
    int i;
    
    printf("Liste des vols\n");
    i = 0;
    while (i < n)
    {
        printf("Vol n° %d\n", i + 1);
        printf("          Identifiant: %d\n", t[i].identifiant_vol);
        printf("          Vol effectué par l'avion: %d\n", t[i].identifiant_avion);
        printf("          Jour de départ: %s \n", t[i].jour_depart);
        printf("          Ville de départ: %s \n", t[i].ville_depart);
        printf("          Heure de départ: %s \n", t[i].heure_depart);
        printf("          Jour d'arrivée: %s \n", t[i].jour_arrivee);
        printf("          Ville d'arrivée: %s \n", t[i].ville_arrivee);
        printf("          Heure de d'arrivée: %s \n", t[i].heure_arrivee);
        printf("          Matricule du pilote: %ld\n", t[i].matricule_pilote1);
        printf("          Matricule du co-pilote: %ld\n", t[i].matricule_pilote2);
        printf("          Nombre de place réservées: %d\n", t[i].nbre_places);
        if (t[i].statut == 0)
        {
            printf("          Statut: %d : Vol non confirmé. Nombre réservation minimal non atteinte\n", t[i].statut);
        }
        else
        {
            printf("          Statut: %d : Vol confirmé. Nombre réservation minimal atteinte\n", t[i].statut);   
        }
        printf("          Prix de la place: %.2f\n", t[i].tarif_place);
        i = i + 1;
    }
    return;
}

int recherche_avion (int n, avion t[], int identifiant)
{
    int i;
    int flag;
    
    i = 0;
    flag = 0;
    
    while (i < n)
    {
        if (t[i].identifiant_avion == identifiant)
        {
            flag = 1;
        }
        i = i + 1;
    }
    
    return flag;
}

void supprime_avion(int *ne, avion t[], int identifiant)
{
    int i;
    int position;
    
    
    i = 0;
    while (i < *ne)
    {
        if (t[i].identifiant_avion == identifiant)
        {
            position = i;
            while (position < *ne)
            {
                if (position < *ne - 1)
                {
                    t[position] = t[position + 1];
                }
                position = position + 1;
                *ne = *ne - 1;
            }
            
        }
        i = i + 1;
    }
    
        
    return;
}

int recherche_vol_par_id (int n, vol t[], int identifiant)
{
    int i;
    int flag;
    
    i = 0;
    flag = 0;
    
    while (i < n)
    {
        if (t[i].identifiant_vol == identifiant)
        {
            flag = 1;
        }
        i = i + 1;
    }
    
    return flag;
}

int verifie_heure(string heure)
{
    int hh;
    
    hh = ((int)(heure[0])-48)*10 + (int)(heure[1])-48;
    if (0 <= hh && hh <= 24)
    {
        return 1;
    }
    else
    {
    return 0;
    }
}

int verifie_minute(string minute)
{
    int mm;
    
    mm = ((int)(minute[3])-48)*10 + (int)(minute[4])-48;
    if (0 <= mm && mm <= 60)
    {
        return 1;
    }
    else
    {
    return 0;
    }
}

void verification_format_date (string date) 
{
    while (date[2] != '/' || date[5] != '/' || strlen(date) != 10 || verifie_jour(date) !=1 || verifie_mois(date) !=1 || verifie_annee(date) != 1)
    {
        printf("Vous n'avez pas respecté le format JJ/MM/AAAA, réessayer : \n");
        fgets(date, 80, stdin);
        date[strlen(date) - 1] = '\0';
    }
    // Faut-il récupérer la nouvelle date saisie et la renvoyer en paramètre ???
    return;
}

void verification_format_heure (string heure) // HHhMM
{
    while (heure[2] != 'h' || strlen(heure) != 5 || verifie_heure(heure) != 1 || verifie_minute(heure) != 1)
    {
        printf("Vous n'avez pas respecté le format. Réessayer : \n");
        fgets(heure, 80, stdin);
        heure[strlen(heure) - 1] = '\0';
    }
    // Faut-il récupérer la nouvelle date saisie et la renvoyer en paramètre ???
    return;
}

int recherche_pilote_par_id (int n, pilote t[], long identifiant)
{
    int i;
    int flag;
    
    i = 0;
    flag = 0;
    
    while (i < n)
    {
        if (t[i].matricule == identifiant)
        {
            flag = 1;
        }
        i = i + 1;
    }
    
    return flag;
}

void tri_date_croissant(int n, vol t[])
{
    int i;
    int format_jj_mm_aaaa_i;
    int format_jj_mm_aaaa_bi;
    int bi;
    int bs;
    vol tmp; 

    i = 0;
    while (i < n)
    {
        bi = 0;
        bs = n - 1;
        while (bi != bs)
        {
            format_jj_mm_aaaa_i = ((int)(t[i].jour_depart[0])-48)*10000000 + ((int)(t[i].jour_depart[1])-48) *1000000 + ((int)(t[i].jour_depart[3])-48)*100000 + ((int)(t[i].jour_depart[4])-48) * 10000+ ((int)(t[i].jour_depart[6])-48)*1000 + ((int)(t[i].jour_depart[7])-48)* 100 + ((int)(t[i].jour_depart[8])-48) * 10 + (int)(t[i].jour_depart[9])-48;
            format_jj_mm_aaaa_i = ((int)(t[bi].jour_depart[0])-48)*10000000 + ((int)(t[bi].jour_depart[1])-48) *1000000 + ((int)(t[bi].jour_depart[3])-48)*100000 + ((int)(t[bi].jour_depart[4])-48) * 10000+ ((int)(t[bi].jour_depart[6])-48)*1000 + ((int)(t[bi].jour_depart[7])-48)* 100 + ((int)(t[bi].jour_depart[8])-48) * 10 + (int)(t[bi].jour_depart[9])-48;

            if (format_jj_mm_aaaa_i < format_jj_mm_aaaa_bi)
            {
                tmp = t[i];
                t[i] = t[bi];
                t[bi] = tmp;
            }
            bi = bi + 1;
        }
        i = i + 1;
    }
    return;
}

void tri_nbre_place_croissant(int n, vol t[])
{
    int i; 
    int bi;
    int bs;
    vol tmp; 

    i = 0;
    while (i < n)
    {
        bi = 0;
        bs = n - 1;
        while (bi != bs)
        {
            if (t[i].nbre_places < t[bi].nbre_places)
            {
                tmp = t[i];
                t[i] = t[bi];
                t[bi] = tmp;
            }
            bi = bi + 1;
        }
        i = i + 1;
    }
    return;
}

void modifie_depart_vol (int n, vol t[], int identifiant, string jour_dep, string ville_dep, string heure_dep)
{
    int i;
    int flag;
    
    i = 0;
    flag = 0;
    
    while (i < n && flag == 0)
    {
        if (t[i].identifiant_vol == identifiant)
        {
            flag = 1;
            strcpy(t[i].jour_depart, jour_dep);
            strcpy(t[i].ville_depart, ville_dep);
            strcpy(t[i].heure_depart, heure_dep);
            
        }
        i = i + 1;
    }
    return;
}

void modifie_arrivee_vol (int n, vol t[], int identifiant, string jour_arr, string ville_arr, string heure_arr)
{
    int i;
    int flag;
    
    i = 0;
    flag = 0;
    
    while (i < n && flag == 0)
    {
        if (t[i].identifiant_vol == identifiant)
        {
            flag = 1;
            strcpy(t[i].jour_arrivee, jour_arr);
            strcpy(t[i].ville_arrivee, ville_arr);
            strcpy(t[i].heure_arrivee, heure_arr);
            
        }
        i = i + 1;
    }
    return;
}

void modifie_id_pilote_vol (int n, vol t[], int identifiant, long identifiant_pilote1, long identifiant_pilote2)
{
    int i;
    int flag;
    
    i = 0;
    flag = 0;
    
    while (i < n)
    {
        if (t[i].identifiant_vol == identifiant && flag == 0)
        {
            flag = 1;
            t[i].matricule_pilote1 = identifiant_pilote1;
            t[i].matricule_pilote2 = identifiant_pilote2;
        }
        i = i + 1;
    }
    return;
}
    
void modifie_all_info_vol (int n, vol t[], int identifiant, int identifiant_plane, string jour_dep, string ville_dep, string heure_dep, string jour_arr, string ville_arr, string heure_arr, long identifiant_pilote1, long identifiant_pilote2, int nombre_place, int stat, float tarif)
{
    int i;
    int flag;
    
    i = 0;
    flag = 0;
    
    while (i < n)
    {
        if (t[i].identifiant_vol == identifiant && flag == 0)
        {
            flag = 1;
            t[i].identifiant_avion = identifiant_plane;
            strcpy(t[i].jour_depart, jour_dep);
            strcpy(t[i].ville_depart, ville_dep);
            strcpy(t[i].heure_depart, heure_dep);
            strcpy(t[i].jour_arrivee, jour_arr);
            strcpy(t[i].ville_arrivee, ville_arr);
            strcpy(t[i].heure_arrivee, heure_arr);
            t[i].matricule_pilote1 = identifiant_pilote1;
            t[i].matricule_pilote2 = identifiant_pilote2;
            t[i].nbre_places = nombre_place;
            t[i].statut = stat;
            t[i].tarif_place = tarif;
        }
        i = i + 1;
    }
    return;
}

void supprime_vol(int *ne, vol t[], int identifiant)
{
    int i;
    int position;
    
    i = 0;
    while (i < *ne)
    {
        if (t[i].identifiant_vol == identifiant)
        {
            position = i;
            while (position < *ne)
            {
                if (position < *ne - 1)
                {
                    t[position] = t[position + 1];
                }
                position = position + 1;
                *ne = *ne - 1;
            }
            
        }
        i = i + 1;
    }
    return;
}

void ajout_pilote (int *ne, pilote t[], long identifiant, string name, string anniversaire, float paie, float heure, string contrat, string embauche, string tel_number, string adresse_pilote, string mail_pilote)
{
    t[*ne].matricule = identifiant;
    strcpy(t[*ne].nom, name);
    strcpy(t[*ne].date_naissance, anniversaire);
    t[*ne].salaire = paie;
    t[*ne].nbre_heure_travail = heure;
    strcpy(t[*ne].type_contrat, contrat);
    strcpy(t[*ne].date_embauche, embauche);
    strcpy(t[*ne].telephone, tel_number);
    strcpy(t[*ne].adresse, adresse_pilote);
    strcpy(t[*ne].email, mail_pilote);
    
    *ne = *ne + 1;
    
}

void affiche_tab_pilote (int n, pilote t[])
{
    int i;
    
    i = 0;
    printf("Liste des pilotes de la compagnie\n");
    while (i < n)
    {
        printf("Pilote n° %d", i + 1);
        printf("\n");
        printf("             Matricule: %ld", t[i].matricule);
        printf("\n");
        printf("             Date de naissance: %s", t[i].date_naissance);
        printf("\n");
        printf("             Numéro de téléphone: %s", t[i].telephone);
        printf("\n");
        printf("             E-mail: %s", t[i].email);
        printf("\n");
        printf("             Adresse: %s", t[i].adresse);
        printf("\n");
        printf("             Salaire: %.2f", t[i].salaire);
        printf("\n");
        printf("             Nombre d'heures: %.2f", t[i].nbre_heure_travail);
        printf("\n");
        printf("             Date d'embauche: %s", t[i].date_embauche);
        printf("\n");
        printf("             Type de contrat: %s", t[i].type_contrat);
        printf("\n");
        i = i + 1; 
    }
    return;
}

void modifie_info_pilote (int n, pilote t[], long identifiant, string name, string anniversaire, float paie, float heure, string contrat, string embauche, string tel_number, string adresse_pilote, string mail_pilote)
{
    int i;
    int flag;
    
    i = 0;
    flag = 0;
    
    while (i < n)
    {
        if (t[i].matricule == identifiant && flag == 0)
        {
            flag = 1;
            strcpy(t[i].nom, name);
            strcpy(t[i].date_naissance, anniversaire);
            t[i].salaire = paie;
            t[i].nbre_heure_travail = heure;
            strcpy(t[i].type_contrat, contrat);
            strcpy(t[i].date_embauche, embauche);
            strcpy(t[i].telephone, tel_number);
            strcpy(t[i].adresse, adresse_pilote);
            strcpy(t[i].email, mail_pilote);
        }
        i = i + 1;
    }
    return;
}


int main()
{
    int choix_utilisateur;
    int choix_client;
    int choix_admin;
    int choix_pilote;
    int nbre_avion;
    int nbre_vol;
    int flag;
    avion tab_avion[MAX];
    pilote tab_pilote[MAX];
    vol tab_vol[MAX];
    int id_plane;
    string designation_plane;
    string model_plane;
    int capacity_plane_premiere;
    int capacity_plane_second;
    int number_fly;
    string date_buy_plane;
    float price_buy_place;
    int validation;
    int nbre_pilote;
    int id_fly;
    string departure_date; 
    string departure_city;
    string departure_hour;
    string arrival_date;
    string arrival_city; 
    string arrival_hour;
    long id_pilote;
    long id_copilote;
    int number_places;
    int statut_fly;
    float price_fly_place;
    long matricule;
    int choix_2;
    string pilote_name;
    string pilote_birthday;
    float pilote_salary;
    float pilote_hours;
    string pilote_contract;
    string pilote_date_hiring;
    string pilote_tel;
    string pilote_address;
    string pilote_mail;
    
    nbre_avion = 0;
    nbre_vol = 0;
    nbre_pilote = 0;
    do
    {
        printf("\n**************Menu principal**************\n");
        printf("Tapez \n");
        printf("1: Si vous etes un administrateur\n"); // peuvent ajouter des avions, des vols, gérer les réservations etc.
        printf("2: Si vous etes un pilote \n"); // consulter fiche de paie, consulter son planning
        printf("3: Si vous etes un client\n"); // consulter les vols, faire des réservations, gérer les réservations (modification, valider réservation, supprimer réservation)
        printf("4: Arreter le programme \n");
        
        printf("Entrez votre choix\n");
        scanf("%d", &choix_utilisateur);
        
        if(choix_utilisateur == 1)
        {
            // Affiche menu de l'administrateur
            do
            {
                printf("\n**************Menu administrateur**************\n");
                // Gestion des avions
                printf("1: Ajouter un avion \n"); // cas d'achat 
                printf("2: Consulter la liste des avions de la compagnie\n");
                printf("3: Supprimer un avion\n"); // en cas de vente ou de dégats irréparables
                
                // Gestion des vols
                printf("4: Ajouter un vol\n");
                printf("5: Consulter la liste des vols\n");
                printf("6: Trier les vols par date de départ\n"); // ??? vols 
                printf("7: Trier les vols par nombre de places réservées\n");
                printf("8: Modifier un vol\n");
                printf("9: Afficher la liste des vols réalisés ou confirmés\n"); // vols déjà réalisés. Condition sur la date 
                printf("10: Supprimer un vol\n");
                
                printf("11: Ajouter un pilote\n");
                printf("12: Consulter la liste des pilotes\n");
                printf("13: Modifier les informations d'un pilote\n");
                
                printf("14: Quitter l'espace admin\n");
                
                printf("Entrez votre choix\n");
                scanf("%d", &choix_admin);
                
                if(choix_admin == 1)
                {
                    printf("                 Ajout d'un avion\n");
                    // Avant d'ajouter un avion, on vérifie si la table des avions est pleine
                    flag = pile_pleine(nbre_avion, MAX);
                    if (flag == 1) // Si elle est pleine, enregistrement impossible
                    {
                        printf("Vous avez déjà enregistré %d avions\n", MAX);
                    }
                    else
                    {
                        printf("Entrez le numéro d'identification de l'avion\n");
                        scanf("%d", &id_plane);
                        fflush(stdin);
                        // Lancer un programme qui vérifie si l'identifiant saisi existe déjà dans la base. L'identifiant doit etre unique
                        // ???
                        while (recherche_avion (nbre_avion, tab_avion, id_plane) == 1) // Si cet identifiant existe, erreur. L'admin doit saisir un nouvel identifiant
                        {
                            printf ("Cette identifiant est déjà pris\n");
                            printf("Veuillez réessayer avec un autre identifiant\n");
                            printf("Entrez le numéro d'identification de l'avion\n");
                            scanf("%d", &id_plane);
                            fflush(stdin);
                        }
                        if (recherche_avion (nbre_avion, tab_avion, id_plane) == 0)
                        {
                            printf("Entrez la désignation de l'avion\n");
                            fgets(designation_plane, 80, stdin);
                            designation_plane[strlen(designation_plane) - 1] = '\0';
                            fflush(stdin);
                            
                            printf("Entrez le modèle de l'avion\n");
                            fgets(model_plane, 80, stdin);
                            model_plane[strlen(model_plane) - 1] = '\0';
                            fflush(stdin);
                            
                            printf("Entrez le nombre de place en première classe\n");
                            scanf("%d", &capacity_plane_premiere);
                            fflush(stdin);
                            
                            printf("Entrez le nombre de place en classe économique\n");
                            scanf("%d", &capacity_plane_second);
                            fflush(stdin);
                            
                            // Est ce qu'il faut demander cette information ou la mettre par defaut à 0 ???
                            printf("Entrez le nombre de vols effectués par cet avion\n");
                            scanf("%d", &number_fly);
                            fflush(stdin);
                            
                            printf("Entrez la date d'acquisition de l'avion au format JJ/MM/AAAA \n");
                            fgets(date_buy_plane, 80, stdin);
                            date_buy_plane[strlen(date_buy_plane) - 1] = '\0';
                            fflush(stdin);
                            // Vérification du format
                            while (date_buy_plane[2] != '/' || date_buy_plane[5] != '/' || strlen(date_buy_plane) != 10 || verifie_jour(date_buy_plane) !=1 || verifie_mois(date_buy_plane) !=1 || verifie_annee(date_buy_plane) != 1)
                            {
                                printf("Vous n'avez pas respecté le format JJ/MM/AAAA, recommencez : ");
                                fgets(date_buy_plane, 80, stdin);
                                date_buy_plane[strlen(date_buy_plane) - 1] = '\0';
                            }
                            
                            printf("Entrez le prix d'acquisition de l'avion\n");
                            scanf("%f", &price_buy_place);
                            fflush(stdin);
                        
                            // Lancer le programme d'Ajout
                            ajout_avion (&nbre_avion, tab_avion, id_plane, designation_plane, model_plane, capacity_plane_premiere, capacity_plane_second, number_fly, date_buy_plane, price_buy_place);
                            printf("Ajout réussi \n");
                        }
                    }
                }
                else
                {
                    if (choix_admin == 2)
                    {
                        flag = pile_vide(nbre_avion);
                        if (flag == 1)
                        {
                            printf("Aucun avion n'a été enregistré\n");
                        }
                        else
                        {
                            affiche_tab_avion(nbre_avion, tab_avion);
                        }
                    }
                    else
                    {
                        if(choix_admin == 3)
                        {
                            printf("                 Suppression\n");
                            printf("Entrez l'identifiant de l'avion à supprimer\n");
                            fflush(stdin);
                            scanf("%d", &id_plane);
                            fflush(stdin);
                            // Rechercher l'avion
                            // ??? est-il forcément obliger de supprimer un avion avant de quitter cette partie?
                            while (recherche_avion(nbre_avion, tab_avion, id_plane) == 0)
                            {
                                printf("Cet avion n'est pas enregistré dans notre base\n");
                                printf("Entrez l'identifiant de l'avion à supprimer\n");
                                scanf("%d", &id_plane);
                                fflush(stdin);
                            }
                            if (recherche_avion(nbre_avion, tab_avion, id_plane) == 1)
                            {
                                printf ("Etes-vous sur de vouloir supprimer cet avion ? Cette opération est irréversible \n");
                                printf("Tapez 1 si vous souhaitez continuer et 2 si vous souhaitez annuler l'opération\n");
                                scanf("%d", &validation);
                                if (validation == 1)
                                {
                                    // Lancer le programme de suppression
                                    supprime_avion(&nbre_avion, tab_avion, id_plane);
                                    printf("Suppression réussie \n");
                                }
                                else
                                {
                                    if (validation == 2)
                                    {
                                        printf ("Suppression annulée\n");
                                    }
                                    else
                                    {
                                        printf("Commande non prise en charge\n");
                                    }
                                }
                                
                            }
                        }
                        else
                        {
                            if (choix_admin == 4)
                            {
                                printf("                 Ajout d'un vol\n");
                                flag = pile_pleine(nbre_vol, MAX);
                                if (flag == 1)
                                {
                                    printf("Vous avez déjà enregistré %d vols\n", MAX);
                                }
                                else
                                {
                                    printf("Entrez l'identifiant du vol\n");
                                    scanf("%d", &id_fly);
                                    fflush(stdin);
                                    // Lancer un programme qui vérifie si l'identifiant saisi existe déjà dans la base. L'identifiant doit etre unique
                                    while (recherche_vol_par_id (nbre_vol, tab_vol, id_fly) == 1)
                                    {
                                        printf ("Cette identifiant est déjà pris\n");
                                        printf("Veuillez réessayer avec un autre identifiant\n");
                                        printf("Entrez l'identifiant du vol'\n");
                                        fflush(stdin);
                                        scanf("%d", &id_fly);
                                    }
                                    if  (recherche_vol_par_id (nbre_vol, tab_vol, id_fly) == 0)
                                    {
                                        printf("Entrez l'identifiant de l'avion qui effectuera ce vol\n");
                                        
                                        scanf("%d", &id_plane);
                                        fflush(stdin);
                                        // Lancer un programme qui vérifie si l'identifiant saisi existe déjà dans la base. L'identifiant doit etre unique
                                        if ( recherche_avion (nbre_avion, tab_avion, id_plane) == 0)
                                        {
                                            printf ("Cet avion n'existe pas dans notre base. Réessayer\n");
                                            printf("Entrez l'identifiant de l'avion qui effectuera ce vol\n");
                                            fflush(stdin);
                                            scanf("%d", &id_plane);
                                        }
                                        else
                                        {
                                            printf("Entrez le jour de départ du vol\n");
                                            fflush(stdin);
                                            fgets(departure_date, 80, stdin);
                                            departure_date[strlen(departure_date) - 1] = '\0';
                                            verification_format_date(departure_date);

                                            //Vérifier format date. Peut etre écrire un Sous-programme spécial pour ca
                                            
                                            printf("Entrez la ville de départ\n");
                                            fflush(stdin);
                                            fgets(departure_city, 80, stdin);
                                            departure_city[strlen(departure_city) - 1] = '\0';
                                            
                                            printf("Entrez l'heure de départ du vol (exemple: 09h30)\n");
                                            fflush(stdin);
                                            fgets(departure_hour, 80, stdin);
                                            departure_hour[strlen(departure_hour) - 1] = '\0';
                                            verification_format_heure(departure_hour);
                                            
                                            printf("Entrez le jour d'arrivée du vol\n");
                                            fflush(stdin);
                                            fgets(arrival_date, 80, stdin);
                                            arrival_date[strlen(arrival_date) - 1] = '\0';
                                            verification_format_date(arrival_date);
                                            //Vérifier format date. Peut etre écrire un Sous-programme spécial pour ca
                                            
                                            printf("Entrez la ville d'arrivée\n");
                                            fflush(stdin);
                                            fgets(arrival_city, 80, stdin);
                                            arrival_city[strlen(arrival_city) - 1] = '\0';
                                            
                                            printf("Entrez l'heure d'arrivée (exemple: 09h30)\n");
                                            fflush(stdin);
                                            fgets(arrival_hour, 80, stdin);
                                            arrival_hour[strlen(arrival_hour) - 1] = '\0';
                                            verification_format_heure(arrival_hour);
                                            
                                            printf("Saisissez les informations sur les pilotes\n");
                                            printf("Entrez le matricule du pilote\n");
                                            fflush(stdin);
                                            scanf("%ld", &id_pilote);
                                            
                                            while(recherche_pilote_par_id (nbre_pilote, tab_pilote, id_pilote) == 0)
                                            {
                                                printf ("Ce pilote n'existe pas. Réessayer \n");
                                                printf("Entrez le matricule du pilote\n");
                                                fflush(stdin);
                                                scanf("%ld", &id_pilote);
                                            }
                                            if (recherche_pilote_par_id (nbre_pilote, tab_pilote, id_pilote) == 1)
                                            {
                                               
                                                printf("Entrez le matricule du copilote\n");
                                                fflush(stdin);
                                                scanf("%ld", &id_copilote);
                                                while (recherche_pilote_par_id (nbre_pilote, tab_pilote, id_copilote) == 0)
                                                {
                                                    printf ("Ce pilote n'existe pas. Réessayer \n");
                                                    printf("Entrez le matricule du pilote\n");
                                                    fflush(stdin);
                                                    scanf("%ld", &id_copilote);
                                                }
                                                if (recherche_pilote_par_id (nbre_pilote, tab_pilote, id_copilote) == 1)
                                                {
                                                    //printf("Entrez le nombre de place"); Inutile de demander ca vu que le nombre de places augmente à chaque réservation
                                                    // Pareil pour le statut. Il est de 0 par défaut 
                                                    number_places = 0;
                                                    statut_fly = 0;
                                                    printf("Entrez le prix de la place\n");
                                                    fflush(stdin);
                                                    scanf("%f", &price_fly_place);
                                                    
                                                    ajout_vol (&nbre_vol, tab_vol, id_fly, id_plane, departure_date, departure_city, departure_hour, arrival_date, arrival_city, arrival_hour, id_pilote, id_copilote, number_places, statut_fly, price_fly_place);
                                                    printf("                 Ajout réussi \n");
                                                    
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            else
                            {
                                if (choix_admin == 5)
                                {
                                    flag = pile_vide(nbre_vol);
                                    if (flag == 1)
                                    {
                                        printf("Aucun vol enregistré\n");
                                        
                                    }
                                    else
                                    {
                                        affiche_tab_vol(nbre_vol, tab_vol);
                                    }
                                }
                                else
                                {
                                    if (choix_admin == 6)
                                    {
                                        flag = pile_vide(nbre_vol);
                                        if (flag == 1)
                                        {
                                            printf("Aucun vol enregistré\n");
                                            
                                        }
                                        else
                                        {
                                            tri_date_croissant(nbre_vol, tab_vol);
                                            printf("                 Vols triés par valeur croissante des dates de départ\n");
                                            affiche_tab_vol(nbre_vol, tab_vol);
                                        }
                                    }
                                    else
                                    {
                                        if(choix_admin == 7)
                                        {
                                            flag = pile_vide(nbre_vol);
                                            if (flag == 1)
                                            {
                                                printf("                 Aucun vol enregistré\n");
                                                
                                            }
                                            else
                                            {
                                                tri_nbre_place_croissant(nbre_vol, tab_vol);
                                                printf("Vols triés par valeur croissante du nombre de places réservés\n");
                                                affiche_tab_vol(nbre_vol, tab_vol);
                                            }
                                        }
                                        else
                                        {
                                            if (choix_admin == 8)
                                            {
                                                printf ("                 Modification\n");
                                                printf("Entrez l'identifiant du vol\n");
                                                fflush(stdin);
                                                scanf("%d", &id_fly);
                                                
                                                while (recherche_vol_par_id(nbre_vol, tab_vol, id_fly) == 0)
                                                {
                                                    printf("Ce vol n'existe pas dans notre base\n");
                                                    printf("Réessayer\n");
                                                    printf("Entrez l'identifiant du vol\n");
                                                    scanf("%d", &id_fly);
                                                }
                                                
                                                if (recherche_vol_par_id(nbre_vol, tab_vol, id_fly) == 1)
                                                {
                                                    printf ("Que souhaitez-vous modifier? \n");
                                                    printf("1: Les informations sur le départ\n");
                                                    printf("2: Les informations sur l'arrivée'\n");
                                                    printf("3: Les informations sur les pilotes\n");
                                                    printf("4: Les autres informations \n");
                                                    printf("5: Toutes les informations\n");
                                                    
                                                    printf("Quel est votre choix? \n");
                                                    fflush(stdin);
                                                    scanf("%d", &choix_2);
                                                    
                                                    if (choix_2 == 1)
                                                    {
                                                        printf("Entrez le jour de départ du vol\n");
                                                        fflush(stdin);
                                                        fgets(departure_date, 80, stdin);
                                                        departure_date[strlen(departure_date) - 1] = '\0';
                                                        verification_format_date(departure_date);
                                                        
                                                        printf("Entrez la ville de départ\n");
                                                        fflush(stdin);
                                                        fgets(departure_city, 80, stdin);
                                                        departure_city[strlen(departure_city) - 1] = '\0';
                                                            
                                                        printf("Entrez l'heure de départ du vol\n");
                                                        fflush(stdin);
                                                        fgets(departure_hour, 80, stdin);
                                                        departure_hour[strlen(departure_hour) - 1] = '\0';
                                                        verification_format_heure(departure_hour);
                                                        
                                                        printf ("Enregistrer les modifications ? Cette opération est irréversible \n");
                                                        printf("Tapez 1 si vous souhaitez continuer et 2 si vous souhaitez annuler l'opération\n");
                                                        fflush(stdin);
                                                        scanf("%d", &validation);
                                                        if (validation == 1)
                                                        {
                                                            // Lancer le programme de modification
                                                            modifie_depart_vol (nbre_vol, tab_vol, id_fly, departure_date, departure_city, departure_hour);
                                                            printf("Modification réussie \n");
                                                        }
                                                        else
                                                        {
                                                            if (validation == 2)
                                                            {
                                                                printf ("Opération annulée\n");
                                                            }
                                                            else
                                                            {
                                                                printf("Commande non prise en charge\n");
                                                            }
                                                        }
                                                    }
                                                    else
                                                    {
                                                        if (choix_2 == 2)
                                                        {
                                                            printf("Entrez le jour d'arrivée du vol\n");
                                                            fflush(stdin);
                                                            fgets(arrival_date, 80, stdin);
                                                            arrival_date[strlen(arrival_date) - 1] = '\0';
                                                            verification_format_date(arrival_date);
                                                            //Vérifier format date. Peut etre écrire un Sous-programme spécial pour ca
                                                            
                                                            printf("Entrez la ville d'arrivée\n");
                                                            fflush(stdin);
                                                            fgets(arrival_city, 80, stdin);
                                                            arrival_city[strlen(arrival_city) - 1] = '\0';
                                                            
                                                            printf("Entrez l'heure d'arrivée\n");
                                                            fflush(stdin);
                                                            fgets(arrival_hour, 80, stdin);
                                                            arrival_hour[strlen(arrival_hour) - 1] = '\0';
                                                            verification_format_heure(arrival_hour);
                                                            
                                                            printf ("Enregistrer les modifications ? Cette opération est irréversible \n");
                                                            printf("Tapez 1 si vous souhaitez continuer et 2 si vous souhaitez annuler l'opération\n");
                                                            fflush(stdin);
                                                            scanf("%d", &validation);
                                                            if (validation == 1)
                                                            {
                                                                // Lancer le programme de modification
                                                                modifie_arrivee_vol (nbre_vol, tab_vol, id_fly, arrival_date, arrival_city, arrival_hour);
                                                                printf("Modification réussie \n");
                                                            }
                                                            else
                                                            {
                                                                if (validation == 2)
                                                                {
                                                                    printf ("Opération annulée\n");
                                                                }
                                                                else
                                                                {
                                                                    printf("Commande non prise en charge\n");
                                                                }
                                                            }
                                                            
                                                        }
                                                        else
                                                        {
                                                            if (choix_2 == 3)
                                                            {
                                                                printf("Saisissez les informations sur les pilotes\n");
                                                                printf("Entrez le matricule du pilote\n");
                                                                fflush(stdin);
                                                                scanf("%ld", &id_pilote);
                                                                
                                                                while(recherche_pilote_par_id (nbre_pilote, tab_pilote, id_pilote) == 0)
                                                                {
                                                                    printf ("Ce pilote n'existe pas. Réessayer \n");
                                                                    printf("Entrez le matricule du pilote\n");
                                                                    fflush(stdin);
                                                                    scanf("%ld", &id_pilote);
                                                                }
                                                                if (recherche_pilote_par_id (nbre_pilote, tab_pilote, id_pilote) == 1)
                                                                {
                                                                    
                                                                    printf("Entrez le matricule du copilote\n");
                                                                    fflush(stdin);
                                                                    scanf("%ld", &id_copilote);

                                                                    while (recherche_pilote_par_id (nbre_pilote, tab_pilote, id_copilote) == 0)
                                                                    {
                                                                        printf ("Ce pilote n'existe pas. Réessayer \n");
                                                                        printf("Entrez le matricule du copilote\n");
                                                                        fflush(stdin);
                                                                        scanf("%ld", &id_copilote);
                                                                    }
                                                                    if (recherche_pilote_par_id (nbre_pilote, tab_pilote, id_copilote) == 1)
                                                                    {
                                                                        printf ("Enregistrer les modifications ? Cette opération est irréversible \n");
                                                                        printf("Tapez 1 si vous souhaitez continuer et 2 si vous souhaitez annuler l'opération\n");
                                                                        fflush(stdin);
                                                                        scanf("%d", &validation);
                                                                        if (validation == 1)
                                                                        {
                                                                            // Lancer le programme de modification
                                                                            modifie_id_pilote_vol (nbre_vol, tab_vol, id_fly, id_pilote, id_copilote);
                                                                            printf("Modification réussie \n");
                                                                        }
                                                                        else
                                                                        {
                                                                            if (validation == 2)
                                                                            {
                                                                                printf ("Opération annulée\n");
                                                                            }
                                                                            else
                                                                            {
                                                                                printf("Commande non prise en charge\n");
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                                
                                                            }
                                                            else
                                                            {
                                                                if (choix_2 == 4)
                                                                {
                                                                    // Id avion, nombre de places, statut
                                                                    
                                                                }
                                                                else
                                                                {
                                                                    if (choix_2 == 5)
                                                                    {
                                                                        printf("Entrez l'identifiant du vol\n");
                                                                        scanf("%d", &id_fly);
                                                                        fflush(stdin);
                                                                        // Lancer un programme qui vérifie si l'identifiant saisi existe déjà dans la base. L'identifiant doit etre unique
                                                                        while (recherche_vol_par_id (nbre_vol, tab_vol, id_fly) == 1)
                                                                        {
                                                                            printf ("Cette identifiant est déjà pris\n");
                                                                            printf("Veuillez réessayer avec un autre identifiant\n");
                                                                            printf("Entrez l'identifiant du vol'\n");
                                                                            fflush(stdin);
                                                                            scanf("%d", &id_fly);
                                                                        }
                                                                        if  (recherche_vol_par_id (nbre_vol, tab_vol, id_fly) == 0)
                                                                        {
                                                                            printf("Entrez l'identifiant de l'avion qui effectuera ce vol\n");
                                                                            
                                                                            scanf("%d", &id_plane);
                                                                            fflush(stdin);
                                                                            // Lancer un programme qui vérifie si l'identifiant saisi existe déjà dans la base. L'identifiant doit etre unique
                                                                            if ( recherche_avion (nbre_avion, tab_avion, id_plane) == 0)
                                                                            {
                                                                                printf ("Cet avion n'existe pas dans notre base. Réessayer\n");
                                                                                printf("Entrez l'identifiant de l'avion qui effectuera ce vol\n");
                                                                                fflush(stdin);
                                                                                scanf("%d", &id_plane);
                                                                            }
                                                                            else
                                                                            {
                                                                                printf("Entrez le jour de départ du vol\n");
                                                                                fflush(stdin);
                                                                                fgets(departure_date, 80, stdin);
                                                                                departure_date[strlen(departure_date) - 1] = '\0';
                                                                                verification_format_date(departure_date);
                                    
                                                                                //Vérifier format date. Peut etre écrire un Sous-programme spécial pour ca
                                                                                
                                                                                printf("Entrez la ville de départ\n");
                                                                                fflush(stdin);
                                                                                fgets(departure_city, 80, stdin);
                                                                                departure_city[strlen(departure_city) - 1] = '\0';
                                                                                
                                                                                printf("Entrez l'heure de départ du vol (exemple: 09h30)\n");
                                                                                fflush(stdin);
                                                                                fgets(departure_hour, 80, stdin);
                                                                                departure_hour[strlen(departure_hour) - 1] = '\0';
                                                                                verification_format_heure(departure_hour);
                                                                                
                                                                                printf("Entrez le jour d'arrivée du vol\n");
                                                                                fflush(stdin);
                                                                                fgets(arrival_date, 80, stdin);
                                                                                arrival_date[strlen(arrival_date) - 1] = '\0';
                                                                                verification_format_date(arrival_date);
                                                                                //Vérifier format date. Peut etre écrire un Sous-programme spécial pour ca
                                                                                
                                                                                printf("Entrez la ville d'arrivée\n");
                                                                                fflush(stdin);
                                                                                fgets(arrival_city, 80, stdin);
                                                                                arrival_city[strlen(arrival_city) - 1] = '\0';
                                                                                
                                                                                printf("Entrez l'heure d'arrivée (exemple: 09h30)\n");
                                                                                fflush(stdin);
                                                                                fgets(arrival_hour, 80, stdin);
                                                                                arrival_hour[strlen(arrival_hour) - 1] = '\0';
                                                                                verification_format_heure(arrival_hour);
                                                                                
                                                                                printf("Saisissez les informations sur les pilotes\n");
                                                                                printf("Entrez le matricule du pilote\n");
                                                                                fflush(stdin);
                                                                                scanf("%ld", &id_pilote);
                                                                                
                                                                                while(recherche_pilote_par_id (nbre_pilote, tab_pilote, id_pilote) == 0)
                                                                                {
                                                                                    printf ("Ce pilote n'existe pas. Réessayer \n");
                                                                                    printf("Entrez le matricule du pilote\n");
                                                                                    fflush(stdin);
                                                                                    scanf("%ld", &id_pilote);
                                                                                }
                                                                                if (recherche_pilote_par_id (nbre_pilote, tab_pilote, id_pilote) == 1)
                                                                                {
                                                                                   
                                                                                    printf("Entrez le matricule du copilote\n");
                                                                                    fflush(stdin);
                                                                                    scanf("%ld", &id_copilote);
                                                                                    while (recherche_pilote_par_id (nbre_pilote, tab_pilote, id_copilote) == 0)
                                                                                    {
                                                                                        printf ("Ce pilote n'existe pas. Réessayer \n");
                                                                                        printf("Entrez le matricule du pilote\n");
                                                                                        fflush(stdin);
                                                                                        scanf("%ld", &id_copilote);
                                                                                    }
                                                                                    if (recherche_pilote_par_id (nbre_pilote, tab_pilote, id_copilote) == 1)
                                                                                    {
                                                                                        //printf("Entrez le nombre de place"); Inutile de demander ca vu que le nombre de places augmente à chaque réservation
                                                                                        // Pareil pour le statut. Il est de 0 par défaut 
                                                                                        number_places = 0;
                                                                                        statut_fly = 0;
                                                                                        printf("Entrez le prix de la place\n");
                                                                                        fflush(stdin);
                                                                                        scanf("%f", &price_fly_place);
                                                                                        
                                                                                        modifie_all_info_vol (nbre_vol, tab_vol, id_fly, id_plane, departure_date, departure_city, departure_hour, arrival_date, arrival_city, arrival_hour, id_pilote, id_copilote, number_places, statut_fly, price_fly_place);
                                                                                        printf("                 Modification réussie \n");
                                                                                        
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                    else
                                                                    {
                                                                        printf("Commande non prise en charge \n");
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                if (choix_admin == 9)
                                                {
                                                    // a faire
                                                }
                                                else
                                                {
                                                    if (choix_admin == 10)
                                                    {
                                                        printf("                 Suppression\n");
                                                        printf("Entrez l'identifiant du vol que vous souhaitez supprimer\n");
                                                        scanf("%d", &id_fly);
                                                        fflush(stdin);
                                                        while (recherche_vol_par_id(nbre_vol, tab_vol, id_fly) == 0)
                                                        {
                                                            printf("Cet avion n'est pas enregistré dans notre base\n");
                                                            printf("Entrez l'identifiant de l'avion à supprimer\n");
                                                            scanf("%d", &id_plane);
                                                            fflush(stdin);
                                                        }
                                                        if (recherche_vol_par_id(nbre_vol, tab_vol, id_fly) == 1)
                                                        {
                                                            printf ("Etes-vous sur de vouloir supprimer cet avion ? Cette opération est irréversible \n");
                                                            printf("Tapez 1 si vous souhaitez continuer et 2 si vous souhaitez annuler l'opération\n");
                                                            scanf("%d", &validation);
                                                            if (validation == 1)
                                                            {
                                                                // Lancer le programme de suppression
                                                                supprime_vol(&nbre_vol, tab_vol, id_fly);
                                                                printf("Suppression réussie \n");
                                                            }
                                                            else
                                                            {
                                                                if (validation == 2)
                                                                {
                                                                    printf ("Suppression annulée\n");
                                                                }
                                                                else
                                                                {
                                                                    printf("Commande non prise en charge\n");
                                                                }
                                                            }
                                                            
                                                        }
                                                    }
                                                    else
                                                    {
                                                        if (choix_admin == 11)
                                                        {
                                                            printf("Ajout pilote\n");
                                                            printf("Entrez le matricule du pilote\n");
                                                            scanf("%ld", &matricule);
                                                            fflush(stdin);
                                                            while (recherche_pilote_par_id(nbre_pilote, tab_pilote, matricule) == 1)
                                                            {
                                                                printf ("Ce pilote existe déjà. Réésayer avec un autre matricule\n");
                                                                printf("Entrez le matricule du pilote\n");
                                                                scanf("%ld", &matricule);
                                                                fflush(stdin);
                                                            }
                                                            if (recherche_pilote_par_id(nbre_pilote, tab_pilote, matricule) == 0)
                                                            {
                                                                printf("Entrez son nom\n");
                                                                fgets(pilote_name, 80, stdin);
                                                                pilote_name[strlen(pilote_name) - 1] = '\0';
                                                                fflush(stdin);
                                                                printf("Entrez sa date de naissance\n");
                                                                fgets(pilote_birthday, 80, stdin);
                                                                pilote_birthday[strlen(pilote_birthday) - 1] = '\0';
                                                                fflush(stdin);
                                                                verification_format_date(pilote_birthday);
                                                                printf("Entrez son salaire mensuel\n");
                                                                scanf("%f", &pilote_salary);
                                                                fflush(stdin);
                                                                printf("Entrez son nombre d'heure de travail par mois\n");
                                                                scanf("%f", &pilote_hours);
                                                                fflush(stdin);
                                                                printf("Entrez son type de contrat\n");
                                                                fgets(pilote_contract, 80, stdin);
                                                                pilote_contract[strlen(pilote_contract) - 1] = '\0';
                                                                fflush(stdin);
                                                                printf("Entrez sa date d'embauche\n");
                                                                fgets(pilote_date_hiring, 80, stdin);
                                                                pilote_date_hiring[strlen(pilote_date_hiring) - 1] = '\0';
                                                                verification_format_date(pilote_date_hiring);
                                                                fflush(stdin);
                                                                printf("Entrez son numéro de téléphone\n");
                                                                fgets(pilote_tel, 80, stdin);
                                                                pilote_tel[strlen(pilote_tel) - 1] = '\0';
                                                                fflush(stdin);
                                                                printf("Entrez son adresse\n");
                                                                fgets(pilote_address, 80, stdin);
                                                                pilote_address[strlen(pilote_address) - 1] = '\0';
                                                                fflush(stdin);
                                                                printf("Entrez son adresse email\n");
                                                                fgets(pilote_mail, 80, stdin);
                                                                pilote_mail[strlen(pilote_mail) - 1] = '\0';
                                                                fflush(stdin);
                                                                
                                                                ajout_pilote (&nbre_pilote, tab_pilote, matricule, pilote_name, pilote_birthday, pilote_salary, pilote_hours, pilote_contract, pilote_date_hiring, pilote_tel, pilote_address, pilote_mail);
                                                                printf("Ajout réussi\n");
                                                            }
                                                        }
                                                        else
                                                        {
                                                            if (choix_admin == 12)
                                                            {
                                                                flag = pile_vide(nbre_pilote);
                                                                if (flag == 1)
                                                                {
                                                                    printf("Aucun vol enregistré\n");
                                                                    
                                                                }
                                                                else
                                                                {
                                                                    affiche_tab_pilote(nbre_pilote, tab_pilote);
                                                                }
                                                            }
                                                            else
                                                            {
                                                                if (choix_admin == 13)
                                                                {
                                                                    printf("Modification \n");
                                                                    printf("Entrez le matricule du pilote dont vous souhaitez modifier les informations\n");
                                                                    scanf("%ld", &matricule);
                                                                    while (recherche_pilote_par_id (nbre_pilote, tab_pilote, matricule) == 0)
                                                                    {
                                                                        printf("matricule non retrouvé. Réessayer\n");
                                                                        printf("Entrez le matricule du pilote dont vous souhaitez modifier les informations\n");
                                                                        scanf("%ld", &matricule);
                                                                    }
                                                                    if (recherche_pilote_par_id (nbre_pilote, tab_pilote, matricule) == 1)
                                                                    {
                                                                        printf("Entrez son nom\n");
                                                                        fgets(pilote_name, 80, stdin);
                                                                        pilote_name[strlen(pilote_name) - 1] = '\0';
                                                                        fflush(stdin);
                                                                        printf("Entrez sa date de naissance\n");
                                                                        fgets(pilote_birthday, 80, stdin);
                                                                        pilote_birthday[strlen(pilote_birthday) - 1] = '\0';
                                                                        fflush(stdin);
                                                                        verification_format_date(pilote_birthday);
                                                                        printf("Entrez son salaire mensuel\n");
                                                                        scanf("%f", &pilote_salary);
                                                                        fflush(stdin);
                                                                        printf("Entrez son nombre d'heure de travail par mois\n");
                                                                        scanf("%f", &pilote_hours);
                                                                        fflush(stdin);
                                                                        printf("Entrez son type de contrat\n");
                                                                        fgets(pilote_contract, 80, stdin);
                                                                        pilote_contract[strlen(pilote_contract) - 1] = '\0';
                                                                        fflush(stdin);
                                                                        printf("Entrez sa date d'embauche\n");
                                                                        fgets(pilote_date_hiring, 80, stdin);
                                                                        pilote_date_hiring[strlen(pilote_date_hiring) - 1] = '\0';
                                                                        verification_format_date(pilote_date_hiring);
                                                                        fflush(stdin);
                                                                        printf("Entrez son numéro de téléphone\n");
                                                                        fgets(pilote_tel, 80, stdin);
                                                                        pilote_tel[strlen(pilote_tel) - 1] = '\0';
                                                                        fflush(stdin);
                                                                        printf("Entrez son adresse\n");
                                                                        fgets(pilote_address, 80, stdin);
                                                                        pilote_address[strlen(pilote_address) - 1] = '\0';
                                                                        fflush(stdin);
                                                                        printf("Entrez son adresse email\n");
                                                                        fgets(pilote_mail, 80, stdin);
                                                                        pilote_mail[strlen(pilote_mail) - 1] = '\0';
                                                                        fflush(stdin);
                                                                        
                                                                        modifie_info_pilote (nbre_pilote, tab_pilote, matricule, pilote_name, pilote_birthday, pilote_salary, pilote_hours, pilote_contract, pilote_date_hiring, pilote_tel, pilote_address, pilote_mail);
                                                                        printf("Modification réussie\n");
                                                                    }
                                                                }
                                                                else
                                                                {
                                                                    if (choix_admin == 14)
                                                                    {
                                                                        
                                                                    }
                                                                    else
                                                                    {
                                                                        printf("Commande non prise en charge\n");
                                                                    }
                                                                }
                                                                
                                                            }
                                                            
                                                        }
                                                    }
                                                }
                                            }
                                         
                                        }
                                    }
          
                                }    
                                
                            }
                        }
                    }
                }
               
            }while (choix_admin != 15);
            
        }
        else
        {
            if(choix_utilisateur == 2)
            {
                printf("Entrez votre matricule\n");
                scanf("%ld", &matricule);
                        
                while (recherche_pilote_par_id(nbre_pilote, tab_pilote, matricule) == 0)
                {
                    printf ("Pilote non enregistré.");
                    printf ("Réessayer\n");
                    printf("Entrez votre matricule\n");
                    scanf("%ld", &matricule);
                }
                // Affiche menu du pilote si le matricule existe
                do
                    {
                        printf("\n**************Menu pilote**************\n");
                        printf("1: Consulter vos informations\n");
                        printf("2: Modifier vos informations\n");
                        printf("3: Afficher votre paie du mois\n");
                        printf("4: Consulter les vols auxquels vous etes affecté\n"); // Que faut-il afficher? Vols passés, ou futurs
                        printf("5: Arreter le programme \n");
                        
                        
                        printf("Quel est votre choix?\n");
                        scanf("%d", &choix_pilote);
                        
                    } while(choix_pilote != 5);
            }
            else
            {
                if (choix_utilisateur == 3)
                {
                    // Menu du client
                    do
                    {
                        printf("\n**************Menu client**************\n");
                        printf("1: Rechercher un vol\n");
                        printf("2: Consulter les vols\n");
                        printf("3: Réserver un vol\n");
                        printf("4: Afficher vos réservations\n");
                        printf("5: Modifier une réservation\n");
                        printf("6: Supprimer une réservation \n");
                        printf("7: Arreter le programme \n");
                        
                        
                        printf("Quel est votre choix?\n");
                        scanf("%d", &choix_client);
                        
                    } while(choix_client != 7);
                }
                else
                {
                    if(choix_utilisateur == 4)
                    {
                        
                    }
                    else
                    {
                        printf("Commande non prise en charge. Réésayer\n");
                    }
                    
                }
            }
        }
        
    } while (choix_utilisateur != 4);
    
    printf("\n**************A bientot**************\n");
    
    return 0;
}





