
Parsing, structures, mutex/cond ✅
Threads coders + monitor, création et join propre ✅
Logique dongles (attribution, anti-deadlock, relâchement) ✅
Logs compile/debug/refactor/burnout, cohérents ✅
Détection du burnout fonctionnelle et testée ✅
Cooldown des dongles — petit, mais à ne pas oublier ✅
Compteur nb_compil + condition d'arrêt "succès" — actuellement ton programme ne s'arrête que sur burnout, jamais sur "tout le monde a fini de compiler le nombre requis de fois" ✅
Cas 1 seul coder — souvent un edge case surveillé de près ✅

Race condition sur last_compil — rapide à corriger (un mutex), mais à ne pas zapper pour la soutenance/l'éval

Nettoyage mémoire (valgrind/helgrind) — peut prendre du temps si des fuites ou races surgissent

README

petit point : last_used est lu avant le lock dans right_dongle_used et left_dongle_used

le scheduler FIFO / EDF