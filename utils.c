#include "codexion.h"

void *routine_function(void *arg)
{
    t_coder *coder;

    coder = (t_coder *)arg;

    return (NULL);
}


/*
[NAISSANCE] 
     ↓
┌─────────────────────────────────────┐
│  Boucle tant que pas fini :          │
│                                       │
│   1. Acquérir dongle gauche + droit  │ ← ici mutex_lock (attente possible)
│   2. COMPILER (time_to_compile ms)   │ ← garde les 2 dongles pendant ce temps
│   3. Libérer les 2 dongles           │ ← mutex_unlock + démarrer cooldown
│   4. nb_compil++, last_compil = now  │
│   5. DEBUG (time_to_debug ms)        │ ← pas de dongle
│   6. REFACTOR (time_to_refactor ms)  │ ← pas de dongle
│   7. → retour en haut, immédiatement │
│                                       │
└─────────────────────────────────────┘
*/