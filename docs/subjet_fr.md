# CODEXION

### 💡 <span style="color: cyan;">Resume</span>

Gérez plusieurs développeurs en compétition pour obtenir des clés USB en nombre limité en utilisant les threads POSIX, les mutex et une planification intelligente

maîtrisez la synchronisation des ressources avant que l'épuisement ne vous guette.

## 📦 Instructions

- langage C
- Norme
- attention au segfault, error, double free...
- memoire alloue sur la heap devra etre libere et leaks non toleres
- compile avec : -Wall -Wextra -Werror -pthread, utilise cc
- Makefile a la racine
- si bonus : _bonus.{c/h} files
- optionnel : creer des fichier tests



## 📦 Vu d'ensemble

Ce qu'il faut savoir pour reussir: 

- Un ou plusieurs développeurs travaillent dans un espace de coworking circulaire et inclusif. Au centre se trouve un compilateur quantique partagé.

- Les programmeurs compilent, déboguent ou refactorisent alternativement.

        - Pendant la compilation, ils ne déboguent ni ne refactorisent ; 

        - pendant le débogage, ils ne compilent ni ne refactorisent ;

        - pendant la refactorisation, ils ne compilent ni ne déboguent.

- Ils ya des cles usb dongles sur la tables. Il y a autant de cles que de programmeurs

- Compiler le code quantique necessite 2 dongles branches simultanement. un dans chaque main: un programmeur utilise son dongle gauche et de droite ppur compiler

- Quand un programmeur a fini de compiler, le programmeur remet les deux dongles sur la table et commence le debugage.

- une fois le debug fait, le programmeur commence le refactorisation.

- La simulation s'arrête lorsqu'un programmeur s'épuise par manque de compilation.

- Chaque programmeur a besoin de compiler regulierement et ne devra jamais s'epuiser

- Les programmeurs ne doivent pas communiquer avec les autres

- les programmeurs ne doivent pas savoir si les autres programmeurs sont sur le point de s'epuises

- les programmeurs doivent eviter l'epuisement !!!


## 📦 Regles globales 

- Variable globales interditent
- le programme devrai prendre les arguments suivant:

    -  **number_of_coders**: Le nombre de programmeurs et aussi le nombre de dongles

    - **time_to_burnout** (in milliseconds): Si un programmeur n'a pas commencer a compiler dans un delai de **time_to_burnout** milliseconds depuis le debut de sa derniere compilation ou le debut de la simulation. il est epuise (burn out)

    - **time_to_compile**(in milliseconds): Le temps que ca prend a un programmeur pour compiler. 
    Durant ce temps, il doit rester 2 dongles

    - **time_to_debug**(in milliseconds): le temps qu'un progammeur consacre au debugage

    - **time_to_refactor** (in milliseconds): le temps qu'un pogrammeur consacrera a la refactorisation. Apres cette phase completee, le programmeur devra immediatement tenter d'aquerir  des dongles et recommencer a compiler a nouveau.

    - **number_of_compiles_required**: si tous les programmeurs ont compile ce nombre la, la simulation s'arrete. sinon ca s'arrete lorsqu'un programmeur est epuise.

    - **dongle_cooldown** (in milliseconds): Apres sa mise en service, un dongle est indisponible jusqu’à la fin de son délai de réactivation.

    - **scheduler** (plannificateur): Politique d’arbitrage utilisée par les dongles pour déterminer leur attribution lorsque plusieurs programmeurs en font la demande. 

    La valeur doit être exactement l'une des suivantes : 

        fifo ou edf: 

        fifo : « Premier entré, premier sorti » : la clé est attribuée au développeur dont la demande est arrivée en premier. 

         edf:  « Date limite la plus proche » avec la date limite = dernière_compilation_début + temps_avant_épuisement


- Chaque programmeur a un nombre range entre 1 et **number_of_coders**

- le programmeur numero 1 est assis a cote du programmeur numero **"number_of_coders"**
Chaque autres programmeurs numero N sera assis entre le programmeur numero N-1 et le programmeur n+1


### ⚠️ Rappel : Tous les arguments sont obligatoires. Les entrées invalides telles que les nombres négatifs, les nombres non entiers ou un ordonnanceur autre que FIFO ou EDF sont rejetées.

- Toute modification d'état d'un codeur doit être formatée comme suit:

timestamp = horodatage

        ◦ timestamp_in_ms X has taken a dongle
        ◦ timestamp_in_ms X is compiling
        ◦ timestamp_in_ms X is debugging
        ◦ timestamp_in_ms X is refactoring
        ◦ timestamp_in_ms X burned out
    

***Remplacez timestamp_in_ms par timestamp actuel en millisecondes et X par le numéro du codeur.***

- Un message d'état affiché ne doit pas être confondu avec un autre message.

- Un message annonçant qu'un programmeur a fait un burn-out ne doit pas s'afficher plus de 10 ms après le burn-out lui-même.

- **LES PROGRAMMEURS DOIVENT EVITER LES BURN OUT**

- Exemple de format de journal attendu: 

```0 1 has taken a dongle
1 1 has taken a dongle
1 1 is compiling
201 1 is debugging
401 1 is refactoring
402 2 has taken a dongle
403 2 has taken a dongl
403 2 is compiling
603 2 is debugging
803 2 is refactoring
1204 3 burned out
```

### ⚠️ Exigence de précision : les journaux de fin de course doivent s’afficher à moins de 10 ms de l’heure réelle de fin de course. Une tolérance minimale est à prévoir lors des tests, car la planification matérielle et du système d’exploitation peut légèrement affecter les temps mesurés.


#### ❗ Afin de réduire l’impact du matériel sur les mesures de performance, il est préférable d’utiliser le temps d’utilisation du processeur plutôt que l’horloge temps réel lorsque cela est possible. Cependant, pour ce projet, les mesures en temps réel effectuées à l’aide de la fonction `gettimeofday()` sont acceptables et recommandées par souci de simplicité.


## 📦 Parties obligatoire

- **Program Name**: codexion
- **Files to Submit**:  Makefile at the root, *.c and *.h in the folder of your choice
- **Makefile**: NAME, all, clean, fclean, re
- **Arguments**:  number_of_coders / time_to_burnout / time_to_compile / time_to_debug /time_to_refactor / number_of_compiles_required / dongle_cooldown scheduler
- **Function externes**: thread_create /  pthread_join / pthread_mutex_init / 
pthread_mutex_lock / pthread_mutex_unlock / pthread_mutex_destroy / pthread_cond_init / pthread_cond_wait / pthread_cond_timedwait / pthread_cond_signal / pthread_cond_broadcast / pthread_cond_destroy /
gettimeofday / clock_gettime / usleep / write / malloc / free / printf / fprintf /
strcmp / strlen / atoi / memset
- **libft non autorized**
- **Description**: progammeurs avec threads and mutexes (C)


Les regles specifiques sont: 

- Chaque programmeur doit etre representer par un thread (utilise pthread_create)

- Il y a un dongle entre chaque pair de programmeur. Donc, s'il ya a plusieurs programmeurs, chaque programmeur a un dongle sur son cote gauche et un dongle sur son cote droit. S'il y a seulement un programmeur, il devra y avoir qu'un seul dongle sur la table.

- Pour empecher les programmeurs de dupliquer les dongles, il faudra proteger l'etat de chaque dongle avec un mutex (pthread_mutex_t). Une variable de condition(pthread_cond_t) peut etre utilise pour gerer les files d'attentes.

-  **Le delai de reactivation est obligatoire**: une fois qu'un programmeur a liberer un dongle, le dongle ne peut pas etre pris avant que le delais de **"dongle_cooldown"**  ne soit ecoule.

- **Un arbitrage équitable est obligatoire**: lorsque plusieurs développeurs demandent la même clé d'accès, celle-ci doit leur accorder l'accès conformément au planificateur. 

Avec le principe ***FIFO***: les requêtes sont traitées par ordre d'arrivée.

Avec le principe ***EDF***: l'accès est attribué au développeur dont la date limite d'épuisement professionnel est la plus proche (c'est-à-dire, depuis le dernier début de compilation + le temps restant avant l'épuisement professionnel).


- LLe programme doi garantir les disponibilite, aucun programmeur ne doit manquer de dongle et s'epuiser sous la plannification edf.

- Un **thread** de surveillance distinct doit détecter précisément la surchauffe et interrompre la simulation. Le journal de surchauffe doit être imprimé dans les 10 ms suivant l'heure réelle de surchauffe.




- Le logging (l'affichage de messages/logs) doit être sérialisé, pour que deux messages ne se mélangent jamais sur une seule ligne (utilise un mutex pour protéger l'affichage)

```
pthread_mutex_lock(&mutex);     // je prends la clé
printf("Bonjour\n");            // j'affiche tranquillement
pthread_mutex_unlock(&mutex);   // je rends la clé
```

- La simulation s'arrête soit lorsqu'un programmeur est épuisé, soit lorsque chaque programmeur a effectué au moins **number_of_compiles_required** de fois.


- Implémenter une file de priorité (tas) pour la planification FIFO/EDF (aucune file de priorité de bibliothèque standard ne peut être utilisée)

- Toute la mémoire doit être correctement allouée et libérée (pas de fuites de mémoire).

- **README**





# 📦 GROSSO MERDO

## 📝 Récap — Ce que j'ai compris du sujet Codexion

### Le principe de base

Plusieurs programmeurs sont assis en cercle, chacun avec un dongle à sa gauche et un dongle à sa droite
Ces dongles sont partagés avec les voisins — un dongle donné est à la fois le dongle droit d'un programmeur et le dongle gauche du suivant
Le dongle est une ressource unique et protégée par mutex : un seul programmeur peut l'utiliser à la fois, les autres doivent attendre qu'il soit relâché (+ le cooldown écoulé)

### Les 3 actions (jamais en même temps)

- **Compiler** → nécessite de posséder 2 dongles simultanément (gauche + droite)

- **Déboguer** → juste une durée à respecter, pas de dongle nécessaire

- **Refactoriser** → juste une durée à respecter, pas de dongle nécessaire — après cette phase, le programmeur retente immédiatement d'acquérir 2 dongles pour recompiler

### Le cycle complet

COMPILER (2 dongles) → DEBUGUER (temps seul) → REFACTORISER (temps seul) → retour à COMPILER


### Le burnout

Si un programmeur ne parvient pas à recommencer à compiler avant l'écoulement de time_to_burnout, il s'épuise (burnout)
Le but du programme est justement d'éviter ça pour tout le monde

### Le scheduler (répartiteur des dongles)

fifo → premier arrivé, premier servi

edf → priorité à celui dont la deadline de burnout est la plus proche

### Fin de la simulation

Soit un programmeur burnout (arrêt immédiat)
Soit tous les programmeurs ont atteint number_of_compiles_required compilations

### Logs

Chaque changement d'état affiche un message avec timestamp
Les messages ne doivent jamais se mélanger entre eux (→ mutex sur l'affichage)
Le message de burnout doit apparaître dans les 10ms suivant le burnout réel

### Les mutex

Une "clé" qu'un thread prend avant d'accéder à une ressource partagée (dongle, affichage...), et relâche une fois fini — ça empêche que deux threads touchent la même ressource en même temps