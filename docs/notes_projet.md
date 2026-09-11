Ce qui a bougé depuis le dernier check
✅ Logs implémentés (dongles pris, compile) — même si format à corriger (takken→taken, retirer left/right)
✅ print_mutex/log_mutex en place, bien utilisé
✅ free_all prévu dans le header (à vérifier si codé)
✅ Relâchement des dongles + is_used = false après compile — fait
🔶 monitor_routine — un brouillon existe, mais l'architecture n'est pas encore la bonne (pas de vraie boucle sur tous les coders, pas de broadcast réel)
❌ ft_debug/ft_refactoring — pas encore faits (mais toi t'estimes 1h, ok)
Rappel de la liste complète

Fait/quasi fait : parsing, structures, init/destroy mutex+cond, attribution dongles, threads+join, anti-deadlock, logs (à peaufiner), relâchement dongles

Reste à faire :

ft_debug/ft_refactoring (1h annoncée)
Cooldown des dongles (dongle_cooldown, last_used) — pas touché
Compteur nb_compil + arrêt sur number_of_compiles_required — pas touché
Thread de monitoring réel et fonctionnel (broadcast, boucle sur tous les coders) — brouillon seulement
Scheduler FIFO/EDF + tas maison — stubs vides
Cas 1 seul coder — pas géré
Nettoyage mémoire complet + README