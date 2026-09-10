FAIT

Parsing arguments (ft_parsing, ft_parsing_nbr_coders, ft_parsing_scheduler, overflow)
Structures (t_coder, t_dongle, t_data, t_monitor)
Init/destroy mutex + cond (dongles + monitor)
Attribution dongles voisins (modulo, cercle)
Création + join threads
Acquisition 2 dongles sans deadlock (pair/impair, is_used mis à jour)
free(monitor) + nettoyage mémoire + README
Relâcher dongles après compile (is_used = false, unlock mutex)


À FAIRE
7. Logging avec timestamp + mutex d'affichage
9. Cooldown dongles (dongle->last_used)
10. Cycle compile → debug → refactor → recompile (boucle infinie)
11. Compteur nb_compil + arrêt sur number_of_compiles_required
12. Thread de monitoring dédié (détection burnout réelle, broadcast)
13. Scheduler FIFO/EDF + tas maison
14. Cas 1 seul coder
15. readme
16. nettoyage memoire